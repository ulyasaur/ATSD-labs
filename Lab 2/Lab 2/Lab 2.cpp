#include <iostream>
#include <algorithm>

class Node
{
public:
    int Value;
    int BalanceFactor;
    int Height;
    Node* Left;
    Node* Right;

    Node(int value = 0, int bf = 0, int height = 0, Node* l = NULL, Node* r = NULL);
};

Node::Node(int value, int bf, int height, Node* l, Node* r)
{
    Value = value;
    BalanceFactor = bf;
    Height = height;
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
    void AddItem(int item);
    void DeleteItem(int item);
    bool Search(int item);
    void PrintPreorder();
    void PrintInorder();
    void PrintPostorder();

private:
    void UpdateNode(Node* node);
    Node* BalanceTree(Node* node);
    Node* AddItem(Node* node, int item);
    Node* DeleteItem(Node* node, int item);
    Node* RightRotation(Node* node);
    Node* LeftRotation(Node* node);
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

void BBST::UpdateNode(Node* node)
{
    int leftHeight;
    if (node->Left == NULL)
    {
        leftHeight = -1;
    }
    else
    {
        leftHeight = node->Left->Height;
    }

    int rightHeight;
    if (node->Right == NULL)
    {
        rightHeight = -1;
    }
    else
    {
        rightHeight = node->Right->Height;
    }

    node->Height = 1 + std::max(leftHeight, rightHeight);
    node->BalanceFactor = rightHeight - leftHeight;
}

Node* BBST::BalanceTree(Node* node)
{
    if (node->BalanceFactor == -2)
    {
        if (node->Left->BalanceFactor <= 0)
        {
            return RightRotation(node);
        }
        else
        {
            node->Left = LeftRotation(node->Left);
            return RightRotation(node);
        }
    }
    else if (node->BalanceFactor == 2)
    {
        if (node->Right->BalanceFactor >= 0)
        {
            return LeftRotation(node);
        }
        else
        {
            node->Right = RightRotation(node->Right);
            return LeftRotation(node);
        }
    }
}

Node* BBST::RightRotation(Node* node)
{
    Node* parent = node->Left;
    node->Left = parent->Right;
    parent->Right = node;
    UpdateNode(node);
    UpdateNode(parent);
    return parent;
}

Node* BBST::LeftRotation(Node* node)
{
    Node* parent = node->Right;
    node->Right = parent->Left;
    parent->Left = node;
    UpdateNode(node);
    UpdateNode(parent);
    return parent;
}

void BBST::AddItem(int item)
{
    if (!Search(item))
    {
        Root = AddItem(Root, item);
    }
    else
    {
        std::cout << "Item is already in the tree\n";
    }
}

Node* BBST::AddItem(Node* node, int item)
{
    if (node == NULL)
    {
        return new Node(item);
    }

    if (item < node->Value)
    {
        node->Left = AddItem(node->Left, item);
    }
    else
    {
        node->Right = AddItem(node->Right, item);
    }

    UpdateNode(node);
    

    return BalanceTree(node);
}

void BBST::DeleteItem(int item)
{
    if (Search(item))
    {
        DeleteItem(Root, item);
    }
    else
    {
        std::cout << "Item isn't in the tree.\n";
    }
}

Node* BBST::DeleteItem(Node* node, int item)
{
    if (node == NULL)
    {
        return NULL;
    } 

    if (item > node->Value)
    {
        node->Right = DeleteItem(node->Right, item);
    }
    else if (item < node->Value)
    {
        node->Left = DeleteItem(node->Left, item);
    }
    else
    {
        if (node->Left == NULL) 
        {
            return node->Right;
        }
        else if (node->Right == NULL) 
        {
            return node->Left;
        }
        else 
        {
            if (node->Left->Height > node->Right->Height) 
            {
                Node* temp = node->Left;
                while (temp->Right != NULL)
                {
                    temp = temp->Right;
                }
                node->Value = temp->Value;

                node->Left = DeleteItem(node->Left, temp->Value);
            }
            else 
            {
                Node* temp = node->Right;
                while (temp->Left != NULL)
                {
                    temp = temp->Left;
                }
                node->Value = temp->Value;

                node->Right = DeleteItem(node->Right, temp->Value);
            }
        }
    }

    UpdateNode(node);
    return BalanceTree(node);
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