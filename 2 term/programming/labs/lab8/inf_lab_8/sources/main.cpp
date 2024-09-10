/// Copyright 2023 ttsypyshev <ttsypyshev01@gmail.com>

#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>


/// task №1
// Пользователь вводит 3 строки - фамилия, имя и отчество учащегося. Образовать новую последовательность,
// оставить только фамилию и инициалы через пробел и точку.

std::string formatName(std::string surname, std::string name, std::string patronymic) {
    std::string initials = name.substr(0, 1) + "." + patronymic.substr(0, 1) + ".";
    return surname + " " + initials;
}

void task1() {
    std::string surname, name, patronymic;
    std::cout << "Enter surname: ";
    std::cin >> surname;
    std::cout << "Enter name: ";
    std::cin >> name;
    std::cout << "Enter patronymic: ";
    std::cin >> patronymic;

    std::string formattedName = formatName(surname, name, patronymic);
    std::cout << "Formatted name: " << formattedName << std::endl;
}


/// task №2
// Пользователь вводит 2 слова в 2-х разных переменных одинаковой длины.
// Образовать новую последовательность, в которой должны чередоваться буквы первого и второго слова.

std::string interleaveWords(const std::string &firstWord, const std::string &secondWord) {
    int n = firstWord.length();
    std::string result(n * 2, ' ');

    for (int i = 0; i < n; i++) {
        result[i * 2] = firstWord[i];
        result[i * 2 + 1] = secondWord[i];
    }

    return result;
}

void task2() {
    std::string firstWord, secondWord;

    std::cout << "Enter two words of equal length: ";
    std::cin >> firstWord >> secondWord;

    if (firstWord.length() != secondWord.length()) {
        std::cout << "Error: Words are not of equal length." << std::endl;
        return;
    }

    std::string interleaved = interleaveWords(firstWord, secondWord);

    std::cout << "The interleaved word is: " << interleaved << std::endl;
}


/// task №3
// Дан текстовый файл. Запишите в другой файл содержимое исходного файла, утроив восклицательный знак.

void replaceExclamationMarks(const std::string &inputFilename, const std::string &outputFilename) {
    std::ifstream inputFile(inputFilename);

    if (!inputFile.is_open()) {
        std::cerr << "Error: could not open input file " << inputFilename << std::endl;
        return;
    }

    std::ofstream outputFile(outputFilename);

    if (!outputFile.is_open()) {
        std::cerr << "Error: could not open output file " << outputFilename << std::endl;
        return;
    }

    std::string line;

    while (std::getline(inputFile, line)) {
        size_t pos = 0;

        while ((pos = line.find('!', pos)) != std::string::npos) {
            line.replace(pos, 1, "!!!");
            pos += 3;
        }

        outputFile << line << std::endl;
    }

    inputFile.close();
    outputFile.close();
}

void task3() {
    std::string inputFileName = "../files/input_task3.txt";
    std::string outputFileName = "../files/output_task3.txt";

    replaceExclamationMarks(inputFileName, outputFileName);

    std::cout << "Done!" << std::endl;
}

/// task №4
// Создайте вектор vector<float> и занесите в него 25 вещественных чисел в цикле for.
// Выведите содержимое вектора. Удалить из вектора элемент с индексом 1 и снова распечатать вектор.
// Переделать программу: печатать вектор с помощью функции.

void printVector(std::vector<float> input) {
    for (auto i: input) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void task4() {
    std::vector<float> v;

    for (float i = 0.0; i < 25.0; i++) {
        v.push_back(i * 2.1);
    }

    std::cout << "Original vector: ";
    printVector(v);

    v.erase(v.begin() + 1);

    std::cout << "Vector after removing element at index 1: ";
    printVector(v);
}

/// task №5
// Ниже представлен пример класса Point. Напишите программу для хранения объектов типа Point в векторе.
// (Подсказка: не забудьте для класса Point определить операторы <, << и ==)
// class Point {
// public:
//     double x, у;
//     Point() { x = у = 0; }
//     Point(double a, double b) { x = а; у = b; }
// };
// Создать массив точек с помощью контейнера vector в main() и сразу занести в него информацию о 6 точках:
// (1.2, 6.3), (4.0, 0.7), (7.2, 0.8), (5.3, 3.0), (4.9, 6.6), (9.3, 0.2).
// Вывести массив на экран таким образом, чтобы координаты каждой точки выводились в отдельной строке.
// Выведите на экран координаты точки, которая наиболее удалена от центра координат.
// Сдвиньте все точки влево по оси абцисс на расстояние, которое введет пользователь и снова выведите массив на экран.
// Напишите функцию вывода массива на экран.

class Point {
public:
    double x, y;

    Point() { x = y = 0; }

    Point(double a, double b) {
        x = a;
        y = b;
    }

    bool operator<(const Point &other) const {
        return x < other.x || (x == other.x && y < other.y);
    }

    friend std::ostream &operator<<(std::ostream &os, const Point &p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }

    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }
};

