//
// Created by 南川 on 2021/2/19.
//
#include "vector"
#include "iostream"
//#include "sstream"
#include "string"
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


template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) {
    cout << "["; for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";
}

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<vector<int>> his;
        int maxLen = 1;
        his.push_back({nums[0]});
         cout << ">>> num: " << nums[0] << endl << his[0] << endl;
        for(int i=1; i<nums.size(); ++i) {
            auto & num = nums[i];
             cout << ">>> num: " << num << endl;
            const int N = his.size();
            for(int j=0; j<N; ++j) {
                auto & rec = his[j];
                if(num > rec[rec.size()-1]) {
                    rec.emplace_back(num);
                    if(rec.size() > maxLen)
                        maxLen = rec.size();
                } else if(rec.size()==1 || num > rec[rec.size()-2]) {
                    rec[rec.size()-1] = num;
                } else {
                    vector<int> newSeq(rec.begin(),
                                       std::lower_bound(rec.begin(), rec.end(), num));
                    newSeq.push_back(num);
                    his.push_back(newSeq);
                }
            }
             for(auto & rec: his) cout << rec << endl;
        }
        return maxLen;
    }
};


int main()
{
    freopen("/Users/mark/MarkLearningCPP/力扣/300. 最长递增子序列/case4.txt", "r", stdin);

    string s;
    cin >> s;
    vector<int> nums = readIntVector1D(s);

    Solution slt;
    cout << slt.lengthOfLIS(nums);
}