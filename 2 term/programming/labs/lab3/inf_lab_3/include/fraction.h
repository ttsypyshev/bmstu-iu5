/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#ifndef INF_LAB_2_FRACTION_H
#define INF_LAB_2_FRACTION_H

#include <iostream>
#include <cstring>
#include <cmath>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

class fraction {
private:
    bool sign;
    unsigned integer, numerator, denominator;
public:
    fraction() {
        sign = false;
        integer = 0;
        numerator = 0;
        denominator = 1;
    }

    fraction(unsigned numerator_, unsigned denominator_, bool sign_ = false, unsigned integer_ = 0) {
        sign = sign_;
        integer = integer_ + numerator_ / denominator_;
        int divisor = gcd(numerator_, denominator_);
        numerator = numerator_ / divisor;
        denominator = denominator_ / divisor;
    }

    fraction(const char *input) {
        if (input[0] == '-') {
            sign = true;
            ++input;
        } else {
            sign = false;
        }

        const char *dot = strchr(input, ' ');
        const char *slash = strchr(input, '/');
        if (dot != nullptr) {
            integer = atoi(input);
            input = dot + 1;
        } else if (slash == nullptr) {
            integer = atoi(input);
        } else {
            integer = 0;
        }

        if (slash != nullptr) {
            unsigned numerator_ = atoi(input), denominator_ = atoi(slash + 1);
            integer += numerator_ / denominator_;
            int divisor = gcd(numerator_, denominator_);
            numerator = numerator_ / divisor;
            denominator = denominator_ / divisor;

        } else {
            numerator = 0;
            denominator = 1;
        }
    }

    fraction(const double decimal) {
        sign = decimal < 0 ? true : false;
        double abs_num = std::abs(decimal);
        int whole_part = static_cast<int>(abs_num);
        double fractional_part = abs_num - whole_part;
        int numerator_ = static_cast<int>(fractional_part * 1000000);
        int denominator_ = 1000000;
        int divisor = gcd(numerator_, denominator_);
        integer = whole_part;
        numerator = numerator_ / divisor;
        denominator = denominator_ / divisor;
    }

    fraction(const int decimal) {
        sign = decimal < 0 ? true : false;
        integer = abs(decimal);
        numerator = 0;
        denominator = 1;
    }

    fraction(const fraction &item) {
        sign = item.sign;
        integer = item.integer;
        numerator = item.numerator;
        denominator = item.denominator;
    }

    friend std::istream &operator>>(std::istream &input, fraction &item) {
        unsigned tmp = 0, integer_ = 0, numerator_ = 0, denominator_ = 1;

        if (input.peek() == '-') {
            input.ignore();
            item.sign = true;
        } else {
            item.sign = false;
        }

        input >> tmp;
        if (input.peek() == '\n' || input.eof()) integer_ = tmp;
        else {
            if (input.peek() == ' ') {
                integer_ = tmp;
                input.ignore();
                input >> tmp;
            }
            numerator_ = tmp;
            input.ignore();
            input >> denominator_;
        }

        int divisor = gcd(numerator_ % denominator_, denominator_);
        item.integer += integer_ + numerator_ / denominator_;
        item.numerator = (numerator_ % denominator_) / divisor;
        item.denominator = denominator_ / divisor;
        return input;
    }

    friend std::ostream &operator<<(std::ostream &output, const fraction &item) {
        if (item.sign && item.denominator != 0) output << '-';
        if (item.integer != 0) output << item.integer << ' ';
        if (item.numerator != 0) output << item.numerator << '/' << item.denominator;
        if (item.integer == 0 && item.numerator == 0) output << '0';
        return output;
    }

    fraction operator+(const fraction &other) const {
        fraction result;
        int numerator_ = 0, denominator_ = 0;
        if (numerator == 0 && other.numerator == 0) {
            result.integer = abs(integer * (sign ? -1 : 1) + other.integer * (other.sign ? -1 : 1));
            result.sign = sign == other.sign ? false : true;
            result.numerator = 0;
            result.denominator = 1;
        } else {
            if (numerator == 0) {
                numerator_ = integer * other.denominator * (sign ? -1 : 1) +
                             (other.integer * other.denominator + other.numerator) * (other.sign ? -1 : 1);
                denominator_ = other.denominator;
                result.sign = numerator_ < 0 ? true : false;
                result.integer = abs(numerator_) / denominator_;
            } else if (other.numerator == 0) {
                numerator_ = (integer * denominator + numerator) * (sign ? -1 : 1) +
                             other.integer * denominator * (other.sign ? -1 : 1);
                denominator_ = denominator;
                result.sign = numerator_ < 0 ? true : false;
                result.integer = abs(numerator_) / denominator_;
            } else {
                numerator_ = (integer * denominator + numerator) * other.denominator * (sign ? -1 : 1) +
                             (other.integer * other.denominator + other.numerator) * denominator *
                             (other.sign ? -1 : 1);
                denominator_ = denominator * other.denominator;
                result.sign = numerator_ < 0 ? true : false;
                result.integer = abs(numerator_) / denominator_;
            }
            int divisor = gcd(abs(numerator_) % denominator_, denominator_);
            result.numerator = (abs(numerator_) % denominator_) / divisor;
            result.denominator = denominator_ / divisor;
        }
        return result;
    }

    friend fraction operator+(const fraction &fraction, double decimal) {
        class fraction other(decimal);
        return fraction + other;
    }

    friend fraction operator+(const fraction &fraction, int integer) {
        class fraction other = integer;
        return fraction + other;
    }

    friend fraction operator+(double decimal, const fraction &fraction) {
        class fraction other = decimal;
        return fraction + other;
    }

    friend fraction operator+(int integer, const fraction &fraction) {
        class fraction other = integer;
        return fraction + other;
    }

    fraction operator+=(const fraction &other) {
        int numerator_ = 0, denominator_ = 0;
        if (numerator == 0 && other.numerator == 0) {
            integer = abs(integer * (sign ? -1 : 1) + other.integer * (other.sign ? -1 : 1));
            sign = sign == other.sign ? false : true;
            numerator = 0;
            denominator = 1;
        } else {
            if (numerator == 0) {
                numerator_ = integer * other.denominator * (sign ? -1 : 1) +
                             (other.integer * other.denominator + other.numerator) * (other.sign ? -1 : 1);
                denominator_ = other.denominator;
                sign = numerator_ < 0 ? true : false;
                integer = abs(numerator_) / denominator_;
            } else if (other.numerator == 0) {
                numerator_ = (integer * denominator + numerator) * (sign ? -1 : 1) +
                             other.integer * denominator * (other.sign ? -1 : 1);
                denominator_ = denominator;
                sign = numerator_ < 0 ? true : false;
                integer = abs(numerator_) / denominator_;
            } else {
                numerator_ = (integer * denominator + numerator) * other.denominator * (sign ? -1 : 1) +
                             (other.integer * other.denominator + other.numerator) * denominator *
                             (other.sign ? -1 : 1);
                denominator_ = denominator * other.denominator;
                sign = numerator_ < 0 ? true : false;
                integer = abs(numerator_) / denominator_;
            }
            int divisor = gcd(abs(numerator_) % denominator_, denominator_);
            numerator = (abs(numerator_) % denominator_) / divisor;
            denominator = denominator_ / divisor;
        }
        return *this;
    }

    fraction operator+=(const int integer) {
        fraction other(integer);
        *this += other;
        return *this;
    }

    fraction operator+=(const double decimal) {
        fraction other(decimal);
        *this += other;
        return *this;
    }

};

#endif //INF_LAB_2_FRACTION_H