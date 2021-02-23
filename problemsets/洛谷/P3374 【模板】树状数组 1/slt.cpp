//
// Created by 南川 on 2021/1/24.
//

#include "cstdio"
#include "string"
using namespace std;

const int N = 5 * 1e5 + 1;

inline int lowbit(int x)
{
    return x & (-x);
}

void update(int a[], const int n, int k, int v)
{
    for(; k<=n; k+=lowbit(k))
        a[k] += v;
}

int findSum(int a[], const int n, int k)
{
    int ans = 0;
    for(; k>0; k-=lowbit(k))
        ans += a[k];
    return ans;
}


int main()
{
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/洛谷/P3374 【模板】树状数组 1/case1.txt", "r", stdin);

    int n, m, v, t1, t2, t3;
    scanf("%d %d", &n, &m);

    int arr[N];
    fill(arr, arr+N, 0);
    for(int i=1; i<=n; i++)
        scanf("%d", &v), update(arr, n, i, v);

    for(int i=0; i<m; i++)
    {
        scanf("%d %d %d", &t1, &t2, &t3);
        if(t1 == 1)
            update(arr, N, t2, t3);
        else if(t1 == 2)
            printf("%d\n", findSum(arr, n, t3) - findSum(arr, n, t2-1));
    }

    return 0;
}