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
#include <unordered_map>
#include <stack>
#include <map>
#include <string>
#include <sstream>
using namespace std;

#define next oapsidfjiuunfiujfa
#define prev sdofljkauohfaodisf

#define sqr(x) ((x)*(x))

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

#define ull unsigned long long
#define ll long long
#define vi vector<int>
#define vll vector<ll>
#define vii vector<ii>
#define pb push_back

#define inf 1000000000
#define INF 100000000000000000LL
#define mod 1000000007LL
#define maxn 2002
#define maxq 200003
#define maxa 1000004

// end of template

int n, m, cnt, match[maxn], visited[maxn];
bool chosen[maxn];
vi g[maxn];

bool dfs(int u)
{
    if(visited[u] == cnt)
        return false;
    visited[u] = cnt;

    REP(i, sz(g[u]))
    {
        int v = g[u][i];

        if(!match[v] || dfs(match[v]))
        {
            match[u] = v;
            match[v] = u;
            return true;
        }
    }
    return false;
}

void konig()
{
    queue<int> q;

    FOR(i, 1, n) if(!match[i]) q.push(i);
    FOR(i, 1, m) if(!match[maxn - i]) q.push(maxn - i);

    while(!q.empty())
    {
        int u = q.front(); q.pop();

        REP(i, sz(g[u]))
        {
            int v = g[u][i];
            if(!(chosen[v]++))
                q.push(match[v]);
        }
    }

    FOR(i, 1, n)
        if(!match[i] && !chosen[i] && !chosen[match[i]])
            chosen[i] = true;
}

void input()
{
    int edge, u, v;
    cin >> n >> m >> edge;

    while(edge--)
    {
        cin >> u >> v;
        g[u].pb(maxn - v);
        g[maxn - v].pb(u);
    }
}

int main()
{
    sync;

    int a = 0;
    if(!(a++)) cout << "cc";
    input();

    int res = 0;

    FOR(i, 1, n) {
        ++cnt;
        res += dfs(i);
    }

    cout << res << '\n';

    konig();

}
/*
4 5 9
1 1
1 4
2 1
2 2
2 4
3 2
3 3
4 2
4 3

*/
