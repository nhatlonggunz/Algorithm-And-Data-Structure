// Nguyen Cao Nhat Long

/**
Trie is a tree, whose nodes do not contain information,
every edge contains a character. A path from the root
to a node u gives the string composed of characters
on the edges of the path (in traversing order).

Advantages:
- Extremely short code, simple implementation, easy to understand

- Memory: when the number of keys (strings) is large and their lengths are
    relatively small, Trie can save memory as keys with the same prefix
    have their prefixes stored only once
    ("memory" and "memorize", ("memor") is stored only once)

- Searching Complexity: O(key.length())
    + compared to Auto Balanced Binary Search Tree:
        * O(log2(number of keys)) per query,
            when the number of queries is large and keys' lengths are small,
            log2(number of keys) ~ key.length()
        * Much harder to implement and take huge amount of time
        * In practice, Trie's operations are simpler, more "basic"
            so it is usually faster.

- Trie can deal with problems involving
    prefix, suffix, lexicographically order, ...
    (find the 'smallest' string that is 'larger' than a given string, lexicographically)
**/

/**
In different problems, the trie needs to store different
things in its nodes. Therefore, there's no general implementation
for a trie, it's the idea that is important.
**/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

struct NODE
{
    int Count; // Count the number of strings ending at this node
    int Next[26]; // 26 characters which continue current string

    NODE()
    {
        Count = 0; // Initially no string ends here
        for(int i = 0; i < 26; i++)
            Next[i] = 0;
    }
};

vector<NODE> trie(1); // initialize root node (empty string) }

void Insert(string s) //
{
    int u = 0;

    for(int i = 0; i < (int)s.length(); i++)
    {
        if(!trie[u].Next[s[i] - 'a']) {
            // if there's no string
            // create new node, stored in the current last element of vector
            trie[u].Next[s[i] - 'a'] = (int)trie.size();
            trie.push_back(NODE()); // add a new last element
        }
        // continue traversing the trie, following character s[i]
        u = trie[u].Next[s[i] - 'a'];
    }
    // there is a string ending with the char stored in node u
    trie[u].Count++;
}

bool Delete(string s)
{
    int u = 0;

    for(int i = 0; i < (int)s.length(); i++)
    {
        if(!trie[u].Next[s[i] - 'a']) {
            // there is no string s in Trie
            return false;
        }
        u = trie[u].Next[s[i] - 'a'];
    }

    // there is no string s in Trie
    if(trie[u].Count == 0)
        return false;

    // decrement the count of string s in Trie
    // we should not remove that node if Count = 0 as
    // there might be other strings which have this node on the path
    trie[u].Count--;

    // successfully deleted
    return true;
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);     cout.tie(0);



    return 0;
}
