#include <iostream>

#define maxn 100003
using namespace std;
int n, BIT[maxn], a[maxn];

int freqTo(int id) {
    int sum = 0;

    while (id > 0) {
        sum += BIT[id];
        id -= (id & -id);
    }
    return sum;
}

void update(int id, int val) {
    while  (id <= n) {
        BIT[id] += val;
        id += (id & -id);
    }
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];

    for(int i = 1; i <= n; i++)
        update(i, a[i]);

    for(int i = 1; i <= n; i++)
        cout << freqTo(i) << '\n';

    return 0;
}
