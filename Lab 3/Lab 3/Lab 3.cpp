#include <iostream>

template <class T>
class List
{
public:
    List(int size = 1);

    void PrintList();

private:
    int Size;
    int LastItem;
    T* Values;

    bool IsFull();
};

template <class T>
List<T>::List(int size)
{
    Size = size;
    LastItem = -1;
    Values = new T[size];
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
