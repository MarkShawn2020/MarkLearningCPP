//
// Created by 南川 on 2021/1/21.
//

#ifndef MARKLEARNINGCPP_SOLUTION_H
#define MARKLEARNINGCPP_SOLUTION_H

#include "iostream"
#include "vector"
#include "queue"
#include "set"
#include "/Users/mark/CLionProjects/MarkLearningCPP/io/read_case.h"

using namespace std;

class Solution{
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {

        const int N = 5 + 1;
        int G[N][N];    memset(G, 0, sizeof G);
        int ID[N][N];   memset(ID, 0, sizeof ID);
        bool vis[N];    memset(vis, 0, sizeof vis);
        int dis[N];     fill(dis, dis+N, INT_MAX);
        vector<vector<int>> adj(N);
        set<int> KE{};
        set<int> FKE{};

        /**
 * 1. 任意设置一个起点，比如0结点，记距离为0
 *    （根据prim算法，距离为每个结点距离出发点集合的最短距离）
 *
 * 2. 从该点出发，重新更新所有点未访问点的距离
 *   2.1. 在更新过程中，若发现目标结点的新距离不等于旧距离（初始值除外），则两条路径中最大的那条必然属于非关键边
 *   2.2. 对于该更新过程遍历结束后，每个结点的最短距离所对应的路径集合（可能有多条相等），
 *       我们肯定能确定他们不是关键边，但我们不能确定它们是伪关键边（之后没有更小）还是非关键边（之后会有更小）
 *
 * 3. 根据prim算法，此时需要重新遍历所有结点，从中找出未访问的、且路径距离最短的结点
 *   （注意，距离最短的结点可能不止一个，而该结点的最短路径集合可能也不止一个）
 *   3.1. 无论距离最短的结点个数有多少，从中任意选取一个结点即可
 *      （比如1->2, 1->3的距离都是1，选2或选3不影响最小生成树的生成）
 *   3.2. 但对于该结点，如果有多条最短距离可到达，比如1->3, 2->3，则两条路径均为伪关键边，否则为关键边
 *      （题目的突破口，正在于此！）
 *
 * 4. 基于以上，可以套用prim模板，写出完整的for循环结构，但对于题目要求的关键边和伪关键边的生成，有以下两点：
 *   4.1. 由于关键边与伪关键边均是从源点出发得到的，可能有多条（但不会重复），所以可以为每个结点设置一个vector记录最短的边
 *   4.2. 但我们不需要额外记录非关键边，因为关键边vector存放的都是更短的边号，与非关键边是互斥的
 *
 * 5. 所以最终分析得出的数据结构如下：
 *   5.1. 两个 N^2 的数组，分别存放每两个结点之间的连通距离 (int G[N][N]) 与 对应的边序号 (int ID[N][N])
 *   5.2. 两个 N   的数组，分别存放每个结点距离出发点集合的最短距离 (int dis[N]) 与 访问记录 (bool vis[N])
 *   5.3. 一个 N   的数组或vector，存放每个结点的最短边集 (vector<vector<int>> adj(N))
 *   5.4. 两个 vector/set，存放答案需要的关键边和伪关键边 (vector<int> KE, vector<int> FKE)
 */

        for(int i=0; i<edges.size(); ++i)
        {
            int x=edges[i][0], y=edges[i][1], w=edges[i][2];
            G[x][y] = G[y][x] = w;
            ID[x][y] = ID[y][x] = i;
        }

        dis[0] = INT_MAX - 1; // 距离最小的就是下一个去访问的结点
        for(int period=0; period < n; period++) // 探访n个结点
        {
            int from=-1, minV=INT_MAX;
            for(int i=0; i<n; i++)
                if(!vis[i] && dis[i]<minV)
                    from = i, minV = dis[i];    // 可能有多个结点的距离都是最短的，但是 either is okay!
            vis[from] = true;

            for(int j=0; j<n; j++){
                if(!vis[j] && G[from][j]){
                    int v = G[from][j];
                    int id = ID[from][j];
                    if(v <= dis[from]){
                        if(v < dis[from])
                            adj[from].clear();
                        adj[from].emplace_back(id);
                        dis[from] = v;
                    }
                    if(v <= dis[j]){
                        if(v < dis[j])
                            adj[j].clear();
                        adj[j].emplace_back(id);
                        dis[j] = v;
                    }
                }
            }

            if(adj[from].size() == 1)           // 该源点连接的下一个最短结点只有一个（即，关键边）
            {
                KE.insert(adj[from][0]);
                for(int k: adj[from]) {
                    int x = edges[k][0];
                    int y = edges[k][1];
                    adj[x].erase(k);

                }

            }
            else{
                for(int e: adj[from])
                    FKE.insert(e);
                adj[from].clear();
            }                                // 该源点连接的下一个最短结点有多个（即，皆是伪关键边）

        }
        vector<vector<int>> ans(2);
        ans[0].insert(ans[0].begin(), KE.begin(), KE.end());
        ans[1].insert(ans[1].begin(), FKE.begin(), FKE.end());
        return ans;
    }
};


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


#endif //MARKLEARNINGCPP_SOLUTION_H
