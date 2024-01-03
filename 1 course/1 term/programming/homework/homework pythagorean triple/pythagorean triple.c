#include <stdio.h>

int main() {
    int x,y,z;
    for (x = 1; x<100; x++){
        for (y = x; y<100; y++){
            for (z = y; z<100; z++){
                if (x*x+y*y==z*z) {
                  printf("x=%d y=%d z=%d\n",x,y,z);
                }
            }
        }
    }
    return 0;
}