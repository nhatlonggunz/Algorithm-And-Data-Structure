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

    for(int i = 1; i <= n; i++) pa[i][0] = p[i];

    for(int j = 1; j <= (int)log2(n); j++)
        for(int i = 1; i <= n; i++)
            if(h[i] >= (1 << j))
                pa[i][j] = pa[pa[i][j - 1]][j - 1];
}

int LCA(int u, int v)
{
    int tmp;
    if(h[u] < h[v]) swap(u, v);

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
    ios::sync_with_stdio(false); cin.tie();
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
