//
// Created by 南川 on 2021/1/28.
//

#ifndef MARKLEARNINGCPP_GRAPHPRESTARS_H
#define MARKLEARNINGCPP_GRAPHPRESTARS_H

#include "queue"

const int PreStarMaxN = 1e5 + 1;

class GraphPreStars {

    /**
     * 适用于：2367 -- Genealogical tree - http://poj.org/problem?id=2367
     */
    struct Node{
        int first = -1; // 从该结点出发的最后一条【边】的id
        int degIn = 0;  // 该结点的入度
    };

    struct Edge{
        int to;         // 该边指向的【结点】的id
        int next;       // 上一条从该结点出发的【边】的id
    };

private:
    int pos = 0;
    const int n;    // num of nodes

public:
    Node nodes[PreStarMaxN]{};
    Edge edges[PreStarMaxN]{};

    explicit GraphPreStars(int n): n(n) {}

    void addEdge(int from, int to, int w=0)
    {
        edges[++pos] = {to, nodes[from].first};
        nodes[from].first = pos;
        nodes[to].degIn++;
    }

    /**
    * 【拓扑排序】
    * 由于前向星中head数组里第i个位置存放的是以第i个结点出发的最后一条边id（出边）
    * 所以如果head[i]==-1，即i结点没有任何出边（出度为0，终结点）
    * 但拓扑排序要求我们不断地删除入度为0的结点（源节点），因此考虑给每个结点增加入度记录
    */
    int * topologyOrder()
    {
        int* ans = new int[n];
        std::queue<int> Q;
        for(int i=1; i<=n; i++)
            if(nodes[i].degIn == 0)
                Q.push(i);

        for(int i=0; i<n; i++)      // 等价于 while(!Q.empty())
        {
            int node = Q.front();
            ans[i] = node;
            Q.pop();
            int edge = nodes[node].first;
            while (edge != -1)
            {
                int to = edges[edge].to;
                if(--nodes[to].degIn == 0)
                    Q.push(to);
                edge = edges[edge].next;
            }
        }

        return ans;
    }
};


#endif //MARKLEARNINGCPP_GRAPHPRESTARS_H
