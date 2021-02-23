//
// Created by 南川 on 2021/1/21.
//

#include "iostream"
#include "vector"
#include "queue"
#include "set"
#include "unordered_set"
#include "/Users/mark/CLionProjects/MarkLearningCPP/io/read_case.h"

using namespace std;


class Solution{
public:

    static const int N = 100 + 1;

    inline int Find(int fa[], int x){
        while (x != fa[x]) x = fa[x];
        return x;
    }

    inline void Merge(int fa[], int f1, int f2){
        fa[f2] = f1;
    }

    struct Node{
        int i, j, c, id;
        bool operator < (const Node & b) const{
            return c <= b.c || c==b.c && i<=b.i;    // 集合比较需要用等号
        }
    };

    bool tryCutEdge(bool G[][N], const vector<vector<int>> & edges, const int n,
                    const Node n1, const Node n2)
    {
        G[n1.i][n1.j] = G[n1.j][n1.i] = false;
        G[n2.i][n2.j] = G[n2.j][n2.i] = true;

        int s = n2.i;
        bool vis[N]; memset(vis, 0, sizeof vis); vis[s] = true;
        queue<int> Q; Q.push(s); vis[s] = true;

        int k = 0;
        while (!Q.empty()){
            int i = Q.front();
            Q.pop();
            ++k;
            for(int j=0; j<n; j++)
                if(!vis[j] && G[i][j])
                    Q.push(j), vis[j]=true;
        }

        G[n2.i][n2.j] = G[n2.j][n2.i] = false;
        G[n1.i][n1.j] = G[n1.j][n1.i] = true;
        return k == n;
    }

    vector<vector<int>> findCriticalAndPseudoCriticalEdges(
            int n, vector<vector<int>>& edges)
    {
        int fa[N];          for(int i=0; i<N; i++) fa[i] = i;
        bool G[N][N];       memset(G,0, sizeof G);
        vector<Node> left;   left.reserve(N);
        vector<Node> right;  right.reserve(N);
        unordered_set<int> FKE, KE;
        set<Node> nodes;
        for(int i=0; i<edges.size(); i++){
            nodes.insert(Node{edges[i][0], edges[i][1], edges[i][2], i});
        }
        /**
         * 本题思路，krusal算法+松弛枚举
         *
         * 1. 首先通过krusal算法得出一棵最小生成树，并求出其权值
         * 2. 我们可以利用排序的信息，将排序过程中被丢弃的侯选边加入队列
         * 3. 通过队列进行暴力枚举，尝试去除树中的其他等长边，以确定是否能保持无环的性质
         */

        int k = 1; // 已连接点的个数
        for(Node const & node: nodes) {
            int x = node.i, y = node.j;
            int fx = Find(fa, x),fy = Find(fa, y);
            if (fx != fy){  // YES！留下来的边
                Merge(fa, fx, fy);
                left.emplace_back(node);
                G[x][y] = G[y][x] = true;
            }else{
                right.emplace_back(node);
                if (++k == n) break;
            }
        }

        int p = 0;
        for(Node n1: left){
            bool isKeyEdge = true;
            for(int i=p; i<right.size(); i++){
                Node n2 = right[i];
                if(n1.c > n2.c) ++p;
                else if(n1.c < n2.c) break;
                else if(tryCutEdge(G, edges, n, n1, n2)){
                        isKeyEdge = false;
                        FKE.insert(n1.id);
                        FKE.insert(n2.id);
                    }
            }
            if(isKeyEdge)
                KE.insert(n1.id);
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
