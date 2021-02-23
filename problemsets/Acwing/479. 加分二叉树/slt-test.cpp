//
// Created by 南川 on 2021/1/29.
//

//
// Created by 南川 on 2021/1/28.
//

#include "fstream"
#include "iostream"
#include "vector"
#include "queue"

using namespace std;

const int N = 5 + 2;
int dp[N][N], ht[N][N];

int getMax(int x, int y)
{
    for(int i=x; i<=y; i++)
    {
        int temp = dp[x][i-1] * dp[i+1][y] + dp[i][i];
        if(temp > dp[x][y])
            dp[x][y] = temp,
            ht[x][y] = i;
    }
}

void printArr(int dp[][N], int n)
{
    for(int i=0; i<=n+1; i++)
    {
        for(int j=0; j<=n+1; j++)
            cout << dp[i][j] << '\t';
        cout << endl;
    }
    cout << endl;
}

void printChain(int i, int j)
{
    if(i > j) return;
    cout << ht[i][j] << endl;
    if(i == j) return;
    printChain(i, ht[i][j]-1);
    printChain(ht[i][j]+1, j);
}

template <typename T>
void run(T & cin)
{
    int n;
    cin >> n;

    for(int i=1; i<=n; i++)
        ht[i][i] = i,
        dp[0][i] = dp[i][n+1] = i,
        dp[i][i-1] = 1,
        cin >> dp[i][i];
    dp[n+1][n] = 1;

    for(int i=1; i<n; i++)
        for(int j=1; i+j<=n; j++)
            getMax(j, j+i);

    printArr(dp, n);
    printArr(ht, n);
    printChain(1, n);
}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    // read from local case if possible, otherwise from console
    ifstream fin("/Users/mark/CLionProjects/MarkLearningCPP/Acwing/479. 加分二叉树/case1.txt");
    run(fin.good() ? fin : cin);
}

