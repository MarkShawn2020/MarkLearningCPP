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

int recurLCS(vector<vector<int>> & dp, string & A, string & B, int i, int j)
{
    cout << "i: " << i << ", j: " << j << endl;
    if(i == 0 || j == 0 || dp[i][j]) return dp[i][j];
    return dp[i][j] = max(recurLCS(dp, A, B, i-1, j), recurLCS(dp, A, B, i, j-1)) + A[i] == B[j];
}

int LCS(string & A, string & B)
{
    vector<vector<int>> dp(A.size()+1, vector<int>(B.size()+1, 0));
    int ans = recurLCS(dp, A, B, A.size()-1, B.size()-1);
    for(auto & row: dp) cout << row << endl;
    return ans;
}


int main()
{
    string A = "abcfbc";
    string B = "abfcab";
    cout << LCS(A, B);
}