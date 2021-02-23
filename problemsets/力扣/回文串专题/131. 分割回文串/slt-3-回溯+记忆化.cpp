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
    static const int N = 5;
    vector<vector<string>> result;
    bool conn[N][N];
    string path[N];
    int p = -1;
    
    void backtracking (const string& s, int i) {
        for (int j = i; j < s.size(); j++) {
            if(!conn[j-i][i]) continue;                             // 剪枝

            path[++p] = s.substr(i, j - i + 1);                     // 压栈    
            j < s.size() - 1
                ? backtracking(s, j + 1)                            // 继续
                : result.push_back(vector<string>(path, path+p+1)); // 输出
            --p;                                                    // 弹栈，回溯
        }
    }

    void initConn(string & s)
    {
        const int n = s.size();
        memset(conn, 1, sizeof conn);
        for(int dis=1; dis<n; ++dis)
            for(int i=0; i+dis<n; ++i)
                if(s[i] != s[i+dis] || dis > 1 && !conn[dis-2][i+1])
                    conn[dis][i] = false;
    }

public:
    vector<vector<string>> partition(string s) {
        initConn(s);
        backtracking(s, 0);
        return result;
    }
};

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
    ifstream fin("/Users/mark/MarkLearningCPP/力扣/回文串专题/131. 分割回文串/case3.txt");
    run(fin.good() ? fin : cin);
}

