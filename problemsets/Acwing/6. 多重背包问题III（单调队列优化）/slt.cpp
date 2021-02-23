//
// Created by 南川 on 2021/1/20.
//

#include "cstdio"
#include "queue"

inline int max(const int & a, const int & b){
    return a > b ? a : b;
}

const int N = 5;
int dp[N + 1];
int ca[N + 1];

void ZeroOnePack(int dp[], int u, int v, const int packs)
{
    for(int i=packs; i>=u; i--)
        dp[i] = max(dp[i], dp[i-u]+v);
}

void MultiPack(int dp[], int u, int v, const int packs)
{
    for(int i=u; i<=packs; i++)
        dp[i] = max(dp[i], dp[i-u]+v);
}

struct Good{
    int cost;
    int value;
    int count;
    float ratio;

    Good(int c, int v, int n){
        cost = c;
        value = v;
        count = n;
        ratio = float(value) / float(cost);
    }

    bool operator < (Good & b) const{
        if(ratio < b.ratio) return true;
        if(ratio > b.ratio) return false;
        if(cost < b.cost) return true;
        return false;
    }
};


int main()
{
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/Acwing/ACW06-多重背包问题III（单调队列优化）/case4.txt", "r", stdin);

    int n, m, u, v, K;
    scanf("%d %d", &n, &m);
    for(int i=0; i<m; i++)
        ca[i] = m;

    using namespace std;

    priority_queue<Good, vector<Good>, less<> > P;

    for(int i=0; i<n; i++)
    {
        scanf("%d %d %d", &u, &v, &K);
        Good  g =  Good{u, v, K};
        P.push(g);
    }

    int ans = 0, surplus = m;
    while (!P.empty() && surplus>0){
        Good g = P.top();
        P.pop();

        int k = min(surplus / g.cost, g.count);

        for(int i=g.cost; i<m; i++){
            k = min(g.count, )
            if(dp[i-g.cost]+g.value > dp[i]){
                ca[i] -= g.cost * min(k, (i-g.cost)+1);
                dp[i] = dp[i-g.cost] + g.value * min(k, (i-g.cost)+1);
            }
        }
    }

    printf("%d", ans);
}