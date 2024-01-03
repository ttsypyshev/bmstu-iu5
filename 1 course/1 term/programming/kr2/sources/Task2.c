/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include <stdio.h>
#include "../include/Header.h"

int task2() {
    printf("\n---Task N2---\n");
    // we create the original string
//    char old_str[] = "The habit of not showing your feelings has become so ingrained that it has become an instinct.";
    char old_str[] = " !#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    printf("Source string:\n'%s'", old_str);
    int size = sizeof(old_str) / sizeof(*old_str);
    printf("\nThe length of the original string: %d\n", size);
    char new_str[size];
    // new symbol = old symbol - 1 (code by table Ascii)
    for (int i = 0; i < size; ++i) {
        new_str[i] = old_str[i] - 1;
//        printf("%c - %c\n", old_str[i], new_str[i]);
    }

    printf("\nModified string:\n'%s'\n\n\n", new_str);

    return 0;
}