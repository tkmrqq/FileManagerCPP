#ifndef MYVECTOR_H
#define MYVECTOR_H

#include "FileItem.h"
#include "exp.h"
#include <iostream>
#include <QStringList>

template<typename T>
class MyVector
{
private:
    T *data;
    size_t size;
    size_t capacity;

public:
    MyVector() : data(nullptr), size(0), capacity(0) {}

    explicit MyVector(size_t initialCapacity)
        : data(new T[initialCapacity]), size(0), capacity(initialCapacity)
    {}

    ~MyVector() { delete[] data; }

    //iterators
    T *begin() { return data; }
    T *end() { return data + size; }
    const T *begin() const { return data; }
    const T *end() const { return data + size; }

    //size-memory
    size_t getSize() const { return size; }
    void resize(size_t newSize, const T &value = T());
    size_t getCapacity() const { return capacity; }
    bool empty() const { return size == 0; }
    void reserve(size_t newCapacity);
    void shrink_to_fit();

    T &operator[](size_t index);
    const T &operator[](size_t index) const;

    T &at(size_t index);
    T &front();
    T &back();

    T *dataR() { return data; }
    const T *dataR() const { return data; }

    void assign(size_t count, const T &value)
    {
        clear();
        resize(count, value);
    }

    void push_back(const T &value);
    void pop_back()
    {
        if (size > 0) {
            --size;
        }
    }
    void insert(T *position, const T &value);
    void erase(T *position);
    void swap(MyVector &other)
    {
        std::swap(data, other.data);
        std::swap(size, other.size);
        std::swap(capacity, other.capacity);
    }
    void clear() { size = 0; }

    template<typename... Args>
    void emplace_back(Args &&... args)
    {
        if (size == capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        new (&data[size++]) T(std::forward<Args>(args)...);
    }
};

template<typename T>
void MyVector<T>::resize(size_t newSize, const T &value)
{
    if (newSize > size) {
        reserve(newSize);
        for (size_t i = size; i < newSize; ++i) {
            data[i] = value;
        }
    }
    size = newSize;
}

template<typename T>
void MyVector<T>::erase(T *position)
{
    size_t index = position - data;
    if (index >= size) {
        throw Exp(1, "Invalid erase position");
    }
    for (size_t i = index; i < size - 1; ++i) {
        data[i] = std::move(data[i + 1]);
    }
    --size;
}

template<typename T>
void MyVector<T>::insert(T *position, const T &value)
{
    size_t index = position - data;
    if (index > size) {
        throw Exp(2, "Out of range");
    }
    if (size == capacity) {
        reserve(capacity == 0 ? 1 : capacity * 2);
    }
    for (size_t i = size; i > index; --i) {
        data[i] = std::move(data[i - 1]);
    }
    data[index] = value;
    ++size;
}

template<typename T>
void MyVector<T>::push_back(const T &value)
{
    if (size == capacity) {
        reserve(capacity == 0 ? 1 : capacity * 2);
    }
    data[size++] = value;
}

template<typename T>
T &MyVector<T>::back()
{
    if (size == 0) {
        throw Exp(2, "Vector is empty");
    }
    return data[size - 1];
}

template<typename T>
T &MyVector<T>::front()
{
    if (size == 0) {
        throw Exp(2, "Vector is empty");
    }
    return data[0];
}

template<typename T>
T &MyVector<T>::at(size_t index)
{
    if (index >= size) {
        throw Exp(1, "Index out of range");
    }
    return data[index];
}

template<typename T>
const T &MyVector<T>::operator[](size_t index) const
{
    if (index >= size) {
        throw Exp(2, "Index out of range");
    }
    return data[index];
}

template<typename T>
T &MyVector<T>::operator[](size_t index)
{
    if (index >= size) {
        throw Exp(2, "Index out of range");
    }
    return data[index];
}

template<typename T>
void MyVector<T>::shrink_to_fit()
{
    if (size < capacity) {
        reserve(size);
    }
}

//template<typename T>
//void MyVector<T>::reserve(size_t newCapacity)
//{
//    if (newCapacity > capacity) {
//        size_t newRealCapacity = capacity == 0 ? 1 : capacity * 2;
//        newRealCapacity = std::max(newRealCapacity, newCapacity);

//        T *newData = new T[newRealCapacity];

//        for (size_t i = 0; i < size; ++i) {
//            newData[i] = std::move(data[i]);
//        }

//        delete[] data;

//        data = newData;
//        capacity = newRealCapacity;
//    }
//}

template<class T>
void MyVector<T>::reserve(size_t new_cap)
{
    if (new_cap > capacity) {
        T *new_data = new T[new_cap];
        for (int i = 0; i < size; i++) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_cap;
    }
}

#endif // MYVECTOR_H
