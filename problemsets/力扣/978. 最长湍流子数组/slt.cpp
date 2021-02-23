#include "vector"
#include "iostream"
#include "string"
#include "sstream"
using namespace std;


vector<int> readIntVectorID(string s)
{
    vector<int> ret;

    for(char & ch: s)
        if(!isdigit(ch) && ch!='-' && ch!='+')
            ch = ' ';

    stringstream ss;
    ss << s;
    int t;
    while (ss >> t)
        ret.push_back(t);
    return ret;
}


class Solution {
public:
    int maxTurbulenceSize(vector<int>& arr) {
        const int N = arr.size();
        if(N == 1) return 1;

        int i, f, d, d2, ans;

        if(arr[1] == arr[0]) ans = i = f = 1, d = 0;
        else ans = 2 , i = f = 0, d = arr[1] > arr[0] || -1;

        for(int j=2; j < N; j++) {
            d2 = (arr[j] > arr[j-1]) || ((arr[j] == arr[j-1]) - 1);
            if(d2 == 0) ++i, f = j;
            else if(d == 0 || (d2 ^ d) >> 31) i >= f ? ++ans : ++i;
            else ++i, f = j - 1;
            d = d2;

            printf("i: %d, j: %d, f: %d, d: %d, d2: %d, ans: %d\n", i, j, f, d, d2, ans);
        }

        
        return ans;
    }
};


int main()
{

    freopen("/Users/mark/MarkLearningCPP/力扣/978. 最长湍流子数组/case1.txt", "r", stdin);
    string s;
    cin >> s;
    auto data = readIntVectorID(s);
    Solution slt;
    slt.maxTurbulenceSize(data);
}