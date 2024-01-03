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


/// creating a bit mask
// in the future, it is used to take only part of the bits of the number
int CreateMask(int a, int b) {
    int r = 0;
    for (int i = a; i <= b; ++i)
        r |= 1 << i;
    return r;
}

/// saving the decoded text to a file
void Output(char filename[], int **dec) {
    FILE *new_write = fopen(filename, "wb");

    for (int i = 0; i < size_out; ++i) {
        for (int j = 0; j < size_word; ++j) {
            if (dec[i][j] != 0) {
//                printf("%c", dec[i][j]);
                fputc(dec[i][j], new_write);
            }
        }
    }

    fclose(new_write);
}


/// the function decodes the phrase
int **Decompress1(int *in, int size_in, int *index) {
    // creating a dictionary (1-255 characters from the ascii table)
    int dictionary[size_dictionary][size_word] = {0}, last_position = 0;;
    for (int i = 1; i < 256; i++) dictionary[last_position++][0] = i;

    // creating a two-dimensional array for output
    // the first level is an array of words, the 2nd level is words
    // we cannot output immediately, because the algorithm refers to the previous output values
    int **out = malloc(size_out * sizeof *out + (size_out * (size_word * sizeof **out)));
    int *offs = &out[size_out];
    for (int i = 0; i < size_out; ++i, offs += size_word) out[i] = offs;
    for (int i = 0; i < size_out; ++i) for (int j = 0; j < size_word; ++j) out[i][j] = 0;
    (*index)++;

    int percent = 0;
    printf("decompression_2 [ ");
    // decoding algorithm
    for (int num = 0; num < size_in; ++num) {
        // beautiful output of compression progress
        if (num > size_in * 0.1 * percent) {
            percent++;
            printf("#");
        }

        int tmp[size_word] = {0};
        int size = 0;

        // <tmp> is equal to the previous value of <out>
        for (size = 0; out[(*index) - 1][size] != 0; ++size) tmp[size] = out[(*index) - 1][size];

        // if the encoded word is already in the dictionary
        // then we take the value from the dictionary
        if (in[num] < last_position) tmp[size++] = dictionary[in[num]][0];
        // otherwise from the last output
        else tmp[size++] = out[(*index) - 1][0];

        // if there is no such value in the dictionary, then save
        if (Find(dictionary, last_position, tmp, size) == -1) {
            for (int i = 0; i < size; ++i) dictionary[last_position][i] = tmp[i];
            last_position++;
        }

        // adding values from the <dictionary> to the <out>
        for (int i = 0; i < size_word; ++i) {
            out[*index][i] = dictionary[in[num]][i];
        }
        (*index)++;
    }
    printf("%.*s ]\n", 10 - percent, "##########");
    return out;
}


/// the function decodes the phrase
int *Decompress2(char filename[], int *size_dec) {
    int type = 1, num = 0;
    int byte = 0, tmp = 0, count = 0;
    int result = 0, mask = 0;

    // we determine the length of the file
    FILE *encode_read = fopen(filename, "rb");
    fseek(encode_read, 0, SEEK_END);
    int enc_size = ftell(encode_read);
    fseek(encode_read, 0, SEEK_SET);

    int *dec = calloc(enc_size, sizeof(int));
    int percent = 0;
    printf("decompression_1 [ ");

    // we read the file to the last element
    // we don't use EOF because the encoded character can equal EOF
    while (num++ <= enc_size) {
        // beautiful output of compression progress
        if (num - 1 > enc_size * 0.1 * percent) {
            percent++;
            printf("#");
        }

        byte = fgetc(encode_read);
        tmp <<= 8;
        mask = CreateMask(0, 7);
        tmp += mask & byte;
        count += 8;

        // if the number of stored bits is greater than the type of bits, then you can extract these bits
        while (count > type) {
            mask = CreateMask(count - type, count - 1);
            result = mask & tmp;
            result >>= count - type;

            // if the resulting <result> is 0, then ...
            if (result == 0) {
                // ... we define a new type
                // as long as the bit is 0, we increase the number of bits (<type>)
                while (result == 0 && type != count + 1) {
                    type++;
                    mask = CreateMask(count - type, count - 1);
                    result = mask & tmp;
                    result >>= count - type;
                }
                type--;
                result >>= 1;
            } else dec[(*size_dec)++] = result; // adding the decoded values to the array
            count -= type;
        }
    }
    printf("%.*s ]\n", 10 - percent, "##########");

    fclose(encode_read);
    return dec;
}


int main() {
    printf("Enter the path to the encoding file (press \"Enter\" to complete the input):\n");
    char filename[100] = {0};
    scanf("%s", filename); // ../files/encode.txt

    int size_dec = 0;
    int *dec = Decompress2(filename, &size_dec); /// decompress 2 method
//    for (int i = 0; i < size_dec; ++i) printf("%d ", dec[i]); /// viewing the result of 2 decompression

    int size_dec1 = 0;
    int **dec1 = Decompress1(dec, size_dec, &size_dec1); /// decompress 1 method
    free(dec);

    printf("\nEnter the path to the new file (press \"Enter\" to complete the input):\n");
    scanf("%s", filename); // ../files/new_file.txt

    Output(filename, dec1); /// output the decoded text
    free(dec1);

    return 0;
}