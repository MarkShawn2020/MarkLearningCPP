#include "iostream"
#include "vector"
#include "string"
#include "cstring"
#include "algorithm"

using namespace std;


class Solution {
public:
    int characterReplacement(string s, int k) {
        int ans = 0;
        const int N = 26;
        int freqs[N];
        memset(freqs, 0, sizeof freqs);
        auto id = [&s](int i) {return s[i] - 'A';};
        auto mv = [&freqs, N]() {return *max_element(freqs, freqs+N);};

        for(int i=0, j=0, m=0; j<s.size(); j++)
        {
            ++freqs[id(j)];
            while(j - i + 1 - mv() > k) 
                --freqs[id(i++)];
            ans = max(ans, j - i + 1);
        }

        return ans;
    }
};

int main()
{
    Solution slt;
    string s = "AABABBA";
    // string s = "ABCDE";
    int k = 1;
    cout << slt.characterReplacement(s, k);
}