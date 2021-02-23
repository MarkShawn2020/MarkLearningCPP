//
// Created by 南川 on 2021/1/27.
//

#include "fstream"
#include "iostream"
#include "vector"
#include "queue"
#include "./GraphPreStars.h"

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

    // 队列初始化（加入入度为0的结点）
    queue<int> Q;
    for(int i=1; i<=n; i++)
        if(gps.nodes[i].degIn == 0)
            Q.push(i);

    // 开始拓扑排序
    int * ans = gps.topologyOrder();
    for(int i=0; i<n; i++)
        cout << ans[i] << " ";
}
