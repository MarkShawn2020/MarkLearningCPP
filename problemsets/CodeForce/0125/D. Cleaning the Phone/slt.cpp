//
// Created by 南川 on 2021/1/26.
//

#include "cstdio"
#include "vector"

using namespace std;

const int N = 10;

int dp[N];

int main()
{
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/CodeForce/0125/D. Cleaning the Phone/case1.txt", "r", stdin);

    int t, n, m, r1;
    scanf("%d", &t);

    for(int i=0; i < t; i++)
    {
        scanf("%d %d", &n, &m);
        vector<int> memories(n);
        vector<bool> isImportant(n);
        for(int j=0; j<n; j++)
            scanf("%d", &memories[j]);
        for(int j=0; j<n; j++)
            scanf("%d", &r1), isImportant[j] = r1 == 2;

        for(int j=0; j<n; j++)
            for(int k=N-1; k>0; k--)
                dp[k] = max(dp[k], dp[k-1])


    }
}
