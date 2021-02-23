//
// Created by 南川 on 2021/1/22.
//
#include "iostream"
#include "vector"
using namespace std;


int allOne;
vector<bool> vis[2];
string ans = "";

int twoPow(int x) {
    return 1 << x;
}

void dfs(int u){
    for(int i=0; i<2; i++)
        if(!vis[i][u]){
            int v = ((u << 1) | i) & allOne;
            vis[i][u] = 1;
        }
}

string getAnswer(int n)
{
    allOne = twoPow(n - 1) - 1;
    for(int i=0; i<2; i++)
        vis[i].resize(twoPow(n-1), 0);

    dfs(0);

    cout << ans;
    return ans;
}