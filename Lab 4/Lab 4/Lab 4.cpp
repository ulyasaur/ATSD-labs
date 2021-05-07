#include <iostream>
#include <string>

using namespace std;

class Node
{
public:
    string Name;
    int Weight;
    Node* Next;

    Node(string name = "", int val = 0, Node* next = NULL);
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
    string* Names;
    int** Matrix;
    int Size;
    int Edge;
    Graph();

    void PrintGraph();
    void PrintAdj(AdjList** list, int weight);
    void Dijkstra(string source);
    void Kruskal();
    void Prim();
    pair<int, pair<string, string>>* Edges();
    AdjList** ToList(pair<int, pair<string, string>> mst[]);

private:
    int Find(int parent[], int ind);
    int Index(string names[], string name);
};

Graph::Graph()
{
    cout << "Enter amount of graph nodes: ";
    cin >> Size;
    Names = new string[Size];
    Matrix = new int*[Size];
    Edge = 0;

    cout << "Enter names of graph nodes: ";

    for (int i = 0; i < Size; i++)
    {
        cin >> Names[i];
        Matrix[i] = new int[Size];
    }

    for (int i = 0; i < Size; i++)
    {
        for (int j = i; j < Size; j++)
        {
            cout << "Weight of edge " << Names[i] << " - " << Names[j] << " : ";
            int value;
            cin >> value;
            Matrix[i][j] = value;
            Matrix[j][i] = value;
            if (value != 0)
            {
                Edge++;
            }
        }
    }
}

