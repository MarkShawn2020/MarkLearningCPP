//
// Created by 南川 on 2021/1/16.
//
#include "vector"
#include "queue"
#include "string"
#include "iostream"
#include "array"
#include "fstream"
#include "sstream"

using namespace std;


class Solution {

public:
//    static const int G = 200;
    int Find(vector<int> & fa, int x){
        return fa[x]==x ? x : fa[x]=Find(fa, fa[x]);
    }

    int Union(vector<int> & fa, vector<int> & sz, const int M, int x, int y){
        /**
         * 把x结点和y结点之间连线
         * 但是考虑到x结点和y结点背后所代表的的其实是分别两个点集
         * 所以需要分别处理，主要分三种：两主（0）、两分（0）、一主一分（+分）
         */
        int fx = Find(fa, x);
        int fy = Find(fa, y);
        if(fx==fy) return 0; // 本题中，即同一个祖先出发产生的分路的汇合，即：环

        bool isTail = fx > fy;        // 重要，若x是链尾，则减去自己
        if(fx<fy) swap(fx, fy); // fy始终是最小号的那个祖先
        fa[fx] = fy;
        sz[fy] += sz[fx];
        return (fy < M && fx >= M) ? sz[fx] - isTail : 0;
    }

    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        const int N = grid.size();
        const int M = grid[0].size();
        int L = hits.size();
        vector<int> ans(L, 0);
        vector<bool> b(L, false);
        vector<int> fa(N*M);
        vector<int> sz(N*M, 1);
        for(int i=0; i<N*M; i++) fa[i] = i;

        // 打掉砖块
        for(int i=0; i<L; i++){
            int x = hits[i][0];
            int y = hits[i][1];
            if(grid[x][y])
                b[i] = true;
            grid[x][y] = 0;
        }

        // 初始建图
        for(int i=0; i<N; i++)
            for(int j=0; j<M; j++){
                if(j>0 && grid[i][j] && grid[i][j-1])
                    Union(fa, sz, M, i*M+j, i*M+j-1);
                if(i>0 && grid[i][j] && grid[i-1][j])
                    Union(fa, sz, M, i*M+j, (i-1)*M+j);
            }

        // 倒序补砖
        while (--L>-1){
            if(!b[L]) continue; // 空砖
            int x = hits[L][0];
            int y = hits[L][1];
            grid[x][y] = 1;     // 补砖
            /**
             * Union函数有两种写法，一种是指定最小元作为祖先，一种是完全以x为祖先
             * 对于第一种，每次需要统计出增量，然后汇总，最后得到答案
             * 对于第二种，只需要无脑合并四次，最后再统计一下增量并减一
             * 第二种比较合适，第一种的祖先可以保证永远是最小元
             */
            if(x>0 && grid[x-1][y])
                ans[L] += Union(fa, sz, M, x*M+y, (x-1)*M+y);
            if(x<N-1 && grid[x+1][y])
                ans[L] += Union(fa, sz, M, x*M+y, (x+1)*M+y);
            if(y>0 && grid[x][y-1])
                ans[L] += Union(fa, sz, M, x*M+y, x*M+y-1);
            if(y<M-1 && grid[x][y+1])
                ans[L] += Union(fa, sz, M, x*M+y, x*M+y+1);
        }

        return ans;
    }
};



void readLine(string line1, vector<vector<int>> & v){
    for(int i=0; i<line1.size()-2; i++)
        if(line1[i]==']' && line1[i+1]==',' && line1[i+2]=='[')
            line1[i] = ' ';
    stringstream ss;
    ss << line1;

    while (!ss.eof() && ss >> line1){
        stringstream ss2;
        ss2 << line1;
        vector<int> tempGrid;
        int k;
        while (!ss2.eof()){
            if(ss2>>k) tempGrid.emplace_back(k);
            else{
                ss2.clear();
                ss2.get();
            }
        }
        v.emplace_back(tempGrid);
    }
}

int main()
{
//    string s = "[[1,0,0,0],[1,1,1,0]]\n"
//               "[[1,0]]";
    vector<vector<int>> grid;
    vector<vector<int>> hits;

    fstream f("/Users/mark/CLionProjects/MarkLearningCPP/LC803/case6.txt");
    string line1, line2;
    f >> line1 >> line2;

    readLine(line1, grid);
    readLine(line2, hits);

    Solution slt;
    for(auto i: slt.hitBricks(grid, hits)){
        cout << i << '\t';
    };
}