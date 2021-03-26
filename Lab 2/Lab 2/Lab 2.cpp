#include <iostream>
#include <algorithm>

template <class T>
class Node
{
public:
    T Value;
    int BalanceFactor;
    int Height;
    Node<T>* Left;
    Node<T>* Right;

    Node(T value = 0, int bf = 0, int height = 0, Node<T>* l = NULL, Node<T>* r = NULL);
};

template <class T>
Node<T>::Node(T value, int bf, int height, Node<T>* l, Node<T>* r)
{
    Value = value;
    BalanceFactor = bf;
    Height = height;
    Left = l;
    Right = r;
}

template <class T>
class BBST
{
public:
    Node<T>* Root;
    BBST(Node<T>* root = NULL);

    void Interface();
    bool IsEmpty();
    bool IsFull();
    int Size();
    void AddItem(T item);
    void DeleteItem(T item);
    bool Search(T item);
    void PrintPreorder();
    void PrintInorder();
    void PrintPostorder();

    void PrintSorted();
    int CountNode();
    T SumKeys();
    T FindSecondLargest();
    bool IsBalanced();
    bool EqualsBBST(BBST<T>* tree);
    T FatherNode(T item);
    T CommonAncestor(T first, T second);

private:
    void UpdateNode(Node<T>* node);
    Node<T>* BalanceTree(Node<T>* node);
    Node<T>* AddItem(Node<T>* node, T item);
    Node<T>* DeleteItem(Node<T>* node, T item);
    Node<T>* RightRotation(Node<T>* node);
    Node<T>* LeftRotation(Node<T>* node);
    void Size(int& size, Node<T>* next);
    bool Search(T item, Node<T>* next);
    void PrintPreorder(Node<T>* next);
    void PrintInorder(Node<T>* next);
    void PrintPostorder(Node<T>* next);

    void PrintAsc(Node<T>* node);
    void PrintDes(Node<T>* node);
    void CountNode(Node<T>* node, int& counter);
    void SumKeys(Node<T>* node, T& sum);
    void EqualsBBST(Node<T>* node, Node<T>* treeNode, bool& flag);
    T FatherNode(T item, Node<T>* node);
    T CommonAncestor(T first, T second, Node<T>* node);
};

template <class T>
BBST<T>::BBST(Node<T>* root)
{
    Root = root;
}

template <class T>
bool BBST<T>::IsEmpty()
{
    return Root == NULL;
}

template <class T>
bool BBST<T>::IsFull()
{
    Node<T>* temp = new Node<T>();
    bool result = temp == NULL;
    delete temp;

    return result;
}

template <class T>
int BBST<T>::Size()
{
    int size = 0;
    Size(size, Root);

    return size;
}

template <class T>
void BBST<T>::Size(int& size, Node<T>* next)
{
    if (next)
    {
        Size(size, next->Left);
        Size(size, next->Right);
        size++;
    }
}

template <class T>
void BBST<T>::UpdateNode(Node<T>* node)
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

template <class T>
Node<T>* BBST<T>::BalanceTree(Node<T>* node)
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

template <class T>
Node<T>* BBST<T>::RightRotation(Node<T>* node)
{
    Node<T>* parent = node->Left;
    node->Left = parent->Right;
    parent->Right = node;
    UpdateNode(node);
    UpdateNode(parent);
    return parent;
}

template <class T>
Node<T>* BBST<T>::LeftRotation(Node<T>* node)
{
    Node<T>* parent = node->Right;
    node->Right = parent->Left;
    parent->Left = node;
    UpdateNode(node);
    UpdateNode(parent);
    return parent;
}

template <class T>
void BBST<T>::AddItem(T item)
{
    if (!Search(item))
    {
        Root = AddItem(Root, item);
    }
}

