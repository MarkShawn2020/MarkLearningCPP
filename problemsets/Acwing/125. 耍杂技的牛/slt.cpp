#include "cstdio"
#include "vector"
#include "algorithm"
#include "cmath"
#include "tuple"

using namespace std;

typedef pair<int, int> pi;

long long total_w, ans = -1e10;
int max_ws;

int main()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/125. 耍杂技的牛/case1.txt", "r", stdin);

    int n, w, s;
    scanf("%d", &n);
    vector<pi> dt(n);
    
    for(int i=0; i<n; i++)
        scanf("%d %d", &w, &s),
        dt[i] = make_pair(w+s, s);
    
    sort(dt.begin(), dt.end());
    for(int i=0; i<n; i++)
        total_w += dt[i].first - dt[i].second,
        max_ws = max(max_ws, dt[i].first),
        ans    = max(ans, total_w - max_ws);
        
    printf("%lld", ans);
}