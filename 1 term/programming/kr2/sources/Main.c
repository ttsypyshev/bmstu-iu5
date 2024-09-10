/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include <stdio.h>
#include "../include/Header.h"

void Help() {
    printf("Menu:\n"
           "1 - Calling the first task\n"
           "2 - Calling the second task\n"
           "3 - Calling the third task\n"
           "4 - Help\n"
           "5 - Completion of the program\n");
}


int main() {
    // the user selects the task that he wants to perform
    // we call a function corresponding to this task
    int num = 0;
    Help();
    while (1) {
        printf("\n---Task selection menu---\n");
        printf("\nSelect a menu item(1-5):");
        scanf("%d", &num);
        if (num == 1) task1();
        else if (num == 2) task2();
        else if (num == 3) task3();
        else if (num == 4) Help();
        else if (num == 5) return 0;
        else {
            printf("There is no such menu item\n");
            Help();
        }
    }
}