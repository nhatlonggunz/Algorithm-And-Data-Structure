#include <iostream>
#include <vector>
using namespace std;
#define maxN long(1e3) + 3
#define ii pair<int,int>
#define fi first
#define se second
int n, q, p[maxN], h[maxN], d[maxN], tree[maxN], nTree, child[maxN], root[maxN];
vector<ii> g[maxN];

void input()
{
    int u, v, t;
    cin >> n >> q;

    for(int i = 2; i <= n; i++)
    {
        cin >> u >> v >> t;

        g[u].push_back(ii(v, t));
        g[v].push_back(ii(u, t));
    }
}

void DFS(int u)
{
    int MAX = 0, v;
    child[u] = 1;

    for(unsigned i = 0; i < g[u].size(); i++)
        if(!p[(v = g[u][i].fi)])
        {
            p[v] = u;
            h[v] = h[u] + 1;
            d[v] = d[u] + g[u][i].se;

            DFS(v);
            child[u] += child[v];

            if(child[v] > MAX)
                MAX = child[v], tree[u] = tree[v];
        }

    if(child[u] != 1) return;
    tree[u] = ++nTree;
}

void setup()
{
    p[1] = 1; DFS(1); h[0] = long(1e9);

    for(int i = 1; i <= n; i++)
        if(h[i] < h[root[tree[i]]])
            root[tree[i]] = i;
}

int LCA(int u, int v)
{
    while(tree[u] != tree[v])
    {
        if(h[root[tree[u]]] > h[root[tree[v]]])
            u = p[root[tree[u]]];
        else
            v = p[root[tree[v]]];
    }
    return h[u] < h[v] ? u : v;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    input();
    setup();

    int an, u, v;
    while(q--)
    {
        cin >> u >> v;
        an = LCA(u, v);
        cout << d[u] + d[v] - 2*d[an] << '\n';
    }

    return 0;
}
