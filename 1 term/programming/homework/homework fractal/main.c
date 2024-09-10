/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include <stdio.h>

// sum = (previous significant vertices * 3) + (previous significant vertices * 2 + previous insignificant vertices)
//        \_______________________________/    \_________________________________________________________________/
//                       |                                                      |
//             new significant vertices                             new insignificant vertices
//
// depth = 0 - 1 vertices  why doesn't it work here? (27-3=24 9-3=6 3-3=0 1-3=-2 hmm, it turns out a negative number of vertices, and this can not be)
// depth = 1 - 3 vertices  therefore, we take a triangle (that is, 3 significant vertices and 0 insignificant vertices) as the "origin"
// depth = 2   sum = (3 * 3) + (3 * 2 + 0)
// depth = 3   sum = (9 * 3) + (9 * 2 + 6)
// depth = 4   sum = (27 * 3) + (27 * 2 + 24)

int main() {
    int significant_vertices = 3, insignificant_vertices = 0, depth = 10;
//    printf("Enter the fractal depth:\n");
//    scanf("%d", &depth);
    for (int i = 1; i < depth + 1; ++i) {
        insignificant_vertices += significant_vertices * 2;
        significant_vertices *= 3;
        printf("iter = %d   vertices = %d   significant_vertices = %d   insignificant_vertices = %d\n", i,
               significant_vertices + insignificant_vertices, significant_vertices, insignificant_vertices);
    }
    return 0;
}
