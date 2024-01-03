#ifndef INF_LAB_6_VECTOR_H
#define INF_LAB_6_VECTOR_H

#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>

const int MAX_SIZE = 5;

template<class TYPE>
class MyVector {
protected:
    int maxsize;
    int size;
    TYPE *pdata;
private:
    void resize();

public:
    MyVector();
    MyVector(TYPE element);
    MyVector(MyVector<TYPE> &other);
    ~MyVector();

    void add_element(TYPE element);
    bool delete_element(int index);
    int find_element(TYPE element);
    void sort();

    friend std::ostream &operator<<(std::ostream &out, MyVector<TYPE> &other) {
        out << "[ ";
        for (size_t i = 0; i < other.size; ++i) {
            out << other[i] << " ";
        }
        out << "]";
        return out;
    }

    const TYPE &operator[](size_t index) const;
    MyVector<TYPE> &operator=(const MyVector<TYPE> &other);
};

template<class TYPE>
void MyVector<TYPE>::resize() {
    if (size >= maxsize) { maxsize = static_cast<int>(maxsize * 1.5); }
    else if (size < maxsize / 2) { maxsize = std::max(static_cast<int>(maxsize * 0.5), MAX_SIZE); }
    else { return; }

    TYPE *new_pdata = new TYPE[maxsize];
    for (size_t i = 0; i < size; ++i) {
        new_pdata[i] = pdata[i];
    }
    delete[] pdata;
    pdata = new_pdata;
}

template<class TYPE>
MyVector<TYPE>::MyVector() {
    maxsize = MAX_SIZE;
    size = 0;
    pdata = new TYPE[MAX_SIZE];
}

template<class TYPE>
MyVector<TYPE>::MyVector(TYPE element) {
    maxsize = MAX_SIZE;
    size = 0;
    pdata = new TYPE[MAX_SIZE];
    pdata[size++] = element;
}

template<>
MyVector<char *>::MyVector(char *element) {
    maxsize = MAX_SIZE;
    size = 0;
    pdata = new char *[MAX_SIZE];
    pdata[0] = new char[strlen(element) + 1];
    strcpy(pdata[size++], element);
}

template<class TYPE>
MyVector<TYPE>::MyVector(MyVector<TYPE> &other) {
    maxsize = other.maxsize;
    size = other.size;
    pdata = new TYPE[maxsize];
    for (size_t i = 0; i < size; ++i) {
        pdata[i] = other[i];
    }
}

template<>
MyVector<char *>::MyVector(MyVector<char *> &other) {
    maxsize = other.maxsize;
    size = other.size;
    pdata = new char *[maxsize];
    for (int i = 0; i < size; ++i) {
        pdata[i] = new char[strlen(other[i]) + 1];
        strcpy(pdata[i], other[i]);
    }
}

template<class TYPE>
MyVector<TYPE>::~MyVector() {
    delete[] pdata;
}

template<>
MyVector<char *>::~MyVector() {
    for (size_t i = 0; i < size; ++i) {
        delete[] pdata[i];
    }
    delete[] pdata;
}

template<class TYPE>
void MyVector<TYPE>::add_element(TYPE element) {
    pdata[size++] = element;
    resize();
}

template<>
void MyVector<char *>::add_element(char *element) {
    pdata[size] = new char[strlen(element) + 1];
    strcpy(pdata[size++], element);
    resize();
}

template<class TYPE>
bool MyVector<TYPE>::delete_element(int index) {
    if (index >= 0 && index <= size--) {
        for (size_t i = index; i < size; ++i) {
            pdata[i] = pdata[i + 1];
        }
        resize();
        return true;
    }
    return false;
}

template<class TYPE>
int MyVector<TYPE>::find_element(TYPE element) {
    for (int i = 0; i < size; ++i) {
        if (pdata[i] == element) return i;
    }
    return -1;
}

template<>
int MyVector<char *>::find_element(char *element) {
    for (size_t i = 0; i < size; ++i) {
        if (strlen(pdata[i]) == strlen(element)) {
            if (strcmp(pdata[i], element) == 0) return i;
        }
    }
    return -1;
}

template<class TYPE>
void MyVector<TYPE>::sort() {
    std::sort(pdata, pdata + size);
}

template<>
void MyVector<char *>::sort() {
    std::sort(pdata, pdata + size, [](const char *a, const char *b) {
        return std::strcmp(a, b) < 0;
    });
}

template<class TYPE>
const TYPE &MyVector<TYPE>::operator[](size_t index) const {
    return pdata[index];
}

template<class TYPE>
MyVector<TYPE> &MyVector<TYPE>::operator=(const MyVector<TYPE> &other) {
    if (this == &other) return *this;

    maxsize = other.maxsize;
    size = other.size;
    delete[] pdata;
    pdata = new TYPE[maxsize];
    for (size_t i = 0; i < size; ++i) {
        pdata[i] = other[i];
    }

    return *this;
}

template<>
MyVector<char *> &MyVector<char *>::operator=(const MyVector<char *> &other) {
    if (this == &other) return *this;

    maxsize = other.maxsize;
    size = other.size;
    delete[] pdata;
    pdata = new char *[maxsize];
    for (int i = 0; i < size; ++i) {
        pdata[i] = new char[strlen(other[i]) + 1];
        strcpy(pdata[i], other[i]);
    }

    return *this;
}

#endif //INF_LAB_6_VECTOR_H
