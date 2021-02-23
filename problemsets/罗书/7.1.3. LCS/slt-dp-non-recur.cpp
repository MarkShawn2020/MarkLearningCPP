//
// Created by 南川 on 2021/2/19.
//

#include "vector"
#include "iostream"
#include "string"
using namespace std;

template<typename A> ostream & operator << (ostream & cout, vector<A> const &v) {
    cout << "["; for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";
}

#define max(a, b) (a) > (b) ? (a) : (b)

int LCS(string & A, string & B)
{
    vector<vector<int>> dp(A.size()+1, vector<int>(B.size()+1, 0));

    for(int i=0; i<A.size(); ++i)
        for(int j=0; j<B.size(); ++j)
            dp[i+1][j+1] = A[i] == B[j] ? dp[i][j] + 1 : max(dp[i][j+1], dp[i+1][j]);

    for(auto & row: dp) cout << row << endl;
    return dp[A.size()][B.size()];
}


int main()
{
    string A = "abcfbc";
    string B = "abfcab";
    cout << LCS(A, B);
}