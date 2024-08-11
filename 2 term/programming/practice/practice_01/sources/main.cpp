/// Copyright 2023 ttsypyshev <ttsypyshev01@gmail.com>

#include <iostream>
#include <algorithm>
#include "../MyLib/include/myLib.h"

using namespace std;

string
findStudentName(DBTableTxt &studentsTable, DBTableTxt &booksTable, DBTableTxt &subscriptionsTable, string bookTitle) {
    int bookID = -1;
    for (int i = 0; i < booksTable.GetSize(); i++) {
        Row row = booksTable[i];
        std::string title = *(static_cast<std::string *>(row["Title"]));
        size_t first_not_space = title.find_first_not_of(' ');
        title = title.substr(first_not_space);
        if (title == bookTitle) {
            bookID = *(int *) row["BookID"];
            break;
        }
    }

    if (bookID == -1) {
        return "(книга не найдена)";
    }

    vector<pair<string, string>> students;
    for (int i = 0; i < subscriptionsTable.GetSize(); i++) {
        Row row = subscriptionsTable[i];
        if (*(int *) row["BookID"] == bookID) {
            string studentID = to_string(*(int *) row["StudentID"]);
            string outDate = (char *) row["OutDate"];
            students.push_back(make_pair(studentID, outDate));
        }
    }

    sort(students.begin(), students.end(),
         [](const pair<string, string> &a, const pair<string, string> &b) -> bool {
             return a.second > b.second;
         });

    if (students.size() > 0) {
        int studentID = stoi(students[0].first);
        for (int i = 0; i < studentsTable.GetSize(); i++) {
            Row row = studentsTable[i];
            if (*(int *) row["StudentID"] == studentID) {
                std::string name = *(static_cast<std::string *>(row["Name"]));
                size_t first_not_space = name.find_first_not_of(' ');
                return name.substr(first_not_space);
            }
        }
    }

    return "(человек не найден)";
}

int item1(DBTableTxt &table, string path, string name = "Students.txt") {
    cout << "Чтение таблицы..." << endl;
    table.ReadDBTable(path + name);
    cout << "Таблица прочитана!" << endl << endl;
    return 0;
}

int item2(DBTableTxt &table, int screenWidth) {
    cout << "Вывод таблицы...";
    table.PrintTable(screenWidth);
    cout << endl << endl;
    return 0;
}

int item3(DBTableTxt &table, string path) {
    cout << "Сохранение таблицы..." << endl;
    table.WriteDBTable(path + "Students.txt");
    cout << "Таблица сохранена!" << endl << endl;
    return 0;
}

int item4(DBTableTxt &table) {
    cout << "Добавление записи в таблицу..." << endl;
    table.AddRow(table.CreateRow(), table.GetSize());
    cout << "Запись добавлена!" << endl << endl;
    return 0;
}

int item5(DBTableTxt &table, int id = 0, string input = "") {
    cout << "Перевод студента в другую группу..." << endl;
    if (id == 0) {
        cout << "Введите StudentID: ";
        cin >> id;
        cin.clear();
        cin.ignore(10, '\n');
    }
    if (input.empty()) {
        cout << "Введите новую группу: ";
        std::getline(std::cin, input);
    }

    vector<int> index = table.IndexOfRecord(&id, "StudentID");
    Row tmp = table[index[0]];

    void *adress = GetValue(input, "Group", table.GetHeader());
    tmp["Group"] = adress;
    table.AddRow(tmp, index[0]);
    cout << "Информация изменена!" << endl << endl;

    return 0;
}

int item6(DBTableTxt &table, int id = 0) {
    cout << "Распечатать ФИО студента, StudentID которого равен: ";
    if (id == 0) {
        cout << "(введите StudentID) ";
        cin >> id;
        cin.clear();
        cin.ignore(10, '\n');
    } else cout << id;
    cout << endl;

    vector<int> index = table.IndexOfRecord(&id, "StudentID");
    cout << "ФИО: " << *(string *) table[index[0]]["Name"] << endl << endl;

    return 0;
}

