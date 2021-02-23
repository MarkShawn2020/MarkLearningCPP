#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_N  = 100 + 2;
const int MAX_T = 1000 + 2;

int n, T, di;

int main ()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/1262. 鱼塘钓鱼/case4.txt", "r", stdin);
    scanf("%d", &n);
    vector<int> w(n+1), d(n+1), c(n+1);
    for(int i=1; i<=n; i++) scanf("%d", &w[i]);
    for(int i=1; i<=n; i++) scanf("%d", &d[i]);
    for(int i=1; i< n; i++) scanf("%d", &c[i]);
    scanf("%d", &T);

    vector<vector<int>> dp(n+1, vector<int>(T+1, 0));
    for(int i=1; i<=n; i++) dp[i][1] = w[i];
    for(int i=1; i<=n; i++)
        for(int j=2; j<=T; j++)
            dp[i][j] = dp[i][j-1] + max(dp[i][1] - d[i] * (j-1), 0);

    
    for(int i=n-1; i>0; i--)
{
        printf("i+1: %d [ ]\t", i+1); for(int j=0; j<=T; j++) printf("%3d ", dp[i+1][j]); printf("\n");
        printf("i  : %d [%d]\t", i, c[i]); for(int j=0; j<=T; j++) printf("%3d ", dp[i][j]); printf("\n");
        for(int j=T; j>c[i]; j--)
        {
            int mx = dp[i][j];
            for(int k=1; k<=j-c[i]; k++)
                mx = max(mx, dp[i+1][k] + dp[i][j-c[i]-k]);
            dp[i][j] = mx;
        }
        printf("i  : %d [%d]\t", i, c[i]); for(int j=0; j<=T; j++) printf("%3d ", dp[i][j]); printf("\n\n");

}   
    printf("%d", dp[1][T]);
}