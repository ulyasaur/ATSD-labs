#include <iostream>

class Node
{
public:
    int Value;
    Node* Next;

    Node(int val = -1, Node* next = NULL);
};

Node::Node(int val, Node* next)
{
    Value = val;
    Next = next;
}

class SortedLinkedList
{
public:
    SortedLinkedList(int size = 0, Node* first = NULL);
    bool IsFull();
    bool IsEmpty();
    void MakeEmpty();
    void AddItem(int item);
    int DeleteItem(int item);
    int Search(int item);
    int Retrieve(int item);
    void PrintList();
    int GetSize();

private:
    int Size;
    Node* First;
};

SortedLinkedList::SortedLinkedList(int size, Node* first)
{
    Size = size;
    First = first;
}

bool SortedLinkedList::IsFull()
{
    bool flag = false;
    Node* temp = new Node();
    flag = temp == NULL;
    delete temp;
    return flag;
}

bool SortedLinkedList::IsEmpty()
{
    return Size == 0;
}

void SortedLinkedList::MakeEmpty()
{
    Node* temp = First;
    while (temp->Next != NULL)
    {
        First = First->Next;
        delete temp;
        temp = First;
    }
    delete temp;
    Size = 0;
}

void SortedLinkedList::AddItem(int item)
{
    if (IsFull())
    {
        std::cout << "List is full. Item can't be added.\n";
        return;
    }
    if (Size == 0 || item < First->Value)
    {
        First = new Node(item, First);
    }
    else
    {
        Node* now = First;
        while (now->Next != NULL && item > now->Next->Value)
        {
            now = now->Next;
        }

        if (now->Next && item == now->Next->Value || now->Value == item)
        {
            std::cout << "Item is already in the list.\n";
            return;
        }

        now->Next = new Node(item, now->Next);
    }
    Size++;
}

int SortedLinkedList::DeleteItem(int item)
{
    if (Search(item) != -1)
    {
        Node* prev = NULL;
        Node* now = First;
        while (true)
        {
            if (now->Value == item)
            {
                break;
            }
            else
            {
                prev = now;
                now = now->Next;
            }
        }

        if (prev == NULL)
        {
            First = now->Next;
        }
        else if (now->Next == NULL)
        {
            prev->Next = NULL;
        }
        else
        {
            prev->Next = now->Next;
        }
        delete now;
        Size--;
        return item;
    }
    else
    {
        return -1;
    }
}

int SortedLinkedList::Search(int item)
{
    bool flag = false;
    int ind = 0;
    Node* temp = First;

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

int SortedLinkedList::Retrieve(int item)
{
    int flag = -1;
    Node* temp = First;

    while (temp != NULL)
    {
        if (temp->Value == item)
        {
            flag = item;
            break;
        }
        else
        {
            temp = temp->Next;
        }
    }
    return flag;
}

void SortedLinkedList::PrintList()
{
    if (!IsEmpty())
    {
        std::cout << "List: ";
        Node* temp = First;

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
int SortedLinkedList::GetSize()
{
    return Size;
}

int main()
{
    
}
