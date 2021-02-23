#include "iostream"
#include "vector"
#include "string"

using namespace std;

class Solution {
public:
    int characterReplacement(string s, int k) {
        int ans = 0;
        const int N = 26;
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(N + 1, 0));

        for(int i=0, j=0; j<n; ++j)
            for(int p=j; p>=i; --p)
            {
                dp[p][0] = max(dp[p][0], ++dp[p][s[j]-'A'+1]);
                if(j - p + 1 - dp[p][0] > k) {i = ++p; break;}    // 剪枝
                ans = max(ans, j + 1 - p); 
            }

        return ans;
    }
};

int main()
{
    Solution slt;
    string s = "ABCDE";
    int k = 1;
    cout << slt.characterReplacement(s, k);
}