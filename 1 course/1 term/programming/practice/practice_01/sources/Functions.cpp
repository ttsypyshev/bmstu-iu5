/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include <iostream>
#include <iomanip>
#include <fstream>
#include "../include/Header.h"

using namespace std;

#define size_dictionary 100
#define size_name 20
#define size_brand 20


struct train {
    int id; // инвентарный номер поезда
    char name[size_name]; // название модели поезда (из документации)
    char brand[size_brand]; // название производителя поезда (из документации)
    int date_release = 2022; // дата выпуска поезда (из документации) (по умолчанию 2022)
    int date_registration = 2022; // дата введения поезда в эксплуатацию (по умолчанию 2022)
    int wear = 100; // состояние поезда (считается от 1% до 100%) (по умолчанию 100)
};
struct train dictionary[size_dictionary]; // список поездов
int last_position = 0; // номер первого пустого поля


/// other functions
int FindItem(int id) { // поиск id в dictionary
    for (int i = 0; i < last_position; ++i) {
        if (dictionary[i].id == id) return i;
    }
    return -1; // если не нашли, то ф-ия возвращает -1
}

/// main functions
void AddItem() { // добавление новых train в dictionary
    // сначала вводим в виде строки, потом переводим в int
    // необходимо, что бы избавиться от ошибки закцикливания при вводе некоректного значения пользователем
    char str_id[8];
    cout << "Введите инвентарный номер поезда:\n";
    cin >> str_id;
    int id = atoi(str_id); // при некоректных значения выдаёт 0

    if (id != 0 and FindItem(id) == -1) { // если значения коректны и элемент отсутствует в dictionary
        // добавляем id (уже известно)
        dictionary[last_position].id = id;
        char name[size_name] = {0}, brand[size_brand] = {0}, tmp[4] = {0};

        // спрашиваем и добавляем name
        cout << "Введите название модели поезда:\n";
        cin >> name;
        for (int i = 0; i < size_name; ++i) dictionary[last_position].name[i] = name[i];

        // спрашиваем и добавляем brand
        cout << "Введите название производителя поезда:\n";
        cin >> brand;
        for (int i = 0; i < size_brand; ++i) dictionary[last_position].brand[i] = brand[i];

        // спрашиваем и добавляем date_release
        cout << "Введите дату выпуска поезда (по умолчанию 2022):\n";
        cin >> tmp;
        int date_release = atoi(tmp);
        if (date_release > 1600) dictionary[last_position].date_release = date_release;

        // спрашиваем и добавляем date_registration
        cout << "Введите дату введения поезда в эксплуатацию (по умолчанию 2022):\n";
        cin >> tmp;
        int date_registration = atoi(tmp);
        if (date_registration > 1600) dictionary[last_position].date_registration = date_registration;

        // спрашиваем и добавляем wear
        cout << "Введите значение состояния поезда (по умолчанию 100):\n";
        cin >> tmp;
        int wear = atoi(tmp);
        if (wear >= 1 and wear <= 100) dictionary[last_position].wear = wear;
        //если 1<=wear<=100 (т.к. проценты, то значение <= 100)

        cout << "Данные успешно добавлены!\n";
        last_position++;
    } else if (id != 0) {
        cout << "Данный инвентарный номер уже присутствует в списке. Добавление отменено!!!\n";
    } else cout << "Неправильный формат ввода. Добавление отменено!!!\n";
}

void RemoveItem() { // удаление старых train из dictionary
    char str_id[8]; // по анологии с void AddItem()
    cout << "Введите инвентарный номер поезда:\n";
    cin >> str_id;
    int id = atoi(str_id);
    int index = FindItem(id);
    if (id != 0 and index != -1) {
        last_position--;
        // мы заменяем удаленный элемент последним, чтобы не тратить ресурсы на сдвиг
        dictionary[index].id = dictionary[last_position].id;
        for (int i = 0; i < size_name; ++i) dictionary[index].name[i] = dictionary[last_position].name[i];
        for (int i = 0; i < size_brand; ++i) dictionary[index].brand[i] = dictionary[last_position].brand[i];
        dictionary[index].date_release = dictionary[last_position].date_release;
        dictionary[index].date_registration = dictionary[last_position].date_registration;
        dictionary[index].wear = dictionary[last_position].wear;
        cout << "Данные успешно удалены!\n";
    } else if (id != 0) {
        cout << "Данный инвентарный номер не найден в списке. Удаление отменено!!!\n";
    } else cout << "Неправильный формат ввода. Удаление отменено!!!\n";
}

