#ifndef INF_LAB_5_MYSET_H
#define INF_LAB_5_MYSET_H

#include <iostream>
#include "MyVector.h"

template<class TYPE>
class MySet : public MyVector<TYPE> {
private:
    int q_find(TYPE element);
public:
    MySet() : MyVector<TYPE>() {}
    MySet(TYPE element) : MyVector<TYPE>(element) {}
    MySet(MySet<TYPE> &other) : MyVector<TYPE>(other) {}

    bool IsElement(TYPE element);
    void AddElement(TYPE element);
    bool DeleteElement(TYPE element);

    MySet<TYPE> operator+(MySet<TYPE> &other);
    MySet<TYPE> operator-(MySet<TYPE> &other);
    MySet<TYPE> operator*(MySet<TYPE> &other);
    MySet<TYPE> &operator+=(MySet<TYPE> &other);
    MySet<TYPE> &operator-=(MySet<TYPE> &other);
    MySet<TYPE> &operator*=(MySet<TYPE> &other);

    friend std::ostream &operator<<(std::ostream &out, MySet<TYPE> &other) {
        out << "{ ";
        for (size_t i = 0; i < other.size; ++i) {
            out << other[i] << " ";
        }
        out << "}";
        return out;
    }

    friend bool operator==(MySet<TYPE> &set1, MySet<TYPE> &set2) {
        if (set1.size != set2.size)
            return false;

        for (int i = 0; i < set1.size; ++i) {
            if (!set2.IsElement(set1[i]))
                return false;
        }
        return true;
    }
};

template<class TYPE>
int MySet<TYPE>::q_find(TYPE value) {
    int left = 0;
    int right = this->size - 1;

    while (left <= right) {
        int middle = (left + right) / 2;
        if (value < (*this)[middle]) {
            right = middle - 1;
        } else if (value > (*this)[middle]) {
            left = middle + 1;
        } else {
            return middle;
        }
    }
    return -1;
}

template<>
int MySet<char *>::q_find(char *value) {
    int left = 0;
    int right = this->size - 1;

    while (left <= right) {
        int middle = (left + right) / 2;
        if (strcmp(value, (*this)[middle]) < 0) {
            right = middle - 1;
        } else if (strcmp(value, (*this)[middle]) > 0) {
            left = middle + 1;
        } else {
            return middle;
        }
    }
    return -1;
}

template<class TYPE>
bool MySet<TYPE>::IsElement(TYPE element) {
    return q_find(element) != -1;
}

template<class TYPE>
void MySet<TYPE>::AddElement(TYPE element) {
    if (!IsElement(element)) {
        this->add_element(element);
        this->sort();
    }
}

template<class TYPE>
bool MySet<TYPE>::DeleteElement(TYPE element) {
    int index = q_find(element);
    return this->delete_element(index);
}

template<class TYPE>
MySet<TYPE> MySet<TYPE>::operator-(MySet<TYPE> &other) {
    MySet<TYPE> result;
    for (int i = 0; i < this->size; ++i) {
        if (other.q_find(this->pdata[i]) == -1)
            result.AddElement(this->pdata[i]);
    }
    return result;
}

template<class TYPE>
MySet<TYPE> MySet<TYPE>::operator+(MySet<TYPE> &other) {
    MySet<TYPE> result(*this);
    for (int i = 0; i < other.size; ++i) {
        result.AddElement(other[i]);
    }
    return result;
}

template<class TYPE>
MySet<TYPE> MySet<TYPE>::operator*(MySet<TYPE> &other) {
    MySet<TYPE> result;
    for (int i = 0; i < this->size; ++i) {
        if (other.IsElement(this->pdata[i]))
            result.AddElement(this->pdata[i]);
    }
    return result;
}

#endif //INF_LAB_5_MYSET_H
