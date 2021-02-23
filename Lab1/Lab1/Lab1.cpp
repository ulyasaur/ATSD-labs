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

int main()
{
    
}
