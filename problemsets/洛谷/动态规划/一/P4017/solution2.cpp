//
// Created by 南川 on 2021/1/17.
//

#include "cstdio"
#define max(a, b) a > b ? a : b;

const int N = 5000 + 1;
const int M = 500000 + 1;

int n, m, t1, t2;

struct node {
    int id;
    node * next;
};

int degOut[N];
node prev[N];
int store[N];

void cutBack(int end)
{
    node * p = prev[end].next;
    if(!p) printf("%d", store[end]);
    while (p){
        store[p->id] += store[end];
        if(!--degOut[p->id]) cutBack(p->id);
        p = p->next;
    }
}


int main()
{
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/洛谷/动态规划/P4017/case1.txt", "r", stdin);
    scanf("%d %d", &n, &m);

    for(int i=1; i<=m; i++)
    {
        scanf("%d %d", &t1, &t2);
        node * p = new node{t1};

        if(prev[t2].next)
            p->next = prev[t2].next;
        prev[t2].next = p;
        ++degOut[t1];
    }

    for(int i=1; i<=n; i++)
        if(!degOut[i])
        {
            store[i] = 1;
            cutBack(i);
            break;
        }

    return 0;
}