#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;
vector<pair<int, int> > G; // Graphs containing edges edges (u,v), edges are stored in ascending order.
vector<pair<int, int> > MST;
double ** adjMatrix;
double minimum_distance(vector<int> x, vector<int> y)
{
    double result = 0.;
    //write your code here
    return result;
}
bool sortByEdgeLen(pair<int, int> a, pair<int, int> b)
{
    return adjMatrix[a.first][a.second] < adjMatrix[b.first][b.second];
}
class DisjointSet
{
private:
    void MakeSet(int n);

public:
    typedef struct Node
    {
        int data;
        int rank;
        struct Node* parent;
    } N;
    vector<N*> map; //uses to find Node from data

    DisjointSet(int n);
    bool Union(int a, int b);
    N* FindSet(N*);
    void display();
};
/*
 * n: number of nodes in graph
 */
DisjointSet::DisjointSet(int n)
{
    for (int i = 0; i < n; ++i)
        MakeSet(i);
}
void DisjointSet::MakeSet(int node)
{
    N *n = new N();
    n->data = node;
    n->rank = 0;
    n->parent = n;
    map.push_back(n);
}
DisjointSet::N* DisjointSet::FindSet(N* n)
{
    if (n->data == n->parent->data)
        return n;
    FindSet(n->parent);
}
bool DisjointSet::Union(int a, int b)
{
    bool added = true;
    N* pa = FindSet(map[a]); //Find parent
    map[a]->parent = pa; //path compression
    N *pb = FindSet(map[b]);
    map[b]->parent = pb; //path compression

    if (pa->data == pb->data) // Same set
        added = false;
    else if (pa->rank == pb->rank) // same rank , choose any one)
    {
        ++pa->rank; // a parent
        pb->parent = pa;
    }
    else if (pa->rank >= pb->rank)
        pb->parent = pa;
    else
        pa->parent = pb;
    return added;
}
void DisjointSet::display()
{
    for (int i = 0; i < map.size(); i++)
        cout << i << "--->" << FindSet(map[i])->data << endl;
}

int main()
{
    size_t n;
    std::cin >> n;
    vector<int> x(n), y(n);
    for (size_t i = 0; i < n; i++)
    {
        std::cin >> x[i] >> y[i];
    }
    adjMatrix = new double*[n];
    for (int i = 0; i < n; i++)
        adjMatrix[i] = new double[n];
    for (int i = 0; i < n; i++)
    {
        adjMatrix[i][i] = 0;
        for (int j = i + 1; j < n; j++)
        {
            adjMatrix[i][j] = adjMatrix[j][i] = sqrt(
                    pow(abs(x[i] - x[j]), 2) + pow(abs(y[i] - y[j]), 2));
            //Push this edge
            G.push_back(make_pair(i, j));
        }
    }
    sort(G.begin(), G.end(), sortByEdgeLen);
//Kruskal algorithm, select edge of least weight which doesn't form a loop
    DisjointSet d(n);
    double cost = 0.0;
    for (auto & i : G)
    {
        if (!d.Union(i.first, i.second)) // if both the vertex are in Forest skip this edge as it create loop.
            continue;
        cost += adjMatrix[i.first][i.second]; // Add cost

        MST.push_back(make_pair(i.first, i.second));
        MST.push_back(make_pair(i.second, i.first)); //Double the edges
    }

    std::cout << std::setprecision(10) << cost << std::endl;
}
