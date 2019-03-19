#include <iostream>
#include <vector>
using namespace std;
#define maxn long(1e4) + 2
int n, scc, cnt;
vector<int> g[maxn], num, low, st;
vector<bool> visited;

void input()
{
    int m, u, v;
    cin >> n >> m;

    while(m--) {
        cin >> u >> v;
        g[u].push_back(v);
    }
}

void DFS(int u)
{
    int v;
    low[u] = num[u] = ++cnt;
    visited[u] = true; st.push_back(u);

    for(unsigned i = 0; i < g[u].size(); i++) {
        v = g[u][i];
        if(!num[v]) DFS(v);
        if(visited[v]) low[u] = min(low[u], low[v]); }

    if(low[u] == num[u])
        while(true) {
            v = st.back(); st.pop_back(); visited[v] = false;
            if(v == u) { ++scc; break; }
        }
}


int main()
{
    ios::sync_with_stdio(false);
    //cin.tie(0); cout.tie(0);

    input();
    num.assign(n + 1, 0); low.assign(n + 1, 0);
    visited.assign(n + 1, false);

    for(int i = 1; i <= n; i++)
        if(!num[i])
            DFS(i);

    cout << scc;

    return 0;
}
