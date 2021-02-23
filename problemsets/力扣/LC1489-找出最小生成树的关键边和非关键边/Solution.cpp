//
// Created by 南川 on 2021/1/21.
//

#include "numeric"
#include "vector"

#include "iostream"
#include "/Users/mark/MarkLearningCPP/io/read_case.h"


using namespace std;



class UnionFind {   // 并查集模板
public:
    vector<int> fa; // father
    vector<int> sz; // size
    int groups;     // 当前连通分量数目

    explicit UnionFind(int _n): groups(_n), fa(_n), sz(_n, 1) {
        // iota 生成连续的++串
        iota(fa.begin(), fa.end(), 0);
    }

    int findGroup(int x) {
        return fa[x] == x ? x : fa[x] = findGroup(fa[x]);
    }

    bool uniteGroups(int x, int y) {
        x = findGroup(x);
        y = findGroup(y);
        if (x == y)
            return false;

        if (sz[x] < sz[y])
            swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];
        --groups;
        return true;
    }
};


class Solution {
public:
    pair<int, int> calcCost(vector<vector<int>> & edges,
                            const int n, const int startEdge, int startCost){
        UnionFind uf(n);
        if(startCost)
            uf.uniteGroups(edges[startEdge][0], edges[startEdge][1]);
        for (int j = 0; j<edges.size(); ++j)
            if (startEdge != j && uf.uniteGroups(edges[j][0], edges[j][1]))
                startCost += edges[j][2];
        return make_pair(startCost, uf.groups);
    }

    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {

        int totalCost, cost, groups, m = edges.size();

        // 对原数组编号、排序
        for (int i = 0; i < m; ++i)
            edges[i].push_back(i);
        sort(edges.begin(), edges.end(), [](const auto& u, const auto& v) {
            return u[2] < v[2];
        });

        // 计算最小生成树的总成本
        totalCost = calcCost(edges, n, -1, 0).first;

        // 依次使用去边法、加边法判定一条边是否是关键边，如不是，是否是伪关键边
        vector<vector<int>> ans(2);
        for (int i = 0; i < m; ++i) {
            // 关键边的两种充分条件： 1. 生成树不连通 2. 成本更高 [不带它玩的情况下]
            tie(cost, groups) = calcCost(edges, n, i, 0);
            if (groups != 1 ||  cost > totalCost) {
                ans[0].push_back(edges[i][3]);
                continue;
            }

            // 伪关键边的三个必要条件： 1. 不是关键边 2. 生成树连通 3. 成本等于最小成本 [首先带它玩的情况下]
            tie(cost, groups) = calcCost(edges, n, i, edges[i][2]);
            if (cost == totalCost)
                ans[1].push_back(edges[i][3]);
        }
        return ans;
    }
};

// 作者：LeetCode-Solution
// 链接：https://leetcode-cn.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/solution/zhao-dao-zui-xiao-sheng-cheng-shu-li-de-gu57q/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。


int main()
{
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/力扣/LC1489-找出最小生成树的关键边和非关键边/case1.txt", "r", stdin);

    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<vector<int>> data = readIntVector2D(s);

    Solution slt;
    vector<vector<int>> ans;
    ans = slt.findCriticalAndPseudoCriticalEdges(n, data);
    for(const auto& items: ans){
        for(int item: items)
            cout << item << '\t';
        cout << endl;
    }

    return 0;
}
