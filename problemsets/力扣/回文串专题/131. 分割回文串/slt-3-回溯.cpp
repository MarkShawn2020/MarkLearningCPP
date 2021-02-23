//
// Created by 南川 on 2021/1/31.
//

#include "fstream"
#include "iostream"
#include "vector"
#include "queue"
#include "cstring"


using namespace std;

class Solution {
private:
    vector<vector<string>> result;
    int p = -1;
    
    void backtracking (const string& s, vector<string> & path, int i) {
        for (int j = i; j < s.size(); j++) {
            if(!isPalindrome(s, i, j)) continue;                                    // 剪枝

            path[++p] = s.substr(i, j - i + 1);                                     // 压栈    
            j < s.size() - 1
                ? backtracking(s, path, j + 1)                                      // 继续
                : result.push_back(vector<string>(path.begin(), path.begin()+p+1)); // 输出
            --p;                                                                    // 弹栈，回溯
        }
    }

    bool isPalindrome(const string& s, int start, int end) {
        while(start<=end && s[start] == s[end]) ++start, --end;
        return start >= end;
    }

public:
    vector<vector<string>> partition(string s) {
        vector<string> path(s.size());                                        // 跟踪栈
        backtracking(s, path, 0);
        return result;
    }
};

// 作者：carlsun-2
// 链接：https://leetcode-cn.com/problems/palindrome-partitioning/solution/131-fen-ge-hui-wen-chuan-hui-su-sou-suo-suan-fa-xi/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

template <typename T>
void run(T & cin)
{
    Solution slt;
    string s;
    cin >> s;
    s = s.substr(1, s.size()-2);
    for(const auto& row: slt.partition(s))
    {
        for(const auto& col: row)
        {
            cout << col << '\t';
        }
        cout << endl;
    }

}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    // read from local case if possible, otherwise from console
    ifstream fin("/Users/mark/MarkLearningCPP/力扣/回文串专题/131. 分割回文串/case4.txt");
    run(fin.good() ? fin : cin);
}

