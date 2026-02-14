package main

import (
	"bytes"
	"encoding/base64"
	"fmt"
	"html/template"
	"image"
	"image/jpeg"
	_ "image/png"
	"log"
	"math"
	"net/http"
	"os"
	"path/filepath"
	"runtime"
	"strings"

	"github.com/disintegration/imaging"
	"github.com/rwcarlsen/goexif/exif"
	onnxruntime "github.com/yalue/onnxruntime_go"
)

var imageClassList = map[int]string{
	0: "apple", 1: "aquarium_fish", 2: "baby", 3: "bear", 4: "beaver", 5: "bed", 6: "bee", 7: "beetle", 8: "bicycle", 9: "bottle", 10: "bowl", 11: "boy", 12: "bridge", 13: "bus",
	14: "butterfly", 15: "camel", 16: "can", 17: "castle", 18: "caterpillar", 19: "cattle", 20: "chair", 21: "chimpanzee", 22: "clock", 23: "cloud", 24: "cockroach", 25: "couch", 26: "crab", 27: "crocodile", 28: "cup", 29: "dinosaur", 30: "dolphin", 31: "elephant", 32: "flatfish", 33: "forest", 34: "fox", 35: "girl", 36: "hamster", 37: "house", 38: "kangaroo", 39: "keyboard", 40: "lamp", 41: "lawn_mower", 42: "leopard", 43: "lion",
	44: "lizard", 45: "lobster", 46: "man", 47: "maple_tree", 48: "motorcycle", 49: "mountain", 50: "mouse", 51: "mushroom", 52: "oak_tree", 53: "orange", 54: "orchid", 55: "otter", 56: "palm_tree", 57: "pear", 58: "pickup_truck", 59: "pine_tree", 60: "plain", 61: "plate", 62: "poppy", 63: "porcupine", 64: "possum", 65: "rabbit", 66: "raccoon", 67: "ray", 68: "road", 69: "rocket", 70: "rose", 71: "sea", 72: "seal", 73: "shark",
	74: "shrew", 75: "skunk", 76: "skyscraper", 77: "snail", 78: "snake", 79: "spider", 80: "squirrel", 81: "streetcar", 82: "sunflower", 83: "sweet_pepper", 84: "table", 85: "tank", 86: "telephone", 87: "television", 88: "tiger", 89: "tractor", 90: "train", 91: "trout", 92: "tulip", 93: "turtle", 94: "wardrobe", 95: "whale", 96: "willow_tree", 97: "wolf", 98: "woman", 99: "worm",
}

var myVariantClasses = map[int]bool{
	14: true, 44: true, 74: true,
}

var session *onnxruntime.DynamicSession[float32, float32]

func main() {
	// 1. Определяем имя библиотеки в зависимости от ОС
	var libName string
	switch runtime.GOOS {
	case "windows":
		libName = "onnxruntime.dll"
	case "darwin":
		libName = "libonnxruntime.dylib"
	default: // linux и прочие
		libName = "libonnxruntime.so"
	}

	// Получаем абсолютный путь к текущей директории для надежности
	execDir, _ := os.Getwd()
	libPath := filepath.Join(execDir, libName)
	modelPath := filepath.Join(execDir, "cifar100_resnet20.onnx")

	// Проверка наличия файлов
	if _, err := os.Stat(libPath); os.IsNotExist(err) {
		log.Printf("ВНИМАНИЕ: %s не найден в %s. Будет предпринята попытка системного поиска.", libName, execDir)
	}

	if _, err := os.Stat(modelPath); os.IsNotExist(err) {
		log.Fatalf("Критическая ошибка: Модель %s не найдена!", modelPath)
	}

	// 2. Инициализация ONNX Runtime
	onnxruntime.SetSharedLibraryPath(libPath)
	err := onnxruntime.InitializeEnvironment()
	if err != nil {
		log.Fatalf("Ошибка инициализации ONNX: %v", err)
	}
	defer onnxruntime.DestroyEnvironment()

	session, err = onnxruntime.NewDynamicSession[float32, float32](
		modelPath,
		[]string{"input"},
		[]string{"output"},
	)
	if err != nil {
		log.Fatalf("Ошибка загрузки модели: %v", err)
	}
	defer session.Destroy()

	// 3. Настройка HTTP сервера
	// Используем filepath.Join для кроссплатформенных путей к папкам
	staticDir := filepath.Join(execDir, "static")
	http.Handle("/static/", http.StripPrefix("/static/", http.FileServer(http.Dir(staticDir))))

	http.HandleFunc("/", scoreImagePage)
	http.HandleFunc("/predictImage", predictImage)

	log.Println("Сервер запущен на http://localhost:8080")
	if err := http.ListenAndServe(":8080", nil); err != nil {
		log.Fatal(err)
	}
}

