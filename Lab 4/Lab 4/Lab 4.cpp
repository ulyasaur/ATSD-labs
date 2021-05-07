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
    //void Kruskal();
    vector <pair<int, pair<string, string>>> Edges();
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
    }

    for (int i = 0; i < Size; i++)
    {
        Matrix[i] = new int[Size];

        for (int j = i; j < Size; j++)
        {
            cout << "Weight of edge " << Names[i] << " - " << Names[j] << " : ";
            cin >> Matrix[i][j];
            Matrix[j][i] = Matrix[i][j];
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


vector <pair<int, pair<string, string>>> Graph::Edges()
{
    vector <pair<int, pair<string, string>>> edges;

    for (int i = 0; i < Size; i++)
    {
        for (int j = i + 1; j < Size; j++)
        {
            edges.push_back(make_pair(Matrix[i][j], make_pair(Names[i], Names[j])));
        }        
    }

    sort(edges.begin(), edges.end());
    return edges;
}

int main()
{
    Graph* graph = new Graph();
    graph->PrintGraph();
}