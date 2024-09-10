/// Copyright 2023 ttsypyshev <ttsypyshev01@gmail.com>

#include <iostream>
#include <string>
#include <typeinfo>

class printed_edition {
protected:
    std::string title;
    int num_pages;
    int index;

    static int current_index; // текущий индекс в списке
    static printed_edition *begin; // указатель на начало списка
    printed_edition *next; // указатель на следующий элемент

public:
    printed_edition(const printed_edition &other)
            : title(other.title), num_pages(other.num_pages), index(current_index) {
        next = nullptr;
    }

    printed_edition(std::string t = "Untitled", int n = 0)
            : title(t), num_pages(n), index(current_index) {
        next = nullptr;
    }

    virtual ~printed_edition() {
        if (this == begin) {
            begin = this->next;
        } else {
            printed_edition *p = begin;
            while (p != nullptr && p->next != this) {
                p = p->next;
            }
            if (p != nullptr) {
                p->next = this->next;
            }
        }
    }

    printed_edition &operator=(const printed_edition &other) {
        if (&other == this) {
            return *this;
        }

        title = other.title;
        num_pages = other.num_pages;
        index = current_index;
        next = nullptr;

        return *this;
    }

    virtual void Show(){
        std::cout << "Index: " << index << std::endl;
        std::string name_type = typeid(*this).name();
        std::cout << "Type: " << name_type.substr(1) << std::endl;
        std::cout << "Title: " << title << std::endl;
        std::cout << "Number of pages: " << num_pages << std::endl;
    }

    void Add() {
        if (begin == nullptr) {
            begin = this;
        } else {
            printed_edition *p = begin;
            while (p->next != nullptr) {
                p = p->next;
            }
            p->next = this;
        }
        current_index++;
    }

    static void Print() {
        printed_edition *p = begin;
        while (p != nullptr) {
            p->Show();
            std::cout << std::endl;
            p = p->next;
        }
    }
};

int printed_edition::current_index = 1;
printed_edition *printed_edition::begin = nullptr;

class magazine : public printed_edition {
protected:
    std::string publisher;
    int issue_number;

public:
    magazine(std::string t = "Untitled", int n = 0, std::string p = "Unknown", int i = 0)
            : printed_edition(t, n), publisher(p), issue_number(i) { Add(); }

    ~magazine() {}

    void Show() override {
        printed_edition::Show();
        std::cout << "Publisher: " << publisher << std::endl;
        std::cout << "Issue number: " << issue_number << std::endl;
    }
};

class book : public printed_edition {
protected:
    std::string author;

public:
    book(std::string t = "Untitled", int n = 0, std::string a = "Unknown")
            : printed_edition(t, n), author(a) { Add(); }

    ~book() {}

    void Show() override {
        printed_edition::Show();
        std::cout << "Author: " << author << std::endl;
    }
};

class textbook : public printed_edition {
protected:
    std::string subject;

public:
    textbook(std::string t = "Untitled", int n = 0, std::string s = "Unknown")
            : printed_edition(t, n), subject(s) { Add(); }

    ~textbook() {}

    void Show() override {
        printed_edition::Show();
        std::cout << "Subject: " << subject << std::endl;
    }
};

int main() {
    magazine m("Scientific American", 100, "Springer Nature", 2021);
    book b("To Kill a Mockingbird", 281, "Harper Lee");
    textbook t("The C++ Programming Language", 1374, "Programming");

    printed_edition::Print();

    return 0;
}
