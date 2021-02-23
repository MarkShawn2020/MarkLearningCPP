//
// Created by 南川 on 2021/2/19.
//

#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;

template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) {
    cout << "["; for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";
}

inline int diff(int a, int mid) {
    if(a > mid) return 1;
    if(a < mid) return -1;
    return 0;
}

int main ()
{
    freopen("/Users/mark/MarkLearningCPP/CodeForce/0218-Div2/D. Max Median/case1.txt", "r", stdin);
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for(int i=0; i<n; ++i) cin >> nums[i];
    cout << "n: " << n << ", k: " << k << endl;
    cout << "input data: " << nums << endl;

    vector<int> nums2(nums);
    sort(nums2.begin(), nums2.end());
    int mid = nums2[(n+1) >> 1];
    cout << "mid: " << mid << endl;

    vector<int> preSum(n+1);
    for(int i=0; i<n; i++)
        preSum[i+1] = preSum[i] + diff(nums[i], mid);
    cout << "preSum: " << preSum << endl;
}