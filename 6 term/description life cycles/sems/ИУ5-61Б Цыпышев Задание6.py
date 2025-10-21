# -*- coding: utf-8 -*-
import threading
import random
import time

# Фиксируем стартовое время для удобного вывода времени событий относительно начала работы программы
start_time = time.time()

class Philosopher(threading.Thread):
    """
    Класс философа, моделирующий его поведение как отдельного потока.
    Каждый философ пытается поесть, используя два вилки (locks).
    """
    running = True  # Глобальный флаг, управляющий работой всех философов

    def __init__(self, name, fork_left, fork_right):
        """
        Инициализация философа:
        :param name: Имя философа (строка)
        :param fork_left: Объект Lock для левой вилки
        :param fork_right: Объект Lock для правой вилки
        """
        super().__init__()
        self.name = name
        self.fork_left = fork_left
        self.fork_right = fork_right
        self.eating_time = 0  # Суммарное время, проведённое за едой этим философом

    def run(self):
        """
        Основной цикл работы философа:
        Философ думает (ждет случайное время), потом пытается поесть,
        пока глобальный флаг running установлен в True.
        """
        while self.running:
            # Философ "думает" (спит от 1 до 2 секунд)
            time.sleep(random.uniform(1, 2))
            self._log("голодный и пытается поесть.")
            self.dine()

    def dine(self):
        """
        Логика приема пищи:
        Философ пытается захватить сначала одну вилку,
        затем другую. Если вторая вилка занята, отпускает первую и меняет порядок захвата вилок.
        Это предотвращает взаимную блокировку (deadlock).
        """
        fork1, fork2 = self.fork_left, self.fork_right

        while self.running:
            fork1.acquire()  # Блокируем первую вилку (ожидание блокировки)
            locked = fork2.acquire(blocking=False)  # Пробуем взять вторую вилку без ожидания
            if locked:
                # Если вторая вилка свободна — начинаем есть
                break
            # Иначе отпускаем первую вилку и меняем порядок вилок, пытаясь избежать deadlock
            fork1.release()
            self._log("не смог взять вторую вилку, меняет порядок захвата вилок.")
            fork1, fork2 = fork2, fork1
        else:
            # Если running стал False, прерываем цикл
            return

        # Философ начал есть
        eat_start = time.time()
        self._log("начал есть.")
        time.sleep(random.uniform(7, 8))  # "Ест" от 7 до 8 секунд
        eat_duration = time.time() - eat_start

        self.eating_time += eat_duration
        self._log(f"закончил есть, провел за едой {eat_duration:.2f} сек., теперь думает.")

        # Освобождаем вилки
        fork2.release()
        fork1.release()

    def _log(self, message):
        """
        Удобный метод для вывода времени и сообщения философа.
        """
        current_time = time.time() - start_time
        print(f"[{current_time:.2f}] {self.name} {message}")


def DiningPhilosophers(num_philosophers):
    """
    Основная функция, запускающая симуляцию обедающих философов.
    :param num_philosophers: количество философов (от 3 до 11)
    """
    if not (3 <= num_philosophers <= 11):
        print("Ошибка: число философов должно быть от 3 до 11!")
        return

    # Создаем вилки как объекты Lock — всего вилок столько же, сколько философов
    forks = [threading.Lock() for _ in range(num_philosophers)]

    # Имена философов для удобства
    philosopher_names = (
        'Кант', 'Маркс', 'Платон', 'Руссо', 'Сократ',
        'Пифагор', 'Гегель', 'Вольтер', 'Декарт',
        'ЛаоЦзы', 'Рассел'
    )

    # Создаем объекты философов, передавая им имена и соответствующие вилки
    philosophers = [
        Philosopher(
            f"{i+1}:{philosopher_names[i]}",
            forks[i],
            forks[(i + 1) % num_philosophers]
        )
        for i in range(num_philosophers)
    ]

    # Зафиксируем случайность для воспроизводимости эксперимента
    random.seed(1537)
    Philosopher.running = True

    # Запускаем всех философов (потоки)
    for p in philosophers:
        p.start()

    # Пусть философы "обедают" заданное время
    simulation_time = 30  # секунд
    print(f"\n=== Симуляция с {num_philosophers} философами запущена на {simulation_time} секунд ===")
    time.sleep(simulation_time)

    # Останавливаем симуляцию
    Philosopher.running = False

    # Ожидаем завершения всех потоков
    for p in philosophers:
        p.join()

    # Выводим итоговую статистику по каждому философу
    print("\n=== Итоги по времени еды ===")
    total_eating = 0
    for p in philosophers:
        print(f"{p.name} ел {p.eating_time:.2f} секунд")
        total_eating += p.eating_time

    print(f"\nОбщее время еды всех философов: {total_eating:.2f} секунд")
    print(f"Среднее время еды на философа: {total_eating / num_philosophers:.2f} секунд")
    print(f"[{time.time() - start_time:.2f}] == Симуляция завершена ==\n")


if __name__ == "__main__":
    # Запускаем тесты для разного количества философов
    for count in [3, 5, 10]:
        DiningPhilosophers(count)
        time.sleep(2)  # Небольшая пауза между тестами для удобства чтения вывода
