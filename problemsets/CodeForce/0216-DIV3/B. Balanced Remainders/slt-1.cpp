//
// Created by 南川 on 2021/2/16.
//


#include "cstdio"
#include "cstring"
#include "cmath"
#include "cassert"

#include "string"
#include "iostream"
#include "fstream"
#include "algorithm"

#include "vector"
#include "stack"
#include "list"
#include "queue"
#include "set"
#include "unordered_set"
#include "map"
#include "unordered_map"

using namespace std;

template <typename T>
void run(T & cin)
{
    int tt;
    cin >> tt;
    while (tt--)
    {
        int ans=0;
        int n, v;
        cin >> n;
        vector<int> freq(3, - n / 3);
        for(int i=0; i<n; i++)
            cin >> v,
            ++freq[v % 3];

        ans += abs(freq[0]);
        freq[1] += freq[0];
        ans += abs(freq[1]);

        cout << ans << endl;
    }
}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    // read from local case if possible, otherwise from console
    ifstream fin("/Users/mark/MarkLearningCPP/CodeForce/0216-DIV3/B. Balanced Remainders/case1.txt");
    run(fin.good() ? fin : cin);
}

