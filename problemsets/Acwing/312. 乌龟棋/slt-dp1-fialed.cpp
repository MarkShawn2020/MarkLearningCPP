const int N = 350 + 1;
const int M = 120 + 1;
int n, m, k, ans, a[N], bi, cnt[5];
bool L[N], R[N];

#include "cstdio"
#include "queue"
using namespace std;

struct Edge {
    int i, j, d, v;
    bool operator < (const Edge & b) const {
        return  v <= b.v;
    }
};
priority_queue<Edge> que;

int main()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/312. 乌龟棋/case4.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    for(int i=1; i<=n; ++i) scanf("%d", &a[i]);
    for(int i=1; i<=m; ++i) scanf("%d", &bi), ++cnt[bi];
    
    for(int i=1; i<n; ++i)
        for(int d=1; d<=4; ++d)
            if(i + d <= n)
                que.push({i, i+d, d, a[i]+a[i+d]});
            
    while(k < m)
    {
        const Edge & e = que.top();
        if(!L[e.i] && !R[e.j] && cnt[e.d]) {
            ++k;
            --cnt[e.d];
            ans += e.v;
            for(int i=e.i; i<e.j; ++i) L[i] = true;
            for(int j=e.j; j>e.i; --j) R[j] = true;
            printf("k: %d, a[%d]=%2d -> a[%d]=%2d\n", k, e.i, a[e.i], e.j, a[e.j]);
        }
        que.pop();

    }
    
    printf("%d", (ans + a[1] + a[n]) >> 1);
}