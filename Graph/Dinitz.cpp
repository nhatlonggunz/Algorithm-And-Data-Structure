#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define maxN long(1e3) + 2
int n, s, t, mf, f[maxN][maxN], c[maxN][maxN];
vector<int> g[maxN], d;
vector<bool> visited;

void input()
{
    int m, u, v, cap;
    cin >> n >> m >> s >> t;

    while(m--)
    {
        cin >> u >> v >> cap;
        g[u].push_back(v);
        g[v].push_back(u);
        c[u][v] = cap;
    }
}

bool findPath()
{
    int u, v;
    d.assign(n + 1, 0);     d[s] = 1;
    queue<int> q;           q.push(s);

    while(!q.empty())
    {
        u = q.front(); q.pop();

        if(d[t] && d[u] > d[t]) return true;

        for(unsigned i = 0; i < g[u].size(); i++)
        {
            v = g[u][i];

            if(!d[v] && f[u][v] < c[u][v])
            {
                d[v] = d[u] + 1;
                if(d[t] && d[v] > d[t]) return true;
                q.push(v);
            }
        }
    }

    return d[t];
}

int augment(int u, int minEdge)
{
    if(u == t) return minEdge;
    visited[u] = true;

    int v, flow;
    for(unsigned i = 0; i < g[u].size(); i++)
    {
        v = g[u][i];

        if(!visited[v] && f[u][v] < c[u][v] && d[v] == d[u] + 1)
            if((flow = augment(v, min(minEdge, c[u][v] - f[u][v]))))
                { f[u][v] += flow, f[v][u] -= flow; return flow; }
    }
    return 0;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie();
    input();

    int flow;
    while(findPath())
    {
        visited.assign(n + 1, false);
        while((flow = augment(s, long(1e9))))
            mf += flow;
    }

    cout << mf;


    return 0;
}
