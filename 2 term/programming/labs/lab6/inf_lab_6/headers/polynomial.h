#ifndef INF_LAB_6_POLYNOMIAL_H
#define INF_LAB_6_POLYNOMIAL_H

#include "../headers/term.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <regex>

using namespace std;

class Polynomial {
public:
    Polynomial();
    Polynomial(int c);
    Polynomial(const Term &t);
    Polynomial(const std::vector<Term> &terms);
    Polynomial(const Polynomial &other);

    Polynomial &operator=(const Polynomial &other);
    Polynomial &operator+=(const Polynomial &other);
    Polynomial &operator*=(const Polynomial &other);
    Polynomial &operator+=(const Term &term);

    friend std::ostream &operator<<(std::ostream &os, const Polynomial &p);
    friend std::istream &operator>>(std::istream &in, Polynomial &poly);

    friend Polynomial operator+(const Polynomial &lhs, const Polynomial &rhs);
    friend Polynomial operator*(const Polynomial &lhs, const Polynomial &rhs);

    enum class Order {
        ASCENDING, DESCENDING
    };

    void setOrder(Order order);
    static const int MAX_TERMS = 6;
    std::vector<Term> poly;
    int degree;
    Order order;

    void sortTerms();
};

Polynomial::Polynomial() : degree(0), order(Order::DESCENDING) {}

Polynomial::Polynomial(int c) : degree(c == 0 ? -1 : 0), order(Order::DESCENDING) {
    if (c != 0) {
        poly.emplace_back(c);
    }
}

Polynomial::Polynomial(const Term &t) : degree(t.power), order(Order::DESCENDING) {
    if (t.coefficient != 0) {
        poly.push_back(t);
    } else {
        degree = -1;
    }
}

Polynomial::Polynomial(const std::vector<Term> &terms) : degree(-1), order(Order::DESCENDING) {
    for (auto &t: terms) {
        if (t.coefficient != 0) {
            poly.push_back(t);
            degree = std::max(degree, t.power);
        }
    }
    sortTerms();
}

Polynomial::Polynomial(const Polynomial &other) : degree(other.degree), order(other.order) {
    std::copy(other.poly.begin(), other.poly.end(), std::back_inserter(poly));
}

Polynomial &Polynomial::operator=(const Polynomial &other) {
    if (&other != this) {
        poly.clear();
        std::copy(other.poly.begin(), other.poly.end(), std::back_inserter(poly));
        degree = other.degree;
        order = other.order;
    }

    return *this;
}

Polynomial &Polynomial::operator+=(const Polynomial &other) {
    for (auto &t: other.poly) {
        *this = *this + Polynomial(t);
    }

    return *this;
}

Polynomial &Polynomial::operator*=(const Polynomial &other) {
    Polynomial result;
    for (auto &t1: poly) {
        for (auto &t2: other.poly) {
            result += Polynomial(Term(t1.coefficient * t2.coefficient, t1.power + t2.power));
        }
    }
    *this = result;

    return *this;
}

Polynomial &Polynomial::operator+=(const Term &term) {
    *this += Polynomial(term);
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Polynomial &p) {
    if (p.poly.empty()) {
        os << "0";
        return os;
    }

    bool first_term = true;
    for (auto &t: p.poly) {
        if (t.coefficient == 0) {
            continue;
        }

        if (!first_term && t.coefficient > 0) {
            os << "+";
        }

        if (t.coefficient == 0) {
            os << "0";
        } else if (t.power == 0) {
            os << t.coefficient;
        } else if (t.coefficient == 1) {
            os << "x";
            if (t.power != 1) {
                os << "^" << t.power;
            }
        } else if (t.coefficient == -1) {
            os << "-x";
            if (t.power != 1) {
                os << "^" << t.power;
            }
        } else {
            os << t.coefficient << "x";
            if (t.power != 1) {
                os << "^" << t.power;
            }
        }

        first_term = false;
    }

    if (first_term) {
        os << "0";
    }

    return os;
}


Polynomial operator+(const Polynomial &lhs, const Polynomial &rhs) {
    Polynomial result;
    std::vector<Term> left_terms(lhs.poly);
    std::vector<Term> right_terms(rhs.poly);
    while (!left_terms.empty() && !right_terms.empty()) {
        if (lhs.order == Polynomial::Order::ASCENDING) {
            if (left_terms.back().power < right_terms.back().power) {
                result.poly.push_back(right_terms.back());
                right_terms.pop_back();
            } else if (left_terms.back().power > right_terms.back().power) {
                result.poly.push_back(left_terms.back());
                left_terms.pop_back();
            } else {
                result.poly.push_back(left_terms.back() + right_terms.back());
                left_terms.pop_back();
                right_terms.pop_back();
            }
        } else {
            if (left_terms.back().power > right_terms.back().power) {
                result.poly.push_back(left_terms.back());
                left_terms.pop_back();
            } else if (left_terms.back().power < right_terms.back().power) {
                result.poly.push_back(right_terms.back());
                right_terms.pop_back();
            } else {
                result.poly.push_back(left_terms.back() + right_terms.back());
                left_terms.pop_back();
                right_terms.pop_back();
            }
        }
    }
    while (!left_terms.empty()) {
        result.poly.push_back(left_terms.back());
        left_terms.pop_back();
    }
    while (!right_terms.empty()) {
        result.poly.push_back(right_terms.back());
        right_terms.pop_back();
    }
    result.sortTerms();
    return result;
}

Polynomial operator*(const Polynomial &lhs, const Polynomial &rhs) {
    Polynomial result;
    for (auto &t1: lhs.poly) {
        for (auto &t2: rhs.poly) {
            result += Polynomial(Term(t1.coefficient * t2.coefficient, t1.power + t2.power));
        }
    }
    result.sortTerms();
    return result;
}

void Polynomial::sortTerms() {
    if (order == Order::ASCENDING) {
        std::sort(poly.begin(), poly.end(), [](const Term &a, const Term &b) { return a.power < b.power; });
    } else {
        std::sort(poly.begin(), poly.end(), [](const Term &a, const Term &b) { return a.power > b.power; });
    }
}

void Polynomial::setOrder(Order order) {
    if (this->order != order) {
        this->order = order;
        sortTerms();
    }
}

istream &operator>>(istream &in, Polynomial &p) {
    char buff[100];
    cin.getline(buff, 100, '\n');
    int s = strlen(buff);

    int sign = 1;
    int currNum = 0;
    bool x_flag = false;

    Term t;

    bool finded = false;

    if (buff[0] == 'x' || (buff[0] == '-' && buff[1] == 'x'))
        currNum = 1;
    for (int i = 0; i <= s; i++) {


        if (buff[i] >= '0' && buff[i] <= '9')
            currNum = currNum * 10 + (buff[i] - '0');

        if (buff[i] == 'x') {
            if (i > 0 && buff[i - 1] >= '0' && buff[i - 1] <= '9') {
                t.coefficient = currNum * sign;
            } else {
                t.coefficient = 1 * sign;
            }
            finded = true;
            currNum = 0;
            sign = 1;
        }

        if (buff[i] == '-' || buff[i] == '+' || buff[i] == '\0') {
            if (!finded) {
                t.power = 0;
                t.coefficient = currNum * sign;
            } else {
                t.power = currNum * sign;
            }
            p += t;

            std::cout << "New term: " << t << '\n';


            finded = false;
            sign = 1;
            t.power = 0;
            t.coefficient = 0;
            currNum = 0;
        }

        if (buff[i] == '-')
            sign = -sign;

    }
    return in;

}

#endif //INF_LAB_6_POLYNOMIAL_H
