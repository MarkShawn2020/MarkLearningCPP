//
// Created by 南川 on 2021/2/13.
//

#include "cstdio"
#include "queue"

using namespace std;

const int N = 1e4 + 1, M = 2e4 + 1;
int n, ai, ans, s1, s2, s0;
priority_queue<int, vector<int>, greater<int>> que;

int main()
{
    scanf("%d", &n);
    for(int i=0; i<n; i++)
    {
        scanf("%d", &ai);
        que.push(ai);
    }
    for(int i=1; i<n; i++)  // 只需合并n-1次
    {
        s1 = que.top(), que.pop();
        s2 = que.top(), que.pop();
        ans += s0 = s1 + s2;
        que.push(s0);
    }
    printf("%d", ans);;
}