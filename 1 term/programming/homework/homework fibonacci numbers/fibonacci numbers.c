#include <stdio.h>

int main() {
    printf("0.000000\n1.000000\n");
    double i=2, a=0, b=1, z;
    while (i<100) {
        z = b;
        b += a;
        a = z;
        i++;
        printf("%lf\n",b);
    }
    return 0;
}