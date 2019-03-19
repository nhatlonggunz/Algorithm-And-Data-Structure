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
#include <fstream>
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
#define maxn 1000003

// End of template

int Phi[maxn];

int power(int a, int n)
{
    if(!n) return 1;
    if(n == 1) return a;
    int tmp = power(a, n >> 1);
    tmp *= tmp;
    return n & 1 ? tmp * a : tmp;
}

int phi(int p, int k)
{
    if(!k) return 1;
    return (p - 1) * power(p, k - 1);
}

int phi(int n)
{
    if(Phi[n]) return Phi[n];

    int save = n, PHI = 1;

    for(int i = 2; i*i <= n; i++)
    {
        int k = 0;
        while(n % i == 0) n /= i, k++;

        PHI *= phi(i, k);
    }

    if(n > 1) PHI *= phi(n, 1);
    return Phi[save] = PHI;
}

int main()
{
    sync;

    int test;
    cin >> test;

    while(test--)
    {
        int n;
        cin >> n;
        cout << phi(n) << '\n';
    }
}
