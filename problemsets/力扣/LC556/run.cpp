//
// Created by 南川 on 2021/1/14.
//

#include "sstream"
#include "iostream"
#include "string"
#include "queue"

using namespace std;

int nextGreaterElement(int n) {
    string s = to_string(n);
    int N = s.size();

    int i = N - 2;
    while(i>=0 && s[i+1]<=s[i]) --i;
    if(i<0) return -1;

    int j = N - 1;
    while(s[j] <= s[i]) --j; // 必然存在
    swap(s[i],s[j]);  // 交换i和j和，i的位置就归位了

    j = N;
    while(j>i+2) swap(s[++i],s[--j]);

    long long res = stoll(s);
    return res > INT_MAX ? -1 : res;
}


int main()
{
    // 21
    // 12443322
    // 12222333
    // 230241
    cout << nextGreaterElement(230241);
}