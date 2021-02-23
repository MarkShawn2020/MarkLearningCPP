
#include "vector"
#include "set"
#include "cstdio"
#include "iostream"
using namespace std;


            // if(mid == addr[i - k]) nums[i] >= *mid ? ++mid : --mid; // 删除自己，移向新结点方向
            // else if(nums[i] > *mid && nums[i-k] < *mid) ++mid;      // 删除左侧，新增右侧，中点右移
            // else if(nums[i] < *mid && nums[i-k] > *mid) --mid;      // 删除右侧，新增左侧，中点左移
            // else;                                                   // 删除、新增同侧，中点不变






class Solution {
private:
    multiset<int> mst;
    vector<multiset<int>::iterator> addr;
    multiset<int>::iterator mid = mst.begin();
    int offset = 0;

    void insert(int i, int v)
    {
        addr[i] = mst.insert(v);
        if(mst.size() == 1) mid = addr[i];         // 初始化，与对滑动窗口为1的特殊处理
        else if(v >= *mid && --offset == -2) ++mid, offset = 0;
        else if(v <  *mid && ++offset ==  2) --mid, offset = 0; 
    }

    void remove(int i, int v)    
    {
        if(mst.size() == 1) offset = 0;
        else if(addr[i] == mid)             
            mid == mst.begin() ? (++mid, ++offset) : (--mid, --offset);
        else if(v >= *mid && ++offset ==   2) --mid, offset = 0;
        else if(v < *mid  && --offset ==  -2) ++mid, offset = 0;
        mst.erase(addr[i]);
    }

public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        const int n = nums.size();
        vector<double> ans(n - k + 1);
        addr.resize(n);

        for(int i=0; i < k-1; i++) insert(i, nums[i]);

        for(int i=k-1; i<n; i++)
            {
                insert(i, nums[i]),

                printf("After Insert (%d, %2d): ", i, nums[i]);
                for(auto &s: mst) printf("%2d\t", s);
                printf("mid: %2d, offset: %2d \n", *mid, offset);

                ans[i-k+1] = *mid,
                remove(i-k+1, nums[i-k+1]);


                printf("After Remove (%d, %2d): ", i-k+1, nums[i-k+1]);
                for(auto &s: mst) printf("%2d\t", s);
                printf("\t\tmid: %2d, offset: %2d \n", *mid, offset);
            }
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