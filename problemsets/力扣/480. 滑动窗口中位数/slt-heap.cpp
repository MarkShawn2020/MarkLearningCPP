#include "vector"
#include "set"
#include "queue"
#include "iostream"
#include "climits"
#include "unordered_map"
using namespace std;

class MedianHeap{

private:
    int k;
    int n1 = 0, n2 = 0;
    priority_queue<int> Small;
    priority_queue<int, vector<int>, greater<int>> Large;
    unordered_map<int, int> his;

    void balance()
    {
        if(n1 > n2 + 1) 
            Large.push(Small.top()), ++n2,
            Small.pop(), --n1;
        else if(n2 > n1)
            Small.push(Large.top()), ++n1,
            Large.pop(), --n2;
        while(!Small.empty() && his[Small.top()]) --his[Small.top()], Small.pop();
        while(!Large.empty() && his[Large.top()]) --his[Large.top()], Large.pop();
    }

public:
    MedianHeap(int k): k(k){}

    void insert(int v)
    {
             if(Small.empty() || v < Small.top()) Small.push(v), ++n1;
        else if(Large.empty() || v > Large.top()) Large.push(v), ++n2;
        else if(n1 <= n2) Small.push(v), ++n1;
        else Large.push(v), ++n2;
        balance();
    }

    void erase(int v)
    {
        ++his[v];
        v <= Small.top() ? --n1 : --n2;
        balance();
    }

    double median()
    {
        return k % 2 
            ? Small.top() 
            : ((double)Small.top() + (double)Large.top()) / 2;
    }
};


class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {

        const int n = nums.size();
        vector<double> ans(n - k + 1);

        MedianHeap mh(k);
        for(int i=0; i < k-1; i++)
            mh.insert(nums[i]);

        for(int i=k-1; i<n; i++)
            mh.insert(nums[i]),
            ans[i-k+1] = mh.median(),
            mh.erase(nums[i-k+1]);
        
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