//
// Created by 南川 on 2021/1/22.
//
#include "cstdio"
#include "climits"
#include "string"

const int N = 1e6 + 1;

class Queue
{
private:
    int m_;
    bool isMax_;
    int * keys;
    int * vals;
    int head = 1;
    int tail = 0;

public:
    explicit Queue(const int m, const bool isMax): m_(m), isMax_(isMax){
        keys = new int[N];
        vals = new int[N];
        keys[0] = -1;
        vals[0] = isMax ? INT_MAX : INT_MIN;
    }

    inline int getHead() const{ return vals[head];}

    inline void addEle(int i, int v)
    {
        while (head <= tail && i - keys[head] >= m_)
            ++head;
        while (head <= tail && (isMax_ ? vals[tail] <= v : vals[tail] >= v))
            --tail;
        vals[++tail] = v;
        keys[tail] = i;
    }
};

int main()
{
//    freopen("/Users/mark/CLionProjects/MarkLearningCPP/洛谷/P1886 滑动窗口 /【模板】单调队列/case1.txt", "r", stdin);

    int n, m;
    scanf("%d %d", &n, &m);

    Queue qMin(m, false);
    Queue qMax(m, true);

    int v;
    for(int i=0; i<m-1; i++){
        scanf("%d", &v);
        qMax.addEle(i, v);
        qMin.addEle(i, v);
    }

    int ansGe[N], ansLe[N];
    for(int i=m-1; i<n; i++){
        scanf("%d", &v);
        qMax.addEle(i, v);
        qMin.addEle(i, v);
        ansLe[i-m+1] = qMin.getHead();
        ansGe[i-m+1] = qMax.getHead();
    }

    // 小 -> 大
    for(int i=0; i<n-m+1; i++) printf("%d ", ansLe[i]);
    printf("\n");
    for(int i=0; i<n-m+1; i++) printf("%d ", ansGe[i]);

    return 0;

}