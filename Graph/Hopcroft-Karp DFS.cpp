#include <iostream>
#include <vector>
 
#define maxn 102
using namespace std;
int n, m, assigned[maxn], visited[maxn], nVisit;
vector<int> g[maxn];
 
void input()
{
    int u, v;
    cin >> n >> m;
 
    while(cin >> u >> v)
        g[u].push_back(v);
}
 
bool augment(int u)
{
    if(visited[u] != nVisit)
        visited[u] = nVisit;
    else
        return false;
 
    for(unsigned i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i];
 
        if(!assigned[v] || augment(assigned[v]))
        {
            assigned[v] = u;
            return true;
        }
    }
    return false;
}
 
void process()
{
    int cnt = 0;
    for(int i = 1; i <= n; i++)
    {
        ++nVisit;
        cnt += augment(i);
    }
 
    cout << cnt << '\n';
    for(int i = 1; i <= m; i++)
        if(assigned[i])
            cout << assigned[i] << ' ' << i << '\n';
}
 
int main()
{
    ios::sync_with_stdio(false);
 
    input();
    process();
 
    return 0;
}
 