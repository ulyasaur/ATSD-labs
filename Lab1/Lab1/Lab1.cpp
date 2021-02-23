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
    bool IsEmpty();
    void AddItem(int item);
    int DeleteItem(int item);
    int Search(int item);
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

bool SortedLinkedList::IsEmpty()
{
    return Size == 0;
}

void SortedLinkedList::AddItem(int item)
{
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

        now->Next = new Node(item, now->Next);
    }
    Size++;
}

int SortedLinkedList::DeleteItem(int item)
{
    int counter = 0;

    while (First && First->Value == item)
    {
        Node* temp = First;
        First = First->Next;
        delete temp;
        counter++;
    }

    if (!counter)
    {
        Node* now = First;

        while (now && now->Value < item)
        {
            while (now->Next && now->Next->Value == item)
            {
                Node* temp = now->Next;
                now->Next = temp->Next;
                delete temp;
                counter++;
            }
            now = now->Next;
        }
    }

    Size -= counter;

    if (counter)
    {
        std::cout << "Deleted " << counter << " occurences of " << item << '\n';
        return item;
    }
    else
    {
        std::cout << "Item was not found in list\n";
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
    SortedLinkedList* List = new SortedLinkedList();
    std::cout << "Enter your linked list. Enter negative number to stop.\n";

    int n;

    while (true)
    {
        std::cin >> n;

        if (n >= 0)
        {
            List->AddItem(n);
        }
        else
        {
            break;
        }
    }

    std::cout << "Your list: ";
    List->PrintList();

    bool flag = true;
    int item;

    std::cout << "Choose operation:\n "
        << "1 - IsEmpty\n "
        << "2 - AddItem\n "
        << "3 - DeleteItem\n "
        << "4 - Search\n "
        << "5 - PrintList\n "
        << "6 - GetSize\n "
        << "0 - Quit program\n ";

    while (flag)
    {
        int operation;
        std::cin >> operation;

        switch (operation)
        {
        case 1:
            if (List->IsEmpty())
            {
                std::cout << "List is empty\n";
            }
            else
            {
                std::cout << "List is not empty\n";
            }
            break;

        case 2:
            std::cout << "Enter an item to add: ";
            std::cin >> item;
            List->AddItem(item);
            List->PrintList();
            break;

        case 3:
            std::cout << "Enter an item to delete: ";
            std::cin >> item;
            if (item == List->DeleteItem(item))
            {
                std::cout << "Item was deleted\n";
                List->PrintList();
            }
            else
            {
                std::cout << "Item was not deleted\n";
            }
            break;

        case 4:
            std::cout << "Enter an item to search: ";
            std::cin >> item;
            std::cout << "Its position in the list: " << List->Search(item) << "\n";
            break;

        case 5:
            List->PrintList();
            break;

        case 6:
            std::cout << "Size of your list: " << List->GetSize() << "\n";
            break;

        default:
            flag = false;
            break;
        }

    }

}




