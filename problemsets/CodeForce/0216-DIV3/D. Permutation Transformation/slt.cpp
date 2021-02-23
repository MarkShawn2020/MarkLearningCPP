//
// Created by 南川 on 2021/2/17.
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

inline int findMaxPos(vector<int> & nums, int s, int t)
{
    int maxI, maxV = 0;
    for(int i=s; i<=t; i++)
        if(nums[i] > maxV)
            maxV = nums[i],
            maxI = i;
    return maxI;
}

void find(vector<int> & ans, vector<int> & nums, int s, int t, int layer)
{
    int p = findMaxPos(nums, s, t);
    ans[p] = layer;
    if(s < p) find(ans, nums, s, p-1, layer + 1);
    if(p < t) find(ans, nums, p+1, t, layer + 1);
}


template <typename T>
void run(T & cin)
{
    int tt;
    cin >> tt;
    while (tt--)
    {
        int n;
        cin >> n;
        vector<int> nums(n), ans(n);
        for(int i=0; i<n; i++)
            cin >> nums[i];
        find(ans, nums, 0, n-1, 0);
        for(int & a: ans)
            cout << a << " ";
        cout << endl;
    }

}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    // read from local case if possible, otherwise from console
    ifstream fin("/Users/mark/MarkLearningCPP/CodeForce/0216-DIV3/D. Permutation Transformation/case1.txt");
    run(fin.good() ? fin : cin);
}

