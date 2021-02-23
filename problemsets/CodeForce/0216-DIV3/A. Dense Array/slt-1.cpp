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
#include "algorithm"

using namespace std;

int calcNToAdd(int a, int b)
{
    int ans = 0;
    if(a > (b << 1) || b > (a << 1))
    {
        int k = (max(a, b)-1) / min(a, b);
        while ((k >>= 1) > 0)
            ++ans;
    }
    return ans;
}

template <typename T>
void run(T & cin)
{
    int tt;
    cin >> tt;
    while (tt--)
    {
        int ans = 0;
        int n, last, cur;
        cin >> n;
        cin >> last;
        while (--n)
        {
            cin >> cur;
            ans += calcNToAdd(last, cur);
            last = cur;
        }
        printf("%d\n", ans);
    }
}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    // read from local case if possible, otherwise from console
    ifstream fin("/Users/mark/MarkLearningCPP/CodeForce/0216-DIV3/A. Dense Array/case1.txt");
    run(fin.good() ? fin : cin);
}

