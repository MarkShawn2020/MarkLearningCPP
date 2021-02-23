//
// Created by 南川 on 2021/2/20.
//


#include "cstdio"
#include "cstring"
#include "cmath"
#include "cassert"

#include "string"
#include "iostream"
#include "fstream"
#include "algorithm"

#include "vector"
#include "stack"
#include "list"
#include "queue"
#include "set"
#include "unordered_set"
#include "map"
#include "unordered_map"

using namespace std;

template<typename A> ostream & operator << (ostream & cout, vector<A> const &v) {
    cout << "["; for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";
}

#define Min(a, b) if((b)<(a)) (a) = (b)
#define Max(a, b) if((b)>(a)) (a) = (b)


const int N = 10000;
vector<int> G1[N + 1], G2[N + 1];
int n, m, a, b, k;
int visGlobal[N + 1];

void bfs(vector<int> G[], int u)
{
    vector<int> vis(n+1, 0);
    queue<int> Q;
    Q.push(u);
    if(!visGlobal[u]) ++k;
    ++visGlobal[u];
    ++vis[u];
//    printf("u: %d, list: [", u);
    while (!Q.empty())
    {
        auto cur = Q.front();
        Q.pop();
//        printf("%d ", cur);
        for(auto & item: G[cur])
            if(!vis[item])
            {
                if(!visGlobal[item]) ++k;
                ++visGlobal[item];
                ++vis[item];
                Q.push(item);
            }
    }
//    printf("]\n");
}

bool solve(int u)
{
    memset(visGlobal, 0, sizeof visGlobal);
    k = 0;
    bfs(G1, u);
    bfs(G2, u);
//    printf("u: %d, k: %d, n: %d\n", u, k, n);
    return k == n;
}

template <typename T>
void run(T & cin)
{
    int ans = 0;
    cin >> n >> m;
    for(int i=1; i<=n; ++i)
        G1[i].clear(),
        G2[i].clear();

    while (m--)
    {
        cin >> a >> b;
        G1[a].push_back(b);
        G2[b].push_back(a);
    }

    for(int i=1; i<=n; ++i)
        ans += solve(i);
    cout << ans << endl;
}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    // read from local case if possible, otherwise from console
    ifstream fin(
            "/Users/mark/MarkLearningCPP/Acwing/3250. 通信网络/case2.txt"
    );
    run(fin.good() ? fin : cin);
}

