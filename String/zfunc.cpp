/*
	z[i] is the longest substring, starting from i, 
	which is prefix of string s
*/

#include <iostream>
#include <vector>
using namespace std;

vector<int> zfunc(string s)
{
    int n = (int)s.size();
    vector<int> z(n);
	z[0] = n;

    for(int i = 1, l = 0, r = 0; i < n; i++)
    {
        if(i > r)
        {
            l = r = i;
            while(r < n && s[r] == s[r - l])
                ++r;
            z[i] = r - l;
            r--;
        }
        else // i <= r
        {
            int k = i - l; // like moving s[i..] to the front (s[1..])
            // z[i] >= min(z[k], r - i + 1)

            if(z[k] < r - i + 1)
                z[i] = z[k];
            else
            {
                l = i;
                while(r < n && s[r] == s[r - l])
                    ++r;
                z[i] = r - l;
                r--;
            }
        }
    }

    return z;
}
