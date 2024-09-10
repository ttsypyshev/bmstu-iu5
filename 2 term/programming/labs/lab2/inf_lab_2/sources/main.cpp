/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include <iostream>
#include "../include/class.h"
#include "../include/functions.h"

int main() {
    const size_t max_size = 100;
    Statement *dictionary = new Statement[max_size];
    int len = 0;

    int item = 7;
    while (true) {
        if (item == 1) reading(dictionary, &len);
        else if (item == 2) logging(dictionary, len);
        else if (item == 3) sorting(dictionary, len);
        else if (item == 4) adding(dictionary, len++);
        else if (item == 5) removing(dictionary, &len);
        else if (item == 6) viewing(dictionary, len);
        else if (item == 7) help();
        else if (item == 8) return 0;
        else { std::cout << "Incorrect values have been entered. Enter them again\n"; }
        std::cout << "\nSelect a menu item (1-8):\n";
        std::cin >> item;
    }

    delete[] dictionary;
}