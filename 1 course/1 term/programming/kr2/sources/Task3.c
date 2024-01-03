/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include <stdio.h>
#include "../include/Header.h"

#define size_dictionary 100
#define size_name 40
#define size_brand 40

struct cars {
    char name[size_name]; // car name
    char brand[size_brand]; // name of the car manufacturer
    int type; // vehicle type number
    int date_release; // car release date
    int date_registration; // date of registration of the car
};
struct cars dictionary[size_dictionary]; // array of structures
int last_position = 0; // index of the first empty element


void AddItem() {
    char name[size_name], brand[size_brand];
    int type, date_release, date_registration;
    // we ask the user for new data
    printf("Enter the name of the car: \n");
    scanf("%s", &name);
    printf("Enter the car brand: \n");
    scanf("%s", &brand);
    printf("Enter the type of car: \n");
    scanf("%d", &type);
    printf("Enter the year of manufacture of the car: \n");
    scanf("%d", &date_release);
    printf("Enter the year of registration of the car: \n");
    scanf("%d", &date_registration);
    // we write new data in place of an empty element
    for (int i = 0; i < size_name; ++i) dictionary[last_position].name[i] = name[i];
    for (int i = 0; i < size_brand; ++i) dictionary[last_position].brand[i] = brand[i];
    dictionary[last_position].type = type;
    dictionary[last_position].date_release = date_release;
    dictionary[last_position].date_registration = date_registration;
    last_position++;
}

void RemoveItem() {
    int n = 0;
    // we ask the user for the index of the item to be deleted
    printf("Enter the number of the item you want to delete: \n");
    scanf("%d", &n);
    n--;
    if (n < 0 || n >= last_position) {
        printf("There is no such element\n");
        return;
    }
    // we replace the deleted element with the last one, so as not to waste resources on shifting
    for (int i = 0; i < size_name; ++i) dictionary[n].name[i] = dictionary[last_position - 1].name[i];
    for (int i = 0; i < size_brand; ++i) dictionary[n].brand[i] = dictionary[last_position - 1].brand[i];
    dictionary[n].type = dictionary[last_position - 1].type;
    dictionary[n].date_release = dictionary[last_position - 1].date_release;
    dictionary[n].date_registration = dictionary[last_position - 1].date_registration;
    last_position--;
}

void EditItem() {
    int n = 0;
    printf("Enter the number of the item you want to change: \n");
    scanf("%d", &n);
    n--;
    if (n < 1 || n >= last_position) {
        printf("There is no such element\n");
        return;
    }
    // we ask the user for new data
    char name[size_name], brand[size_brand];
    int type, date_release, date_registration;
    printf("Enter the name of the car: \n");
    scanf("%s", &name);
    printf("Enter the car brand: \n");
    scanf("%s", &brand);
    printf("Enter the type of car: \n");
    scanf("%d", &type);
    printf("Enter the year of manufacture of the car: \n");
    scanf("%d", &date_release);
    printf("Enter the year of registration of the car: \n");
    scanf("%d", &date_registration);
    // we are changing the selected item
    for (int i = 0; i < size_name; ++i) dictionary[n].name[i] = name[i];
    for (int i = 0; i < size_brand; ++i) dictionary[n].brand[i] = brand[i];
    dictionary[n].type = type;
    dictionary[n].date_release = date_release;
    dictionary[n].date_registration = date_registration;
}

void ViewingDictionary(struct cars tmp_dictionary[], int size) {
    // we output each element of the array (structure) until the empty elements begin
    for (int i = 0; i < size; ++i) {
        printf("%d.\t %s %s %d %d %d\n", i + 1, tmp_dictionary[i].name, tmp_dictionary[i].brand, tmp_dictionary[i].type,
               tmp_dictionary[i].date_release, tmp_dictionary[i].date_registration);
    }
}

void FilterDictionary() {
    int date_release, date_registration;
    printf("Select the year of manufacture of the car: \n");
    scanf("%d", &date_release);
    printf("Choose the year of registration of the car: \n");
    scanf("%d", &date_registration);
    struct cars tmp_dictionary[size_dictionary];
    int cursor = 0;
    // we create a new array and add only those elements of the old one that fit the above condition
    for (int i = 0; i < size_dictionary; ++i) {
        if (dictionary[i].date_release <= date_release & dictionary[i].date_registration == date_registration) {
            for (int i = 0; i < size_name; ++i) tmp_dictionary[cursor].name[i] = dictionary[i].name[i];
            for (int i = 0; i < size_brand; ++i) tmp_dictionary[cursor].brand[i] = dictionary[i].brand[i];
            tmp_dictionary[cursor].type = dictionary[i].type;
            tmp_dictionary[cursor].date_release = dictionary[i].date_release;
            tmp_dictionary[cursor].date_registration = dictionary[i].date_registration;
            cursor++;
        }
    }
    ViewingDictionary(tmp_dictionary, cursor);
}

void Help_Task3() {
    printf("1 - Adding a item to the dictionary \n"
           "2 - Deleting a item from the dictionary \n"
           "3 - Editing an item in the dictionary \n"
           "4 - Displaying the dictionary on the screen \n"
           "5 - Show cars manufactured before X and registered in Y  \n"
           "6 - Help \n"
           "7 - Return to the task selection menu \n");
}

int task3() {
    printf("\n---Task N3---\n");
    // the user selects the action that he wants to perform
    // we call a function that corresponds to this action
    int item = 0;
    Help_Task3();
    while (1) {
        printf("\nSelect a menu item (1-7):\n");
        scanf("%d", &item);
        if (item == 1) AddItem();
        else if (item == 2) RemoveItem();
        else if (item == 3) EditItem();
        else if (item == 4) ViewingDictionary(dictionary, last_position);
        else if (item == 5) FilterDictionary();
        else if (item == 6) Help_Task3();
        else if (item == 7) return 0;
        else { printf("Incorrect values have been entered. Enter them again\n"); }
    }
}