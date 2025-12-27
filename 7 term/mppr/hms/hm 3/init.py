import os
import ssl
import torch
import torch.onnx
import onnx

# 1. Исправление проблем с загрузкой (SSL)
def bypass_ssl_verification():
    """Исправляет ошибку сертификатов при скачивании весов на macOS."""
    try:
        _create_unverified_https_context = ssl._create_unverified_context
    except AttributeError:
        pass
    else:
        ssl._create_default_https_context = _create_unverified_https_context

def export_model():
    # Константы
    MODEL_NAME = "cifar100_resnet20"
    OUTPUT_FILE = f"{MODEL_NAME}.onnx"
    
    # 2. Определение устройства (добавлена поддержка Apple Silicon/MPS)
    if torch.backends.mps.is_available():
        device = torch.device("mps")
    elif torch.cuda.is_available():
        device = torch.device("cuda")
    else:
        device = torch.device("cpu")
    
    print(f"Используемое устройство: {device}")

    # 3. Загрузка модели
    print(f"Загрузка модели {MODEL_NAME}...")
    try:
        model = torch.hub.load("chenyaofo/pytorch-cifar-models",
            MODEL_NAME,
            pretrained=True,
            verbose=False)
        model.to(device)
        model.eval()
    except Exception as e:
        print(f"Ошибка при загрузке модели: {e}")
        return

    # 4. Подготовка входных данных
    # (1, 3, 32, 32) для CIFAR
    dummy_input = torch.randn(1, 3, 32, 32, device=device)

    # 5. Экспорт в ONNX
    print(f"Экспорт в {OUTPUT_FILE} (opset 15)...")
    try:
        torch.onnx.export(
            model,
            dummy_input,
            OUTPUT_FILE,
            export_params=True,      # Сохранять веса внутри файла
            opset_version=18,
            do_constant_folding=True, # Оптимизация констант
            input_names=['input'],
            output_names=['output'],
            # Настройка динамических осей для гибкости (Batch size)
            dynamic_axes={
                'input': {0: 'batch_size'},
                'output': {0: 'batch_size'}
            }
        )
        print("Экспорт завершен.")
    except Exception as e:
        print(f"Ошибка при экспорте: {e}")
        return

    # 6. Проверка созданного файла
    if os.path.exists(OUTPUT_FILE):
        print("Верификация ONNX модели...")
        onnx_model = onnx.load(OUTPUT_FILE)
        onnx.checker.check_model(onnx_model)
        print(f"Успех! Модель {OUTPUT_FILE} проверена и готова к работе.")

if __name__ == "__main__":
    bypass_ssl_verification()
    export_model()