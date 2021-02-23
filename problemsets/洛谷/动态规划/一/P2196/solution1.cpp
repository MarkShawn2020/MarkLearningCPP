//
// Created by 南川 on 2021/1/17.
//
#include "cstdio"
#define max(a,b) a>b?a:b;

const int N = 21;

int n;
int nBooms[N];
int graph[N][N];
int store[N];
int child[N];

int dfs(int i){
    if(store[i]) return store[i];   // memory search
    int s = 0;
    int k = 0;
    for(int j=1; j<=n; ++j)
        if(graph[i][j]){
            int s2 = dfs(j);
            if(s < s2){
                s = s2;
                k = j;
            }
        }
    child[i] = k;
    return store[i] = s + nBooms[i];
}

int main()
{
//    freopen("/Users/mark/CLionProjects/MarkLearningCPP/洛谷/动态规划/P2196/case1.txt", "r", stdin);

    scanf("%d", &n);
    for(int i=1; i<=n; ++i)
        scanf("%d", &nBooms[i]);
    for(int i=1; i<=n; ++i)
        for(int j=1; j<=n-i; ++j)
            scanf("%d", &graph[i][i+j]);

    int ans1 = 0;
    int head = 0;
    for(int i=1; i<n; ++i){
        int ans2 = dfs(i);
        if(ans2 > ans1){
            ans1 = ans2;
            head = i;
        }
    }
    while (child[head]){
        printf("%d ", head);
        head = child[head];
    }
    printf("%d", head);

    printf("\n%d", ans1);
    return 0;
}