
#include "vector"
#include "set"
#include "cstdio"
#include "iostream"
using namespace std;

class Solution {

    struct Node{
        int id, val;
        Node * prev, * next;
    }L, R;

    int n1 = 0, n2 = 0;

    void insert(int i, int v)
    {
        if(!n1 && !n2) L = R = Node{i, v};
        
    }


public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        const int n = nums.size();
        vector<double> ans(n - k + 1);

       
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