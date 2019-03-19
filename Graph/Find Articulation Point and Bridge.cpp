// Nguyen Cao Nhat Long
// Pikachuuuuuuuuuuuuu
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <set>
#include <queue>
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <sstream>
using namespace std;

#define next oapsidfjiuunfiujfa
#define prev sdofljkauohfaodisf

#define sqr(x) ((x)*(x))
#define PI acos(-1)

#define FOR(i,a,b) for(int i = (a); i <= (b); i++)
#define FORD(i,a,b) for(int i = (a); i >= (b); i--)
#define REP(i,a) for(int i = 0, _a = (a); i < _a; i++)
#define REPD(i,n) for(int i = (n) - 1; i >= 0; i--)

#define ii pair<int,int>
#define fi first
#define se second
#define mp make_pair

#define sz(x) (int)x.size()
#define ALL(x) (x).begin(), (x).end()
#define MS(a,x) memset(a, x, sizeof(a))

#define sync ios::sync_with_stdio(false)

#define ll long long
#define vi vector<int>
#define vll vector<ll>
#define vii vector<ii>
#define pb push_back

#define inf 1000000000
#define INF 100000000000000000LL
#define mod 1000000007LL
#define maxn 200005

// End of template

int n, m, low[maxn], num[maxn], bridges, art, cnt, root, child;
bool isArt[maxn];
vi g[maxn];

void input()
{
    int m, u, v;
    cin >> n >> m;

    while(m--)
    {
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
}

void dfs(int u, int p)
{
    low[u] = num[u] = ++cnt;

    REP(i, sz(g[u]))
    {
        int v = g[u][i];

        if(!num[v])
        {
            if(u == root) child++;

            dfs(v, u);

            if(low[v] >= num[u]) isArt[u] = true;
            if(low[v] > num[u]) bridges++;

            low[u] = min(low[u], low[v]);
        }
        else if(v != p) low[u] = min(low[u], num[v]);
    }
}

int main()
{
    sync;

    input();

    FOR(i, 1, n)
        if(!num[i])
        {
            root = i, child = 0, dfs(i, 0);
            isArt[i] = (child > 1);
        }

    FOR(i, 1, n)
        if(isArt[i])
            art++;

    cout << art << ' ' << bridges;
}
