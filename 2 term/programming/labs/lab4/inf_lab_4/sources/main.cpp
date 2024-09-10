/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include "..\include\MyStack.h"

#include "iostream"

template<class INF>
MyStack<INF>::MyStack() {
    top = nullptr;
}

template<class INF>
MyStack<INF>::MyStack(const MyStack<INF> &other) {
    top = nullptr;
    Node *current = other.top;
    MyStack<INF> tmp;
    while (current != nullptr) {
        tmp.push(current->d);
        current = current->next;
    }
    Node *tmp_node = tmp.top;
    while (tmp_node != nullptr) {
        push(tmp_node->d);
        tmp_node = tmp_node->next;
    }
}

template<class INF>
MyStack<INF> &MyStack<INF>::operator=(const MyStack<INF> &other) {
    if (this != &other) {
        while (!empty()) {
            pop();
        }
        Node *current = other.top;
        MyStack<INF> tmp;
        while (current != nullptr) {
            tmp.push(current->d);
            current = current->next;
        }
        Node *tmp_node = tmp.top;
        while (tmp_node != nullptr) {
            push(tmp_node->d);
            tmp_node = tmp_node->next;
        }
    }
    return *this;
}

template<class INF>
MyStack<INF>::~MyStack() {
    while (!empty()) pop();
}

template<class INF>
bool MyStack<INF>::empty() {
    return top == nullptr;
}

template<class INF>
bool MyStack<INF>::push(INF value) {
    Node *newNode = new Node;
    newNode->d = value;
    newNode->next = top;
    top = newNode;
    return true;
}

template<class INF>
bool MyStack<INF>::pop() {
    if (empty()) {
        std::cout << "Stack is empty!" << std::endl;
        return false;
    }
    Node *oldNode = top;
    top = top->next;
    delete oldNode;
}

template<class INF>
INF *MyStack<INF>::top_inf() {
    if (empty()) {
        std::cout << "Stack is empty!" << std::endl;
        return nullptr;
    }
    return &top->d;
}

void Multipliers(int n, MyStack<int> &stack) {
    int i = 2;
    while (n > 1) {
        if (n % i == 0) {
            stack.push(i);
            n /= i;
        } else {
            i++;
        }
    }
}

int main() {
    int n = 3960;
//    int n;
//    std::cout << "Enter the number you want to decompose:";
//    std::cin >> n;

    MyStack<int> stack1, stack2;
    Multipliers(n, stack1);

    if (stack1.empty()) {
        std::cout << "This number cannot be decomposed into prime numbers!" << std::endl;
        return 1;
    }

    std::cout << n << " = ";
    while (!stack1.empty()) {
        std::cout << *stack1.top_inf();
        stack2.push(*stack1.top_inf());
        stack1.pop();
        if (!stack1.empty()) {
            std::cout << " * ";
        }
    }
    std::cout << std::endl;

    std::cout << n << " = ";
    while (!stack2.empty()) {
        std::cout << *stack2.top_inf();
        stack2.pop();
        if (!stack2.empty()) {
            std::cout << " * ";
        }
    }
    std::cout << std::endl;

    return 0;
}