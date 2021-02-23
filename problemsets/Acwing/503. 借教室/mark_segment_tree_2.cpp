#include "cstdio"
#include "cmath"
#include "cstring"
#include "algorithm"
#include "iostream"

using namespace std;

const int MAX_N = 1e6 + 1;  // 教室的最大可能数量

int n, m;                   // n: 教室数量， m: 订单个数
int d, s, t;                // d: 租借数量， s: 租借开始日， t: 租借结束日

int H, N, B;            // H: 树的高度，N: 树的结点数
                        // B: 树的最后一层第一个结点编号，也是最后一层个数

int caps[4 * MAX_N];        // 线段树的数组实现需要开辟4倍空间
int lazy[MAX_N];            // 懒更新标记数组

void push_up(int i)
{
    printf("push up to %d\n", i);
    caps[i] = min(caps[i << 1], caps[i<< 1 | 1]);
}

void push_down(int i)
{
    printf("push down from %d\n", i);
    if(lazy[i])
    {
        lazy[i << 1] += lazy[i],
        lazy[i << 1 | 1] += lazy[i];
        caps[i << 1] -= lazy[i];
        caps[i << 1 | 1] -= lazy[i];
        lazy[i] = 0;
    }
}


void build(int n)
{
    H = log2(n - 1) + 2;    // 树的高度，考虑8个结点，就是四层（1, 2, 4, 8）；9个结点就是5层
    N = 1 << H;             // 树的结点数，考虑4层，总结点数就是16（1+1+2+4+8），含虚结点
    B = N >> 1;             // 由于输入数据存在最后一层，所以记最后一层第一个结点下标为B(ase)
    
    // 将输入数据存入最后一层的起始部分
    for(int i=0; i<n; i++)   scanf("%d", &caps[B + i]);

    // 预填充最大
    for(int i=B+n; i<N; i++) caps[i] = 0x3f3f3f3f;

    // 最关键的一步，从后往前填充数组（根据两倍的父子关系）
    for(int i=B-1; i>0; i--) push_up(i);
}


bool updateStep(int d, int s, int t, int L, int R, int id)
{
    bool status = true;
    printf("id: %d, L: %d, R: %d\t", id, L, R);
    for(int i=1; i<N; i++) printf("(%2d, %d) ", caps[i], lazy[i]);
    printf("\n");

    if(s == L && t == R)
    {
        if(L < R) lazy[id] += d; // 非叶结点，标记懒更新
        status &= (caps[id] -= d) >= 0;
        if(!status){
            printf("----- over -----\t");
            for(int i=1; i<N; i++) printf("(%2d, %d) ", caps[i], lazy[i]);
            printf("\n");
        }
    }
    else
    {
        push_down(id);

        int M = (L + R) >> 1;
        if(t <= M) 
            status &= updateStep(d, s, t, L, M, id << 1);
        else if(s > M)
            status &= updateStep(d, s, t, M+1, R, id << 1 | 1);
        else
            status &= updateStep(d, s, M, L, M, id << 1),
            status &= updateStep(d, M+1, t, M+1, R, id << 1 | 1);
        
    }

        push_up(id);    
    return status;
}

   
int update(int m)
{
    for(int i=1; i<=m; i++) {
        cin >> d >> s >> t;
        printf(">>> (d: %d) [s - t]: [%d - %d]\n", d, s, t);
        if(!updateStep(d, s, t, 1, B, 1))
            return i;
    }
    return 0;
}

int main()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/503. 借教室/case3.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    build(n);
    
    int i = update(m);
    i ? printf("-1\n%d", i) : printf("0");
    return 0;
}