#include <iostream>
#include <string>

using namespace std;

class Node
{
public:
    string Name;
    int Value;
    Node* Next;

    Node(string name = "",  int val = -1, Node* next = NULL);
};

Node::Node(string name, int val, Node* next)
{
    Name = name;
    Value = val;
    Next = next;
}

int main()
{
}