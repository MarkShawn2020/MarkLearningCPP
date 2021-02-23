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
    static const int N = 100;
    vector<vector<string>> ans;
    bool dt[N][N];


    void traverse(string & s, vector<string> & prev, int i, const int n)
    {
        if(i >= n) { ans.push_back(prev); return;}

        for(int k=0; k< n - i; k++)
            if(dt[k][i])
            {
                vector<string> temp(prev);
                temp.insert(temp.end(), s.substr(i, k + 1));
                traverse(s, temp, i + k + 1, n);
            }
    }

public:
    vector<vector<string>> partition(string s) {
        const int n = s.size();
        memset(dt, 0, sizeof dt);

        for(int k=0; k<n; k++)
            for(int i=0; i<n-k; i++)
                if(s[i] == s[i+k] && (k<2 || dt[k-2][i+1]))
                    dt[k][i] = true;

        vector<string> init{};
        traverse(s, init, 0, n);
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
    ifstream fin("/Users/mark/MarkLearningCPP/力扣/回文串专题/131. 分割回文串/case1.txt");
    run(fin.good() ? fin : cin);
}

