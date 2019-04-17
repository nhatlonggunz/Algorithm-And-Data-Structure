/**
For more explanation on Sparse Table, see Data Structure/SparseTable.cpp

This code applies Sparse Table to find the LCA of u and v

pa[u][i]: the 2^i parent of node u 
The idea is to let u and v jump up 2^i nodes (i as large as possible)
until direct parents of u and v, which are p[u] and p[v] are the same

Complexity: 
- Query: O(logn)
- Initialize: O(nlogn)
- Memory: O(nlogn)

It is slower and requires more memory than Heavy Light Decomposition
HLD Complexity:
- Query: O(logn)
- Initialize: O(n) for setting up dfs and O(n) for decomposition
- Memory: O(n)


However, Sparse Table is much shorter
**/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
#define maxN long(1e3) + 3
#define ii pair<int,int>
#define fi first
#define se second
int root, n, q, pa[maxN][13];
vector<int> h, d, p;
vector<ii> g[maxN];

void input()
{
    int u, v, t;
    cin >> n >> q;

    d.assign(n + 1, 0);
    h.assign(n + 1, 0);
    p.assign(n + 1, 0);

    for(int i = 1; i < n; i++)
    {
        cin >> u >> v >> t;

        g[u].push_back(ii(v, t));
        g[v].push_back(ii(u, t));
    }
}

/**
DFS to initialize
**/

void DFS(int u)
{
    int v;

    for(unsigned i = 0; i < g[u].size(); i++)
    {
        v = g[u][i].fi;
        if(!p[v])
        {
            h[v] = h[u] + 1;
            d[v] = d[u] + g[u][i].se;
            p[v] = u; DFS(v);
        }
    }
}

void setup()
{
    root = 1, p[root] = -1, DFS(root), p[root] = 0;

    for(int i = 1; i <= n; i++) 
		pa[i][0] = p[i];

	// Setup Sparse Table
	// pa[u][i]: 2^i parent of u
    for(int j = 1; j <= (int)log2(n); j++)
        for(int i = 1; i <= n; i++)
            if(h[i] >= (1 << j))
                pa[i][j] = pa[pa[i][j - 1]][j - 1];
}

int LCA(int u, int v)
{
    int tmp;
    if(h[u] < h[v]) swap(u, v);

	// Jump up u and v to have equal height
    while(h[u] > h[v])
    {
        tmp = (int)log2(h[u] - h[v]);
        u = pa[u][tmp];
    }

    if(u == v) return u;

    while(pa[u][0] != pa[v][0])
    {
        tmp = (int)log2(h[u]);

        for(int i = tmp; i >= 0; i--)
            if(pa[u][i] != pa[v][i])
                { u = pa[u][i], v = pa[v][i]; break; }
    }

    return pa[u][0];
}

int main()
{
    ios::sync_with_stdio(false); 
	cin.tie();		cout.tie(0);

    input();
    setup();

    int u, v, an;
	
    while(q--)
    {
        cin >> u >> v;
        an = LCA(u, v);
        cout << d[u] + d[v] - 2*d[an] << '\n';
    }

    return 0;
}
