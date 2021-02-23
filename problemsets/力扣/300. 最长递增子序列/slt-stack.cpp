//
// Created by 南川 on 2021/2/19.
//

#include "vector"
#include "iostream"
#include "stack"

using namespace std;

#include "sstream"
vector<int> readIntVector1D(string s)
{
    vector<int> ret;

    for(char & ch: s)
        if(!isdigit(ch) && ch!='-' && ch!='+')
            ch = ' ';

    std::stringstream ss;
    ss << s;
    int t;
    while (ss >> t)
        ret.push_back(t);
    return ret;
}

template<typename A> ostream & operator << (ostream & cout, vector<A> const &v) {
    cout << "["; for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";
}




int solve(vector<int> & nums)
{
    int maxLen = 1, minVal = 1e9;
    vector<vector<int>> his;
    for(auto & num: nums)
    {
        cout << "num: " << num << endl;

        // 最小值新开一个队列
        if(num < minVal) { minVal = num;his.push_back({num}); }

        // 最大值加入到第一个队列的末尾
        else if(num > his[0].back()) {his[0].push_back(num); ++maxLen;}

        else
            for(int i=1; i<his.size(); ++i)
            {
                const int k = (int) his[i].size() - 1;
                if(num > his[i][k] && num < his[i-1][k+1])
                {
                    his[i].push_back(num);
                    if(his[i].size() == his[i-1].size())
                        his.erase(his.begin() + i-1);
                    break;
                }
            }

        for(auto & row: his)
            cout << row << endl;
    }
    return maxLen;

}


int main ()
{
    freopen("/Users/mark/MarkLearningCPP/力扣/300. 最长递增子序列/case5.txt", "r", stdin);

    string s;
    cin >> s;
    vector<int> nums = readIntVector1D(s);
    cout << "Input: " << nums << endl;
    int ans;
    cin >> ans;

    int myAns = solve(nums);
    cout << "My Ans: " << myAns << endl;
    cout << "Sd Ans: " << ans << endl;

}
