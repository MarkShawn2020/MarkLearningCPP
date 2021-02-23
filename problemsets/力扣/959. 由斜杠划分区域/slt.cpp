//
// Created by 南川 on 2021/1/25.
//
#include "vector"
#include "string"
#include "iostream"
#include "sstream"
using namespace std;


class Solution {
public:
    inline int Find(vector<int> & fa, int x)
    {
        while(x != fa[x]) x = fa[x];
        return x;
    }

    inline int Merge(vector<int> & fa, int x, int y)
    {
        x = Find(fa, x), y = Find(fa, y);
        if(x == y) return 1;
        fa[x] = y;
        return 0;
    }

    int regionsBySlashes(vector<string>& grid) {
        const int N = grid.size();

        vector<int> fa((N+1) * (N+1));
        for(int i=0; i<N+1; ++i)
            for(int j=0; j<N+1; j++)
                fa[i*(N+1)+j] = i*(N+1)+j;

        for(int i=0; i<N+1; ++i)
            fa[i] = fa[i*(N+1)] = fa[i*(N+1)+N] = fa[N*(N+1)+i] = 0;

        int areas = 1;
        for(int row=0; row<N; ++row)
        {
            int j = 0;
            for(int col=0; col<N; ++col)
            {
                if(grid[row][j] == '/')
                    areas += Merge(fa, row*(N+1)+col+1, (row+1)*(N+1)+col), j+=1;
                else if(grid[row][j] == '\\')
                    areas += Merge(fa, row*(N+1)+col, (row+1)*(N+1)+col+1), j += 2;
                else;
            }
        }

        return areas;
    }
};


int main()
{
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/力扣/959. 由斜杠划分区域/case1.txt", "r", stdin);

    vector<string> data;
    string s;
    cin >> s;
    for(char & ch: s)
        if(ch == ',' || ch == '[' || ch == ']' || ch == '"')
            ch = ' ';
    stringstream ss;
    ss << s;
    while (ss >> s)
    {
        data.emplace_back(s);
    }

    Solution slt;
    cout << slt.regionsBySlashes(data);
}
