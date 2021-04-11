#include <iostream>

template <class T>
class List
{
public:
    List(int size = 1);

private:
    int Size;
    int LastItem;
    T* Values;
};

template <class T>
List<T>::List(int size)
{
    Size = size;
    LastItem = -1;
    Values = new T[size];
}

int main()
{
    
}