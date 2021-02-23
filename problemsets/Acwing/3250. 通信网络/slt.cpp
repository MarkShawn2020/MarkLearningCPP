//
// Created by 南川 on 2021/2/20.
//

#include "cstdio"
#include "vector"
using namespace std;

const int N = 1000;
int degIn[N+1], degOut[N+1], vis[N+1];
vector<vector<int>> adjIn(N+1), adjOut(N+1);
int nStt, nEnd;
int n, m, a, b, ans, k;


//#define printf(...) true
void check()
{
    nStt = nEnd = 0;
    vector<int> delStt, delEnd;
    for(int i=1; i<=n; ++i)
    {
        if(!vis[i] && !degIn [i]) {
             printf("[no in] i: %d\n", i);
            vis[i] = true;
            --k;
            ++nStt;
            delStt.push_back(i);
        }

        if(!vis[i] && !degOut[i]){
             printf("[no out] i: %d\n", i);
            vis[i] = true;
            --k;
            ++nEnd;
            delEnd.push_back(i);
        }
    }

    if(delStt.empty() && delEnd.empty())
    {
        ans += k;
        k = 0;
        return;
    }
    if(nStt == 1) ++ans;
    if(nEnd == 1) ++ans;
    for(auto & i: delStt) for(auto & j: adjOut[i]) --degIn[j];
    for(auto & i: delEnd) for(auto & j: adjIn[i]) --degOut[j];
    printf("n: %d, k: %d, nStt: %d, nEnd: %d, ans: %d\n", n, k, nStt, nEnd, ans);
}


#define printf(...) printf(__VA_ARGS__)
int main()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/3250. 通信网络/case3.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    k = nStt = nEnd = n;
    while(m--)
    {
        scanf("%d %d", &a, &b);
        ++degOut[a];
        ++degIn [b];
        adjOut[a].push_back(b);
        adjIn [b].push_back(a);
    }

    while(k)
        check();

    printf("%d", ans);
}