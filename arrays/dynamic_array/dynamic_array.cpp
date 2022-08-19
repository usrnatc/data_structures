/**
 * dynamic_array.cpp
 *
 * Generic Dynamic Array
 * 
 * NC, 2022
 */

#include <iostream>
#include <algorithm>

#include "dynamic_array.hpp"

using namespace std;

template <typename T>
DynamicArray<T>::DynamicArray(unsigned int capacity)
{
    this->size = capacity;
    this->used = 0;

    this->data = new T[capacity];
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
    delete[] this->data;
    this->used = 0;
    this->size = 0;
}

template <typename T>
void DynamicArray<T>::setSize(int newSize)
{
    this->used = newSize;
}

template <typename T>
void DynamicArray<T>::setCapacity(int newCapacity)
{
    this->size = newCapacity;
}

template <typename T>
void DynamicArray<T>::setData(T *newData) {

    this->data = newData;
}

template <typename T>
void DynamicArray<T>::expand(unsigned int newSpace)
{
    this->setCapacity(this->getCapacity() + newSpace);
    /* FIXME: valgrind specifies memory leak from new call */
    T *tmp = new T[this->getCapacity()];

    copy(this->getData(), this->getData() + this->getSize(), tmp);
    delete[] this->getData();

    this->setData(tmp);
}

template <typename T>
void DynamicArray<T>::display()
{
    cout << "[ ";
    for (unsigned int i = 0; i < this->getSize(); i++) {

        cout << this->getData()[i] << ", ";
    }
    cout << "]" << endl;
}

template <typename T>
void DynamicArray<T>::append(T data)
{
    if (this->getSize() == this->getCapacity()) {

        this->expand(1);
    }

    this->getData()[this->getSize()] = data;
    this->setSize(this->getSize() + 1);
}

template <typename T>
void DynamicArray<T>::chop()
{
    this->removeFrom(this->getSize() - 1);
}

/* TODO: maybe should use copy instead of manually mutating */
template <typename T>
void DynamicArray<T>::insertAt(T data, int index)
{
    if (index < 0 || index > this->getSize())
        return;

    if (index == this->getSize())
        this->append(data);

    if (this->getSize() == this->getCapacity())
        this->expand(1);

    this->setSize(this->getSize() + 1);
    for (unsigned int i = this->getSize(); i > index; i--) {

        this->getData()[i] = this->getData()[i - 1];
    }

    this->getData()[index] = data;
}

/* TODO: maybe should use copy instead of manually mutating */
template <typename T>
void DynamicArray<T>::removeFrom(int index)
{
    if (index < 0 || index > this->getSize())
        return;

    if (index == this->getSize())
        this->chop();

    for (unsigned int i = index; i < this->getSize(); i++) {

        this->getData()[i] = this->getData()[i + 1];
    }
    
    this->setSize(this->getSize() - 1);
}

template <typename T>
void DynamicArray<T>::removeAll(T data)
{
    unsigned int cnt = 0;

    for (unsigned int i = 0; i < this->getSize(); i++) {

        if (this->getData()[i] != data)
            cnt++;
    }

    T *tmp = new T[cnt];

    copy_if(this->getData(), this->getData() + this->getSize(), tmp,
            [data](T elem) { return elem != data; });

    delete[] this->getData();
    this->setData(tmp);
    this->setSize(cnt);
}

template <typename T>
int DynamicArray<T>::findFirst(T data)
{
    int ret = -1;

    for (unsigned int i = 0; i <= this->getSize(); i++) {

        if (data == this->getData()[i]) {

            ret = i;
            break;
        }
    }

    return ret;
}

template <typename T>
int DynamicArray<T>::findLast(T data)
{
    int ret = -1;

    for (unsigned int i = this->getSize() - 1; i >= 0; i--) {

        if (data == this->getData()[i]) {

            ret = i;
            break;
        }
    }

    return ret;
}

template <typename T>
void DynamicArray<T>::bubblesort()
{
    int length = this->getSize();

    if (length <= 1) return;

    while (length > 1) {

        int n = 0;

        for (unsigned int i = 1; i < length; i++) {

            if (this->getData()[i - 1] > this->getData()[i]) {

                T tmp = this->getData()[i];
                this->getData()[i] = this->getData()[i - 1];
                this->getData()[i - 1] = tmp;
                n = i;
            }
        }
        length = n;
    }
}

int main(void)
{
    DynamicArray<int> *da = new DynamicArray<int>(0);

    for (int i = 10000; i >= 0; i--) {

        da->append(i);
    }

    da->bubblesort();

    return 0;
}
