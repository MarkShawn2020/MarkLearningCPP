
//
// Created by 南川 on 2021/1/17.
//

#include "cstdio"
#include "vector"

using namespace std;

#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

static const int N = 100 + 2;

int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
int n,m, a[N][N], s[N][N], ans=0;

int dfs(int x,int y){
    /**
     * 记忆化搜索的关键
     */
    if(s[x][y])return s[x][y];//记忆化搜索
    s[x][y]=1;//题目中答案是有包含这个点的
    for(int i=0;i<4;i++)
    {
        int xx=dx[i]+x;
        int yy=dy[i]+y;//四个方向
        /**
         * 遇到比自己低的就往下遍历，最后使自己的路径长度加一
         */
        if(xx>0&&yy>0&&xx<=n&&yy<=m&& a[x][y]>a[xx][yy])
        {
            dfs(xx,yy);
            s[x][y]=max(s[x][y],s[xx][yy]+1);
        }
    }
    return s[x][y];
}


int main()
{
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/洛谷/动态规划/P1434/case1.txt", "r", stdin);

    scanf("%d%d",&n,&m);//同题目的R,C
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&a[i][j]);
    for(int i=1;i<=n;i++)//找从每个出发的最长距离
        for(int j=1;j<=m;j++)
            ans=max(ans,dfs(i,j));//取最大值
    printf("%d",ans);
    return 0;
}