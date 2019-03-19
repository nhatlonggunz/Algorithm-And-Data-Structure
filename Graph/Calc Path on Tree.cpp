#include <iostream>
#include <cstdio>
#include <vector>
#define ii pair<int,int>
#define fi first
#define se second
#define maxN long(1e3) + 10
#define inf long(1e9)
using namespace std;
int n, q;
vector<ii> g[maxN];
vector<int> d, p;
vector<bool> visited;

void input()
{
    int u, v, t;
    scanf("%d%d", &n, &q);

    for(int i = 1; i < n; i++)
    {
        scanf("%d%d%d", &u, &v, &t);
        g[u].push_back(ii(v, t));
        g[v].push_back(ii(u, t));
    }

    d.assign(n + 1, inf);
    p.assign(n + 1, 0);
}

void mkTree(int root = 1)
{
    ii v;
    for(unsigned i = 0; i < g[root].size(); i++)
    {
        v = g[root][i];
        if(d[v.fi] == inf)
        {
            p[v.fi] = root;
            d[v.fi] = d[root] + v.se;
            mkTree(v.fi);
        }
    }
}

int calcPath(int a, int b)
{
    int u = a;
    visited.assign(n + 1, false); visited[a] = true;

    while(p[u])
    {
        u = p[u];
        if(visited[u]) break;
        visited[u] = true;
    }

    u = b;
    while(!visited[u]) u = p[u];

    return d[a] + d[b] - 2*d[u];
}

int main()
{
    int a, b;
    input();
    mkTree();

    while(q--)
    {
        scanf("%d%d", &a, &b);

        printf("%d\n", calcPath(a, b));
    }

    return 0;
}

/*
5 3
2 1 2
4 5 4
4 3 2
1 4 3
3 4
3 2
5 2

*/
