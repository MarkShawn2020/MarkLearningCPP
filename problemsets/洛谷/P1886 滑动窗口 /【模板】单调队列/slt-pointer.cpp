//
// Created by 南川 on 2021/1/22.
//
#include "cstdio"
#include "climits"

const int N = 1e6 + 1;
int head = 0, tail = -1;
int qKey[N], qVal[N], ansGe[N], ansLe[N];


struct Node{
    int key = -1;
    int val = INT_MAX;
    Node * next{};
    Node * prev{};
} P;


void step(const int & m, const int & i)
{
    int v;
    scanf("%d", &v);
    Node * n = new Node{i, v};
    Node * p = & P;

    while (p->next && i - p->next->key >= m)
        p->next->prev = p, p->next = p->next->next;
    while (p->prev && i - p->prev->key >= m)
        p->prev->next = p, p->prev = p->prev->prev;

    while (p->next && p->next!=&P && p->next->val > v)
        p = p->next;
    if(p->next){
        n->next = p->next;
        n->prev = p;
        p->next = n->next->prev = n;
    }else{
        p->prev = p->next = n;
        n->next = n->prev = p;
    }
}

int main()
{
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/洛谷/P1886 滑动窗口 /【模板】单调队列/case1.txt", "r", stdin);

    int n, m;
    scanf("%d %d", &n, &m);

    for(int i=0; i<m-1; i++)
        step(m, i);
    for(int i=m-1; i<n; i++){
        step(m, i);
        ansGe[i-m+1] = P.next->val;
        ansLe[i-m+1] = P.prev->val;
    }

    for(int i=0; i<n-m+1; i++) printf("%d ", ansLe[i]);
    printf("\n");
    for(int i=0; i<n-m+1; i++) printf("%d ", ansGe[i]);

}