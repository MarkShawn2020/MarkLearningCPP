#include "cstdio"
#include "cstring"

using std::memset;

const int N = 1e6 + 1;
int raw[N];
int dp[N];

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    
    memset(dp, 0, sizeof dp);
    long long ans = 0;
    
    for(int i=1, j=1, s=0; i <= n; i++)
    {
        scanf("%d", &raw[i]);
        for(j=i, s=raw[j]; j > 0 && s % k; j--, s += raw[j] %= k);
        if(j > 0) ans += dp[i] = dp[--j] + 1;
    }
    
    printf("%lld", ans);
    
}   