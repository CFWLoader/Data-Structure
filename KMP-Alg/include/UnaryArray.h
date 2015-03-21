#ifndef UNARYARRAY_H
#define UNARYARRAY_H
#include<iostream>
#include<stdexcept>

/*
 * This template class is for simplifying my work.
 * Using this abstraction of unary array, We can ignore memory management.
 * And save time of building function for basic data type.
 */
template<typename T>
class UnaryArray
{
    public:
        UnaryArray();
        UnaryArray(int);
        UnaryArray(const char*);
        int getSize();
        void setSize(int);
        void printArray(std::ostream&);
        T& operator[](int);
        virtual ~UnaryArray();
    protected:
    private:
        T* array;
        int size;
};

template<typename T>
UnaryArray<T>::UnaryArray() : size(0), array(0){}

template<typename T>
UnaryArray<T>::UnaryArray(int setSize) : size(setSize), array(new T[setSize]){}

template<typename T>
UnaryArray<T>::UnaryArray(const char* originalString){
    size = 0;
    while(originalString[++size] != '\0');
    array = new T[size];
    for(int counter = 0; counter < size; ++counter)array[counter] = originalString[counter];
}

template<typename T>
int UnaryArray<T>::getSize(){
    return size;
}

template<typename T>
void UnaryArray<T>::setSize(int newSize){
    if(size > 0)delete[] array;
    size = newSize;
    array = new T[size];
}

template<typename T>
void UnaryArray<T>::printArray(std::ostream& os){
    for(int counter = 0; counter < size; ++counter)
        os << array[counter] << " ";
    os << std::endl;
}

template<typename T>
T& UnaryArray<T>::operator[](int idx){
    if(idx >= size)throw std::invalid_argument("Max index is " + (size - 1));
    return array[idx];
}

template<typename T>
UnaryArray<T>::~UnaryArray()
{
    if(size > 0)delete[] array;
    array = 0;
    size = 0;
    //dtor
}

#endif // UNARYARRAY_H
