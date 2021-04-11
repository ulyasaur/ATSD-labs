#include <iostream>

template <class T>
class List
{
public:
    List(int size = 1);

    void AddItem(T item);
    void HeapsortMax();
    void HeapsortMin();
    void PrintList();
    int Size();
    bool IsFull();

private:
    int MaxSize;
    int LastItem;
    T* Values;

    void DoubleSize();
    void HeapsortMax(int index, int size);
    void HeapsortMin(int index, int size);
};

template <class T>
List<T>::List(int size)
{
    MaxSize = size;
    LastItem = -1;
    Values = new T[size];
}

template <class T>
void List<T>::DoubleSize()
{
    T* temp = Values;
    Values = new T[MaxSize * 2 + 1];
    for (int i = 0; i < MaxSize; ++i)
    {
        Values[i] = temp[i];
    }
    delete[] temp;
    MaxSize *= 2;
}

template <class T>
void List<T>::AddItem(T item)
{
    if (IsFull())
    {
        DoubleSize();
    }

    Values[++LastItem] = item;
}

template <class T>
void List<T>::HeapsortMax()
{
    int size = LastItem + 1;

    for (int i = size / 2 - 1; i >= 0; i--)
    {
        HeapsortMax(size, i);
    }

    for (int i = size - 1; i > 0; i--) 
    {
        T temp = Values[i];
        Values[i] = Values[0];
        Values[0] = temp;

        HeapsortMax(i, 0);
    }
}

template <class T>
void List<T>::HeapsortMax(int size, int index)
{
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && Values[left] > Values[largest])
    {
        largest = left;
    }
    
    if (right < size && Values[right] > Values[largest])
    {
        largest = right;
    }

    if (largest != index)
    {
        T temp = Values[index];
        Values[index] = Values[largest];
        Values[largest] = temp;

        HeapsortMax(size, largest);
    }
}

template <class T>
void List<T>::HeapsortMin()
{
    int size = LastItem + 1;

    for (int i = size / 2 - 1; i >= 0; i--)
    {
        HeapsortMin(size, i);
    }

    for (int i = size - 1; i > 0; i--) 
    {
        T temp = Values[i];
        Values[i] = Values[0];
        Values[0] = temp;

        HeapsortMin(i, 0);
    }
}

template <class T>
void List<T>::HeapsortMin(int size, int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && Values[left] < Values[smallest])
    {
        smallest = left;
    }
    
    if (right < size && Values[right] < Values[smallest])
    {
        smallest = right;
    }

    if (smallest != index)
    {
        T temp = Values[index];
        Values[index] = Values[smallest];
        Values[smallest] = temp;

        HeapsortMin(size, smallest);
    }
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
int List<T>::Size()
{
    return LastItem + 1;
}

template <class T>
bool List<T>::IsFull()
{
    return LastItem + 1 == MaxSize;
}

int main()
{
    List<int> list;
    int n;
    std::cin >> n;

    while (n != -1)
    {
        list.AddItem(n);
        std::cin >> n;
    }

    list.PrintList();
    list.HeapsortMin();
    list.PrintList();
}
