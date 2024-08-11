/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include <iostream>
#include <fstream>

using namespace std;


///global variables
#define max_len_word 50
#define size_dictionary 100

struct words {
    char eng[max_len_word];
    char rus[max_len_word];
};
words dictionary[size_dictionary];
int count = 0, last_position = 0;


///other fubctions
bool ComparisonWords(char word1[], char word2[]) {
    for (int i = 0; i < max_len_word; i++) {
        if (word1[i] != word2[i])
            return false;
        if (word1[i] == '\0' && word2[i] == '\0')
            return true;
    }
    return true;
}

int FindWords(char word[], int mode) {
    if (mode == 0) {
        for (int i = 0; i < count; i++)
            if (ComparisonWords(dictionary[i].eng, word))
                return i;
    } else if (mode == 1) {
        for (int i = 0; i < count; i++)
            if (ComparisonWords(dictionary[i].rus, word))
                return i;
    }
    return -1;
}

void EditDictionary(int num, char word1[], char word2[]) {
    for (int i = 0; i < max_len_word; ++i) {
        dictionary[num].eng[i] = word1[i];
        dictionary[num].rus[i] = word2[i];
    }
}

bool SortingWords(char word1[], char word2[]) {
    for (int i = 0; word1[i] != '\0' || word2[i] != '\0'; i++)
        if (word1[i] > word2[i])
            return true;
        else if (word1[i] < word2[i])
            return false;
}

void SortingDictionary() {
    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - i - 1; j++)
            if (SortingWords(dictionary[j].eng, dictionary[j + 1].eng))
                swap(dictionary[j], dictionary[j + 1]);
}


///main functions
void AddWord() {
    char word_eng[max_len_word], word_rus[max_len_word];
    cout << "Enter a word in English:";
    cin >> word_eng;
    int index = FindWords(word_eng, 0);
    if (index == -1) {
        cout << "Enter a word in Russian:";
        cin >> word_rus;
        EditDictionary(last_position, word_eng, word_rus);
        count++;
        last_position++;
        cout << "The word '" << word_eng << "' (" << word_rus << ") has been added to the dictionary\n";
    } else { cout << "The word '" << word_eng << "' was added earlier\n"; }
}

void RemoveWord() {
    char word_eng[max_len_word];
    cout << "Enter a word in English:";
    cin >> word_eng;
    int index = FindWords(word_eng, 0);
    if (index == -1) { cout << "The word '" << word_eng << "' is not in the dictionary\n"; }
    else {
        cout << "The word '" << word_eng << "' has been removed from the dictionary\n";
        EditDictionary(index, dictionary[last_position - 1].eng, dictionary[last_position - 1].rus);
        EditDictionary(last_position - 1, "", "");
        last_position--;
        count--;
    }
}

void Translate(int mode) {
    char word[max_len_word];
    cout << "Enter a word:";
    cin >> word;
    int index = FindWords(word, mode);
    if (index == -1) { cout << "The word '" << word << "' is not in the dictionary\n"; }
    else {
        if (mode == 0) { cout << "The word '" << word << "' translates as '" << dictionary[index].rus << "'\n"; }
        else { cout << "The word '" << word << "' translates as '" << dictionary[index].eng << "'\n"; }
    }
}

void ViewingDictionary() {
    for (int i = 0; i < count; i++)
        if (dictionary[i].rus[0] != '0')
            cout << i + 1 << ". " << dictionary[i].eng << " - " << dictionary[i].rus << endl;
    cout << endl;
}

void LoggingDictionary() {
    ofstream log_file("../log.txt", ios_base::trunc | ios_base::out);
    if (!(log_file)) { log_file.open("../log.txt"); }

    SortingDictionary();
    for (int i = 0; i < count; i++)
        if (dictionary[i].rus[0] != '0')
            log_file << i + 1 << ". " << dictionary[i].eng << " - " << dictionary[i].rus << endl;
    cout << "The dictionary is written to a file\n";
}

void Help() {
    cout << "1 - Adding a word to the dictionary \n"
         << "2 - Deleting a word from the dictionary \n"
         << "3 - Translation of words from English to Russian \n"
         << "4 - Translation of words from Russian to English \n"
         << "5 - Displaying the dictionary on the screen  \n"
         << "6 - Dictionary output to a file \n"
         << "7 - Help \n"
         << "8 - Completion of the program \n";
}


int main() {
    int item = 7;
    while (true) {
        if (item == 1) AddWord();
        else if (item == 2) RemoveWord();
        else if (item == 3) Translate(0);
        else if (item == 4) Translate(1);
        else if (item == 5) ViewingDictionary();
        else if (item == 6) LoggingDictionary();
        else if (item == 7) Help();
        else if (item == 8) return 0;
        else { cout << "Incorrect values have been entered. Enter them again\n"; }
        cout << "\nSelect a menu item (1-7):\n";
        cin >> item;
    }
}