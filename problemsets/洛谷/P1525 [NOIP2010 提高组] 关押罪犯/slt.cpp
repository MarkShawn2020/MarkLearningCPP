//
// Created by 南川 on 2021/1/28.
//

#include "fstream"
#include "iostream"
#include "vector"
#include "queue"
#include "map"
#include "algorithm"
#include "cassert"

using namespace std;

typedef pair<int, pair<int, int>> ppi;

const int N = 2e4 + 1;
const int M = 1e5 + 1;

int fa[N], w[N], op[N]; // op存储并查集内祖先结点的对手结点
ppi adj[M];

int Find(int x){return x == fa[x] ? x : fa[x] = Find(fa[x]);}

bool Do(int x, int y)
{
    x = Find(x), y = Find(y);
    if(x == y) return true;                                 // 已在同一个组，不能再分
    else if(!op[x] && !op[y]) op[x] = y, op[y] = x;         // 同一个群里的两个组
    else if(!op[x] &&  op[y]) fa[x] = op[y], ++w[x];                // 不同群的两个组，x待分类，分类至y对面
    else if( op[x] && !op[y]) fa[y] = op[x], ++w[y];                // 反之
    else if(op[x] != y && op[x] != op[y]) 
    {
        int ox = op[x], oy = op[y];
        if(w[x] < w[oy]) swap(x, oy); fa[oy] = x, w[x] += w[oy];
        if(w[y] < w[ox]) swap(y, ox); fa[ox] = y, w[y] += w[ox];
        op[x] =y, op[y] =x; // important
    }
    else {}
    // printf("x: %d, y: %d, ox: %d, oy: %d\n", x, y, op[x], op[y]);
    return false;
}

template <typename T>
int run(T & cin)
{
    int n, m, r1, r2, r3;
    cin >> n >> m;
    for(int i=1; i<=n; i++) fa[i] = i, w[i] = 1;

    for(int i=0; i<m; i++)
        cin >> r1 >> r2 >> r3,
        adj[i] = {r3, {r1, r2}};
    sort(adj, adj+m, greater<ppi>());

    for(auto & p: adj)
    {
        // printf("v: %6d, x_: %d, y_: %d\t", p.first, p.second.first, p.second.second);
        if(Do(p.second.first, p.second.second))
            return printf("%d", p.first);
    }

    return printf("%d", 0);
}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    // read from local case if possible, otherwise from console
    ifstream fin("/Users/mark/MarkLearningCPP/洛谷/P1525 [NOIP2010 提高组] 关押罪犯/case1.txt");
    run(fin.good() ? fin : cin);
}

