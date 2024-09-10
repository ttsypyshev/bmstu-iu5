#ifndef INF_LAB_6_TERM_H
#define INF_LAB_6_TERM_H

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

class Term {
public:
    int coefficient;
    int power;

    Term() : coefficient(0), power(0) {}
    Term(int c) : coefficient(c), power(0) {}
    Term(int c, int p) : coefficient(c), power(p) {}

    friend Term operator+(const Term &t1, const Term &t2);
    friend Term operator-(const Term &t1, const Term &t2);
    friend Term operator*(const Term &t1, const Term &t2);

    friend std::istream &operator>>(std::istream &is, Term &term);
    friend std::ostream &operator<<(std::ostream &os, const Term &term);

    int getCoefficient() const { return coefficient; }
    int getPower() const { return power; }
};

Term operator+(const Term &t1, const Term &t2) {
    if (t1.power != t2.power) throw std::invalid_argument("Terms must have the same power");
    return Term(t1.coefficient + t2.coefficient, t1.power);
}

Term operator-(const Term &t1, const Term &t2) {
    if (t1.power != t2.power) throw std::invalid_argument("Terms must have the same power");
    return Term(t1.coefficient - t2.coefficient, t1.power);
}

Term operator*(const Term &t1, const Term &t2) {
    return Term(t1.coefficient * t2.coefficient, t1.power + t2.power);
}

std::istream &operator>>(std::istream &is, Term &term) {
    char ch, sign = '+', sign_exp = '+';
    int coeff = 0, power = 0;
    is >> std::skipws;

    is.get(ch);
    if (ch == '-') {
        sign = '-';
        is.get(ch);
    }

    while (isdigit(ch)) {
        coeff = coeff * 10 + (ch - '0');
        is.get(ch);
    }

    if (coeff == 0)
        coeff = sign == '+' ? 1 : -1;
    else
        coeff *= sign == '+' ? 1 : -1;

    if (ch == 'x') {
        is.get(ch);

        if (ch == '^') {
            is >> std::skipws;
            is.get(ch);

            if (ch == '-') {
                sign_exp = '-';
                is.get(ch);
            }

            while (isdigit(ch)) {
                power = power * 10 + (ch - '0');
                is.get(ch);
            }

            power *= sign_exp == '+' ? 1 : -1;

        } else {
            power = 1;
        }
    } else {
        power = 0;
    }

    if (!is.eof())
        is.unget();

    term.coefficient = coeff;
    term.power = power;

    return is;
}

std::ostream &operator<<(std::ostream &os, const Term &term) {
    if (term.power == 0) {
        os << term.coefficient;
    } else if (term.power == 1) {
        if (term.coefficient == 1) {
            os << "x";
        } else if (term.coefficient == -1) {
            os << "-x";
        } else {
            os << term.coefficient << "x";
        }
    } else {
        if (term.coefficient == 1) {
            os << "x^" << term.power;
        } else if (term.coefficient == -1) {
            os << "-x^" << term.power;
        } else {
            os << term.coefficient << "x^" << term.power;
        }
    }

    return os;
}


#endif //INF_LAB_6_TERM_H
