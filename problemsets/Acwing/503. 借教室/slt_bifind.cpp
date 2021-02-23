#include "cstring"
#include "cstdio"

typedef long long ll;

int n, m;
const int N = 1e6+2;
int c1[N], v[N], s[N], t[N];
ll  c2[N];

bool check(int k)
{
    for(int i=1; i<=n; i++)     // 要拷贝到n
        c2[i] = c1[i];
        
    for(int i=1; i<=k; i++)     // 这里要从1开始，不能从L
        c2[s[i]  ] -= v[i],     
        c2[t[i]+1] += v[i];
    
    for(int i=1, s=0; i<=n; i++)
        if((s+= c2[i]) < 0)
            return true;
    return false;
}


int main()
{
    scanf("%d %d", &n, &m);
    
    for(int i=1; i<=n; i++)
        scanf("%lld", &c1[i]);
    
    for(int i=n; i>0; i--)
        c1[i] -= c1[i-1];
    
    for(int i=1; i<=m; i++)
        scanf("%d %d %d", &v[i], &s[i], &t[i]);
        
    int L = 0, R = m;
    while(L <= R)
    {
        int M = (L + R) >> 1;
        check(M) ? R = M - 1 : L = M + 1;
    }
    
    L > m ? printf("0") : printf("-1\n%d", L);
    return 0;
}