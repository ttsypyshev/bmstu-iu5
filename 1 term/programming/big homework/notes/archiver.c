#include <stdio.h>
#include <stdlib.h>

#define size_dictionary 10000
#define size_out 100000
#define size_word 100


int Find(int in[size_dictionary][size_word], int last_position, int str[size_word], int size) {
    for (int i = 0; i < last_position; ++i) {
        int flag = 1;
        for (int j = 0; j < size; ++j) {
            if (in[i][j] != str[j]) flag = 0;
        }
        if (flag) return i;
    }
    return -1;
}


int CountZero(int tmp) {
    int flag = 1, count = 0;
    for (int position = sizeof(int) * 8 - 1; position >= 0; --position) {
        if (((tmp >> position) & 0x1) == 0 & flag) count++;
        else break;
    }
    return 32 - count;
}


void Print(int tmp, int n) {
    for (int position = n - 1; position >= 0; --position) {
        printf("%d", (tmp >> position) & 0x1);
    }
    printf("\n");
}


int CreateMask(int a, int b) {
    int r = 0;
    for (int i = a; i <= b; ++i)
        r |= 1 << i;
    return r;
}


int *Analysis(int *size_enc, int enc[]) {
    int tmp_size = 0, index, type = 0;
    int *tmp = calloc(*size_enc + *size_enc, sizeof(int));

    for (index = 0; index < *size_enc; ++index) {
        if (type < CountZero(enc[index])) {
            type = CountZero(enc[index]);
            tmp[tmp_size++] = 0;
//            tmp = realloc(tmp, tmp_size * sizeof(int));
        }
        tmp[tmp_size++] = enc[index];
//        tmp = realloc(tmp, tmp_size * sizeof(int));
    }

    *size_enc = tmp_size;
    tmp = realloc(tmp, tmp_size * sizeof(int));
    return tmp;
}


void Output(char filename[], int **dec) {
    FILE *new_write = fopen(filename, "wb");

    for (int i = 0; i < size_out; ++i) { /// decoded output
        for (int j = 0; j < size_word; ++j) {
            if (dec[i][j] != 0) {
                printf("%c", dec[i][j]);
                fputc(dec[i][j], new_write);
            }
        }
    }

    fclose(new_write);
}


int *Compress1(FILE *in, int *index) {
    int dictionary[size_dictionary][size_word] = {0}, last_position = 0;
    for (int i = 1; i < 256; i++) dictionary[last_position++][0] = i;

    int *out = malloc(size_out * sizeof(int));

    int byte;
    int num = 0;
    int current_string[size_word] = {0};
    int size = 0;
    while ((byte = fgetc(in)) != EOF) {
        num++;
        current_string[size++] = byte;
        if (Find(dictionary, last_position, current_string, size) == -1) {
            for (int i = 0; i < size_word; ++i) dictionary[last_position][i] = current_string[i];
            last_position++;

//            if (last_size < size) {
//                out[(*index)++] = 0;
//                last_size = size;
//            }

            out[(*index)++] = Find(dictionary, last_position, current_string, size - 1);

            for (int i = 0; i < size_word; ++i) current_string[i] = 0;
            current_string[0] = byte;
            size = 1;
        }
    }
    out[(*index)++] = Find(dictionary, last_position, current_string, size);
    return out;
}


int **Decompress1(int *in, int size_in, int *index) {
    int dictionary[size_dictionary][size_word] = {0}, last_position = 0;;
    for (int i = 1; i < 256; i++) dictionary[last_position++][0] = i;

    int **out = malloc(size_out * sizeof *out + (size_out * (size_word * sizeof **out)));
    int *offs = &out[size_out];
    for (int i = 0; i < size_out; ++i, offs += size_word) out[i] = offs;
    for (int i = 0; i < size_out; ++i) for (int j = 0; j < size_word; ++j) out[i][j] = 0;
    (*index)++;

    for (int num = 0; num < size_in; ++num) {
        int tmp[size_word] = {0};
        int size = 0;
        for (size = 0; out[(*index) - 1][size] != 0; ++size) tmp[size] = out[(*index) - 1][size];

        if (in[num] < last_position) tmp[size++] = dictionary[in[num]][0];
        else tmp[size++] = out[(*index) - 1][0];

        if (Find(dictionary, last_position, tmp, size) == -1) {
            for (int i = 0; i < size; ++i) dictionary[last_position][i] = tmp[i];
            last_position++;
        }

        for (int i = 0; i < size_word; ++i) {
            out[*index][i] = dictionary[in[num]][i];
        }
        (*index)++;
    }
    return out;
}


