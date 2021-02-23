#include "vector"
#include "set"
#include "iostream"
using namespace std;

class Solution {

    inline double getVal(set<pair<int, int>> & st, int k)
    {
        auto iter = st.begin();
        advance(iter, k / 2);
        return k % 2 
            ? iter->first
            : ((double)iter->first + (double)(--iter)->first) / 2;
    }

public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {

        const int n = nums.size();
        vector<double> ans(n - k + 1);

        set<pair<int, int>> st;
        for(int i=0; i < k-1; i++)
            st.insert(pair<int, int>(nums[i], i));

        for(int i=k-1; i<n; i++)
            st.insert(pair<int, int> (nums[i], i)),
            ans[i-k+1] = getVal(st, k),
            st.erase(pair<int, int> (nums[i-k+1], i-k+1));
        
        return ans;
    }
};


int main()
{
    vector<int> dta = {1,3,-1,-3,5,3,6,7};
    int k = 3;
    Solution slt;
    for(auto & d: slt.medianSlidingWindow(dta, k))
        cout << d << "\t";
}