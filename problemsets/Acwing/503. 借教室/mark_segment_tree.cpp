#include "cstdio"
#include "cmath"
#include "cstring"
#include "algorithm"

using namespace std;

const int MAX_N = 1e6 + 1;  // 教室的最大可能数量
const int MAX = 0x3f3f3f3f; // 题目求最小，所以预填充最大

int n, m;                   // n: 教室数量， m: 订单个数
int d, s, t;                // d: 租借数量， s: 租借开始日， t: 租借结束日

int H, N, B;                // H: 树的高度，N: 树的结点数，B: 树的最后一层第一个结点编号

int caps[4 * MAX_N];        // 线段树的数组实现需要开辟4倍空间
int lazy[MAX_N];            // 懒更新标记数组


void build(int n)
{
    H = log2(n - 1) + 2;    // 树的高度，考虑8个结点，就是四层（1, 2, 4, 8）；9个结点就是5层
    N = 1 << H;             // 树的结点数，考虑4层，总结点数就是16（1+1+2+4+8），含虚结点
    B = N >> 1;             // 由于输入数据存在最后一层，所以记最后一层第一个结点下标为B(ase)
    
    // 将输入数据存入最后一层的起始部分
    for(int i=0; i<n; i++)  
        scanf("%d", &caps[B + i]);

    // 预填充最大
    for(int i=B+n; i<N; i++) 
        caps[i] = MAX;

    // 最关键的一步，从后往前填充数组（根据两倍的父子关系）
    for(int i=B-1; i>0; i--)    
        caps[i] = min(caps[i << 1], caps[(i << 1) + 1]);
}

/**
 * 给定区间[s, t]，更新的时候，从线段树的顶部往下二分地去寻找区间的匹配
 * 
 * 首先L = 0, R = N; 这样[s, t] ⊆ [L, R]
 * 由于L == 2^0, R == 2^H，因此可对L、R进一步二分，即 M = (L + R) >> 1，
 * 则有 [L, M], [M+1, R]，以此递归进行。
 * 
 * 紧接着，[L, R] 在递归过程中，主要会出现三种情况：
 * 1. [s, t] ⊆ [L, M],  则[L, R] = [L, M]，继续递归
 * 2. [s, t] ⊆ [M+1, R],则[L, R] = [M+1, R]，继续递归
 * 3. L <= s <= M < t <= R， 此时，就需要二分：
 *      01. [L1, R1] = [L,   M]，且[s1, t1] = [s,   M]
 *      02. [L2, R2] = [M+1, R]，且[s2, t2] = [M+1, t]
 * 
 * 最终，将必然会抵达 [s, t] == [L, R]，此时：
 * 1. 若是叶子结点，则直接更新，并往上同步
 * 2. 若是中间节点，则标记更新，并往上同步
 */
bool BiUpdate(int d, int s, int t, int L, int R)
{
    // 区间[L, R]对应的根节点编号：u
    int u = L >> (int)log2(R - L + 1);
    printf("d: %d, s: %d, t: %d, L: %d, R: %d, u: %d\n", d, s, t, L, R, u);

    // 同区间，更新并往上同步
    // 考虑L=6, R=7，则应该更新第3个结点，即 L >> 1
    // 考虑L=4, R=7，则应该更新第1个结点，即 L >> log2(R-L+1)
    if(s == L && t == R)    
    {
        if(L != R) lazy[u] += d; // 非叶结点懒标记
        if((caps[u] -= d) <0) return false;
        while(u > 1) 
            u >>= 1,
            caps[u] = min(caps[u << 1], caps[(u << 1) + 1]);
        return true;
    }   

    // 懒标记下钻更新
    if(lazy[u])
    {
        caps[u << 1]        -= lazy[u];
        caps[(u << 1) + 1]  -= lazy[u];
        if((u << 1) < B)
            lazy[u << 1] += lazy[u],
            lazy[(u << 1) + 1] += lazy[u];
        lazy[u] = 0;
    }

    // 递归与二分
    int M = (L + R) >> 1;
    if(t <= M) 
        return BiUpdate(d, s, t, L, M);
    else if(s > M)
        return BiUpdate(d, s, t, M+1, R);
    else if(BiUpdate(d, s, M, L, M))
        return BiUpdate(d, M+1, t, M+1, R);
    else
        return false;
}


void update(int m)
{
    for(int i=1; i<=m; i++)
    {
        scanf("%d %d %d", &d, &s, &t);
        if(!BiUpdate(d, s, t, 1, N-1))
        {
            for(int i=1; i<N; i++)
                printf("%d ", caps[i]);
            printf("-1\n%d", i);
            return;
        }
    }
    printf("0");
}

int main()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/503. 借教室/case1.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    build(n);
    update(m);
    return 0;
}