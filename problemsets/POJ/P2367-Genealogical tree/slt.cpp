//
// Created by 南川 on 2021/1/27.
//

#include "fstream"
#include "iostream"
#include "vector"
#include "queue"

using namespace std;

template <typename T>
void run(T &);

int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    // read from local case if possible, otherwise from console
    ifstream fin("../POJ/P2367-Genealogical tree/case1.txt");
    run(fin.good() ? fin : cin);
}



const int N = 1e5 + 1;

class GraphPreStars {

    /**
    * 【拓扑排序】
    * 由于前向星中head数组里第i个位置存放的是以第i个结点出发的最后一条边id（出边）
    * 所以如果head[i]==-1，即i结点没有任何出边（出度为0，终结点）
    * 但拓扑排序要求我们不断地删除入度为0的结点（源节点），因此考虑给每个结点增加入度记录
    */
    struct Node{
        int first; // 从该结点出发的最后一条【边】的id
        int degIn;  // 该结点的入度
        Node(): first(-1), degIn(0){}
    };

    struct Edge{
        int to;         // 该边指向的【结点】的id
        int next;       // 上一条从该结点出发的【边】的id
    };

private:
    int pos;
    const int n;    // num of nodes

public:
    Node nodes[N];
    Edge edges[N];

    explicit GraphPreStars(int n): n(n), pos(0), nodes(), edges(){}

    void addEdge(int from, int to, int w=0)
    {
        edges[++pos] = {to, nodes[from].first};
        nodes[from].first = pos;
        nodes[to].degIn++;
    }


    /**
     * 适用于：2367 -- Genealogical tree - http://poj.org/problem?id=2367
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

template <typename T>
void run(T & cin)
{
    int n, t;
    cin >> n;

    // 链式前向星建图
    GraphPreStars gps(n);    // n为实际结点数，N为最大结点数（固定数组）
    for(int f=1; f<=n; f++)
        while (cin >> t && t)
            gps.addEdge(f, t);

    // 开始拓扑排序
    int * ans = gps.topologyOrder();
    for(int i=0; i<n; i++)
        cout << ans[i] << " ";//////////

}
