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

    void PrintGraph();
    void AddItem(string father, string child, int weight);
    void Dijkstra(string source);
    int** AdjMatrix();

    int Size();
};

void Graph::PrintGraph()
{
    int** matrix = AdjMatrix();

    cout << "  ";

    for (int i = 0; i < Size(); i++)
    {
        cout.width(3);
        cout << Names[i] << " ";
    }
    cout << "\n";

    for (int i = 0; i < Size(); i++)
    {
        cout << Names[i] << " ";
        for (int j = 0; j < Size(); j++)
        {
            cout.width(3);
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

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

    if (!flagF)
    {
        Names.push_back(father);
        Nodes.push_back(new AdjList(new Node(father)));
        Nodes[Nodes.size() - 1]->AddItem(new Node(child, weight));
        return;
    }
    else
    {
        Nodes[index]->AddItem(new Node(child, weight));
    }
    
    if (!flagC)
    {
        Names.push_back(child);
        Nodes.push_back(new AdjList(new Node(child)));
        Nodes[Nodes.size() - 1]->AddItem(new Node(father, weight));
    }
}

void Graph::Dijkstra(string source)
{
    int srcInd;

    int* distance = new int[Size()];
    bool* isSet = new bool[Size()];

    int** matrix = AdjMatrix();
    for (int i = 0; i < Size(); i++)
    {
        distance[i] = INT_MAX;
        isSet[i] = false;
        if (Names[i] == source)
        {
            srcInd = i;
            distance[i] = 0;
            isSet[i] = true;
        }
    }

    for (int i = 0; i < Size(); i++)
    {
        if (matrix[srcInd][i] != 0)
        {
            distance[i] = matrix[srcInd][i];
        }        
    }

    for (int i = 0; i < Size(); i++)
    {
        int minIndex = -1, min = INT_MAX;
        for (int j = 0; j < Size(); j++)
        {
            if (!isSet[j] && distance[j] <= min)
            {
                min = distance[j];
                minIndex = j;
            }
        }
        isSet[minIndex] = true;

        for (int j = 0; j < Size(); j++)
        {
            if (!isSet[j] && matrix[minIndex][j] && distance[minIndex] != INT_MAX
                && distance[minIndex] + matrix[minIndex][j] < distance[j])
            {
                distance[j] = distance[minIndex] + matrix[minIndex][j];
            }
        }
    }

    cout << "Vertex   Distance\n";
    for (int i = 0; i < Size(); i++)
    {
        cout.width(6);
        cout << Names[i];
        cout.width(11);
        cout << distance[i];
        cout << "\n";
    }
}

int** Graph::AdjMatrix()
{
    int** matrix = new int*[Names.size()];

    for (int i = 0; i < Names.size(); i++)
    {
        matrix[i] = new int[Names.size()];

        for (int j = 0; j < Names.size(); j++)
        {
            matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < Nodes.size(); i++)
    {
        Node* temp = Nodes[i]->First->Next;

        for (int j = 0; j < Nodes.size(); j++)
        {
            for (int k = 0; k < Nodes.size(); k++)
            {
                if (temp->Name == Names[k])
                {
                    matrix[i][k] = temp->Weight;
                    matrix[k][i] = temp->Weight;
                    temp = temp->Next;
                    break;
                }
            }
            if (!temp)
            {
                break;
            }
        }
    }

    return matrix;
}

int Graph::Size()
{
    return Names.size();
}

int main()
{
    Graph* graph = new Graph();
    string father;
    string child;
    int weight;

    cin >> father >> child >> weight;

    while (weight != -1)
    {
        graph->AddItem(father, child, weight);
        cin >> father >> child >> weight;
    }

    graph->PrintGraph();

    graph->Dijkstra("1");
}