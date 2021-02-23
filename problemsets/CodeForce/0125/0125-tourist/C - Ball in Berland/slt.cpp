//
// Created by 南川 on 2021/1/26.
//

/**
 *    author:  tourist
 *    created: 25.01.2021 18:01:50
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/CodeForce/0125-tourist/C - Ball in Berland/case1.txt", "r", stdin);


    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    cin >> tt;
    while (tt--) {
        /**
         * 构建A、B数组，同下标表示一对
         */
        int a, b, k;
        cin >> a >> b >> k;
        vector<int> A(k);
        for (int i = 0; i < k; i++) {
            cin >> A[i];
        }
        vector<int> B(k);
        for (int i = 0; i < k; i++) {
            cin >> B[i];
        }

        /**
         * 用ma、mb字典，记录每个人的度数
         */
        map<int, int> ma;
        map<int, int> mb;
        for (int i = 0; i < k; i++) {
            ma[A[i]] += 1;
            mb[B[i]] += 1;
        }

        /**
         * 一、对于第i组男孩和女孩，所有的k对可以分成四类：
         * 1. 一类就是a_i, b_i，即就是这个男孩和女孩；
         * 2. 一类是a_i与非b_i；
         * 3. 一类是b_i与非a_i；
         * 4. 剩下的就是即非a_i也非b_i。
         * 所以t神的答案里就出来了：(k-1) - (deg_a_i-1) - (deg_b_i-1)的写法。
         *
         * 二、之所以要除以2是因为每个情况都会被计算两遍。
         * 比如对于枚举(𝑏𝑖,𝑔𝑖)的时候会枚举到(𝑏𝑗,𝑔𝑗)，那么枚举到(𝑏𝑗,𝑔𝑗)的时候同样也会枚举到(𝑏𝑖,𝑔𝑖)。
         */
        long long ans = 0;
        for (int i = 0; i < k; i++) {
            ans += (k - 1) - (ma[A[i]] - 1) - (mb[B[i]] - 1);
        }
        assert(ans % 2 == 0);
        cout << ans / 2 << '\n';
    }
    return 0;
}

