//
// Created by 南川 on 2021/2/21.
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

const int N = 1000;
template <typename T>
void run(T & cin) {
    int n, v, sum[N + 1]{0}, dp[N + 1][N + 1];
    memset(dp, 0x3f, sizeof dp);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> v,
        sum[i] = sum[i - 1] + v,
        dp[i][i] = 0;

    for (int k = 1; k < n; ++k)
        for (int i = 1; i <= n-k; ++i)
        {
            int j = i + k;
            for (int u = i; u < i + k; ++u)
                    Min(dp[i][j], dp[i][u] + dp[u+1][j] + sum[j] - sum[i - 1]);
        }

//    for(int i=1; i<=n; ++i)
//    {
//        printf("[%d] ", i);
//        for(int j=1; j<=n; ++j)
//            printf("%2d ", dp[i][j] > 100 ? 0 : dp[i][j]);
//        printf("\n");
//    }
    printf("%d", dp[1][n]);
}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    // read from local case if possible, otherwise from console
    ifstream fin(
            "/Users/mark/MarkLearningCPP/Acwing/3240. 压缩编码/case1.txt"
    );
    run(fin.good() ? fin : cin);
}

