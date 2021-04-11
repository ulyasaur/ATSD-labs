#include <iostream>

template <class T>
class List
{
public:
    List(int size = 1);

    void AddItem(T item);
    void PrintList();
    bool IsFull();

private:
    int Size;
    int LastItem;
    T* Values;

    void DoubleSize();
};

template <class T>
List<T>::List(int size)
{
    Size = size;
    LastItem = -1;
    Values = new T[size];
}

template <class T>
void List<T>::DoubleSize()
{
    T* temp = Values;
    Values = new T[Size * 2 + 1];
    for (int i = 0; i < Size; ++i)
    {
        Values[i] = temp[i];
    }
    delete[] temp;
    Size *= 2;
}

template <class T>
void List<T>::AddItem(T item)
{
    if (IsFull())
    {
        DoubleSize();
    }

    Values[++last] = item;
}

template <class T>
void List<T>::PrintList()
{
    for (int i = 0; i <= LastItem; i++)
    {
        std::cout << Values[i] << " ";
    }
    std::cout << "\n";
}

template <class T>
bool List<T>::IsFull()
{
    return LastItem + 1 == Size;
}

int main()
{

}