int item7(DBTableTxt &table, string path) {
    cout << "Увеличение на 1 количество экземпляров всех книг в библиотеке..." << endl;
    int id;
    Row tmp;
    for (int i = 0; i < table.GetSize(); ++i) {
        tmp = table[i];
        id = *(int *) table[i]["Quantity"];
        tmp["Quantity"] = GetValue(std::to_string(id + 1), "Quantity", table.GetHeader());
        table.AddRow(tmp, i);
    }
    table.WriteDBTable(path + "Books.txt");
    cout << "Количество увеличено!" << endl << endl;

    return 0;
}

int item8(DBTableTxt &studentsTable, DBTableTxt &booksTable, DBTableTxt &subscriptionsTable, string bookTitle = "") {
    cout << "Определение студента, который дольше всех держит на руках: ";
    if (bookTitle.empty()) {
        cout << "(введите название книги) ";
        std::getline(std::cin, bookTitle);
    } else cout << bookTitle;
    cout << endl;

    cout << "Результат: " << findStudentName(studentsTable, booksTable, subscriptionsTable, bookTitle) << endl << endl;

    return 0;
}

int item9(DBTableTxt &studentsTable, DBTableTxt &booksTable, DBTableTxt &subscriptionsTable, string path) {
    item1(studentsTable, path); // чтение
    item2(studentsTable, 44); // печать

    item4(studentsTable); // добавление записи в таблицу
    item2(studentsTable, 44); // печать

    item5(studentsTable, 2, "IU5-23"); // перевести студента в другую группу
    item2(studentsTable, 44); // печать

    item6(studentsTable, 3); // распечатать ФИО студента, StudentID которого равен 3

    item7(booksTable, path); // увеличить на 1 количество экземпляров всех книг в библиотеке
    item2(booksTable, 78); // печать

    item8(studentsTable, booksTable, subscriptionsTable, "Feynman Lectures on Physics");
    item8(studentsTable, booksTable, subscriptionsTable, "The Design of Everyday Things");
    item8(studentsTable, booksTable, subscriptionsTable, "Hawking's Guide to the Universe");
    // Определить студента, который дольше всех держит на руках экземпляр указанной книги

    item1(studentsTable, path); // чтение
    item2(studentsTable, 44); // печать
    return 0;
}

int menu() {
    cout << endl << "Выбирите один из пунктов: " << endl;
    cout << "\t1 - Чтение таблицы из файла" << endl;
    cout << "\t2 - Печать таблицы" << endl;
    cout << "\t3 - Запись таблицы в файл" << endl;
    cout << "\t4 - Добавление записи в таблицу" << endl;
    cout << "\t5 - Перевести студента в другую группу" << endl;
    cout << "\t6 - Распечатать ФИО студента, StudentID которого равен 3" << endl;
    cout << "\t7 - Увеличить на 1 количество экземпляров всех книг в библиотеке " << endl;
    cout << "\t8 - Определить студента, который дольше всех держит на руках экземпляр указанной книги" << endl;
    cout << "\t9 - Тестирование"
         << endl;
    cout << "\t10 - Выход" << endl;
    int choice;
    cout << "Выберите действие" << endl;
    cin >> choice;
    cin.clear();
    cin.ignore(10, '\n');
//    while (cin.fail()) {
//        cout << "Ошибка ввода. Повторите ввод" << endl;
//        cin.clear();
//        cin.ignore(10, '\n');
//        cin >> choice;
//    }
    return choice;
}

int main() {
    string path = "../files/";

    DBTableTxt studentsTable;
    studentsTable.ReadDBTable(path + "Students.txt");

    DBTableTxt booksTable;
    booksTable.ReadDBTable(path + "Books.txt");

    DBTableTxt subscriptionsTable;
    subscriptionsTable.ReadDBTable(path + "Subscriptions.txt");

    while (true) {
        switch (menu()) {
            case 1:
                item1(studentsTable, path);
                break;
            case 2:
                item2(studentsTable, 78);
                break;
            case 3:
                item3(studentsTable, path);
                break;
            case 4:
                item4(studentsTable);
                break;
            case 5:
                item5(studentsTable);
                break;
            case 6:
                item6(studentsTable, 3);
                break;
            case 7:
                item7(booksTable, path);
                break;
            case 8:
                item8(studentsTable, booksTable, subscriptionsTable);
                break;
            case 9:
                item9(studentsTable, booksTable, subscriptionsTable, path);
                break;
            case 10:
                return 0;
            default:
                cout << "Недопустимое действие. Повторите выбор" << endl;
                break;
        }
    }
}
