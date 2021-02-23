//
// Created by 南川 on 2021/1/22.
//
#include "cstdio"
#include "tuple"
#include "climits"


const int N = 8 + 1;
int keys[N] = {0};
int vals[N];
int h1 = 0, h2 = 0, l1 = 0, l2 = 0, A = 0;


void addNode(int i, int v, const int T)
{
    // 移除端点的过期结点，由于采用了紧凑的技术，只需加加渐渐即可
    if(i - keys[h1] >= T) ++h1;
    if(i - keys[l2] >= T) --l2;

    // 寻找恰好v较大的位置，即 vals[p-1] > v >= vals[p]
    int p = h1;
    while (v < vals[p]) ++p;

    if(p <= h2) { // 尝试紧凑p位置起到h2之前的结点
        for(int j=p-1; j>=h1; --j)
            vals[j+h2-p] = vals[j], keys[j+h2-p] = keys[j];
        h1 += h2 - p;
    }else { // 尝试紧凑h1位置到p位置之间的结点
        for(int j=p; j>=l1; --j)
            vals[j-p+l1] = vals[j], keys[j-p+l1] = keys[j];


    }



//
//    int p;
//    if(v >= vals[A])
//        for(p=h1; p<=h2 && v<vals[p]; ++p);
//    else
//        for(p=l1; p<=l2 && v<vals[p]; ++p);
//
//    // 更新h2、l1、h2
//    if(p >= A) l1 = p;
//    if(p <= A) h2 = p;
//    if(p > h2) ++h2;
//
//    // 在右链的移动
//
//
//    { // p在A上，且比A大，从A起要整体右移
//        for(int j = l2; j>=A; --j)
//            keys[j+1] = keys[j], vals[j+1] = vals[j];
//        ++l1;
//    }
//    vals[p] = v, keys[p] = i, A = p;
}

int main()
{
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/洛谷/P1886 滑动窗口 /【模板】单调队列/case1.txt", "r", stdin);

    int n, m, v;
    scanf("%d %d", &n, &m);

    scanf("%d", &vals[0]);

    int ansLe[N], ansGe[N];
    for(int i=1; i<n; i++)
    {
        scanf("%d", &v);

        addNode(i, v, m);
        if(i>=m-1)
            ansGe[i-m+1] = vals[h1], ansLe[i-m+1] = vals[l2];
    }

    // 小 -> 大
    for(int i=0; i<n-m+1; i++) printf("%d ", ansLe[i]);
    printf("\n");
    for(int i=0; i<n-m+1; i++) printf("%d ", ansGe[i]);

    return 0;

}