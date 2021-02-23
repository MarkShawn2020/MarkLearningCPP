//
// Created by 南川 on 2021/1/19.
//

#include "vector"
#include "iostream"
#include "string"
#include "sstream"
#include "set"
#include "queue"
#include "algorithm"

using namespace std;

class Solution {
public:

    int Find(vector<int> & fa, const int x){
        return fa[x] == x ? x : Find(fa, fa[x]);
    }

    int minCostConnectPoints(vector<vector<int>>& points) {
        const int N = points.size();
        const int P = N * (N-1) / 2;

        struct Path{
            int k1; // 第一个结点在原序列中的下标
            int k2; // 第二个结点在原序列中的下标
            double v;  // 两个结点之间的哈曼顿距离
            bool operator < (const Path & b) const{
                return this->v < b.v;
            }
        } ps[P];

        for(int i=0; i<N; ++i)
            for(int j=i+1; j<N; ++j)
                ps[(2*N-i-1)*i/2+j-i-1] = Path{i, j, fabs(points[i][0] - points[j][0]) + fabs(points[i][1] - points[j][1])};
        sort(ps, ps+P);

        vector<int> fa(N);
        for(int i=0; i<N; i++)
            fa[i] = i;

        double ans = 0;
        for (int i=0, connected=0; i<P && connected<N-1; ++i) {
            int k1 = ps[i].k1, k2 = ps[i].k2;
            int f1 = Find(fa, k1), f2 = Find(fa, k2);
            if (f1 != f2) {
                fa[f2] = f1;
                ans += ps[i].v;
                if (++connected == N - 1)
                    break;
            }
        }
        return int(ans);
    }
};

int main()
{
    const int N = 100000;
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/力扣/LC1584/case4.txt.txt", "r", stdin);
    string s;
    cin >> s;
    for(char & ch: s)
        if(ch=='[' || ch==']' || ch==',')
            ch = ' ';
    vector<vector<int>> data;
    stringstream ss;
    ss << s;
    int a1, a2;
    while(ss >> a1 >> a2)
        data.emplace_back(vector<int> {a1, a2});

    Solution slt;
    cout << slt.minCostConnectPoints(data);
    return 0;
}