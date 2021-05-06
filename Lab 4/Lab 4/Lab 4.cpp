#include <iostream>
#include <string>

using namespace std;

class Node
{
public:
    string Name;
    int Weight;
    Node* Next;

    Node(string name = "",  int val = 0, Node* next = NULL);
};

Node::Node(string name, int val, Node* next)
{
    Name = name;
    Weight = val;
    Next = next;
}

class AdjList
{
public:
    AdjList(Node* first = NULL);
    void AddItem(Node* node);

private:
    Node* First;
};

AdjList::AdjList(Node* first)
{
    First = first;
}

void AdjList::AddItem(Node* node)
{
    Node* temp = First;
    while (temp->Next)
    {
        temp = temp->Next;
    }

    temp->Next = node;
}

int main()
{

}