//
// Created by 南川 on 2021/2/18.
//

#include "cstdio"
#include "queue"
#include "tuple"

using namespace std;

#define Min(a, b) if((b)<(a)) (a) = (b)
#define Max(a, b) if((b)>(a)) (a) = (b)
#define Encode(x, y) ((x) * 1000 + (y))


const int N = 1000;
int n, m, k2, d, r1, r2, r3;

enum Type{Default, Store, Customer, Obstacle};
struct Grid{
    int v = 0;
    Type t = Default;
} grid[N+2][N+2];
int stores[N * N + 1][2];

queue<pair<int, int>> Q;
int vis[N+2][N+2];
int offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void readCase()
{
    int k;
    scanf("%d %d %d %d", &n, &m, &k, &d);
    for(int i=0; i<m; ++i)
    {
        scanf("%d %d", & r1, & r2);
        grid[r1][r2].t = Store;
        stores[i][0] = r1;
        stores[i][1] = r2;
    }

    for(int i=0; i<k; ++i)
    {
        scanf("%d %d %d", & r1, & r2, & r3);
        if(grid[r1][r2].t == Default) ++k2;
        grid[r1][r2].t = Customer;
        grid[r1][r2].v += r3;       // multi customers hook
    }

    for(int i=0; i<d; ++i)
    {
        scanf("%d %d", & r1, & r2);
        grid[r1][r2].t = Obstacle;
    }
}

long long bfsSolveCustomers()
{
    long long ans = 0;
    for(int i=0; i<m; ++i)
        Q.push({stores[i][0], stores[i][1]});
    int dis = 0;
    while (!Q.empty())
    {
        ++dis;
        const int size = Q.size();
        for(int i=0; i<size; ++i)
        {
            auto & cur = Q.front();
//            printf("cur: <%d, %d>\n", cur.first, cur.second);
            for(auto & j : offset)
            {
                int x = cur.first + j[0], y = cur.second + j[1];
                if(x < 1 || x > n || y < 1 || y > n) continue;
                if(vis[x][y] || grid[x][y].t == Obstacle || grid[x][y].t == Store) continue;
                ++vis[x][y];
                Q.push({x, y});
                if(grid[x][y].t == Customer) {
                    ans += (long long)dis * grid[x][y].v;
//                    printf("dis: %d, x: %d, y: %d, v: %d, ans: %lld\n", dis, x, y, grid[x][y].v, ans);
                    if(--k2 == 0) return ans;
                }
            }
            Q.pop();
        }
    }
}

int main()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/3205. 最优配餐/case4.txt", "r", stdin);
    readCase();
    printf("%lld", bfsSolveCustomers());
}