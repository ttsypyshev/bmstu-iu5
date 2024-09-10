#include "../headers/term.h"
#include "../headers/polynomial.h"

#include <iostream>

int main() {
    Term t1(3);
    cout << "3x^0 = " << t1 << endl;

    t1.power = 1;
    cout << "3x^1 = " << t1 << endl;

    t1.coefficient = 1;
    t1.power = 3;
    cout << "1x^3 = " << t1 << endl;

    t1.coefficient = -3;
    t1.power = 2;
    cout << "-3x^2 = " << t1 << endl;

    Term t2;
    cout << "Initialization without args = " << t2 << endl;

    t2.coefficient = 6;
    t2.power = 2;
    cout << "-3x^2 + 6x^2 = " << t2 + t1 << endl;


    Term t3;
    cout << "Enter term #3\n";
    cin >> t3;
    cout << t3 << endl;

    Term t4;
    cout << "Enter term #4\n";
    cin >> t4;
    cout << t4 << endl;


    cout << "5x^5 - 4x^3 + 1x^2 + 0x^1 - 7x^0\n";
    Polynomial p(Term(5, 5));
    p += Term(-7);
    p += Term(0, 1);
    p += Term(-4, 3);
    p += Term(1, 2);
    cout << p << endl;

    Polynomial p2(Term(3, 2));
    p2 += Term(-1, 1);
    cout << "Polynom #1: " << p << endl;
    cout << "Polynom #2: " << p2 << endl;
    cout << "Their product: " << p * p2 << endl;
    cout << "Their sum: " << p + p2 << endl;

    cout << "Enter Polynom #3: ";
    Polynomial p3;
    cin.ignore();
    cin >> p3;
    cout << "Polynom #3: " << p3 << endl;
    cout << "Enter Polynom #4: ";
    Polynomial p4;
    cin >> p4;
    cout << "Polynom #4: " << p4 << endl;
    cout << "Their product: " << p3 * p4 << endl;
    cout << "Their sum: " << p3 + p4 << endl;

    return 0;
}