template <class T>
Node<T>* BBST<T>::AddItem(Node<T>* node, T item)
{
    if (node == NULL)
    {
        return new Node<T>(item);
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

template <class T>
void BBST<T>::DeleteItem(T item)
{
    if (Search(item))
    {
        DeleteItem(Root, item);
    }
}

template <class T>
Node<T>* BBST<T>::DeleteItem(Node<T>* node, T item)
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
                Node<T>* temp = node->Left;
                while (temp->Right != NULL)
                {
                    temp = temp->Right;
                }
                node->Value = temp->Value;

                node->Left = DeleteItem(node->Left, temp->Value);
            }
            else
            {
                Node<T>* temp = node->Right;
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

template <class T>
bool BBST<T>::Search(T item)
{
    return Search(item, Root);
}

template <class T>
bool BBST<T>::Search(T item, Node<T>* next)
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

template <class T>
void BBST<T>::PrintPreorder()
{
    PrintPreorder(Root);
    std::cout << "\n";
}

template <class T>
void BBST<T>::PrintPreorder(Node<T>* next)
{
    if (next)
    {
        std::cout << next->Value << " ";
        PrintPreorder(next->Left);
        PrintPreorder(next->Right);
    }
}

template <class T>
void BBST<T>::PrintInorder()
{
    PrintInorder(Root);
    std::cout << "\n";
}

template <class T>
void BBST<T>::PrintInorder(Node<T>* next)
{
    if (next)
    {
        PrintInorder(next->Left);
        std::cout << next->Value << " ";
        PrintInorder(next->Right);
    }
}

template <class T>
void BBST<T>::PrintPostorder()
{
    PrintPostorder(Root);
    std::cout << "\n";
}

template <class T>
void BBST<T>::PrintPostorder(Node<T>* next)
{
    if (next)
    {
        PrintPostorder(next->Left);
        PrintPostorder(next->Right);
        std::cout << next->Value << " ";
    }
}

template <class T>
void BBST<T>::PrintSorted()
{

    PrintAsc(Root);
    std::cout << "\n";
    PrintDes(Root);
    std::cout << "\n";
}

template <class T>
void BBST<T>::PrintAsc(Node<T>* node)
{
    if (node != NULL)
    {
        PrintAsc(node->Left);
        std::cout << node->Value << " ";
        PrintAsc(node->Right);
    }
}

template <class T>
void BBST<T>::PrintDes(Node<T>* node)
{
    if (node != NULL)
    {
        PrintDes(node->Right);
        std::cout << node->Value << " ";
        PrintDes(node->Left);
    }
}

template <class T>
int BBST<T>::CountNode()
{
    int counter = 0;
    CountNode(Root, counter);
    return counter;
}

template <class T>
void BBST<T>::CountNode(Node<T>* node, int& counter)
{
    if (node != NULL)
    {
        if (node->Left != NULL)
        {
            CountNode(node->Left, ++counter);
        }
        CountNode(node->Right, counter);
    }
}

template <class T>
T BBST<T>::SumKeys()
{
    T sum = 0;
    SumKeys(Root, sum);
    return sum;
}

template <class T>
void BBST<T>::SumKeys(Node<T>* node, T& sum)
{
    if (node != NULL)
    {
        if (node->Right != NULL)
        {
            sum += node->Right->Value;
            SumKeys(node->Right, sum);
        }
        SumKeys(node->Left, sum);
    }
}

template <class T>
T BBST<T>::FindSecondLargest()
{
    Node<T>* temp = Root;

    while (temp->Right->Right)
    {
        temp = temp->Right;
    }

    return temp->Value;
}

template <class T>
bool BBST<T>::IsBalanced()
{
    return Root->BalanceFactor < 2 && Root->BalanceFactor > -2;
}

template <class T>
bool BBST<T>::EqualsBBST(BBST<T>* tree)
{
    bool flag = true;
    EqualsBBST(Root, tree->Root, flag);
    return flag;
}

template <class T>
void BBST<T>::EqualsBBST(Node<T>* node, Node<T>* treeNode, bool& flag)
{
    if (node && treeNode)
    {
        if (node->Value != treeNode->Value)
        {
            flag = false;
            return;
        }

        EqualsBBST(node->Left, treeNode->Left, flag);
        EqualsBBST(node->Right, treeNode->Right, flag);
    }
    else if (node && !treeNode || !node && treeNode)
    {
        flag = false;
        return;
    }
}

template <class T>
T BBST<T>::FatherNode(T item)
{
    if (Search(item) && item != Root->Value)
    {
        return FatherNode(item, Root);
    }

    return NULL;
}

template <class T>
T BBST<T>::FatherNode(T item, Node<T>* node)
{
    if (node->Value < item && node->Right->Value != item)
    {
        return FatherNode(item, node->Right);
    }
    else if (node->Value > item && node->Left->Value != item)
    {
        return FatherNode(item, node->Left);
    }

    return node->Value;
}

template <class T>
T BBST<T>::CommonAncestor(T first, T second)
{
    if (Search(first) && Search(second) && Root->Value != first && Root->Value != second)
    {
        return CommonAncestor(first, second, Root);
    }

    return NULL;
}

template <class T>
T BBST<T>::CommonAncestor(T first, T second, Node<T>* node)
{
    if (node->Value < first && node->Value < second && (node->Right->Value != first && node->Right->Value != second))
    {
        return CommonAncestor(first, second, node->Right);
    }
    else if (node->Value > first && node->Value > second && (node->Left->Value != first && node->Left->Value != second))
    {
        return CommonAncestor(first, second, node->Left);
    }

    return node->Value;
}

template <class T>
void BBST<T>::Interface()
{
    std::cout << "Enter your linked list. Enter -1 to stop.\n";

    T n;

    while (true)
    {
        std::cin >> n;

        if (n != -1)
        {
            AddItem(n);
        }
        else
        {
            break;
        }
    }

    bool flag = true;
    T item;

    std::cout << "Choose operation:\n "
        << "1 - IsEmpty\n "
        << "2 - IsFull\n "
        << "3 - AddItem\n "
        << "4 - DeleteItem\n "
        << "5 - Search\n "
        << "6 - PrintPreorder\n "
        << "7 - PrintInorder\n "
        << "8 - PrintPostorder\n "
        << "9 - Size\n "
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
                std::cout << "Tree is empty\n";
            }
            else
            {
                std::cout << "Tree is not empty\n";
            }
            break;

        case 2:
            if (IsFull())
            {
                std::cout << "Tree is full\n";
            }
            else
            {
                std::cout << "Tree is not full\n";
            }
            break;

        case 3:
            std::cout << "Enter an item to add: ";
            std::cin >> item;
            AddItem(item);
            break;

        case 4:
            std::cout << "Enter an item to delete: ";
            std::cin >> item;
            DeleteItem(item);
            break;

        case 5:
            std::cout << "Enter an item to search: ";
            std::cin >> item;

            if (Search(item))
            {
                std::cout << "Item is in the tree\n";
            }
            else
            {
                std::cout << "Item is not in the tree\n";
            }
            break;

        case 6:
            PrintPreorder();
            break;

        case 7:
            PrintInorder();
            break;

        case 8:
            PrintPostorder();
            break;

        case 9:
            std::cout << "Size of your tree: " << Size() << "\n";
            break;

        case 0:
            flag = false;
            break;
        }
    }
}

int main()
{
    BBST<int>* tree = new BBST<int>();
    tree->Interface();
}