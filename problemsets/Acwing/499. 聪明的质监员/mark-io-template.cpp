//
// Created by 南川 on 2021/1/28.
//

#include "fstream"
#include "iostream"
#include "vector"
#include "queue"
#include "algorithm"

using namespace std;

typedef long long lld;

const int N = 2e5 + 1;
int w[N], v[N];
int L[N], R[N];
lld Sum[N];
int Cnt[N];
int n, m;
lld ans=1e12, S;


void BiFind(int p, int q)
{
    if(p > q) return;

    int W = (p + q) / 2;
    for(int i=1; i<=n; ++i)
        if(w[i] >= W)
            Sum[i] = Sum[i-1] + v[i], // 不能用+=，因为会多次外循环
            Cnt[i] = Cnt[i-1] + 1;
        else
            Sum[i] = Sum[i-1],
            Cnt[i] = Cnt[i-1];

    lld Y = 0;
    int x, y;
    for(int i=1; i<=m; ++i)
        x = L[i]-1, y = R[i],
        Y += (Sum[y] - Sum[x]) * (Cnt[y] - Cnt[x]);

    ans = min(ans, llabs(S - Y));
//    printf("p: %6d, q: %6d, W: %6d, Y: %10lld, delta: %10lld ans: %10lld\n", p, q, W, Y, S - Y, ans);
    return Y < S ? BiFind(p, W-1) : BiFind(W+1, q);
}

template <typename T>
void run(T & cin)
{
    cin >> n >> m >> S;
    for(int i=1; i<=n; ++i) cin >> w[i] >> v[i];
    for(int i=1; i<=m; ++i) cin >> L[i] >> R[i];

    BiFind(0, N);
//    BiFind(8140,  8142);
    cout << ans;
}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    // read from local case if possible, otherwise from console
    ifstream fin("/Users/mark/MarkLearningCPP/Acwing/499. 聪明的质监员/case4.txt");
    run(fin.good() ? fin : cin);
}

