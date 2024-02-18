#include "myString.h"

size_t getLength(const char *str)
{
    size_t len = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        len++;
    }
    return len;
}

size_t MyString::getLen() const
{
    return this->length;
}

MyString::MyString(const char *str_t)
{
    length = getLength(str_t);
    str = new char[length + 1];
    strcpy(str, str_t);
}

MyString::MyString(const MyString &other)
{
    length = other.length;
    str = new char[length + 1];
    strcpy(str, other.str);
}

bool MyString::operator!=(const MyString &other) const
{
    return !(*this == other);
}

bool MyString::operator==(const MyString &other) const
{
    if (strcmp(str, other.str) == 0) {
        return true;
    } else
        return false;
}

MyString MyString::operator+(const MyString &other) const
{
    MyString result;
    result.length = length + other.length;
    result.str = new char[result.length + 1];

    strcpy(result.str, str);
    strcat(result.str, other.str);

    return result;
}

MyString &MyString::operator=(const MyString &other)
{
    if (this == &other)
        return *this;
    delete[] str;

    length = other.length;
    str = new char[length + 1];
    strcpy(str, other.str);

    return *this;
}

MyString &MyString::operator+=(const MyString &other)
{
    char *temp = new char[length + other.length + 1];
    strcpy(temp, str);
    strcat(temp, other.str);

    delete[] str;

    str = temp;
    length += other.length;

    return *this;
}

char MyString::operator[](int index) const
{
    if (index < 0 || index > length - 1)
        throw std::invalid_argument("You must to refer only to existing elements");
    return str[index];
}

MyString MyString::operator()(int start, int end) const
{
    if (start < 0 || start >= length || end < 0 || end >= length || start > end) {
        throw std::invalid_argument("Please input correct values");
    }

    int temp_length = end - start + 1;
    char *temp = new char[temp_length + 1];

    for (int i = 0; i < temp_length; i++) {
        temp[i] = str[start + i];
    }
    temp[temp_length] = '\0';

    MyString tempStr(temp);
    delete[] temp;
    return tempStr;
}
