#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int, int> pi;

const int MAX_N  = 100 + 2;
int N, T, w[MAX_N], d[MAX_N], c[MAX_N];

int pq(int k, int t)
{
    priority_queue<pi> PQ;
    for(int i=1; i<=k; i++)
        PQ.push({w[i], d[i]});
    int ans = 0;
    while(t-- > 0) {
        const pi & f = PQ.top();
        ans += f.first;
        PQ.push({max(f.first - f.second, 0), f.second});
        PQ.pop();
    }
    return ans;
}

int main ()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/1262. 鱼塘钓鱼/case1.txt", "r", stdin);
    scanf("%d", &N);
    for(int i=1; i<=N; i++) scanf("%d", &w[i]);
    for(int i=1; i<=N; i++) scanf("%d", &d[i]);
    for(int i=1; i< N; i++) scanf("%d", &c[i]);
    scanf("%d", &T);

    int t = T, k = 1;
    while(t > 0 && k < N)
        t -= c[k++];
    t += c[--k];
    
    int ans = 0, ans_new = 0;
    while(k > 0 && (ans_new = pq(k, t)) > ans)
        ans = ans_new, k--, t += c[k];
    printf("%d", ans);
}