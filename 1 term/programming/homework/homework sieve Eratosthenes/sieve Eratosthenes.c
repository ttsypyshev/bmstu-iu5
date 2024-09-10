#include <stdio.h>

int main() {
    int arr[100];
    for (int i = 0; i < 100; i++) {arr[i] = i;}

    for (int i1 = 2; i1 < 100; i1++){
        if (arr[i1] != 0){
            printf("%d\n",arr[i1]);
            for (int i2 = i1*i1; i2 < 100; i2 += i1) {arr[i2] = 0;}
        }
    }
    return 0;
}