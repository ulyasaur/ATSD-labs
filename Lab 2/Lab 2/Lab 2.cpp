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
};

BBST::BBST(Node* root)
{
    Root = root;
}

int main()
{
    
}