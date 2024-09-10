/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include <iostream>
#include <fstream>
#include "../include/class.h"

void reading(Statement *dictionary, int *len) {
    std::ifstream file("../other/log.txt", std::ios_base::in);
    if (!file) std::cout << "The file does not exits\n";
    else {
        while (!file.eof()) {
            file >> dictionary[(*len)++];
        }
    }
    std::cout << "The database is reading\n";
    file.close();
}

void logging(Statement *dictionary, const int len) {
    std::ofstream file("../other/log.txt", std::ios_base::out);
    if (!file) std::cout << "The file does not exits\n";
    else {
        for (int i = 0; i < len; ++i) {
            file << dictionary[i];
            if (i != len - 1) file << "\n";
        }
    }
    std::cout << "The database is saved\n";
    file.close();
}

void sorting(Statement *dictionary, const int len) {
    for (int i = 0; i < len - 1; ++i) {
        for (int j = 0; j < len - i - 1; ++j) {
            if (dictionary[j] < dictionary[j + 1]) {
                Statement tmp(dictionary[j]);
                dictionary[j] = dictionary[j + 1];
                dictionary[j + 1] = tmp;
            }
        }
    }
    std::cout << "The database is sorted\n";
}

void adding(Statement *dictionary, const int len) {
    std::cout << "Enter the data of the new statement (separated by a space/enter):\n";
    std::cin >> dictionary[len];
    std::cout << "New statement added\n";
}

void removing(Statement *dictionary, int *len) {
    int i = 0;
    std::cout << "Enter the statement number from the database:\n";
    std::cin >> i;
    if (i > 0 && i <= *len) {
        dictionary[--i] = dictionary[--(*len)];
        std::cout << "New statement deleted\n";
    } else { std::cout << "This statement is not in the database\n"; }
}

void viewing(Statement *dictionary, int len) {
    std::cout << "|" << std::setw(16) << "NAME"
              << "|" << std::setw(10) << "TYPE"
              << "|" << std::setw(8) << "STATUS"
              << "|" << std::setw(12) << "ESTIMATION"
              << "|\n";

    for (int i = 0; i < len; ++i)
        std::cout << dictionary[i];

}

void help() {
    std::cout << "1 - Reading a database from a file \n"
              << "2 - Writing a database to a file \n"
              << "3 - Sorting the database \n"
              << "4 - Adding a new statement \n"
              << "5 - Removing a statement \n"
              << "6 - Viewing the database \n"
              << "7 - Help \n"
              << "8 - Completion of the program \n";
}
