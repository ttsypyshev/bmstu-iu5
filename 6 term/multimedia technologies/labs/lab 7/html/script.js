// 1) Создаём сцену, камеру и рендерер
const scene = new THREE.Scene();

// Настраиваем камеру: (угол обзора, соотношение сторон, ближняя/дальняя плоскости)
const camera = new THREE.PerspectiveCamera(
  75,
  window.innerWidth / window.innerHeight,
  0.1,
  1000
);
camera.position.z = 3; // Отодвигаем камеру чуть дальше

// Создаём WebGLRenderer и указываем наш <canvas id="canvas">
const renderer = new THREE.WebGLRenderer({
  canvas: document.getElementById('canvas'),
  antialias: true // сглаживание
});
renderer.setSize(window.innerWidth, window.innerHeight);

// 2) Добавим немного света
// Точечный свет (PointLight)
const pointLight = new THREE.PointLight(0xffffff, 1); // белый свет, мощность 1
pointLight.position.set(5, 5, 5);
scene.add(pointLight);

// Можно добавить ещё AmbientLight, чтобы не было слишком тёмно:
const ambientLight = new THREE.AmbientLight(0xffffff, 0.5);
scene.add(ambientLight);

// 3) Загрузим модель .glb
// Создаём экземпляр загрузчика GLTF
const loader = new THREE.GLTFLoader();

// Пусть файл называется "model.glb" и лежит рядом с index.html
loader.load(
  'model.glb',
  function (gltf) {
    // Когда модель загрузится, добавим в сцену
    scene.add(gltf.scene);

    // Можно, например, чуть отмасштабировать модель, если она слишком большая/маленькая
    // gltf.scene.scale.set(0.5, 0.5, 0.5);

  },
  function (xhr) {
    // Функция прогресса (опционально)
    console.log((xhr.loaded / xhr.total * 100) + '% загружено');
  },
  function (error) {
    // Обработка ошибок
    console.error('Ошибка при загрузке модели:', error);
  }
);

// 4) Подключаем OrbitControls
const controls = new THREE.OrbitControls(camera, renderer.domElement);
// Можно подстроить чувствительность масштабирования, если хочется
// controls.zoomSpeed = 1.0;

// 5) Отслеживаем изменение размеров окна
window.addEventListener('resize', function () {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(window.innerWidth, window.innerHeight);
});

// 6) Функция анимации
function animate() {
  requestAnimationFrame(animate);

  // Здесь можно анимировать что-нибудь, напр. вращать сцену:
  // scene.rotation.y += 0.01;

  // Обновляем контроллеры (OrbitControls)
  controls.update();

  // Рендерим сцену
  renderer.render(scene, camera);
}
animate();
