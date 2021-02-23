
#include "vector"
#include "set"
#include "cstdio"
#include "iostream"
using namespace std;

class Solution {
private:
    typedef multiset<int>::iterator it;
    multiset<int> mst;
    it L, R;
    vector<it> addr;

    void insert(it & i, int & v) {
        i = mst.insert(v);
        if(mst.size() == 1) L = R = i;          // init
        else if(v < *L)  L == R ? --L : --R;    // left
        else if(v >= *R) L == R ? ++R : ++L;    // right
        else ++L,  --R;                         // between
    }

    void remove(const it & i, int & v) {
        if(i == L && i == R) --L, ++R;          
        else if(i == L) ++L;
        else if(i == R) --R;
        else if(v <= *L) ++R;
        else if(v >  *R) --L;
        else throw;
        mst.erase(i);
    }

public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        const int n = nums.size();
        vector<double> ans(n - k + 1);
        addr.resize(n);

        for(int i=0; i < k-1; i++) insert(addr[i], nums[i]);
            
        for(int i=k-1; i<n; i++)
        {
            insert(addr[i], nums[i]);
            
            printf("After Insert (%d, %2d): ", i, nums[i]);
            for(auto &s: mst) printf("%2d\t", s);
            printf("\n");

            ans[i-k+1] = (double(*L) + (double)*R) / 2;

            remove(addr[i-k+1], nums[i-k+1]);

            printf("After Remove (%d, %2d): ", i-k+1, nums[i-k+1]);
            for(auto &s: mst) printf("%2d\t", s);
            printf("\n");
        }

        return ans;
    }
};


int main()
{
    // vector<int> dta = {1,3,-1,-3,5,3,6,7};
    vector<int> dta = {6,5,9,5,4,9,1,7,5,5};
    int k = 4;
    Solution slt;
    for(auto & d: slt.medianSlidingWindow(dta, k))
        cout << d << "\t";
}