//
// Created by 南川 on 2021/2/20.
//

#include "iostream"
#include "vector"
#include "queue"
#define Min(a, b) if((b) < (a)) (a) = (b)
using namespace std;

template<typename A> ostream & operator << (ostream & cout, vector<A> const &v) {
    cout << "["; for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";
}

const int N = 10000;
vector<int> G[2][N + 1];
int Vis[2][N + 1];
int n, m, a, b;

int ancestors[N + 1], nums[N + 1], vis[N + 1], stack[N + 1], top, num, k;
vector<int> scc[N + 1];

#define printf(...) true
void dfs(int u)
{
    stack[top++] = u;
    printf(">>> u: %d\n", u);
    ancestors[u] = nums[u] = ++k;
    for(auto & v: G[0][u])
    {
        if(!nums[v])
        {
            printf("to visit child v: %d\n", v);
            dfs(v);
            if(ancestors[u] > ancestors[v])
                printf("low[%d] = low[%d] = %d\n", u, v, ancestors[v]);
            Min(ancestors[u], ancestors[v]);
        }
        else if(!vis[v] && nums[v] < nums[u])
        {
            if(ancestors[u] > nums[v])
                printf("low[%d] = nums[%d] = %d\n", u, v, nums[v]);
            Min(ancestors[u], nums[v]);
        }
    }

    printf("u: %d, nums[%d]=%d, lows[%d]=%d\n", u, u, nums[u], u, ancestors[u]);
    ++vis[u];
    if(nums[u] == ancestors[u])
    {
        while (true)
        {
            int v = stack[--top];
            scc[num].push_back(v);
            printf("u: %d, v: %d\n", u, v);
            if(u == v) break;
        }
        ++num;
    }
    printf("    u: %d <<<\n", u);

}

void tarjan()
{
    for(int i=1; i<=n; ++i)
        if(!nums[i]){
            printf("--- %d ---\n", i);
            dfs(i);
            printf(" \n---- ||| ----\n");
        }
}

void bfs(vector<int> G[], int vis[], int u)
{
    queue<int> Q; Q.push(u); ++vis[u];
    while (!Q.empty())
    {
        auto cur = Q.front(); Q.pop();
        for(auto & item: G[cur])
            if(!vis[item])
                ++vis[item], Q.push(item);
    }
}

bool solve(int u)
{
    for(int i=1; i<=n; ++i)
        Vis[0][i] = Vis[1][i] = 0;
    bfs(G[0], Vis[0], u);
    bfs(G[1], Vis[1], u);
    for(int i=1; i<=n; ++i)
        if(!Vis[0][i] && !Vis[1][i])
            return false;
    return true;
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    freopen("/Users/mark/MarkLearningCPP/Acwing/3250. 通信网络/case2.txt", "r", stdin);

    cin >> n >> m;
    while (m--){
        cin >> a >> b;
        G[0][a].push_back(b);
        G[1][b].push_back(a);
    }

    tarjan();
    int ans = 0;
    for(int i=0; i<num; ++i)
//        cout << "i: " << i << ", scc: " << scc[i] << endl,
        ans += solve(scc[i][0]) ? (int)scc[i].size() : 0;
    cout << ans << endl;
}

