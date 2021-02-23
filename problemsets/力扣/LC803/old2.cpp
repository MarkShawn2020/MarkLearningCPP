class Solution {

public:
    static const int G = 200;

    enum InDir{UP=-1, DOWN=1, LEFT=-2, RIGHT=2, START=0};

    struct Deg{
        bool up = false;
        bool down = false;
        bool left = false;
        bool right = false;
        short in = 0;
    };

    void stableTraverse(vector<vector<int>> & grid, array<array<Deg, G>, G> & ds, int N, int M, int x, int y, InDir dir){
        /**
         * 一定是单向更新！
         */
        if(x<N-1 && grid[x+1][y] && !ds[x+1][y].up && dir!=DOWN){            // up to down
            ds[x+1][y].up = true;
            ++ds[x+1][y].in;
            stableTraverse(grid, ds, N, M, x+1, y, UP);
        }
        if(x>0 && grid[x-1][y] && !ds[x-1][y].down && dir!=UP){            // down to up
            ds[x-1][y].down = true;
            ++ds[x-1][y].in;
            stableTraverse(grid, ds, N, M, x-1, y, DOWN);
        }
        if(y<M-1 && grid[x][y+1] && !ds[x][y+1].left && dir!=RIGHT){          // left to right
            ds[x][y+1].left = true;
            ++ds[x][y+1].in;
            stableTraverse(grid, ds, N, M, x, y+1, LEFT);
        }
        if(y>0 && grid[x][y-1] && !ds[x][y-1].right && dir!=LEFT){           // right to left
            ds[x][y-1].right = true;
            ++ds[x][y-1].in;
            stableTraverse(grid, ds, N, M, x, y-1, RIGHT);
        }
    }

    void clearBackChain(vector<vector<int>> & grid, array<array<Deg, G>, G> & ds, int N, int M, int x, int y) {
        /**
         * 回溯清空链只考虑入度为1的结点，并沿着它的反方向删除入结点
         */
         if(x>0 && ds[x][y].up && ds[x-1][y].down){
             ds[x-1][y].down = false;
             if(--ds[x-1][y].in == 1)
                 clearBackChain(grid, ds, N, M, x-1, y);
         }
         if(x<N-1 && ds[x][y].down && ds[x+1][y].up){
             ds[x+1][y].up = false;
             if(--ds[x+1][y].in == 1)
                 clearBackChain(grid, ds, N, M, x+1, y);
         }
         if(y>0 && ds[x][y].left && ds[x][y-1].right){
             ds[x][y-1].right = false;
             if(--ds[x][y-1].in == 1)
                 clearBackChain(grid, ds, N, M, x, y-1);
         }
          if(y<M-1 && ds[x][y].right && ds[x][y+1].left){
             ds[x][y+1].left = false;
             if(--ds[x][y+1].in == 1)
                 clearBackChain(grid, ds, N, M, x, y+1);
         }

    }
    void killChain(vector<vector<int>> & grid, array<array<Deg, G>, G> & ds, int N, int M, int x, int y, int & k) {
        /**
         * 杀死自己只考虑入度为0的结点
         */
        grid[x][y] = 0;     // 杀死自己
        ds[x][y] = Deg{};   // 清空状态
        if(x>0 && ds[x-1][y].down){
            ds[x-1][y].down = false;
            if(--ds[x-1][y].in == 0) killChain(grid, ds, N, M, x-1, y, ++k);
            if(ds[x-1][y].in == 1) clearBackChain(grid, ds, N, M, x-1, y);
        }
        if(x<N-1 && ds[x+1][y].up){
            ds[x+1][y].up = false;
            if(--ds[x+1][y].in == 0) killChain(grid, ds, N, M, x+1, y, ++k);
            if(ds[x+1][y].in == 1) clearBackChain(grid, ds, N, M, x+1, y);
        }
        if(y>0 && ds[x][y-1].right){
            ds[x][y-1].right = false;
            if(--ds[x][y-1].in == 0) killChain(grid, ds, N, M, x, y-1, ++k);
            if(ds[x][y-1].in == 1) clearBackChain(grid, ds, N, M, x, y-1);
        }
        if(y<M-1 && ds[x][y+1].left){
            ds[x][y+1].left = false;
            if(--ds[x][y+1].in == 0) killChain(grid, ds, N, M, x, y+1, ++k);
            if(ds[x][y+1].in == 1) clearBackChain(grid, ds, N, M, x, y+1);
        }
    }

    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        const int N = grid.size();
        const int M = grid[0].size();
        const int L = hits.size();
        vector<int> ans(L, 0);

        // 图初始化，单向流动
        array<array<Deg, G>, G> ds;
        for(int col=0; col<M; ++col){
            if(grid[0][col]){
                ds[0][col].up = true;  // 对第一行的源点引入虚拟入度
                ++ds[0][col].in;
                stableTraverse(grid, ds, N, M, 0, col, UP);
            }
        }

        for(int i=0; i<L; ++i){
            int k = 0;
            int x = hits[i][0];
            int y = hits[i][1];
            if(!grid[x][y]) continue;
            killChain(grid, ds, N, M, x, y, k);
            cout << "Period: " << i << ", x: " << x <<", y: " << y << ", k: " << k << endl;
            for(int n=0; n<N; n++){
                for(int m=0; m<M; m++){
                    cout << grid[n][m] << " ";
                }
                cout << endl;
            }
            cout << "\n------------\n";
            ans[i] = k;
        }

        return ans;
    }
};
