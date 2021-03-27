#include <iostream>
#include <algorithm>
#include <string>
#include <type_traits>

template <class T>
class Node
{
public:
    T Value;
    int BalanceFactor;
    int Height;
    Node<T>* Left;
    Node<T>* Right;

    Node(T value = NULL, int bf = 0, int height = 0, Node<T>* l = NULL, Node<T>* r = NULL);
    Node(bool flag);
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
Node<T>::Node(bool flag)
{
}



template <class T>
class BBST
{
public:
    Node<T>* Root;
    BBST(Node<T>* root = NULL);

    void TreeDiagram();
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
    void DeleteEven();
    int FindMiddle();
    T FindSecondLargest();
    BBST<T>* CopyBBST();
    void InsertBBST(BBST<T>* tree);
    bool ContainsBBST(BBST<T>* tree);
    bool IsBalanced();
    bool EqualsBBST(BBST<T>* tree);
    BBST<T>* SymmetricalBBST();
    T FatherNode(T item);
    T CommonAncestor(T first, T second);

private:
    void TreeDiagram(Node<T>* node, int level);
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
    Node<int>* DeleteEven(Node<int>* node);
    int FindMiddle(Node<int>* node, int key);
    std::string SumKeys(Node<std::string>* node);
    int SumKeys(Node<int>* node);
    Node<T>* CopyBBST(Node<T>* node, Node<T>* treeNode);
    void InsertBBST(Node<T>* node);
    bool ContainsBBST(Node<T>* node);
    void EqualsBBST(Node<T>* node, Node<T>* treeNode, bool& flag);
    Node<T>* SymmetricalBBST(Node<T>* node, Node<T>* treeNode);
    T FatherNode(T item, Node<T>* node);
    T CommonAncestor(T first, T second, Node<T>* node);
};

template <class T>
BBST<T>::BBST(Node<T>* root)
{
    Root = root;
}

template <class T>
void BBST<T>::TreeDiagram()
{
    TreeDiagram(Root, 0);
}

template <class T>
void BBST<T>::TreeDiagram(Node<T>* node, int level)
{
    if (node)
    {
        TreeDiagram(node->Right, level + 1);
        for (int i = 0; i < level; i++)
        {
            std::cout << "   ";
        }
        std::cout << node->Value << std::endl;
        TreeDiagram(node->Left, level + 1);
    }
}

template <class T>
bool BBST<T>::IsEmpty()
{
    return Root == NULL;
}

template <class T>
bool BBST<T>::IsFull()
{
    Node<T>* temp = new Node<T>(true);
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
    return SumKeys(Root);
}

template <>
std::string BBST<std::string>::SumKeys(Node<std::string>* node)
{
    if (node != NULL)
    {
        std::string sum;
        if (node->Right)
        {
            sum = node->Right->Value;
            sum += SumKeys(node->Right);
        }
        
        if (node->Left)
        {
            sum += SumKeys(node->Left);
        }

        return sum;
    }
}

template <>
int BBST<int>::SumKeys(Node<int>* node)
{
    if (node != NULL)
    {
        int sum = NULL;
        if (node->Right)
        {
            sum = node->Right->Value;
            sum += SumKeys(node->Right);
        }
        
        if (node->Left)
        {
            sum += SumKeys(node->Left);
        }

        return sum;
    }
}

template <>
void BBST<int>::DeleteEven()
{
    Root = DeleteEven(Root);
}

template <>
Node<int>* BBST<int>::DeleteEven(Node<int>* node)
{
    if (node)
    {
        while (node && node->Value % 2 == 0)
        {
            node = DeleteItem(node, node->Value);
        }

        if (node)
        {
            node->Left = DeleteEven(node->Left);
            node->Right = DeleteEven(node->Right);
        }

        return node;
    }

    return NULL;
}

template <>
int BBST<int>::FindMiddle()
{
    int key = 0;
    Node<int>* temp = Root;

    while (temp && temp->Left)
    {
        temp = temp->Left;
    }

    key += temp->Value;

    temp = Root;

    while (temp && temp->Right)
    {
        temp = temp->Right;
    }

    key += temp->Value;
    key /= 2;

    return FindMiddle(Root, key);

}

template <>
int BBST<int>::FindMiddle(Node<int>* node, int key)
{
    if (node)
    {
        int l = FindMiddle(node->Left, key);
        int r = FindMiddle(node->Right, key);

        int nval = abs(node->Value - key);
        int lval = abs(l - key);
        int rval = abs(r - key);

        if (nval < lval && nval < rval)
        {
            return node->Value;
        }
        else if (rval < lval && rval < nval)
        {
            return r;
        }

        return l;
    }
}

template <class T>
T BBST<T>::FindSecondLargest()
{
    Node<T>* temp = Root;

    while (temp->Right && temp->Right->Right)
    {
        temp = temp->Right;
    }

    return temp->Value;
}

template <class T>
BBST<T>* BBST<T>::CopyBBST()
{
    BBST<T>* copy = new BBST<T>();
    copy->Root = CopyBBST(Root, copy->Root);
    return copy;
}

template <class T>
Node<T>* BBST<T>::CopyBBST(Node<T>* node, Node<T>* treeNode)
{
    if (node)
    {
        treeNode = new Node<T>(node->Value, node->BalanceFactor, node->Height);

        treeNode->Left = CopyBBST(node->Left, treeNode->Left);
        treeNode->Right = CopyBBST(node->Right, treeNode->Right);

        return treeNode;
    }
    else
    {
        return NULL;
    }
}

template <class T>
void BBST<T>::InsertBBST(BBST<T>* tree)
{
    InsertBBST(tree->Root);
}

template <class T>
void BBST<T>::InsertBBST(Node<T>* node)
{
    if (node)
    {
        AddItem(node->Value);
        InsertBBST(node->Left);
        InsertBBST(node->Right);
    }
}

template <class T>
bool BBST<T>::ContainsBBST(BBST<T>* tree)
{
    return ContainsBBST(tree->Root);
}

template <class T>
bool BBST<T>::ContainsBBST(Node<T>* node)
{
    if (node)
    {
        return Search(node->Value) && ContainsBBST(node->Left) && ContainsBBST(node->Right);
    }

    return true;
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
BBST<T>* BBST<T>::SymmetricalBBST()
{
    BBST<T>* copy = new BBST<T>();
    copy->Root = SymmetricalBBST(Root, copy->Root);
    return copy;
}

template <class T>
Node<T>* BBST<T>::SymmetricalBBST(Node<T>* node, Node<T>* treeNode)
{
    if (node)
    {
        treeNode = new Node<T>(node->Value, node->BalanceFactor, node->Height);

        treeNode->Left = SymmetricalBBST(node->Right, treeNode->Left);
        treeNode->Right = SymmetricalBBST(node->Left, treeNode->Right);

        return treeNode;
    }
    else
    {
        return NULL;
    }
}

template <class T>
T BBST<T>::FatherNode(T item)
{
    if (Search(item) && item != Root->Value)
    {
        return FatherNode(item, Root);
    }

    return item;
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

    return first + second;
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

int main()
{
    std::cout << "Choose int {i} or string {s}\n";
    char op;
    std::cin >> op;

    if (op == 's')
    {
        BBST<std::string>* tree = new BBST<std::string>();

        std::cout << "Enter keys of your binary tree. Enter -1 to stop.\n";

        std::string n;

        while (true)
        {
            std::cin >> n;

            if (n != "-1")
            {
                tree->AddItem(n);
            }
            else
            {
                break;
            }
        }

        std::cout << "Your tree now:\n";
        tree->TreeDiagram();

        bool flag = true;

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
            << "10 - PrintSorted\n"
            << "11 - CountNode\n"
            << "12 - SumKeys\n"
            << "13 - FindSecondLargest\n"
            << "14 - CopyBBST\n"
            << "15 - InsertBBST\n"
            << "16 - ContainsBBST\n"
            << "17 - IsBalanced\n"
            << "18 - EqualsBBST\n"
            << "10 - SymmetricalBBST\n"
            << "20 - FatherNode\n"
            << "21 - CommonAncestor\n"
            << "0 - Quit program\n ";

        while (flag)
        {
            std::string item;
            BBST<std::string>* tree1 = new BBST<std::string>();

            int operation;
            std::cin >> operation;

            switch (operation)
            {
            case 1:
                if (tree->IsEmpty())
                {
                    std::cout << "Tree is empty\n";
                }
                else
                {
                    std::cout << "Tree is not empty\n";
                }
                break;

            case 2:
                if (tree->IsFull())
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
                tree->AddItem(item);
                std::cout << "Your tree now:\n";
                tree->TreeDiagram();
                break;

            case 4:
                std::cout << "Enter an item to delete: ";
                std::cin >> item;
                tree->DeleteItem(item);
                std::cout << "Your tree now:\n";
                tree->TreeDiagram();
                break;

            case 5:
                std::cout << "Enter an item to search: ";
                std::cin >> item;

                if (tree->Search(item))
                {
                    std::cout << "Item is in the tree\n";
                }
                else
                {
                    std::cout << "Item is not in the tree\n";
                }
                break;

            case 6:
                tree->PrintPreorder();
                break;

            case 7:
                tree->PrintInorder();
                break;

            case 8:
                tree->PrintPostorder();
                break;

            case 9:
                std::cout << "Size of your tree: " << tree->Size() << "\n";
                break;

            case 10:
                tree->PrintSorted();
                break;

            case 11:
                std::cout << "Number of left son nodes: " << tree->CountNode() << "\n";
                break;

            case 12:
                std::cout << "Sum of keys in right son nodes: " << tree->SumKeys() << "\n";
                break;

            case 13:
                std::cout << "The second largest key: " << tree->FindSecondLargest() << "\n";
                break;

            case 14:
                tree1 = tree->CopyBBST();
                std::cout << "Copy of your tree:\n";
                tree1->TreeDiagram();
                break;

            case 15:
                std::cout << "Enter keys of your binary tree. Enter -1 to stop.\n";

                while (true)
                {
                    std::cin >> n;

                    if (n != "-1")
                    {
                        tree1->AddItem(n);
                    }
                    else
                    {
                        break;
                    }
                }
                std::cout << "You entered:\n";
                tree1->TreeDiagram();

                tree->InsertBBST(tree1);
                std::cout << "Your tree now:\n";
                tree->TreeDiagram();
                break;

            case 16:
                std::cout << "Enter keys of your binary tree. Enter -1 to stop.\n";

                while (true)
                {
                    std::cin >> n;

                    if (n != "-1")
                    {
                        tree1->AddItem(n);
                    }
                    else
                    {
                        break;
                    }
                }

                std::cout << "You entered:\n";
                tree1->TreeDiagram();

                if (tree->ContainsBBST(tree1))
                {
                    std::cout << "This BBST is in the tree\n";
                }
                else
                {
                    std::cout << "This BBST is not in the tree\n";
                }
                break;

            case 17:
                if (tree->IsBalanced())
                {
                    std::cout << "Tree is balanced\n";
                }
                else
                {
                    std::cout << "Tree is not balanced\n";
                }
                break;

            case 18:
                std::cout << "Enter keys of your binary tree. Enter -1 to stop.\n";

                while (true)
                {
                    std::cin >> n;

                    if (n != "-1")
                    {
                        tree1->AddItem(n);
                    }
                    else
                    {
                        break;
                    }
                }

                std::cout << "You entered:\n";
                tree1->TreeDiagram();

                if (tree->EqualsBBST(tree1))
                {
                    std::cout << "Trees are equal\n";
                }
                else
                {
                    std::cout << "Trees are not equal\n";
                }
                break;

            case 19:
                tree1 = tree->SymmetricalBBST();
                std::cout << "Symmetrical tree:\n";
                tree1->TreeDiagram();
                break;

            case 20:
                std::cout << "Enter key:\n";
                std::cin >> item;
                std::cout << "Father node: " << tree->FatherNode(item) << "\n";
                break;

            case 21:
                std::cout << "Enter keys:\n";
                std::cin >> item >> n;
                std::cout << "Ancestor: " << tree->CommonAncestor(item, n) << "\n";
                break;

            case 0:
                flag = false;
                break;
            }
        }
    }
    else
    {
        BBST<int>* tree = new BBST<int>();

        std::cout << "Enter keys of your binary tree. Enter -1 to stop.\n";

        int n;

        while (true)
        {
            std::cin >> n;

            if (n != -1)
            {
                tree->AddItem(n);
            }
            else
            {
                break;
            }
        }

        std::cout << "Your tree now:\n";
        tree->TreeDiagram();

        bool flag = true;

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
            << "10 - PrintSorted\n"
            << "11 - CountNode\n"
            << "12 - SumKeys\n"
            << "13 - DeleteEven\n"
            << "14 - FindMiddle\n"
            << "15 - FindSecondLargest\n"
            << "16 - CopyBBST\n"
            << "17 - InsertBBST\n"
            << "18 - ContainsBBST\n"
            << "19 - IsBalanced\n"
            << "20 - EqualsBBST\n"
            << "21 - SymmetricalBBST\n"
            << "22 - FatherNode\n"
            << "23 - CommonAncestor\n"
            << "0 - Quit program\n ";

        while (flag)
        {
            int item;
            BBST<int>* tree1 = new BBST<int>();

            int operation;
            std::cin >> operation;

            switch (operation)
            {
            case 1:
                if (tree->IsEmpty())
                {
                    std::cout << "Tree is empty\n";
                }
                else
                {
                    std::cout << "Tree is not empty\n";
                }
                break;

            case 2:
                if (tree->IsFull())
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
                tree->AddItem(item);
                std::cout << "Your tree now:\n";
                tree->TreeDiagram();
                break;

            case 4:
                std::cout << "Enter an item to delete: ";
                std::cin >> item;
                tree->DeleteItem(item);
                std::cout << "Your tree now:\n";
                tree->TreeDiagram();
                break;

            case 5:
                std::cout << "Enter an item to search: ";
                std::cin >> item;

                if (tree->Search(item))
                {
                    std::cout << "Item is in the tree\n";
                }
                else
                {
                    std::cout << "Item is not in the tree\n";
                }
                break;

            case 6:
                tree->PrintPreorder();
                break;

            case 7:
                tree->PrintInorder();
                break;

            case 8:
                tree->PrintPostorder();
                break;

            case 9:
                std::cout << "Size of your tree: " << tree->Size() << "\n";
                break;

            case 10:
                tree->PrintSorted();
                break;

            case 11:
                std::cout << "Number of left son nodes: " << tree->CountNode() << "\n";
                break;

            case 12:
                std::cout << "Sum of keys in right son nodes: " << tree->SumKeys() << "\n";
                break;

            case 13:
                tree->DeleteEven();
                std::cout << "Your tree now:\n";
                tree->TreeDiagram();
                break;

            case 14:
                std::cout << "The tree key which is the nearest to the valuemid: " << tree->FindMiddle() << "\n";
                break;

            case 15:
                std::cout << "The second largest key: " << tree->FindSecondLargest() << "\n";
                break;

            case 16:
                tree1 = tree->CopyBBST();
                std::cout << "Copy of your tree:\n";
                tree1->TreeDiagram();
                break;

            case 17:
                std::cout << "Enter keys of your binary tree. Enter -1 to stop.\n";

                while (true)
                {
                    std::cin >> n;

                    if (n != -1)
                    {
                        tree1->AddItem(n);
                    }
                    else
                    {
                        break;
                    }
                }

                std::cout << "You entered:\n";
                tree1->TreeDiagram();

                tree->InsertBBST(tree1);
                std::cout << "Your tree now:\n";
                tree->TreeDiagram();
                break;

            case 18:
                std::cout << "Enter keys of your binary tree. Enter -1 to stop.\n";

                while (true)
                {
                    std::cin >> n;

                    if (n != -1)
                    {
                        tree1->AddItem(n);
                    }
                    else
                    {
                        break;
                    }
                }

                std::cout << "You entered:\n";
                tree1->TreeDiagram();

                if (tree->ContainsBBST(tree1))
                {
                    std::cout << "This BBST is in the tree\n";
                }
                else
                {
                    std::cout << "This BBST is not in the tree\n";
                }
                break;

            case 19:
                if (tree->IsBalanced())
                {
                    std::cout << "Tree is balanced\n";
                }
                else
                {
                    std::cout << "Tree is not balanced\n";
                }
                break;

            case 20:
                std::cout << "Enter keys of your binary tree. Enter -1 to stop.\n";

                while (true)
                {
                    std::cin >> n;

                    if (n != -1)
                    {
                        tree1->AddItem(n);
                    }
                    else
                    {
                        break;
                    }
                }

                std::cout << "You entered:\n";
                tree1->TreeDiagram();

                if (tree->EqualsBBST(tree1))
                {
                    std::cout << "Trees are equal\n";
                }
                else
                {
                    std::cout << "Trees are not equal\n";
                }
                break;

            case 21:
                tree1 = tree->SymmetricalBBST();
                std::cout << "Symmetrical tree:\n";
                tree1->TreeDiagram();
                break;

            case 22:
                std::cout << "Enter key:\n";
                std::cin >> item;
                std::cout << "Father node: " << tree->FatherNode(item) << "\n";
                break;

            case 23:
                std::cout << "Enter keys:\n";
                std::cin >> item >> n;
                std::cout << "Ancestor: " << tree->CommonAncestor(item, n) << "\n";
                break;

            case 0:
                flag = false;
                break;
            }
    }
}
}