double distanceFromOrigin(const Point &p) {
    return sqrt(p.x * p.x + p.y * p.y);
}

void task5() {
    std::vector<Point> points = {Point(1.2, 6.3),
                                 Point(4.0, 0.7),
                                 Point(7.2, 0.8),
                                 Point(5.3, 3.0),
                                 Point(4.9, 6.6),
                                 Point(9.3, 0.2)};

    std::cout << "Point array:" << std::endl;
    for (const auto &point: points) {
        std::cout << point << std::endl;
    }
    std::cout << std::endl;

    Point farthest = points[0];
    for (const auto &point: points) {
        if (distanceFromOrigin(point) > distanceFromOrigin(farthest)) {
            farthest = point;
        }
    }
    std::cout << "Farthest point from the center of coordinates: " << farthest << std::endl;
    std::cout << std::endl;

    double shift;
    std::cout << "Enter the distance to shift along the x-axis: ";
    std::cin >> shift;
    for (auto &point: points) {
        point.x -= shift;
    }

    std::cout << "Array of points after shift:" << std::endl;
    for (const auto &point: points) {
        std::cout << point << std::endl;
    }
}

/// task №6
// Описать функцию, которая добавляет после каждого элемента заданного контейнера-списка list <int>
// еще один такой же элемент, но с обратным знаком, а затем исключает из списка все отрицательные элементы
// и распечатывает результат.  Переделать программу: печатать список до изменения и после с помощью функции.

void addOpposite(std::list<int> &input) {
    for (auto it = input.begin(); it != input.end(); it) {
        int opposite = -(*it);
        input.insert(++it, opposite);
    }
}

std::list<int> removeNegativeAndPrint(const std::list<int> &oppositeList) {
    std::list<int> positiveList = oppositeList;
    positiveList.remove_if([](int n) { return n < 0; });
    return positiveList;
}

