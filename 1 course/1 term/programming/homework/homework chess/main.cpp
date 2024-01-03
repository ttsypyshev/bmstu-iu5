#include <iostream>

using namespace std;

#define recursion_depth 10 //can be reduced to reduce the load (~5)
int x1, y1, x2, y2;
uint64_t min_log = 10 * recursion_depth; //the shortest sequence is stored in this variable

void OutputActions(int log) { //the function outputs the values of the coordinates of the horse
    while (log > 0) {
        if (log % 10 == 1) {
            x2 -= 2;
            y2 -= 1;
        } else if (log % 10 == 2) {
            x2 -= 2;
            y2 += 1;
        } else if (log % 10 == 3) {
            x2 += 2;
            y2 -= 1;
        } else if (log % 10 == 4) {
            x2 += 2;
            y2 += 1;
        } else if (log % 10 == 5) {
            x2 -= 1;
            y2 -= 2;
        } else if (log % 10 == 6) {
            x2 += 1;
            y2 -= 2;
        } else if (log % 10 == 7) {
            x2 -= 1;
            y2 += 2;
        } else if (log % 10 == 8) {
            x2 += 1;
            y2 += 2;
        }
        cout << "  ^       ^\n";
        cout << "x = " << x2 << "   y = " << y2 << "\n";
        log /= 10;
    }
}


int f(int x1, int y1, int x2, int y2, int log, int iter) { //recursive function
    if (x1 == x2 & y1 == y2) { //if the horse hit the target
        if (log < min_log) min_log = log;
    } else if (iter >= recursion_depth) { //recursion limitation
        return -1;
    } else {
        if (x1 + 2 <= 8 & y1 + 1 <= 8) f(x1 + 2, y1 + 1, x2, y2, log * 10 + 1, iter + 1); //1
        if (x1 + 2 <= 8 & y1 - 1 >= 0) f(x1 + 2, y1 - 1, x2, y2, log * 10 + 2, iter + 1); //2

        if (x1 - 2 >= 0 & y1 + 1 <= 8) f(x1 - 2, y1 + 1, x2, y2, log * 10 + 3, iter + 1); //3
        if (x1 - 2 >= 0 & y1 - 1 >= 0) f(x1 - 2, y1 - 1, x2, y2, log * 10 + 4, iter + 1); //4

        if (y1 + 2 <= 8 & x1 + 1 <= 8) f(x1 + 1, y1 + 2, x2, y2, log * 10 + 5, iter + 1); //5
        if (y1 + 2 <= 8 & x1 - 1 >= 0) f(x1 - 1, y1 + 2, x2, y2, log * 10 + 6, iter + 1); //6

        if (y1 - 2 >= 0 & x1 + 1 <= 8) f(x1 + 1, y1 - 2, x2, y2, log * 10 + 7, iter + 1); //7
        if (y1 - 2 >= 0 & x1 - 1 >= 0) f(x1 - 1, y1 - 2, x2, y2, log * 10 + 8, iter + 1); //8
    }
}

int main() {
    cout << "Enter the coordinates of the hores (x & y):";
    cin >> x1 >> y1;
    cout << "Enter the coordinates of the target (x & y):";
    cin >> x2 >> y2;

    f(x1, y1, x2, y2, 0, 0);
    if (min_log != 10 * recursion_depth) { //if a sequence is found
        cout << "\nCoordinates of the horse's movement:\n";
        cout << "x = " << x2 << "   y = " << y2 << "\n";
        OutputActions(min_log);
    } else cout << "The horse will never defeat the target";
    //otherwise, we write that the horse will never defeat the goal
    return 0;
}
