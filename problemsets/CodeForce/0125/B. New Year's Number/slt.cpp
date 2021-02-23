//
// Created by 南川 on 2021/1/25.
//

#include "cstdio"


bool judge(int v)
{
    int a, b;
    a = v / 2020;
    b = v % 2020;
    return b <= a;
}


int main()
{
//    freopen("/Users/mark/CLionProjects/MarkLearningCPP/CodeForce/0125/B. New Year's Number/case1.txt", "r", stdin);

    int n, v;
    scanf("%d", &n);
    for(int i=0; i<n; i++)
    {
        scanf("%d", &v);

        judge(v) ? printf("YES") : printf("NO");

        if(i != n-1) printf("\n");
    }
}