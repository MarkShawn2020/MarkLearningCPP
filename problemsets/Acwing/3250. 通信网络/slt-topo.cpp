//
// Created by 南川 on 2021/2/23.
//
#include "cstdio"
#include "iostream"
#include "vector"
#include "unordered_set"

using namespace std;

#include "MarkTemplates.h"

int n, m, a, b, ans, epoch;
const int N = 10;
const int M = 20;
bool closed[N], open[N];

int head[N], edge_next[M], edge_to[M], edge_vis[M];
int degIn[N];
unordered_set<int> S;

bool checkNoChildren(int u) {
    for (int e = head[u]; e; e = edge_next[e])
        if(degIn[edge_to[e]])
            return false;
    return true;
}

// 每次加完集合之后判断集合元素个数
void judge()
{
    const int sz = S.size();
    if(sz == 1) ++ans;      // 集合元素只有1个，加入
    for(int u: S) {
        for (int e = head[u]; e; e = edge_next[e]) {
            if (edge_vis[e]) continue;
            ++edge_vis[e];
            int v = edge_to[e];
            printf("u: %d, v: %d\n", u, v);
            if (--degIn[v] > 0) continue;
            S.insert(v);
        }
    }
    for(int u: S) {
        if(checkNoChildren(u))
            S.erase(u);
    }

    epoch++;
    printf(">> epoch: %d, ", epoch);
    mark::printSTL(S.begin(), S.end(), "S");

}

int main()
{
    freopen("/Users/mark/MarkLearningCPP/problemsets/Acwing/3250. 通信网络/case2.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    printf("n: %d, m: %d\n", n, m);

    for(int i=1; i<=m; ++i) {
        scanf("%d %d", &a, &b);
        printf("%d->%d  ", a, b);
        ++degIn[b];
//        ++degOut[a];
        edge_to[i] = b;
        edge_next[i] = head[a];
        head[a] = i;
    }
    cout << endl;


    for(int i=1; i<=n; ++i) if(!degIn[i]) S.insert(i);

    printf(">> epoch: %d, ", epoch);
    mark::printSTL(S.begin(), S.end(), "S");
    for (int i = 0; i < 5; ++i) {
        judge();
    }

    /**
     * S 1对1， 则两个都是答案，S1 被 S2取代
     * S 1对多，则第一个是答案，S1 被 S2取代
     * S 多对1，则第二个是答案，S1 被 S2取代
     * S 多对多，
     */

    printf("%d\n", ans);
}