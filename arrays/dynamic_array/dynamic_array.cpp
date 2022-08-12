/**
 * dynamic_array.cpp
 *
 * Generic Dynamic Array
 * 
 * NC, 2022
 */

#include <iostream>

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

/* FIXME: memory leak in new call */
template <typename T>
void DynamicArray<T>::expand(unsigned int newSpace)
{
    this->size += newSpace;
    T *tmp = new T[this->size];

    copy(this->data, this->data + this->used, tmp);
    delete[] this->data;

    this->data = tmp;
}

template <typename T>
void DynamicArray<T>::shrink()
{
    for (unsigned int i = this->used; i < this->size; i++) {

        free(this->data[i]);
    }
    this->size = this->used;
}

template <typename T>
void DynamicArray<T>::display()
{
    cout << "[ ";
    for (unsigned int i = 0; i < this->used; i++) {

        cout << this->data[i] << ", ";
    }
    cout << "]" << endl;
}

template <typename T>
void DynamicArray<T>::append(T data)
{
    if (this->used == this->size) {

        this->expand(1);
    }

    this->data[this->used++] = data;
}

template <typename T>
void DynamicArray<T>::chop()
{
    this->removeFrom(this->used - 1);
}

template <typename T>
void DynamicArray<T>::insertAt(T data, int index)
{
    return;
}

template <typename T>
void DynamicArray<T>::removeFrom(int index)
{
    return;
}

template <typename T>
void DynamicArray<T>::removeAll(T data)
{

}

template <typename T>
int DynamicArray<T>::findFirst(T data)
{
    int ret = -1;

    for (unsigned int i = 0; i < this->used; i++) {

        if (data == this->data[i]) {

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

    for (unsigned int i = this->used - 1; i >= 0; i--) {

        if (data == this->data[i]) {

            ret = i;
            break;
        }
    }

    return ret;
}

int main(void)
{
    DynamicArray<int> *da = new DynamicArray<int>(0);
    
    for (unsigned int i = 0; i < 10; i++) {

        da->append(i);
    }

    da->display();

    int index = da->findFirst(10);
    int index1 = da->findLast(3);


    cout << index << " :: " << index1 << endl;

    return 0;
}
