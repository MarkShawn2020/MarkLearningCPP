//
// Created by 南川 on 2021/1/27.
//

#include "bits/stdc++.h"

std::vector<int> A = {1, 3, 4, 5, 7, 9, 12};    // sorted
const int x = 12;                               // target sum of 2 elements;


int BiFindSum(int start, int end)
{
    if(start >= end) return -1;
    int mid = (start + end) / 2;
    if(A[mid] + A[mid+1] == x) return mid;
    else if(A[mid] + A[mid+1] < x) return BiFindSum(start, mid);
    else return BiFindSum(mid + 1, end);
}


int main()
{

    const int N = A.size();
    int ans = BiFindSum(0, N - 1);
    std::cout << ans;
}
