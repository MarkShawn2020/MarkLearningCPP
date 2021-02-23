//
// Created by 南川 on 2021/1/22.
//
#include "cstdio"

const int N = 1e6 + 1;
int head = 0, tail = -1;
int qKey[N], qVal[N], ansGe[N], ansLe[N];


void step(const int & m, const int & i)
{
    int v;
    scanf("%d", &v);

    // 消消乐，从i到m的i-m+1个事有效，m-1已无效
    while (head<=tail && i-qKey[tail]>=m) --tail;
    while (head<=tail && i-qKey[head]>=m) ++head;

    int j = tail;
    while (j >= head && v > qVal[j]) {
        qVal[j + 1] = qVal[j];
        qKey[j + 1] = qKey[j];
        --j;
    }
    qVal[++j] = v;
    qKey[j] = i;
    ++tail;
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
        ansGe[i-m+1] = qVal[head];
        ansLe[i-m+1] = qVal[tail];
    }

    for(int i=0; i<n-m+1; i++) printf("%d ", ansLe[i]);
    printf("\n");
    for(int i=0; i<n-m+1; i++) printf("%d ", ansGe[i]);

}