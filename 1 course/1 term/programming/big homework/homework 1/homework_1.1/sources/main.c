/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

/// Error: "Process finished with exit code -1073741571 (0xC00000FD)"
//  it is necessary to increase the stack size in the ide settings
//  add to CMakeLists:  MATH(EXPR stack_size "64 * 1024 * 1024") # 64 Mb
//                      set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")
///  Note: but I still couldn't open 1984 (I don't have enough computer power)
//  you can try to run asynchronously

/// A flaw: reading a file with the Russian language does not work
// in this ide it is difficult to fix
// Note: need to test in other IDEs


/*-----------------------------------------------------------------------------------------------------------------*/


#include <stdio.h>
#include <inttypes.h>
// <inttypes.h> for uint64_t ( = unsigned long long int)

/// changing the set
void EditSet(int buffer, uint64_t len_buffer, int n, int set[][2], int *len_set) {
    buffer >>= len_buffer - n;

    int flag = 0, index = 0;
    for (; index < *len_set; ++index) { // searching for an item in set
        if (set[index][0] == buffer) {
            flag = 1;
            break;
        }
    }

    if (flag) set[index][1] += 1; // increasing the number
    else { // adding new item
        set[*len_set][0] = buffer;
        set[*len_set][1] = 1;
        ++(*len_set);
    }
}

/// universal addition of a new element to the set without the need for a full copy of the file
// type - 8/12/16/20
void EditItem(const int type, const int byte, int *buffer, uint64_t *len_buffer, int set[][2], int *len_set) {
    //adding a new byte to the buffer
    *buffer <<= 8;
    *buffer += byte;
    *len_buffer += 8;

    // addition of a new item to the set
    while (*len_buffer >= type) {
        EditSet(*buffer, *len_buffer, type, set, len_set);
        *buffer <<= 32 - (*len_buffer - type);
        *buffer >>= 1; // it is necessary to correct the error with the shift (1101 >>= 2 == 001101, but not 111101)
        *buffer &= ~(1 << 31);
        *buffer >>= 31 - (*len_buffer - type);
        *len_buffer -= type;
    }
}

/// bubble sorting
void SortingSet(int set[][2], int len_set) {
    for (int i = 0; i < len_set - 1; i++) {
        for (int j = 0; j < len_set - i - 1; j++) {
            if (set[j][1] < set[j + 1][1]) {
                int tmp1 = set[j][0]; // swap items
                int tmp2 = set[j][1];
                set[j][0] = set[j + 1][0];
                set[j][1] = set[j + 1][1];
                set[j + 1][0] = tmp1;
                set[j + 1][1] = tmp2;
            }
        }
    }
}

/// output of elements from set
void Output(int set[][2], int size, int count) {
    for (int i = 0; i < size; ++i) {
        // %b outputs insignificant zeros , so I wrote the output myself
        int tmp = set[i][0];
        for (int position = count - 1; position >= 0; --position)
            printf("%d", (tmp >> position) & 0x1);

        printf(" - %d\n", set[i][1]);
    }
    printf("\n");
}

int main() {
    FILE *file = fopen("../files/text.txt", "rb"); // ../files/text.txt     ../files/1984.pdf

    // we determine the length of the text
    fseek(file, 0, SEEK_END);
    uint64_t text_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // important variables
    // where set - array with statistics, len_set - len set
    int set8[text_size][2], len_set8 = 0;
    int set12[text_size][2], len_set12 = 0;
    int set16[text_size][2], len_set16 = 0;
    int set20[text_size][2], len_set20 = 0;

    //creating an array with statistics for 8, 12, 16, 20 bits
    int byte;
    int buffer8 = 0, buffer12 = 0, buffer16 = 0, buffer20 = 0;
    uint64_t len_buffer8 = (text_size * 8 - text_size * 8) % 8;
    uint64_t len_buffer12 = (text_size * 12 - text_size * 8) % 12;
    uint64_t len_buffer16 = (text_size * 16 - text_size * 8) % 16;
    uint64_t len_buffer20 = (text_size * 20 - text_size * 8) % 20;
    while ((byte = fgetc(file)) != EOF) {
        EditItem(8, byte, &buffer8, &len_buffer8, set8, &len_set8);
        EditItem(12, byte, &buffer12, &len_buffer12, set12, &len_set12);
        EditItem(16, byte, &buffer16, &len_buffer16, set16, &len_set16);
        EditItem(20, byte, &buffer20, &len_buffer20, set20, &len_set20);
    }

    // sorting set for 8/12/16/20 bit
    SortingSet(set8, len_set8); //for 8 bit
    SortingSet(set12, len_set12); //for 12 bit
    SortingSet(set16, len_set16); //for 16 bit
    SortingSet(set20, len_set20); //for 20 bit

    // output set for 8/12/16/20 bit
    Output(set8, len_set8, 8);
    Output(set12, len_set12, 12);
    Output(set16, len_set16, 16);
    Output(set20, len_set20, 20);

    fclose(file);
    return 0;
}
