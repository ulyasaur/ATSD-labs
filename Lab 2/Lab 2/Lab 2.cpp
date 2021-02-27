#include <iostream>

class Node
{
public:
    int Value;
    Node* Left;
    Node* Right;

    Node(int value = 0, Node* l = NULL, Node* r = NULL);
};

Node::Node(int value, Node* l, Node* r)
{
    Value = value;
    Left = l;
    Right = r;
}

class BBST
{
public:
    Node* Root;
    BBST(Node* root = NULL);

    bool IsEmpty();
    bool IsFull();
};

BBST::BBST(Node* root)
{
    Root = root;
}

bool BBST::IsEmpty()
{
    return Root == NULL;
}

bool BBST::IsFull()
{
    Node* temp = new Node();
    bool result = temp == NULL;
    delete temp;

    return result;
}

int main()
{
    
}