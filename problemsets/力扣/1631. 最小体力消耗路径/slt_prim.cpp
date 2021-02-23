//
// Created by 南川 on 2021/1/28.
//

#include "fstream"
#include "iostream"
#include "iomanip"
#include "vector"
#include "queue"
#include "algorithm"
#include "cmath"
#include "/Users/mark/MarkLearningCPP/io/read_case.h"

using namespace std;


class Solution {
public:
    int minimumEffortPath(vector<vector<int> >& heights) {
        const int H = heights.size();
        const int W = heights[0].size();

        vector<vector<bool>> vis(H, vector<bool>(W, false));
        vector<vector<int> > dis(H, vector<int>(W, 0x3f3f3f3f));
        dis[0][0] = 0;

        typedef pair<int, pair<int, int> > Pair;
        priority_queue<Pair, vector<Pair>, greater<Pair>> PQ;
        PQ.push({0, {0, 0}});

        for(int epoch=1; !vis[H-1][W-1]; epoch++)
        {
            while (vis[PQ.top().second.first][PQ.top().second.second]) PQ.pop();
            int x, y, v = PQ.top().first;
            tie(x, y) = PQ.top().second;
            PQ.pop();

            vis[x][y] = true;
            if(y>0 && !vis[x][y-1])
                dis[x][y-1] = min(dis[x][y-1], max(v, (int)fabs(heights[x][y] - heights[x][y-1]))),
                PQ.push({dis[x][y-1], {x, y-1}});

            if(y<W-1 && !vis[x][y+1])
                dis[x][y+1] = min(dis[x][y+1], max(v, (int)fabs(heights[x][y] - heights[x][y+1]))),
                PQ.push({dis[x][y+1], {x, y+1}});

            if(x>0 && !vis[x-1][y])
                dis[x-1][y] = min(dis[x-1][y], max(v, (int)fabs(heights[x][y] - heights[x-1][y]))),
                PQ.push({dis[x-1][y], {x-1, y}});

            if(x<H-1 && !vis[x+1][y])
                dis[x+1][y] = min(dis[x+1][y], max(v, (int)fabs(heights[x][y] - heights[x+1][y]))),
                PQ.push({dis[x+1][y], {x+1, y}});


            cout << setw(3) << setfill('.') << ++epoch
                << ":\tdis[" << x << "][" << y << "]=" << dis[x][y] << endl;
    
        }
        return dis[H-1][W-1];
    }
};

template <typename T>
void run(T & cin)
{
    string s;
    cin >> s;
    vector<vector<int> > dta = readIntVector2D(s);
    Solution slt;
    cout << slt.minimumEffortPath(dta);

}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    // read from local case if possible, otherwise from console
    ifstream fin("/Users/mark/MarkLearningCPP/力扣/1631. 最小体力消耗路径/case4.txt");
    run(fin.good() ? fin : cin);
}

