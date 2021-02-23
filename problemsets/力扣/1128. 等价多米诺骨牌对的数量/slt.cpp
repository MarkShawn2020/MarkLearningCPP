//
// Created by 南川 on 2021/1/26.
//

#include "cstdio"
#include "iostream"
#include "vector"
#include "fstream"
#include "/Users/mark/CLionProjects/MarkLearningCPP/io/read_case.h"

using std::vector;

class Solution {
public:
    const int K = 9;

    inline int getIndex(int i, int j)
    {
        if(i > j) std::swap(i, j);
        return (2*K-i+1)*i/2 + (j-i);
    }

    int numEquivDominoPairs(vector<vector<int>>& dominoes) {

        vector<int> ds(K * (K + 1) / 2 , 0);
        int ans = 0;
        for(vector<int> & domino: dominoes)
        {
            int i = --domino[0], j = --domino[1];
            int index = getIndex(i, j);
            ans += ds[index]++;
        }

        return ans;
    }
};

int main()
{
    ifstream f("/Users/mark/CLionProjects/MarkLearningCPP/力扣/1128. 等价多米诺骨牌对的数量/case1.txt");
    string s;
    f >> s;
    vector<vector<int> > dominoes = readIntVector2D(s);
    Solution slt;
    std::cout << slt.numEquivDominoPairs(dominoes);
}