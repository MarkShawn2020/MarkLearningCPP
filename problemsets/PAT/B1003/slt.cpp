//
// Created by 南川 on 2021/1/19.
//
/**
 * 核心参考：PAT 1003 Emergency (Dijkstra算法 ) 示例解析 - 知乎 - https://zhuanlan.zhihu.com/p/138001717
 */
#include "cstdio"
#include "climits"
#include "cstring"
#define max(a, b) (a)>(b)?(a):(b)

const int N = 500;

int n, m, c1, c2, t1, t2, t3;

int edge[N][N], vex[N], vis[N];
unsigned int dis[N], teams[N], roads[N];


int main()
{
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/PAT/B1003/case1.txt", "r", stdin);

    scanf("%d %d %d %d", &n, &m, &c1, &c2);
    for(int i=0; i<n; i++)
        scanf("%d", &vex[i]);
    for(int i=0; i<m; i++){
        scanf("%d %d %d", &t1, &t2, &t3);
        edge[t2][t1] = edge[t1][t2] = t3;
    }

    unsigned int s = c1;
    memset(dis, -1, sizeof(dis));
    dis[s] = 0;
    teams[s] = vex[s];
    roads[s] = 1;
    for(int k=0; k<n; k++)
    {
        unsigned int u=-1, minDist = INT_MAX;
        // 获取未访问的结点中，已经探明的结点中的最小值
        for(int i=0; i<n; i++)
            if(!vis[i] && dis[i] < minDist){ u=i;minDist=dis[i];}
        if(u==-1) return 0;

        vis[u] = true;
        for(int v=0; v<n; v++){
            // 未访问 && 能连通 && 撑杆跳
            if(!vis[v] && edge[u][v]){
                if(dis[u] + edge[u][v] <= dis[v]){
                    dis[v] = dis[u] + edge[u][v];
                    if(dis[u] + edge[u][v] == dis[v]){
                        teams[v] = max(teams[v], teams[u] + vex[v]);
                        roads[v] = roads[u] + roads[v];
                    }else{
                        teams[v] = teams[u] + vex[v];
                        roads[v] = roads[u];
                    }
                }
            }
        }
    }
    printf("%d %d\n", roads[c2], teams[c2]);
}

