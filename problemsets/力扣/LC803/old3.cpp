//
// Created by 南川 on 2021/1/16.
//


class Solution {

public:

    static const int G = 5;
    static const int S = -1;

    void initFather(vector<vector<int>>& grid, int fa[], const int N, const int M, int x, int y, const int f) {
        if(x>0 && grid[x-1][y] && fa[(x-1)*G+y]==(x-1)*G+y){
            fa[(x-1)*G+y] = f;
            initFather(grid, fa, N, M, x - 1, y, f);
        }
        if(x<N-1 && grid[x+1][y] && fa[(x+1)*G+y]==(x+1)*G+y){
            fa[(x+1)*G+y] = f;
            initFather(grid, fa, N, M, x + 1, y, f);
        }
        if(y>0 && grid[x][y-1] && fa[x*G+(y-1)]==x*G+(y-1)) {
            fa[x*G+(y-1)] = f;
            initFather(grid, fa, N, M, x, y - 1, f);
        }
        if(y<M-1 && grid[x][y+1] && fa[x*G+(y+1)]==x*G+(y+1)){
            fa[x*G+(y+1)] = f;
            initFather(grid, fa, N, M, x, y + 1, f);
        }
    }

    void joinBrick(vector<vector<int>>& grid, int fa[], const int N, const int M, int x, int y, const int f, int & k) {
        if(x>0 && grid[x-1][y] && fa[(x-1)*G+y]!=f){  // join的都是那些没有连的，所以不用Find了
            fa[(x-1)*G+y] = f;
            joinBrick(grid, fa, N, M, x - 1, y, f, ++k);
        }
        if(x<N-1 && grid[x+1][y] && fa[(x+1)*G+y]!=f){
            fa[(x+1)*G+y] = f;
            joinBrick(grid, fa, N, M, x + 1, y, f, ++k);
        }
        if(y>0 && grid[x][y-1] && fa[x*G+(y-1)]!=f) {
            fa[x*G+(y-1)] = f;
            joinBrick(grid, fa, N, M, x, y - 1, f, ++k);
        }
        if(y<M-1 && grid[x][y+1] && fa[x*G+(y+1)]!=f){
            fa[x*G+(y+1)] = f;
            joinBrick(grid, fa, N, M, x, y + 1, f, ++k);
        }
    }

    int addBrick(vector<vector<int>>& grid, int fa[], const int N, const int M, int x, int y) {
        grid[x][y] = 1;
        int sFather = x*G+y; // 最小的父亲
        if(x>0 && grid[x-1][y] && Find(fa, (x-1)*G+y)<sFather) sFather = fa[(x-1)*G+y];
        if(x<N-1 && grid[x+1][y] && Find(fa, (x+1)*G+y)<sFather) sFather = fa[(x+1)*G+y];
        if(y>0 && grid[x][y-1] && Find(fa, (x)*G+y-1)<sFather) sFather = fa[(x)*G+y-1];
        if(y<M-1 && grid[x][y+1] && Find(fa, (x)*G+y+1)<sFather) sFather = fa[(x)*G+y+1];
        fa[x*G+y] = sFather;    // 把自己更新一下
        if(sFather>=G) return 0; // 所有的结点都没有连到顶部的

        int k = 0;
        if(x>0 && grid[x-1][y]) {
            if(fa[fa[(x-1)*G+y]]>=G){
                fa[fa[(x-1)*G+y]] = sFather;
                joinBrick(grid, fa, N, M, x-1, y, sFather, ++k);
            }else{
                fa[fa[(x-1)*G+y]] = sFather;
            }
        }
        if(x<N-1 && grid[x+1][y]) {
            if(fa[fa[(x+1)*G+y]]>=G)
            {
                fa[fa[(x+1)*G+y]] = sFather;
                joinBrick(grid, fa, N, M, x+1, y, sFather, ++k);
            }else{
                fa[fa[(x+1)*G+y]] = sFather;
            }
        }
        if(y>0 && grid[x][y-1]) {
            if(fa[fa[x*G+y-1]]>=G){
                fa[fa[x*G+y-1]] = sFather;
                joinBrick(grid, fa, N, M, x, y-1, sFather, ++k);
            }else{
                fa[fa[x*G+y-1]] = sFather;
            }
        }
        if(y<M-1 && grid[x][y+1]) {
            if(fa[fa[x*G+y+1]]>=G){
                fa[fa[x*G+y+1]] = sFather;
                joinBrick(grid, fa, N, M, x, y+1, sFather, ++k);
            }else{
                fa[fa[x*G+y+1]] = sFather;
            }
        }
        return k;
    }

    int Find(int fa[], int x){
        return fa[x]==x ? x : fa[x]=Find(fa, fa[x]);
    }

    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        const int N = grid.size();
        const int M = grid[0].size();
        int L = hits.size();
        vector<int> ans(L, 0);
        vector<int> initHasBrick(L, 0);

        int fa[G*G];
        for(int i=0; i<G*G; ++i)
            fa[i] = i;

        // 先敲，不掉其它
        for(int i=0; i<L; i++){
            initHasBrick[i] = grid[hits[i][0]][hits[i][1]];
            grid[hits[i][0]][hits[i][1]] = 0;
        }

        // 计算初始图的并查集状态
        for(int j=0; j<M; j++)
            if(grid[0][j] && fa[j]==j)
                initFather(grid, fa, N, M, 0, j, j);

        // 反向使用并查集
        while (--L>=0){
            int x = hits[L][0];
            int y = hits[L][1];
            if(initHasBrick[L]) // 原先有砖块才补
                ans[L] = addBrick(grid, fa, N, M, x, y);
        }

        return ans;
    }
};
