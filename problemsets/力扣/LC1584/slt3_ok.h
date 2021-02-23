//
// Created by 南川 on 2021/1/19.
//

#ifndef MARKLEARNINGCPP_SLT3_OK_H
#define MARKLEARNINGCPP_SLT3_OK_H


class Solution {
public:
    int Find(vector<int> & fa, const int x){
        return fa[x] == x ? x : Find(fa, fa[x]);
    }

    void Merge(vector<int> & fa, vector<int> &rank, int x, int y){
        if(rank[x] < rank[y])
            swap(x, y);
        fa[y] = x;
        rank[x] += rank[y];
    }

    int minCostConnectPoints(vector<vector<int>>& points) {
        const int N = points.size();
        if(N < 2) return 0;

        const int P = N * (N-1) / 2;
        struct Path{
            int k1; // 第一个结点在原序列中的下标
            int k2; // 第二个结点在原序列中的下标
            double v;  // 两个结点之间的哈曼顿距离
            bool operator < (const Path & b) const{return this->v < b.v;}
        } ps[P];

        for(int i=0; i<N; ++i)
            for(int j=i+1; j<N; ++j)
                ps[(2*N-i-1)*i/2+j-i-1] = Path{i, j,
                                               fabs(points[i][0] - points[j][0]) + fabs(points[i][1] - points[j][1])
                };
        sort(ps, ps+P); // 从小到大排序所有的两点之间的路径距离

        vector<int> fa(N);
        vector<int> rank(N, 1);
        for(int i=0; i<N; i++)
            fa[i] = i;

        double ans = 0;
        for (int i=0, connected=0; i<P && connected<N-1; ++i) {
            int k1 = ps[i].k1, k2 = ps[i].k2;
            int f1 = Find(fa, k1), f2 = Find(fa, k2);
            if (f1 != f2) { // 路径合并
                Merge(fa, rank, f1, f2);
                ans += ps[i].v;
                if (++connected == N - 1)
                    break;
            }
        }
        return int(ans);
    }
};

#endif //MARKLEARNINGCPP_SLT3_OK_H
