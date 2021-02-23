//
// Created by 南川 on 2021/1/20.
//
#include "iostream"
using namespace std;

int getN(int n)
{
    return n && getN(n-1);
}

int main()
{
    int n = 3;
    cout << getN(n);
    return 0;
}
