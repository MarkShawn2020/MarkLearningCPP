//
// Created by 南川 on 2021/2/13.
//

#include "cstdio"
#include "queue"

using std::queue;

const int M = 100 + 1, N = 1000 + 1;
int m, n, ni, ans, isIn[N];
queue<int> que;


int main()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/496. 机器翻译/case4.txt", "r", stdin);
    scanf("%d %d", &m, &n);
    for(int i=1; i<=n; ++i) {
        scanf("%d", &ni);
        if(isIn[ni]) continue;
        ++isIn[ni];
        que.push(ni);
        ++ans;
        if(que.size() > m)
            --isIn[que.front()],
            que.pop();
    }
    printf("%d", ans);
}