void printList(std::list<int> input) {
    for (auto i: input) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void task6() {
    std::list<int> originalList{-4, 1, 3, 6};
    std::list<int> resultList;

    std::cout << "List before change: ";
    printList(originalList);

    addOpposite(originalList);
    printList(originalList);
    resultList = removeNegativeAndPrint(originalList);

    std::cout << "List after change: ";
    printList(resultList);
}

/// task №7
// Создать класс с именем Planet для хранения следующей информации:
// название (string), количество спутников.
// Создать массив планет с помощью контейнера list в main().
// Занести в вектор информацию о 9 планетах. Данные о планетах:
// "Меркурий", 0
// "Венера", 0
// "Земля", 1
// "Марс", 2
// "Юпитер", 69
// "Сатурн", 62
// "Уран", 27
// "Нептун", 14
// "Плутон", 10
// Вывести массив планет на экран, используя функцию.
// В цикле определите элемент, у которого максимальное количество спутников.

class Planet {
public:
    std::string name;
    int numSatellites;

    Planet(std::string _name, int _numSatellites) : name(_name), numSatellites(_numSatellites) {}

    Planet(const Planet &other) : name(other.name), numSatellites(other.numSatellites) {}
};

void printPlanets(std::list<Planet> planets) {
    for (auto planet: planets) {
        std::cout << "Planet " << planet.name << ", number of satellites: " << planet.numSatellites << std::endl;
    }
}

void task7() {
    std::list<Planet> planets = {
            Planet("Меркурий", 0),
            Planet("Венера", 0),
            Planet("Земля", 1),
            Planet("Марс", 2),
            Planet("Юпитер", 69),
            Planet("Сатурн", 62),
            Planet("Уран", 27),
            Planet("Нептун", 14),
            Planet("Плутон", 100)
    };

    printPlanets(planets);

    Planet maxPlanet("", -1);
    for (auto planet: planets) {
        if (planet.numSatellites > maxPlanet.numSatellites) {
            maxPlanet = planet;
        }
    }

    std::cout << "The planet " << maxPlanet.name << " has the maximum number of satellites: " << maxPlanet.numSatellites
              << std::endl;
}

/// task №8
// Создайте отображение  map<char,int> и занесите в него пары A-1, B-2, C-3, D-4, E-5.
// Выведите содержимое отображения на экран. Удалить пару с ключом C и снова распечатать отображение.

void task8() {
    std::map<char, int> myMap{{'A', 1},
                              {'B', 2},
                              {'C', 3},
                              {'D', 4},
                              {'E', 5}};

    for (auto &[key, value]: myMap) {
        std::cout << key << ": " << value << std::endl;
    }

    myMap.erase('C');

    std::cout << "\nAfter removing C:\n";
    for (auto &[key, value]: myMap) {
        std::cout << key << ": " << value << std::endl;
    }
}

/// task №9
// Даны два массива:
//string states[] = { "Wyoming", "Colorado", "Nevada", "Montana", "Arizona", "Idaho"};
// int pops[] = { 470, 2890, 800, 787, 2718, 944 };
//На основе этих массивов создайте отображение, в котором ключ – это название американского штата,
// а значение – количество жителей этого штата  в тысячах из массива pops.
// Напишите программу: пользователь вводит название штата, а в консоль выводится количество жителей этого штата.
// Выведите всё содержимое отображения в консоль с помощью функции.

void task9() {
    std::string states[] = {"Wyoming", "Colorado", "Nevada", "Montana", "Arizona", "Idaho"};
    int pops[] = {470, 2890, 800, 787, 2718, 944};

    std::map<std::string, int> statePops;
    for (int i = 0; i < 6; ++i) {
        statePops[states[i]] = pops[i];
    }

    std::cout << "State populations in thousands:\n";
    for (auto &[key, value]: statePops) {
        std::cout << key << ": " << value << "\n";
    }

    std::string inputState;
    std::cout << "\nEnter a state name to get its population: ";
    std::getline(std::cin, inputState);

    if (statePops.find(inputState) != statePops.end()) {
        std::cout << inputState << " population: " << statePops[inputState] << " thousand\n";
    } else {
        std::cout << "State not found.\n";
    }
}

void help() {
    std::cout << "Please select a task from the menu below:" << std::endl;
    std::cout << "1. Task 1." << std::endl;
    std::cout << "2. Task 2." << std::endl;
    std::cout << "3. Task 3." << std::endl;
    std::cout << "4. Task 4." << std::endl;
    std::cout << "5. Task 5." << std::endl;
    std::cout << "6. Task 6." << std::endl;
    std::cout << "7. Task 7." << std::endl;
    std::cout << "8. Task 8." << std::endl;
    std::cout << "9. Task 9." << std::endl;
    std::cout << "0. Exit Program" << std::endl;
}

int main() {
    std::cout << "Welcome to the program!" << std::endl;
    int choice = -1;
    while (choice != 0) {
        help();

        std::cin >> choice;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 0:
                std::cout << "Exiting program..." << std::endl;
                break;
            case 1:
                std::cout << "You have selected Task 1." << std::endl;
                task1();
                break;
            case 2:
                std::cout << "You have selected Task 2." << std::endl;
                task2();
                break;
            case 3:
                std::cout << "You have selected Task 3." << std::endl;
                task3();
                break;
            case 4:
                std::cout << "You have selected Task 4." << std::endl;
                task4();
                break;
            case 5:
                std::cout << "You have selected Task 5." << std::endl;
                task5();
                break;
            case 6:
                std::cout << "You have selected Task 6." << std::endl;
                task6();
                break;
            case 7:
                std::cout << "You have selected Task 7." << std::endl;
                task7();
                break;
            case 8:
                std::cout << "You have selected Task 8." << std::endl;
                task8();
                break;
            case 9:
                std::cout << "You have selected Task 9." << std::endl;
                task9();
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
        std::cout << std::endl;
    }

    std::cout << "Thank you for using this program!" << std::endl;
    return 0;
}
