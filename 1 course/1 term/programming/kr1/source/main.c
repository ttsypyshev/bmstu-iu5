/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

///The main file is intended for data input/output and task invocation
///All calculations are made in files: "Task1.c" "Task2.c" "Task3.c"
///2 task is divided into 3 subtasks, so there are 3 functions in the file "Task2.c"
///In the 3rd task, the conditions are not very clear to me, so I divided it into 3 and 4:
/// - In the third task, the user himself enters the value of X
/// - In the fourth task, iteration of X values is implemented according to the condition |x| >= 2 (there is a limit of + - 1000 with a step of 0.1)
///All function prototypes are in a common file: "all_task.h" (~/include/all_task.h)

#include <stdio.h>
#include "../include/all_tasks.h"

int main() {
    int num_task = 0; //task number
    printf("Enter task number (1-4): ");
    scanf("%d", &num_task);

    if (num_task == 1) { //task 1
        printf("\n--- N1 ---\n");
        int size; //array length
        printf("\nEnter the length of the array: ");
        scanf("%d", &size);
        int arr[size]; //array
        printf("\nEnter array elements: ");
        for (size_t i = 0; i < size; ++i) scanf("%d", &arr[i]);


        int result = Task1(arr, size); //I call 1 function for 1 task
        printf("\nMultiplication = %d\n\n", result);

    } else if (num_task == 2) { //task 2
        printf("\n--- N2.1 ---\n");
        int *x1, y1, z1, a, b; // x y z [a,b]
        printf("\nEnter x, y, z, a, b values: ");
        scanf("%d%d%d%d%d", &x1, &y1, &z1, &a, &b);
        Task2_1(&x1, &y1, &z1, a, b); //I call 1 function for 2 task (it herself changes the value of x, y, z)
        printf("x = %d   y = %d   z = %d\n", x1, y1, z1);

        printf("\n--- N2.2 ---\n");
        int x2, y2, z2; // x y z
        printf("\nEnter x, y, z values: ");
        scanf("%d%d%d", &x2, &y2, &z2);
        double result2 = Task2_2(x2, y2, z2); //I call 2 function for 2 task (it outputs the value of b)
        printf("\nb = %lf\n", result2);

        printf("\n--- N2.3 ---\n");
        int x3; // x
        char days[][12] = { //dictionary with the names of the days of the week (0-6)
                "Monday", "Tuesday", "Wednesday", "Thursday",
                "Friday", "Saturday", "Sunday"
        };
        printf("\nEnter x value: ");
        scanf("%d", &x3);
        int result3 = Task2_3(x3); //I call 3 function for 2 task (it returns the numeric number of the day of the week)
        printf("\n%d - %s\n\n", result3, days[result3]); //the number corresponds to the day of the week from the "days"

    } else if (num_task == 3) { //task 3 (manual input)
        printf("\n--- N3 ---\n");
        double x;
        printf("\nEnter x value: ");
        scanf("%lf", &x);
        if (x <= -2 || x >= 2) { // |x|>=2
            double result = Task3(x);
            printf("\nx = %lf   s = %lf\n\n", x, result); //output in the format: x = ...   s = ...
        } else { printf("Data isn't correct"); }

    } else if (num_task == 4) { //task 3 (enumeration of x values)
        printf("\n--- N3(|x|>=2) ---\n");
        double result;

        for (double x = -1000.0; x < -1.9; x += 0.1) { // (-inf, -2]
            result = Task3(x);
            printf("x = %lf\ns = %lf\n\n", x, result);
        }
        for (double x = 2.0; x < 1001; x += 0.1) { // [2, inf)
            result = Task3(x);
            printf("x = %lf\ns = %lf\n\n", x, result);
        }

    } else { //if there is no such number
        fputs("Error: incorrect data entered", stderr);
    }

    return 0;
}
