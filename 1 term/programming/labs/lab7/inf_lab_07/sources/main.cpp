/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int count_keys = 1, size = 0;
    char tmp;
    unsigned char buffer;

    ///discovery all files
    ifstream file_keys("../texts/keys.txt", ios_base::in);
    if (!(file_keys)) {
        cout << "Error of file1 opening." << endl;
        return 1;
    } else {
        while (file_keys.get(tmp)) {
            if (tmp == ' ') { count_keys++; }
        }
        file_keys.clear();
        file_keys.seekg(0, ios_base::beg);
    }

    ifstream original_text("../texts/original.txt", ios_base::in);
    if (!(original_text)) {
        cout << "Error of file2 opening." << endl;
        return 1;
    } else {
        original_text.seekg(0, ios::end); //we move the cursor to the last element and look at its address
        size = original_text.tellg();
        original_text.seekg(0, ios_base::beg);
    }

    ofstream encrypted_text("../texts/encrypted.txt", ios_base::trunc | ios_base::out);
    if (!(encrypted_text)) { encrypted_text.open("../texts/encrypted.txt"); }

    ofstream deciphered_text("../texts/decrypted.txt", ios_base::trunc | ios_base::out);
    if (!(deciphered_text)) { deciphered_text.open("../texts/decrypted.txt"); }


    ///getting a letter for statistics
    unsigned char symbol;
    cout << "Enter the letter: ";
    cin >> symbol;
    int array_statistic[size][2];
    int last_position = 0;


    ///creating am array of keys
    int *array_keys = new int[count_keys]();
    int num = 0;
    while (file_keys.get(tmp)) {
        if (tmp == ' ') {
            num++;
        } else {
            buffer = tmp;
            array_keys[num] += buffer;
        }
    }


    ///encoding of the original text
    int code_symbol;
    bool flag;
    for (int i = 0; original_text.get(tmp); ++i) {
        buffer = tmp;
        code_symbol = (buffer + array_keys[i % count_keys]) % 256;
        encrypted_text << (unsigned char) code_symbol;

        flag = true;
        if (buffer == symbol) {
            for (int j = 0; j <= last_position; ++j) {
                if (array_statistic[j][0] == code_symbol) {
                    ++array_statistic[j][1];
                    flag = false;
                    break;
                }
            }
            if (flag) {
                array_statistic[last_position][0] = code_symbol;
                array_statistic[last_position][1] = 1;
                ++last_position;
            }
        }
    }


    ///decoding the origimal text
    encrypted_text.close();
    ifstream encrypted_text1("../texts/encrypted.txt", ios_base::in);
    for (int i = 0; encrypted_text1.get(tmp); ++i) {
        buffer = tmp;
        deciphered_text << char((buffer - array_keys[i % count_keys]) % 256);
    }


    ///statistics output
    if (last_position != 0) {
        cout << setw(8) << "Symbol" << setw(10) << "Code" << setw(10) << "Count\n";
        for (int i = 0; i < last_position; ++i) {
            cout << setw(8) << char(array_statistic[i][0]) << setw(10) << array_statistic[i][0] << setw(10)
                 << array_statistic[i][1] << endl;
        }
    }


    delete[] array_keys;
    file_keys.close();
    original_text.close();
    encrypted_text1.close();
    deciphered_text.close();
    return 0;
}