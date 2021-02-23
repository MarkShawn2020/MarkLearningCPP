//
// Created by 南川 on 2021/2/18.
//

#include "cstdio"
#include "queue"
#include "tuple"
using namespace std;

const int N = 1000;
int n, m, k, k2, d, r1, r2, r3;
long long ans;

int customers[N+2][N+2];
queue<pair<int, int>> Q;
int vis[N+2][N+2];
const int offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void readCase()
{
    scanf("%d %d %d %d", &n, &m, &k, &d);
    for(int i=0; i<m; ++i) {
        scanf("%d %d", & r1, & r2);
        ++vis[r1][r2];
        Q.push({r1, r2});
    }
    for(int i=0; i<k; ++i) {
        scanf("%d %d %d", &r1, &r2, &r3);
        if (!customers[r1][r2]) ++k2;
        customers[r1][r2] += r3;
    }
    for(int i=0; i<d; ++i) {
        scanf("%d %d", & r1, & r2);
        ++vis[r1][r2];
    }
}

void bfsSolveCustomers(int depth)
{
    int size = Q.size();
    while (size--)
    {
        auto & cur = Q.front(); Q.pop();
        for(auto & j : offset) {
            int x = cur.first + j[0], y = cur.second + j[1];
            if(x < 1 || x > n || y < 1 || y > n || vis[x][y]) continue;
            ++vis[x][y]; Q.push({x, y});
            if(customers[x][y]) {
                ans += depth * customers[x][y];
                if(--k2 == 0) return;
            }
        }
    }
    bfsSolveCustomers(++depth);
}

int main()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/3205. 最优配餐/case4.txt", "r", stdin);
    readCase();
    bfsSolveCustomers(1);
    printf("%lld", ans);
}