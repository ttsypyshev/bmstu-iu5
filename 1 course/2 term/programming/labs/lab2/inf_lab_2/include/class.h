/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#ifndef INF_LAB_2_CLASS_H
#define INF_LAB_2_CLASS_H

#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>

class Statement {
private:
    char *name;
    unsigned type;
    bool status;
    unsigned estimation;
public:
    Statement() {
        name = new char[1];
        strcpy(name, "");
        type = 0;
        status = false;
        estimation = 0;
    }

    Statement(char *name_, unsigned type_, bool status_, unsigned estimation_) {
        name = new char[strlen(name_) + 1];
        strcpy(name, name_);
        type = type_;
        status = status_;
        estimation = estimation_;
    }

    Statement(Statement &other) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        type = other.type;
        status = other.status;
        estimation = other.estimation;
    }

    ~Statement() { delete[] name; }

    Statement &operator=(Statement &other) {
        if (this != &other) {
            delete[] name;
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
            type = other.type;
            status = other.status;
            estimation = other.estimation;
        }
        return *this;
    }

    friend std::istream &operator>>(std::istream &input, Statement &statement) {
        char *name_ = new char[256];
        input >> name_ >> statement.type >> statement.status >> statement.estimation;
        statement.set_name(name_);
        delete[] name_;
        return input;
    }

    friend std::ostream &operator<<(std::ostream &output, const Statement &statement) {
        output << "|" << std::setw(16) << statement.name
               << "|" << std::setw(10) << statement.type
               << "|" << std::setw(8) << statement.status
               << "|" << std::setw(12) << statement.estimation
               << "|\n";
        return output;
    }

    friend std::ifstream &operator>>(std::ifstream &input, Statement &statement) {
        char *name_ = new char[256];
        input >> name_ >> statement.type >> statement.status >> statement.estimation;
        statement.set_name(name_);
        delete[] name_;
        return input;
    }

    friend std::ofstream &operator<<(std::ofstream &output, const Statement &statement) {
        output << statement.name << " " << statement.type << " " << statement.status << " " << statement.estimation;
        return output;
    }

    friend bool operator<(const Statement &statement1, const Statement &statement2) {
        return statement1.type < statement2.type;
    }

    friend bool operator==(const Statement &statement1, const Statement &statement2) {
        return statement1.type == statement2.type;
    }

    char *get_name() const { return name; }
    unsigned get_type() const { return type; }
    bool get_status() const { return status; }
    unsigned get_estimation() const { return estimation; }

    void set_name(const char *name_) {
        delete[] name;
        size_t len = strlen(name_) + 1;
        name = new char[len];
        strcpy_s(name, len, name_);
    }
    void set_type(unsigned type_) { type = type_; }
    void set_status(bool status_) { status = status_; }
    void set_estimation(unsigned estimation_) { estimation = estimation_; }
};

#endif //INF_LAB_2_CLASS_H
