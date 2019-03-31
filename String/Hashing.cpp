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
#define maxn 1000005
#define maxq 200003
#define maxa 1000004

// end of template
const ll modHash = mod;
string text, pattern;
ll pow26[maxn], hashT[maxn], hashP[maxn];

ll getHash(int i, int j) {
    return (hashT[j] - hashT[i - 1] * pow26[j - i + 1] + mod*mod) % mod;
}

int main()
{
    sync;

    cin >> text >> pattern;
    text = " " + text;
    pattern = " " + pattern;

    pow26[0] = 1;
    FOR(i, 1, sz(text) - 1)
        pow26[i] = (pow26[i - 1] * 26) % modHash;

    FOR(i, 1, sz(text) - 1)
        hashT[i] = (hashT[i - 1] * 26 + text[i] - 'a')  % modHash;

    FOR(i, 1, sz(pattern) - 1)
        hashP[i] = (hashP[i - 1] * 26 + pattern[i] - 'a') % modHash;

    FOR(i, 1, sz(text) - sz(pattern) + 1)
        if(getHash(i, i + sz(pattern) - 2) == hashP[sz(pattern) - 1])
            cout << i << ' ';
}
