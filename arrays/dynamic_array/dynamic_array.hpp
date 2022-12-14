/**
 * dynamic_array.hpp
 *
 * Generic Dynamic Array
 *
 * NC, 2022
 */

template <typename T>
class DynamicArray
{
    private:
        T *data;
        int size;
        int used;

    public:
        DynamicArray(unsigned int capacity);
        ~DynamicArray();

        int getSize() { return this->used; }
        int getCapacity() { return this->size; }
        T *getData() { return this->data; }
        void setSize(int newSize);
        void setCapacity(int newCap);
        void setData(T *newData);

        void expand(unsigned int newSpace);

        void append(T data);
        void chop();
        void insertAt(T data, int index);
        void removeFrom(int index);
        void removeAll(T data);

        int findFirst(T data);
        int findLast(T data);

        void quicksort();
        void bubblesort();
        void mergesort();

        void display();
};
