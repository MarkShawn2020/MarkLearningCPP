//
// Created by 南川 on 2021/2/18.
//

#include "cstdio"
#include "queue"
#include "cstring"

using namespace std;

#define Min(a, b) if((b)<(a)) (a) = (b)
#define Max(a, b) if((b)>(a)) (a) = (b)
#define Encode(x, y) ((x) * 1000 + (y))


const int N = 1000 + 2;
int n, m, k, d, r1, r2, r3;

enum Type{Default, Store, Customer, Obstacle};
Type grid[N][N];
int customers[N*N][3];

queue<pair<int, int>> Q;
int vis[N][N];
int offset[4][4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int memory[N][N];

void readCase()
{
    scanf("%d %d %d %d", &n, &m, &k, &d);
    for(int i=0; i<m; ++i)
    {
        scanf("%d %d", & r1, & r2);
        grid[r1][r2] = Store;
    }

    for(int i=0; i<k; ++i)
    {
        scanf("%d %d %d", & r1, & r2, & r3);
        customers[i][0] = r1;
        customers[i][1] = r2;
        customers[i][2] = r3; // multi customers hook
        grid[r1][r2] = Customer;
    }

    for(int i=0; i<d; ++i)
    {
        scanf("%d %d", & r1, & r2);
        grid[r1][r2] = Obstacle;
    }
}

int bfsSolveCustomers(int *customer)
{
    if(memory[customer[0]][customer[1]])
        return memory[customer[0]][customer[1]];

    while (!Q.empty()) Q.pop();
    memset(vis, 0, sizeof vis);

    int dis = 0;
    Q.push({customer[0], customer[1]});
    while (!Q.empty())
    {
        ++dis;
        const int size = Q.size();
        for(int i=0; i<size; ++i)
        {
            auto & cur = Q.front();
            for(auto & j : offset)
            {
                int x = cur.first + j[0], y = cur.second + j[1];
                if(x < 1 || x > N || y < 1 || y > N) continue;
                if(vis[x][y] || grid[x][y] == Obstacle) continue;
                if(grid[x][y] == Store) return memory[x][y] = dis * customer[2];
                ++vis[x][y];
                Q.push({x, y});
            }
            Q.pop();
        }
    }
}

int main()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/3205. 最优配餐/case1.txt", "r", stdin);
    readCase();
    int ans = 0;
    for(int i=0; i<k; ++i)
        ans += bfsSolveCustomers(customers[i]);
    printf("%d", ans);
}