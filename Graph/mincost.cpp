#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define maxN 110
int n, k, s, t, mf, c[maxN][maxN], f[maxN][maxN], cost[maxN][maxN];
vector<int> g[maxN], p, d;
vector<bool> inQueue;

void input()
{
    int m, u, v, d, cap;

    cin >> n >> m >> k >> s >> t;

    g[0].push_back(s);
    g[s].push_back(0);
    cost[0][s] = 0;
    c[0][s] = k;
    s = 0;

    while(m--)
    {
        cin >> u >> v >> d >> cap;

        g[u].push_back(v);
        g[v].push_back(u);
        cost[u][v] = cost[v][u] = d;
        c[u][v] = c[v][u] = cap;
    }
}

int calc(int flow, int cost) { return flow < 0 ? -cost : cost; }

bool findPath()
{
    int u, v;
    p.assign(n + 1, 0);             p[s] = -1;
    inQueue.assign(n + 1, false);
    d.assign(n + 1, long(1e9));     d[s] = 0;
    queue<int> q;                   q.push(s);

    while(!q.empty())
    {
        u = q.front(); q.pop(); inQueue[u] = false;

        for(unsigned i = 0; i < g[u].size(); i++)
        {
            v = g[u][i];

            if(f[u][v] < c[u][v] && d[v] > d[u] + calc(f[u][v], cost[u][v]))
            {
                p[v] = u;
                d[v] = d[u] + calc(f[u][v], cost[u][v]);

                if(!inQueue[v])
                    q.push(v), inQueue[v] = true;
            }
        }
    }

    return d[t] != long(1e9);
}

void augment()
{
    int flow = long(1e9), u, v;

    for(v = t; (u = p[v]) != -1; v = u)
        flow = f[u][v] < 0 ? min(flow, -f[u][v]) : min(flow, c[u][v] - f[u][v]);
    for(v = t; (u = p[v]) != -1; v = u)
        f[u][v] += flow, f[v][u] -= flow;

    mf += flow;
}

int main()
{
    input();

    while(findPath())
        augment();

    if(mf < k) { cout << "-1"; return 0; }

    mf = 0;

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            mf += f[i][j] > 0 ? f[i][j] * cost[i][j] : 0;
    cout << mf << '\n';

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            if(f[i][j] > 0)
                cout << i << ' ' << j << ' ' << f[i][j] << '\n';
    cout << "0 0 0";

    return 0;
}
