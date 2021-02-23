#include "vector"
#include "iostream"
using namespace std;

class Solution {

    int biFind(vector<int> & wd, int v, int k) // p是恰好v大于wd[p]的位置
    {
        int p = k >> 1;
        for(int i=0, j=k-1; i <= j && wd[p] != v; p = (i+j) >> 1)
            wd[p] < v ? i = ++p : j = --p;
        return p;
    }

    inline double getVal(vector<int> & wd, int k)
    {
        return k % 2 ? wd[k>>1] : ((double)wd[k>>1] + (double)wd[(k>>1) - 1]) / 2;
    }

    double insert(vector<int> & wd, int v_old, int v_new, int k)
    {
        if(v_old == v_new) return getVal(wd, k);
        int p_old = biFind(wd, v_old, k);
        if(v_new > v_old)
            while(p_old < k-1 && wd[p_old+1] < v_new)
                wd[p_old] = wd[p_old+1], ++p_old;
        else
            while(p_old > 0   && wd[p_old-1] > v_new)
                wd[p_old] = wd[p_old-1], --p_old;
        wd[p_old] = v_new;
        return getVal(wd, k);
    }

public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {

        const int n = nums.size();
        vector<double> ans(n - k + 1);

        vector<int> wd(nums.begin(), nums.begin() + k);
        sort(wd.begin(), wd.end());

        ans[0] = getVal(wd, k);
        for(int i=0; i<n-k; i++)
            ans[i+1] = insert(wd, nums[i], nums[i+k], k);
        
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