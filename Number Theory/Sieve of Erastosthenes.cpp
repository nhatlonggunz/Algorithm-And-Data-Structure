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

void sieve(bool isPrime[], int bound)
{
    REP(i, bound + 1) isPrime[i] = true;
    isPrime[1] = isPrime[0] = false;

    REP(i, bound + 1)
        if(isPrime[i])
            for(ll j = i * 1LL *i; j <= bound; j += i)
                isPrime[j] = false;
}

vi listPrime(bool isPrime[], int bound)
{
    vi a;

    REP(i, bound + 1)
        if(isPrime[i])
            a.pb(i);
    return a;
}

int main()
{
	sync;

	bool isPrime[100];
	sieve(isPrime, 99);

	vi a = listPrime(isPrime, 99);
    REP(i, sz(a)) cout << a[i] << ' ';

	return 0;
}
