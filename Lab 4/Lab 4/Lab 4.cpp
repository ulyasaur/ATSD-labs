#include <iostream>
#include <string>
#include <vector>

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

class Graph
{
public:
    vector<AdjList*> Nodes;
    vector<string> Names;

    void AddItem(string father, string child, int weight);
};

void Graph::AddItem(string father, string child, int weight)
{
    bool flagF = false;
    bool flagC = false;
    int index = -1;
    for (int i = 0; i < Names.size(); i++)
    {
        if (Names[i] == father)
        {
            flagF = true;
            index = i;
        }

        if (Names[i] == child)
        {
            flagC = true;
        }
    }

    if (!flagC)
    {
        Names.push_back(child);
        Nodes.push_back(new AdjList(new Node(child)));
        return;
    }
    
    if (!flagF)
    {
        Names.push_back(child);
        Nodes.push_back(new AdjList(new Node(child)));
        Nodes[Nodes.size() - 1]->AddItem(new Node(child, weight));
        return;
    }

    Nodes[index]->AddItem(new Node(child, weight));
}

int main()
{

}