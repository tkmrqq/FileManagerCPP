#ifndef MYSTRING_H
#define MYSTRING_H

#include "QString"
#include <cstring>
#include <iostream>

size_t getLength(const char *str);

class MyString
{
    char *str;
    size_t length;

public:
    MyString() : str(nullptr), length(0) {}
    explicit MyString(const char *str_t);
    MyString(const MyString &other);

    MyString &operator=(const MyString &other);
    MyString operator+(const MyString &other) const;
    MyString &operator+=(const MyString &other);
    MyString operator()(int start, int end) const;
    MyString &operator=(const QString &other)
    {
        delete[] str;
        length = other.length();
        str = new char[length + 1];
        std::strcpy(str, other.toUtf8().constData());
        return *this;
    }
    bool operator==(const MyString &other) const;
    bool operator!=(const MyString &other) const;
    char operator[](int index) const;
    friend std::ostream &operator<<(std::ostream &os, const MyString &str_t)
    {
        os << str_t.str;
        return os;
    }

    size_t getLen() const;
    void print() { std::cout << "This string: " << this->str; }

    ~MyString() { delete[] str; }
};

#endif // MYSTRING_H
