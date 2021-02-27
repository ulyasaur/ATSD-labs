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
    int Size();
    bool Search(int item);
    void PrintPreorder();
    void PrintInorder();
    void PrintPostorder();

private:
    void Size(int& size, Node* next);
    bool Search(int item, Node* next);
    void PrintPreorder(Node* next);
    void PrintInorder(Node* next);
    void PrintPostorder(Node* next);
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

int BBST::Size()
{
    int size = 0;
    Size(size, Root);

    return size;
}

void BBST::Size(int& size, Node* next)
{
    if (next)
    {
        Size(size, next->Left);
        Size(size, next->Right);
        size++;
    }
}

bool BBST::Search(int item)
{
    return Search(item, Root);
}

bool BBST::Search(int item, Node* next)
{

    if (next)
    {
        if (item == next->Value)
        {
            return true;
        }
        else if (item < next->Value)
        {
            return Search(item, next->Left);
        }
        else
        {
            return Search(item, next->Right);
        }
    }

    return false;
}

void BBST::PrintPreorder()
{
    PrintPreorder(Root);
}

void BBST::PrintPreorder(Node* next)
{
    if (next)
    {
        std::cout << next->Value << " ";
        PrintPreorder(next->Left);
        PrintPreorder(next->Right);
    }
}

void BBST::PrintInorder()
{
    PrintInorder(Root);
}

void BBST::PrintInorder(Node* next)
{
    if (next)
    {
        PrintInorder(next->Left);
        std::cout << next->Value << " ";
        PrintInorder(next->Right);
    }
}

void BBST::PrintPostorder()
{
    PrintPostorder(Root);
}

void BBST::PrintPostorder(Node* next)
{
    if (next)
    {
        PrintPostorder(next->Left);
        PrintPostorder(next->Right);
        std::cout << next->Value << " ";
    }
}

int main()
{
    
}