#include <iostream>
#include <cmath>

#define maxn 50003
using namespace std;
int n, q, a[maxn], rmaxq[17][maxn], rminq[17][maxn];

void setup()
{
    for(int i = 1; i <= n; i++) rmaxq[0][i] = a[i];
    for(int i = 1; i <= n; i++) rminq[0][i] = a[i];

    for(int j = 1; j <= (int)log2(n); j++)
        for(int i = 1; i <= n; i++)
            if(i + (1 << j) - 1 <= n)
            {
                rmaxq[j][i] = max(rmaxq[j - 1][i], rmaxq[j - 1][i + (1 << (j - 1))]);
                rminq[j][i] = min(rminq[j - 1][i], rminq[j - 1][i + (1 << (j - 1))]);
            }
}

int query(int l, int r)
{
    int tmp, MIN = long(1e9), MAX = -long(1e9);
    while(l <= r)
    {
        tmp = (int)log2(r - l + 1);
        MIN = min(MIN, rminq[tmp][l]);
        MAX = max(MAX, rmaxq[tmp][l]);
        l += (1 << tmp);
    }
    return MAX - MIN;
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> q;
    for(int i = 1; i <= n; i++)
        cin >> a[i];

    setup();

    int l, r;
    while(q--)
    {
        cin >> l >> r;
        cout << query(l, r) << '\n';
    }

    return 0;
}
