/**
Sliding Window with Deque (double-ended queue) 
to find Min, Max in previous K elements in O(n)
**/

#include <iostream>
#include <deque>
#include <cstdio>

#define ii pair<int,int>

using namespace std;

void SlidingWindow(int A[], int n, int K)
{
    deque<ii> window;
    for (int i = 1; i <= n; i++)
    {
        while (!window.empty() && window.back().first >= A[i])
            window.pop_back();

        window.push_back(ii(A[i], i));

        while (window.front().second <= i - K)
            window.pop_front();

        if(i >= K)
            printf("%d", window.front().first);
    }
}

int a[1000], n, k;

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> k;
    for(int i = 1; i <= n; i++)
        cin >> a[i];

    SlidingWindow(a, n, k);

    return 0;
}
/*
14 4
1 2 3 6 7 2 3 4 5 6 3 2 1 0
*/
