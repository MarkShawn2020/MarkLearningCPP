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
    vector<vector<string>> ans;

    static bool isHuiwen(string & s, int x, int y)
    {
        while(x<=y && s[x] == s[y]) ++x, --y;
        return x >= y;
    }

    void traverse(string & s, const vector<string>& prev, int i, const int n)
    {
        for(int j=i; j<n; j++)
            if(isHuiwen(s, i, j)) 
            {
                vector<string> temp(prev);
                temp.push_back(s.substr(i, j-i+1));
                j==n-1 ? ans.push_back(temp) : traverse(s, temp, j+1, n);
            }
    }

public:
    vector<vector<string>> partition(string s) {
        traverse(s, {}, 0, s.size());
        return ans;
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
    ifstream fin("/Users/mark/MarkLearningCPP/力扣/回文串专题/131. 分割回文串/case4qqq.txt");
    run(fin.good() ? fin : cin);
}

