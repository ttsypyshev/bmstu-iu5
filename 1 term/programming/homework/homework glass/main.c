/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int count1 = 0, count2 = 0, count3 = 0, a1 = 0, a2 = 0, k = 50;
    for (int i = 0; i < k; ++i) {
        int position = rand() % 3; // we put the ball randomly in 1,2 or 3 cups
        if (position == 0) { // check where the ball is located
            ++count1;
            ++a1;
        } else if (position == 1) {
            ++count2;
            ++a2;
        } else ++count3;
    }

    printf("Put the ball in the cup %d times\n", k);
    printf("\n\tAnalysis of results: \n");
    printf("The ball was in 1 cup %d time(s)\n", count1);
    printf("The ball was in 2 cup %d time(s)\n", count2);
    printf("The ball was in 3 cup %d time(s)\n", count3);
    printf("\n\tOutput: \n");
    printf("According to statistics, it takes %d opening for %d iterations to detect the ball.\n", a1 > a2 ? 1 : 2, k);

    return 0;
}