void Compress2(char filename[], int size_enc, int enc[]) {
    int byte = 0, count = 0, tmp = 0, tmp_len = 0;
    int type = 0;
    int mask = 0, result = 0;
    FILE *encode_write = fopen(filename, "wb");
    for (int i = 0; i < size_enc; ++i) {
        if (enc[i] == 0) { type = CountZero(enc[i + 1]); }
        tmp = enc[i];
        tmp_len = type;

//        printf("\n\ntype - %d new_tmp - %d - ", type, tmp);
//        Print(tmp, 32);

        while (tmp_len != 0) {
//            printf("count - %d byte - ", count);
//            Print(byte, count);
//            printf("tmp_type - %d temp - ", tmp_len);
//            Print(tmp, tmp_len);

            mask = CreateMask(0, tmp_len - 1);
            result = mask & tmp;
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

//            printf("end_byte - ");
//            Print(byte, count);
//            printf("%d %d\n", tmp_len, count);

            if (count == 8) {
                fputc(byte, encode_write);
//                printf("output - ");
//                Print(byte, 8);
                count = 0;
                byte = 0;
            }
        }
    }
    byte <<= 8 - count;
    fputc(byte, encode_write);
//    printf("output - ");
//    Print(byte, 8);

//    free (enc);
    fclose(encode_write);
}


int *Decompress2(char filename[], int *size_dec) {
    int type = 1, num = 0;
    int byte = 0, tmp = 0, count = 0;
    int result = 0, mask = 0;

    FILE *encode_read = fopen(filename, "rb");
    fseek(encode_read, 0, SEEK_END);
    int enc_size = ftell(encode_read);
    fseek(encode_read, 0, SEEK_SET);

    int *dec = calloc(enc_size, sizeof(int));

    while (num++ <= enc_size) {
        byte = fgetc(encode_read);
//        printf("type - %d\nbyte - ", type);
//        Print(byte, 8);

        tmp <<= 8;
        mask = CreateMask(0, 7);
        tmp += mask & byte;
        count += 8;
//        printf("count - %d tmp - ", count);
//        Print(tmp, count);

        while (count > type) {
            mask = CreateMask(count - type, count - 1);
            result = mask & tmp;
            result >>= count - type;

            if (result == 0) {
                while (result == 0 && type != count + 1) {
                    type++;
                    mask = CreateMask(count - type, count - 1);
                    result = mask & tmp;
                    result >>= count - type;
                }
                type--;
                result >>= 1;
//                printf("new type - %d\n", type);
            }

//            Print(result, type);
//            printf("RESULT = %d\n", result);
            if (result != 0) dec[(*size_dec)++] = result;

            count -= type;
//            printf("count - %d tmp_end - ", count);
//            Print(tmp, count);
        }
//        printf("\n");
    }
//    printf("type - %d\nend - ", type);
//    Print(byte, 32);

    fclose(encode_read);
    return dec;
}


int main() {
    FILE *original_read = fopen("../files/old_file.txt", "rb");

    int size_enc = 0;
    int *enc1 = Compress1(original_read, &size_enc);    /// compress 1 method
    for (int i = 0; i < size_enc; ++i) printf("%d ", enc1[i]);

    int *enc2 = Analysis(&size_enc, enc1);
    free(enc1);

    Compress2("../files/encode.txt", size_enc, enc2);

    free(enc2);

    /*-------------------------------------------------------------------------*/

    int size_dec = 0;
    int *dec = Decompress2("../files/encode.txt", &size_dec);

    printf("\n\n");
    for (int i = 0; i < size_dec; ++i) printf("%d ", dec[i]);
    printf("\n\n");

    int size_dec1 = 0;
    int **dec1 = Decompress1(dec, size_dec, &size_dec1); /// decompres 1 method

    free(dec);

    Output("../files/new_file.txt", dec1);

    free(dec1);
    return 0;
}