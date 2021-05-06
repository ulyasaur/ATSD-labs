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
    bool IsEmpty();
    T DeleteTop();

private:
    int MaxSize;
    int LastItem;
    T* Values;

    void DoubleSize();
    void HeapsortMax(int index, int size);
    void HeapsortMin(int index, int size);
    void SiftDown(int item);
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
        std::swap(Values[i], Values[0]);

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
        std::swap(Values[index], Values[largest]);

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
        std::swap(Values[i], Values[0]);

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
        std::swap(Values[index], Values[smallest]);

        HeapsortMin(size, smallest);
    }
}

template <class T>
T List<T>::DeleteTop()
{
    HeapsortMin();
    std::swap(Values[0], Values[LastItem]);
    Values[LastItem--] = NULL;
    SiftDown(0);
    for (int i = 0; i < LastItem; i++)
    {
        std::swap(Values[i], Values[i + 1]);
    }
    return 0;
}

template <class T>
void List<T>::SiftDown(int item)
{
    int size = LastItem + 1;
    int left = 2 * item + 1;
    int right = 2 * item + 2;
    int min_index;

    if (right >= size)
    {
        if (left >= size)
        {
            return;
        }
        else
        {
            min_index = left;
        }
    }
    else
    {
        if (Values[left] <= Values[right])
        {
            min_index = left;
        }
        else
        {
            min_index = right;
        }
    }

    if (Values[item] > Values[min_index])
    {
        std::swap(Values[item], Values[min_index]);
        SiftDown(min_index);
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

template <class T>
bool List<T>::IsFull()
{
    return LastItem == -1;
}

int main()
{
    List<int> list;
    int n;

    std::cout << "Enter your list. Enter -1 to stop\n";

    std::cin >> n;

    while (n != -1)
    {
        list.AddItem(n);
        std::cin >> n;
    }

    std::cout << "Your list: ";
    list.PrintList();
    std::cout << "Your list (maxheap): ";
    list.HeapsortMax();
    list.PrintList();
    std::cout << "Your list after DeleteTop() (minheap): ";
    list.DeleteTop();
    list.PrintList();
}
