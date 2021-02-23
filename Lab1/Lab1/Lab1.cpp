#include <iostream>
#include <string>
#include <typeinfo>

template <class T>
class Node
{
public:
    T Value;
    Node* Next;

    Node(T val = "", Node* next = NULL);
};

template <class T>
Node<T>::Node(T val, Node* next)
{
    Value = val;
    Next = next;
}

template <class T>
class SortedLinkedList
{
public:
    SortedLinkedList(int size = 0, Node<T>* first = NULL);
    bool IsEmpty();
    void AddItem(T item);
    void DeleteItem(T item);
    int Search(T item);
    void PrintList();
    int GetSize();
    SortedLinkedList<T>* CopyReverse();
    void AddItemUnsorted(T item);
    void Interface();

private:
    int Size;
    Node<T>* First;
};

template <class T>
SortedLinkedList<T>::SortedLinkedList(int size, Node<T>* first)
{
    Size = size;
    First = first;
}

template <class T>
bool SortedLinkedList<T>::IsEmpty()
{
    return Size == 0;
}

template <class T>
void SortedLinkedList<T>::AddItem(T item)
{
    if (Size == 0 || item < First->Value)
    {
        First = new Node<T>(item, First);
    }
    else
    {
        Node<T>* now = First;
        while (now->Next != NULL && item > now->Next->Value)
        {
            now = now->Next;
        }

        now->Next = new Node<T>(item, now->Next);
    }
    Size++;
}

template <class T>
void SortedLinkedList<T>::DeleteItem(T item)
{
    int counter = 0;

    while (First && First->Value == item)
    {
        Node<T>* temp = First;
        First = First->Next;
        delete temp;
        counter++;
    }

    if (!counter)
    {
        Node<T>* now = First;

        while (now && now->Value < item)
        {
            while (now->Next && now->Next->Value == item)
            {
                Node<T>* temp = now->Next;
                now->Next = temp->Next;
                delete temp;
                counter++;
            }
            now = now->Next;
        }
    }

    Size -= counter;

    if (counter)
    {
        std::cout << "Deleted " << counter << " occurences of " << item << '\n';
    }
    else
    {
        std::cout << "Item was not found in list\n";
    }
}

template <class T>
int SortedLinkedList<T>::Search(T item)
{
    bool flag = false;
    int ind = 0;
    Node<T>* temp = First;

    while (temp != NULL)
    {
        if (temp->Value == item)
        {
            flag = true;
            break;
        }
        else
        {
            temp = temp->Next;
        }
        ind++;
    }

    if (flag)
    {
        return ind;
    }
    else
    {
        return -1;
    }
}

template <class T>
void SortedLinkedList<T>::PrintList()
{
    if (!IsEmpty())
    {
        std::cout << "List: ";
        Node<T>* temp = First;

        while (temp != NULL)
        {
            std::cout << temp->Value << " ";
            temp = temp->Next;
        }
        std::cout << "\n";
    }
    else
    {
        std::cout << "List is empty. \n";
    }
}

template <class T>
int SortedLinkedList<T>::GetSize()
{
    return Size;
}

template <class T>
SortedLinkedList<T>* SortedLinkedList<T>::CopyReverse()
{
    SortedLinkedList* cur = new SortedLinkedList();
    Node<T>* now = First;

    while (now)
    {
        cur->AddItemUnsorted(now->Value);
        now = now->Next;
    }
    return cur;
}

template <class T>
void SortedLinkedList<T>::AddItemUnsorted(T value)
{
    First = new Node<T>(value, First);
    Size++;
}

template <class T>
void SortedLinkedList<T>::Interface()
{
    std::cout << "Your list: ";
    PrintList();

    bool flag = true;
    T item;
    SortedLinkedList<T>* copied = new SortedLinkedList<T>();

    std::cout << "Choose operation:\n "
        << "1 - IsEmpty\n "
        << "2 - AddItem\n "
        << "3 - DeleteItem\n "
        << "4 - Search\n "
        << "5 - PrintList\n "
        << "6 - GetSize\n "
        << "7 - CopyReverse\n "
        << "0 - Quit program\n ";

    while (flag)
    {
        int operation;
        std::cin >> operation;

        switch (operation)
        {
        case 1:
            if (IsEmpty())
            {
                std::cout << "List is empty\n";
            }
            else
            {
                std::cout << "List is not empty\n";
            }
            break;

        case 2:
            std::cout << "Enter an item to add: ";
            std::cin >> item;
            AddItem(item);
            PrintList();
            break;

        case 3:
            std::cout << "Enter an item to delete: ";
            std::cin >> item;
            DeleteItem(item);
            PrintList();
            break;

        case 4:
            std::cout << "Enter an item to search: ";
            std::cin >> item;
            std::cout << "Its position in the list: " << Search(item) << "\n";
            break;

        case 5:
            PrintList();
            break;

        case 6:
            std::cout << "Size of your list: " << GetSize() << "\n";
            break;

        case 7:
            copied = CopyReverse();
            copied->PrintList();
            break;

        case 0:
            flag = false;
            break;
        }
    }
}

int main()
{
    std::cout << "Choose int {i} or string {s}\n";
    char op;
    std::cin >> op;

    if (op == 's')
    {
        SortedLinkedList <std::string>* List = new SortedLinkedList<std::string>();

        std::cout << "Enter your linked list. Enter -1 to stop.\n";

        std::string n;

        while (true)
        {
            std::cin >> n;

            if (n != "-1")
            {
                List->AddItem(n);
            }
            else
            {
                break;
            }
        }

        List->Interface();
    }
    else
    {
        SortedLinkedList <int>* List = new SortedLinkedList<int>();

        std::cout << "Enter your linked list. Enter -1 to stop.\n";

        int n;

        while (true)
        {
            std::cin >> n;

            if (n != -1)
            {
                List->AddItem(n);
            }
            else
            {
                break;
            }
        }

        List->Interface();
    }
}
