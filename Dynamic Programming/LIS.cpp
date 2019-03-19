#include <cstdio>
#include <algorithm>
#include <iostream>
#define maxN long(3e4) + 10
using namespace std;
int n, a, lis[maxN], len = 1;

int main()
{
    scanf("%d", &n);
    scanf("%d", &lis[1]);

    for(int i = 2; i <= n; i++)
    {
        scanf("%d", &a);
        else if(a > lis[len]) lis[++len] = a;
        else *lower_bound(lis + 1, lis + len + 1, a) = a;
    }

    printf("%d", len);

    return 0;
}