void Graph::PrintGraph()
{
    cout << "  ";

    for (int i = 0; i < Size; i++)
    {
        cout.width(3);
        cout << Names[i] << " ";
    }
    cout << "\n";

    for (int i = 0; i < Size; i++)
    {
        cout << Names[i] << " ";
        for (int j = 0; j < Size; j++)
        {
            cout.width(3);
            cout << Matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

void Graph::PrintAdj(AdjList** list, int weight)
{
    cout << "\nPrim method:\n";
    cout << "Adjacency lists:\n";

    for (int i = 0; i < Size; ++i)
    {
        cout << list[i]->First->Name;
        Node* temp = list[i]->First->Next;
        while (temp)
        {
            cout << " -> " << temp->Name << "(" << temp->Weight << ")";
            temp = temp->Next;
        }
        cout << "\n";
    }
    cout << "\nWeight of MST is " << weight << "\n";
}

void Graph::Dijkstra(string source)
{
    if (Index(Names, source) != -1)
    {
        int srcInd;

        int* distance = new int[Size];
        bool* isSet = new bool[Size];

        for (int i = 0; i < Size; i++)
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

        for (int i = 0; i < Size; i++)
        {
            if (Matrix[srcInd][i] != 0)
            {
                distance[i] = Matrix[srcInd][i];
            }
        }

        for (int i = 0; i < Size; i++)
        {
            int minIndex = -1, min = INT_MAX;
            for (int j = 0; j < Size; j++)
            {
                if (!isSet[j] && distance[j] <= min)
                {
                    min = distance[j];
                    minIndex = j;
                }
            }
            isSet[minIndex] = true;

            for (int j = 0; j < Size; j++)
            {
                if (!isSet[j] && Matrix[minIndex][j] && distance[minIndex] != INT_MAX
                    && distance[minIndex] + Matrix[minIndex][j] < distance[j])
                {
                    distance[j] = distance[minIndex] + Matrix[minIndex][j];
                }
            }
        }

        cout << "Vertex   Distance\n";
        for (int i = 0; i < Size; i++)
        {
            cout.width(6);
            cout << Names[i];
            cout.width(11);
            cout << distance[i];
            cout << "\n";
        }
    }
    else
    {
        cout << "Node is not in the graph\n";
    }
}

int Graph::Find(int parent[], int ind)
{
    if (parent[ind] == ind)
    {
        return ind;
    }

    return Find(parent, parent[ind]);
}

int Graph::Index(string names[], string name)
{
    for (int i = 0; i < Size; i++)
    {
        if (names[i] == name)
        {
            return i;
        }
    }
    return -1;
}

void Graph::Kruskal()
{
    pair<int, pair<string, string>>* edges = Edges();
    pair<int, pair<string, string>>* mst = new pair<int, pair<string, string>>[Size - 1];
    int weight = 0;
    int last = -1;

    int* parent = new int[Size];
    for (int i = 0; i < Size; i++)
    {
        parent[i] = i;
    }

    for (int i = 0; i < Edge && last + 1 < Size; i++)
    {
        int p1 = Find(parent, Index(Names, edges[i].second.first));
        int p2 = Find(parent, Index(Names, edges[i].second.second));
        if (p1 != p2)
        {
            last++;
            mst[last] = edges[i];
            weight += edges[i].first;
            parent[p1] = p2;
        }
    }

    cout << "Kruskal method:\n";
    cout << " Edge   Weight\n";

    for (int i = 0; i < Size - 1; i++)
    {
        cout.width(5);
        cout << mst[i].second.first << " - " << mst[i].second.second;
        cout.width(9);
        cout << mst[i].first << "\n";
    }
    cout << "\nWeight of MST is " << weight << "\n";
}

void Graph::Prim()
{
    pair<int, pair<string, string>>* edges = Edges();
    pair<int, pair<string, string>>* mst = new pair<int, pair<string, string>>[Size - 1];
    string* parent = new string[Size];
    int weight = 0;
    int count = 0;

    mst[count] = edges[0];
    weight += edges[0].first;
    parent[count] = edges[0].second.first;
    count++;
    parent[count] = edges[0].second.second;
    
    while (count != Size - 1)
    {
        for (int i = 1; i < Edge; i++)
        {
            int ind1 = Index(parent, edges[i].second.first);
            int ind2 = Index(parent, edges[i].second.second);
            if (ind1 == -1 && ind2 != -1)
            {
                mst[count] = edges[i];
                parent[++count] = edges[i].second.first;
                weight += edges[i].first;
                break;
            }
            else if (ind2 == -1 && ind1 != -1)
            {
                mst[count] = edges[i];
                parent[++count] = edges[i].second.second;
                weight += edges[i].first;
                break;
            }
        }
    }

    AdjList** list = ToList(mst);
    PrintAdj(list, weight);
}

AdjList** Graph::ToList(pair<int, pair<string, string>> mst[])
{
    AdjList** list = new AdjList*[Size];
    string* names = new string[Size];
    int last = -1;

    for (int k = 0; k < Size - 1; k++)
    {
        string father = mst[k].second.first;
        string child = mst[k].second.second;
        int weight = mst[k].first;
        bool flagF = false;
        bool flagC = false;
        int indexF = -1;
        int indexC = -1;

        for (int i = 0; i <= last; i++)
        {
            if (names[i] == father)
            {
                flagF = true;
                indexF = i;
            }

            if (names[i] == child)
            {
                flagC = true;
                indexC = i;
            }
        }

        if (!flagF)
        {
            ++last;
            names[last] = father;
            list[last] = new AdjList(new Node(father));
            list[last]->AddItem(new Node(child, weight));
        }
        else
        {
            list[indexF]->AddItem(new Node(child, weight));
        }

        if (!flagC)
        {
            ++last;
            names[last] = child;
            list[last] = new AdjList(new Node(child));
            list[last]->AddItem(new Node(father, weight));
        }
        else
        {
            list[indexC]->AddItem(new Node(father, weight));
        }
    }

    return list;
}



int part_sort(pair<int, pair<string, string>> arr[], int low, int high)
{
    pair<int, pair<string, string>> pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            pair<int, pair<string, string>> temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    pair<int, pair<string, string>> temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void sort(pair<int, pair<string, string>> arr[], int low, int high)
{
    if (low < high)
    {
        int pi = part_sort(arr, low, high);

        sort(arr, low, pi - 1);
        sort(arr, pi + 1, high);
    }
}

pair<int, pair<string, string>>* Graph::Edges()
{
    pair<int, pair<string, string>>* edges = new pair<int, pair<string, string>>[Edge];
    int last = -1;

    for (int i = 0; i < Size; i++)
    {
        for (int j = i + 1; j < Size; j++)
        {
            if (Matrix[i][j] != 0)
            {
                pair<string, string> str = make_pair(Names[i], Names[j]);
                pair<int, pair<string, string>> edge = make_pair(Matrix[i][j], str);
                last++;
                edges[last] = edge;
            }
        }        
    }

    sort(edges, 0, Edge - 1);
    return edges;
}

int main()
{
    Graph* graph = new Graph();
    graph->PrintGraph();

    graph->Kruskal();
    graph->Prim();

    string source;
    cout << "Enter source node: ";
    cin >> source;
    graph->Dijkstra(source);
}