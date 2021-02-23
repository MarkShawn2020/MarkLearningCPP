//
// Created by 南川 on 2021/1/17.
//

#include "cstdio"
#include "vector"
#include "queue"

using namespace std;

const int N = 5000 + 1;
const int M = 500000 + 1;
const int D = 80112002;

int n, m, t1, t2;

int degOut[N];
int store[N];
queue<int> Q;


int main()
{
    long long ans = 0;
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/洛谷/动态规划/P4017/case4.txt.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    vector<vector<int>> prev(n+1);

    for(int i=1; i<=m; i++)
    {
        scanf("%d %d", &t1, &t2);
        prev[t2].emplace_back(t1);
        ++degOut[t1];
    }

    for(int i=1; i<=n; i++)
        if(!degOut[i]){
            Q.push(i);
            store[i] = 1;
        }

    while (!Q.empty()){
        int i = Q.front();
        Q.pop();
        if(prev[i].empty()){
            ans += store[i];
            ans %= D;
        }else{
        for(int j: prev[i]){
            store[j] += store[i];
            store[j] %= D;
            if(!--degOut[j])
                Q.push(j);
        }}
    }

    printf("%d", int(ans % D));
    return 0;
}