func scoreImagePage(w http.ResponseWriter, r *http.Request) {
	tmplPath := filepath.Join("templates", "scorepage.html")
	tmpl, err := template.ParseFiles(tmplPath)
	if err != nil {
		http.Error(w, "Шаблон не найден: "+err.Error(), 500)
		return
	}
	tmpl.Execute(w, nil)
}

func predictImage(w http.ResponseWriter, r *http.Request) {
	if r.Method != "POST" {
		http.Redirect(w, r, "/", http.StatusSeeOther)
		return
	}

	file, _, err := r.FormFile("filePath")
	if err != nil {
		http.Error(w, "Ошибка чтения файла", http.StatusBadRequest)
		return
	}
	defer file.Close()

	img, _, err := image.Decode(file)
	if err != nil {
		http.Error(w, "Неверный формат изображения", http.StatusBadRequest)
		return
	}

	// Исправление ориентации
	file.Seek(0, 0)
	if x, err := exif.Decode(file); err == nil {
		if orientationTag, err := x.Get(exif.Orientation); err == nil {
			orientVal, _ := orientationTag.Int(0)
			img = fixOrientation(img, orientVal)
		}
	}

	inputData := preprocessImage(img)
	inputShape := onnxruntime.NewShape(1, 3, 32, 32)
	inputTensor, err := onnxruntime.NewTensor(inputShape, inputData)
	if err != nil {
		http.Error(w, "Ошибка тензора", 500)
		return
	}
	defer inputTensor.Destroy()

	outputShape := onnxruntime.NewShape(1, 100)
	outputTensor, err := onnxruntime.NewEmptyTensor[float32](outputShape)
	if err != nil {
		http.Error(w, "Ошибка выходного тензора", 500)
		return
	}
	defer outputTensor.Destroy()

	if err = session.Run([]*onnxruntime.Tensor[float32]{inputTensor}, []*onnxruntime.Tensor[float32]{outputTensor}); err != nil {
		http.Error(w, "Ошибка при запуске модели", 500)
		return
	}

	probabilities := softmax(outputTensor.GetData())
	predictedIndex := argmax(probabilities)

	data := map[string]interface{}{
		"scorePrediction": fmt.Sprintf("%s (%.1f%%)", strings.Title(imageClassList[predictedIndex]), probabilities[predictedIndex]*100),
		"img_uri":         template.URL(createDataURI(img)),
		"isSuccess":       myVariantClasses[predictedIndex],
	}

	tmpl, _ := template.ParseFiles(filepath.Join("templates", "scorepage.html"))
	tmpl.Execute(w, data)
}

func fixOrientation(img image.Image, orientation int) image.Image {
	switch orientation {
	case 3:
		return imaging.Rotate180(img)
	case 6:
		return imaging.Rotate270(img)
	case 8:
		return imaging.Rotate90(img)
	}
	return img
}

func argmax(data []float32) int {
	maxIdx, maxVal := 0, float32(-math.MaxFloat32)
	for i, v := range data {
		if v > maxVal {
			maxVal, maxIdx = v, i
		}
	}
	return maxIdx
}

func softmax(logits []float32) []float32 {
	probs := make([]float32, len(logits))
	var sum, maxLogit float64 = 0, -math.MaxFloat32
	for _, v := range logits {
		if float64(v) > maxLogit {
			maxLogit = float64(v)
		}
	}
	for i, v := range logits {
		res := math.Exp(float64(v) - maxLogit)
		probs[i] = float32(res)
		sum += res
	}
	for i := range probs {
		probs[i] /= float32(sum)
	}
	return probs
}

func preprocessImage(img image.Image) []float32 {
	resized := imaging.Resize(img, 32, 32, imaging.Lanczos)
	w, h := 32, 32
	mean := []float32{0.485, 0.456, 0.406}
	std := []float32{0.229, 0.224, 0.225}
	tensor := make([]float32, 3*h*w)
	for y := 0; y < h; y++ {
		for x := 0; x < w; x++ {
			r, g, b, _ := resized.At(x, y).RGBA()
			tensor[y*w+x] = (float32(r)/65535.0 - mean[0]) / std[0]
			tensor[w*h+y*w+x] = (float32(g)/65535.0 - mean[1]) / std[1]
			tensor[2*w*h+y*w+x] = (float32(b)/65535.0 - mean[2]) / std[2]
		}
	}
	return tensor
}

func createDataURI(img image.Image) string {
	buf := new(bytes.Buffer)
	jpeg.Encode(buf, img, &jpeg.Options{Quality: 85})
	return "data:image/jpeg;base64," + base64.StdEncoding.EncodeToString(buf.Bytes())
}
