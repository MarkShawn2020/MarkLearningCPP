//#include "bits/stdc++.h"
#include "iostream"
using namespace std;


const int N = 5; // 20000

int main() {

    int n, maxCapacity;
    int dp[N + 2], _dp[N + 2], que[N + 2];
    //que[head]为队首元素（最大值的下标）
    //dp[]为dp[i][]
    //_dp[]为dp[i-1][]

    freopen("/Users/mark/CLionProjects/MarkLearningCPP/Acwing/ACW06-多重背包问题III（单调队列优化）/case1.txt", "r", stdin);

    cin >> n >> maxCapacity;
    for (int _ = 0; _ <= n; ++_) {
        int size, value, count;
        cin >> size >> value >> count;
        memcpy(_dp, dp, sizeof(dp));    // 备份数组，dp -> _dp

        for (int r = 0; r < size; ++r) {   // r是分组，即小于v的余数
            /*
            hh为队首位置，tt为队尾位置，数值越大，表示位置越后面
            队首在队尾后面队列为空，即hh>tt时队列为空
            */
            int head = 0, tail = -1;
            /* 
            que[]为单调队列
            存储前s个(物品数量)中的最大值
            数组从头(head)到尾(tail)单调递减
            */
            for (int i = r; i <= maxCapacity; i += size) {   // k是每个组内，一个个相隔v的下标，也代表当前的背包容量

                /*
                维护一个大小为k的区间，使最大值为前k个元素中最大
                (capacity - que[head]) / size 表示拿取物品的数量（相当于最原始的多重背包dp的k）
                */
                if (head <= tail && (i - que[head]) / size > count)
                    head++;


                /*
                若队内有值，该值就是前k个元素的最大值
                que[head]为队首元素（_dp[]中前k个数中最大值的下标），_dp[]为dp[_-1][]
                所以 _dp[que[head]]为只考虑前i-1个物品时，拿前q[head]个物品的最大价值
                */
                /**
                 * que[head]为队首元素的位置
                 * _dp[que[head]]即为上一个dp状态中，该位置的dp值
                 * (_ - que[head]) / size 显然就是当前i离队首之间能装该物品的件数（即k），再乘以value就是能够多获得的价值
                 */
                if (head <= tail)
                    dp[i] = max(dp[i], _dp[que[head]] + (i - que[head]) / size * value);


                /*
                若队尾元素小于当前元素，则队尾元素出队；
                若队内一个元素比当前元素小，则该元素一定不会被用到（单调队列思想）
                _dp[que[tail]] + (capacity - que[tail]) / size * value
                与
                _dp[capacity] - (capacity - r) / size * value
                分别表示队尾元素的值和当前元素的值
                */
                while (head <= tail && _dp[que[tail]] - (que[tail]-r)/size*value <=_dp[i] - (i-r)/size*value)
                    tail--;

                //去除了比当前小的元素，保证队列里的元素都比当前元素大，入队
                que[++tail] = i;
            }
        }
    }
    cout << dp[maxCapacity] << endl;
}

//作者：o_O
//        链接：https://www.acwing.com/solution/content/1537/
//来源：AcWing
//        著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。