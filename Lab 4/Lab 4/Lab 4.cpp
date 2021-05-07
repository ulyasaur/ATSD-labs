#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Graph
{
public:
    string* Names;
    int** Matrix;
    int Size;
    Graph();

    void PrintGraph();
    void Dijkstra(string source);
    void Kruskal();
    vector <pair<int, pair<string, string>>> Edges();

private:
    int Find(int parent[], int ind);
    int Index(string name);
};

Graph::Graph()
{
    cout << "Enter amount of graph nodes: ";
    cin >> Size;
    Names = new string[Size];
    Matrix = new int*[Size];

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

void Graph::Dijkstra(string source)
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

int Graph::Find(int parent[], int ind)
{
    if (parent[ind] == ind)
    {
        return ind;
    }

    return Find(parent, parent[ind]);
}

int Graph::Index(string name)
{
    for (int i = 0; i < Size; i++)
    {
        if (Names[i] == name)
        {
            return i;
        }
    }
}

void Graph::Kruskal()
{
    vector <pair<int, pair<string, string>>> edges = Edges();
    vector <pair<int, pair<string, string>>> mst;
    int weight = 0;

    int* parent = new int[Size];
    for (int i = 0; i < Size; i++)
    {
        parent[i] = i;
    }

    for (int i = 0; i < edges.size() && mst.size() < Size; i++)
    {
        int p1 = Find(parent, Index(edges[i].second.first));
        int p2 = Find(parent, Index(edges[i].second.second));
        if (p1 != p2)
        {
            mst.push_back(edges[i]);
            weight += edges[i].first;
            parent[p1] = p2;
        }
    }

    cout << " Edge   Weight\n";

    for (int i = 0; i < mst.size(); i++)
    {
        cout.width(5);
        cout << mst[i].second.first << " - " << mst[i].second.second;
        cout.width(9);
        cout << mst[i].first << "\n";
    }
    cout << "\nWeight of MST is " << weight << "\n";
}

vector <pair<int, pair<string, string>>> Graph::Edges()
{
    vector <pair<int, pair<string, string>>> edges;

    for (int i = 0; i < Size; i++)
    {
        for (int j = i + 1; j < Size; j++)
        {
            if (Matrix[i][j] != 0)
            {
                pair<string, string> str = make_pair(Names[i], Names[j]);
                pair<int, pair<string, string>> edge = make_pair(Matrix[i][j], str);
                edges.push_back(edge);
            }
        }        
    }

    sort(edges.begin(), edges.end());
    return edges;
}

int main()
{
    Graph* graph = new Graph();
    graph->PrintGraph();

    graph->Kruskal();
    graph->Dijkstra("0");
}