void EditItem() { // изменение старых train в dictionary
    char old_str_id[8]; // по анологии с void AddItem()
    cout << "Введите старый инвентарный номер поезда:\n";
    cin >> old_str_id;
    int old_id = atoi(old_str_id);
    int index = FindItem(old_id);
    if (old_id != 0 and index != -1) {
        char new_str_id[8] = {0}, name[size_name] = {0}, brand[size_brand] = {0}, tmp[4] = {0};
        int new_id = 0;

        // нам необходим коректный id, т.к. на нём завязана функция поиска
        while (new_id == 0) {
            cout << "Введите новый инвентарный номер поезда:\n";
            cin >> new_str_id;
            new_id = atoi(new_str_id);
        }
        dictionary[index].id = new_id;

        // спрашиваем новые значения -> заменяем старые значения
        cout << "Введите новое название модели поезда:\n";
        cin >> name;
        for (int i = 0; i < size_name; ++i) dictionary[index].name[i] = name[i];

        cout << "Введите новое название производителя поезда:\n";
        cin >> brand;
        for (int i = 0; i < size_brand; ++i) dictionary[index].brand[i] = brand[i];

        cout << "Введите новую дату выпуска поезда (по умолчанию 2022):\n";
        cin >> tmp;
        int date_release = atoi(tmp);
        if (date_release > 1600) dictionary[index].date_release = date_release;

        cout << "Введите новую дату введения поезда в эксплуатацию (по умолчанию 2022):\n";
        cin >> tmp;
        int date_registration = atoi(tmp);
        if (date_registration > 1600) dictionary[index].date_registration = date_registration;

        cout << "Введите новое значение состояния поездаv (по умолчанию 100):\n";
        cin >> tmp;
        int wear = atoi(tmp);
        if (wear >= 1 and wear <= 100) dictionary[index].wear = wear;

        cout << "Данные успешно изменены!\n";
    } else if (old_id != 0) {
        cout << "Данный инвентарный номер не найден в списке. Изменение отменено!!!\n";
    } else cout << "Неправильный формат ввода. Изменение отменено!!!\n";
}

void ViewingDictionary() { // вывод всех train из dictionary в консоль
    cout << "Список поездов: \n";
    cout << setw(50 + size_name + size_brand) << setfill('-') << "\n" << setfill(' ');
    cout << "| " << setw(3) << "N" << " | "
         << setw(8) << "ID" << " | "
         << setw(size_name) << "NAME" << " | "
         << setw(size_brand) << "BRAND" << " | "
         << setw(6) << "DATE 1" << " | "
         << setw(6) << "DATE 2" << " | "
         << setw(4) << "WEAR" << " |\n";
    cout << setw(50 + size_name + size_brand) << setfill('-') << "\n" << setfill(' ');

    for (int i = 0; i < last_position; ++i) {
        cout << "| " << setw(3) << i + 1 << " | "
             << setw(8) << dictionary[i].id << " | "
             << setw(size_name) << dictionary[i].name << " | "
             << setw(size_brand) << dictionary[i].brand << " | "
             << setw(6) << dictionary[i].date_release << " | "
             << setw(6) << dictionary[i].date_registration << " | "
             << setw(4) << dictionary[i].wear << " |\n";
    }

    cout << setw(50 + size_name + size_brand) << setfill('-') << "\n" << setfill(' ');
}

void FindItem() { // вывод конкретного train из dictionary в консоль
    char str_id[8]; // по анологии с void AddItem()
    cout << "Введите инвентарный номер поезда:\n";
    cin >> str_id;
    int id = atoi(str_id);
    int index = FindItem(id);

    if (id != 0 and index != -1) { // проходимся по dictionary
        cout << setw(44 + size_name + size_brand) << setfill('-') << "\n" << setfill(' ');
        cout << "| " << setw(8) << "ID" << " | "
             << setw(size_name) << "NAME" << " | "
             << setw(size_brand) << "BRAND" << " | "
             << setw(6) << "DATE 1" << " | "
             << setw(6) << "DATE 2" << " | "
             << setw(4) << "WEAR" << " |\n";
        cout << setw(44 + size_name + size_brand) << setfill('-') << "\n" << setfill(' ');

        cout << "| " << setw(8) << dictionary[index].id << " | "
             << setw(size_name) << dictionary[index].name << " | "
             << setw(size_brand) << dictionary[index].brand << " | "
             << setw(6) << dictionary[index].date_release << " | "
             << setw(6) << dictionary[index].date_registration << " | "
             << setw(4) << dictionary[index].wear << " |\n";

        cout << setw(44 + size_name + size_brand) << setfill('-') << "\n" << setfill(' ');
    } else if (id != 0) {
        cout << "Данный инвентарный номер не найден в списке. Поиск отменён!!!\n";
    } else cout << "Неправильный формат ввода. Поиск отменён!!!\n";
}

void LoggingDictionary() { // запись всех train из dictionary в файл
    char filename[100] = {0}; // узнаём название файла
    cout << "Введите название файла для сохранения (пример: ../other/log.txt)\n";
    cin >> filename;
//    char filename[] = "../other/log.txt";

    // открываем или создаём файл
    ofstream log_file(filename, ios_base::trunc | ios_base::out);
    if (!(log_file)) { log_file.open(filename); }

    for (int i = 0; i < last_position; ++i)
        log_file << i + 1 << ".\t"
                 << dictionary[i].id << " "
                 << dictionary[i].name << " "
                 << dictionary[i].brand << " "
                 << dictionary[i].date_release << " "
                 << dictionary[i].date_registration << " "
                 << dictionary[i].wear << "\n";
    cout << "Список поездов успешно записан в: " << filename << ".\n";
}

void SortDictionary() { // сортируем dictionary по id из train
    // метод пузырьковой сортировки
    for (int i = 0; i < last_position; i++)
        for (int j = 0; j < last_position - 1; j++)
            if (dictionary[j].id > dictionary[j + 1].id)
                swap(dictionary[j], dictionary[j + 1]);
    cout << "Список успешно отсортирован\n";
}

void Help() { // вывод в консоль всех доступных действий
    cout << "1 - Добавление новых данных в список \n"
         << "2 - Удаление данных из списка \n"
         << "3 - Изменение данных в списке \n"
         << "4 - Вывод списка на экран  \n"
         << "5 - Поиск по инвентарному номеру поезда \n"
         << "6 - Запись списка в файл \n"
         << "7 - Сортировка по инвентарному номеру поездов \n"
         << "8 - Просмотр всех команд \n"
         << "9 - Завершение программы \n";
}
