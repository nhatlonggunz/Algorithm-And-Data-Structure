#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
#define ii pair<int,int>
#define fi first
#define se second
#define vi vector<int>
#define vii vector<ii>
#define maxN
#define ll long long
#define inf long(1e9)

/** Memset **/
memset(memo, -1, sizeof(memo)); // initialize DP memoization table
memset(arr, 0, size(arr)); // clear array

/** Some basic shortcut **/
index = (index + 1) % n; // index++; if(index >= n) index = 0;
index = index % n + 1;

index = (index + n - 1) % n; // index--; if(index < 0) index = n - 1;
index = (index ) % n - 1;

ans = (int)((double)d + 0.5); // rounding to the nearest integer
