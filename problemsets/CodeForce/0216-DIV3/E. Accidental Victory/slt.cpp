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

template <typename T>
void run(T & cin)
{
    int tt;
    cin >> tt;
    while (tt--)
    {
        int n, v;
        cin >> n;
        vector<pair<int, int>> nums(n + 1);
        for(int i=1; i<=n; i++)
        {
            cin >> v;
            nums[i] = pair<int, int>{v, i};
        }
        sort(nums.begin() + 1, nums.end());

        int pos = 0;
        for(int i=1; i<n; i++)
        {
            nums[i].first += nums[i - 1].first;
            if(nums[i] > nums[n]) break;            // 剪枝
            if(nums[i].first < nums[i+1].first)
                pos = i;
        }
        cout << n - pos << endl;

        vector<int> seqs(n - pos);
        for(int i=pos+1; i<=n; i++)
            seqs[i-pos-1] = nums[i].second;
        sort(seqs.begin(), seqs.end());

        for(int i=0; i<n-pos; i++)
            cout << seqs[i] << " ";
        cout << endl;
    }
}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    // read from local case if possible, otherwise from console
    ifstream fin("/Users/mark/MarkLearningCPP/CodeForce/0216-DIV3/E. Accidental Victory/case1.txt");
    run(fin.good() ? fin : cin);
}

