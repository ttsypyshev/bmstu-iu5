/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

/// Error: "Process finished with exit code -1073741571 (0xC00000FD)"
//  it is necessary to increase the stack size in the ide settings
//  add to CMakeLists:  MATH(EXPR stack_size "64 * 1024 * 1024") # 64 Mb
//                      set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")
///  Note: but I still couldn't open 1984 (I don't have enough computer power)
//  can try to run asynchronously

/// A flaw: reading a file with the Russian language does not work
// in this ide it is difficult to fix
// Note: need to test in other IDEs


/*-------------------------------------------------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>

/// dictionary size values
// with these values, the program will work only if you increase the stack size to 64mb
#define size_dictionary 100000
#define size_out 1000000
#define size_word 100


/// search for a word in the dictionary
int Find(int in[size_dictionary][size_word], int last_position, int str[size_word], int size) {
    for (int i = 0; i < last_position; ++i) {
        int flag = 1;
        for (int j = 0; j < size; ++j) {
            if (in[i][j] != str[j]) flag = 0;
        }
        // if found, then output the index
        if (flag) return i;
    }
    // if not found, then output -1
    return -1;
}


/// determining the number of insignificant zeros
int CountZero(int tmp) {
    int flag = 1, count = 0;
    // we go through the bits until the bit is 0
    for (int position = sizeof(int) * 8 - 1; position >= 0; --position) {
        if (((tmp >> position) & 0x1) == 0 & flag) count++;
        else break;
    }
    return 32 - count;
}


/// creating a bit mask
// in the future, it is used to take only part of the bits of the number
int CreateMask(int a, int b) {
    int r = 0;
    for (int i = a; i <= b; ++i)
        r |= 1 << i;
    return r;
}


/// delimiting a <enc1> for 2 compression
// adding delimiters ('0') to <enc> when increasing the number of significant bits
int *Analysis(int *size_enc, int enc[]) {
    int tmp_size = 0, index, type = 0;
    int *tmp = calloc(*size_enc + *size_enc, sizeof(int));

    // realloc could not be used because some newly added characters were deleted
    for (index = 0; index < *size_enc; ++index) {
        // if the number of insignificant bits is greater than the previous maximum number, then...
        if (type < CountZero(enc[index])) {
            // ...we insert a delimiter
            type = CountZero(enc[index]);
            tmp[tmp_size++] = 0;
        }
        tmp[tmp_size++] = enc[index];
    }

    *size_enc = tmp_size;
    tmp = realloc(tmp, tmp_size * sizeof(int));
    return tmp;
}


/// the function compresses the text
int *Compress1(char filename[], int *index) {
    // opening the original file
    FILE *in = fopen(filename, "rb");

    // creating a dictionary (1-255 characters from the ascii table)
    int dictionary[size_dictionary][size_word] = {0}, last_position = 0;
    for (int i = 1; i < 256; i++) dictionary[last_position++][0] = i;

    // creating a two-dimensional array for output
    int *out = malloc(size_out * sizeof(int));

    // encoding algorithm
    int byte = 0, num = 0;
    int current_string[size_word] = {0}, size = 0;
    int percent = 0;
    printf("compression [ ");
    while ((byte = fgetc(in)) != EOF) {
        // beautiful output of compression progress
        if (last_position > size_dictionary * 0.1 * percent) {
            percent++;
            printf("#");
        }

        num++;
        current_string[size++] = byte;
        // if there is no <current_string> in the <dictionary>, then...
        if (Find(dictionary, last_position, current_string, size) == -1) {
            // ...we are adding it
            for (int i = 0; i < size_word; ++i) dictionary[last_position][i] = current_string[i];
            last_position++;

            // output the number of the previous value <current_string>
            out[(*index)++] = Find(dictionary, last_position, current_string, size - 1);

            // clearing <current_string> and equating <byte>
            for (int i = 0; i < size_word; ++i) current_string[i] = 0;
            current_string[0] = byte;
            size = 1;
        }
    }
    printf("%.*s ]\n", 10 - percent, "##########");
    // the last element is not taken into account by the algorithm, so you have to add it manually
    out[(*index)++] = Find(dictionary, last_position, current_string, size);

    fclose(in);
    return out;
}


/// the function compresses the text
void Compress2(char filename[], int size_enc, int enc[]) {
    int byte = 0, count = 0, tmp = 0, tmp_len = 0;
    int mask = 0, result = 0;
    int type = 0, percent = 0;
    printf("saving [ ");
    FILE *encode_write = fopen(filename, "wb");
    for (int i = 0; i < size_enc; ++i) {
        // beautiful output of compression progress
        if (i > size_enc * 0.1 * percent) {
            percent++;
            printf("#");
        }

        // if we meet a separator, then we define a new length
        if (enc[i] == 0) { type = CountZero(enc[i + 1]); }
        tmp = enc[i];
        tmp_len = type;

        while (tmp_len != 0) {
            mask = CreateMask(0, tmp_len - 1);
            result = mask & tmp;
            // if result + byte > 8 bits, then...
            if (count + tmp_len > 8) {
                result >>= tmp_len - (8 - count);
                tmp_len = tmp_len - (8 - count);
                byte <<= 8 - count;
                count = 8;
                mask = CreateMask(0, tmp_len - 1);
                tmp = mask & tmp;
            } else {
                byte <<= tmp_len;
                count += tmp_len;
                tmp_len = 0;
                tmp = 0;
            }
            byte += result;

            // if all 8 bits are filled in byte, then we write to the file
            if (count == 8) {
                fputc(byte, encode_write);
                count = 0;
                byte = 0;
            }
        }
    }
    printf("%.*s ]\n", 10 - percent, "##########");

    // we add the remaining bits
    byte <<= 8 - count;
    fputc(byte, encode_write);

    fclose(encode_write);
}

int main() {
    printf("Enter the path to the original file (press \"Enter\" to complete the input):\n");
    char filename[100] = {0};
    scanf("%s", filename); // ../files/old_file.txt

    int size_enc = 0;
    int *enc1 = Compress1(filename, &size_enc);    /// compress 1 method
//    for (int i = 0; i < size_enc; ++i) printf("%d ", enc1[i]);    /// viewing the result of 1 compression

    int *enc2 = Analysis(&size_enc, enc1);  /// delimiting a <enc1> for 2 compression
    free(enc1);

    printf("\nEnter the path to the encoding file (press \"Enter\" to complete the input):\n");
    scanf("%s", filename); // ../files/encode.txt

    Compress2(filename, size_enc, enc2);    /// compress 2 method
    free(enc2);

    return 0;
}