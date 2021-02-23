//
// Created by 南川 on 2021/1/17.
//

#include "climits"
#include "cstdio"
#include "array"
using namespace std;

static const int N = 300;

struct Node {
    int first;
    int second;
    int value;
    Node * nextNode;
};

void addNode(Node* p0, Node* pn){
    while (p0->nextNode)
        if (p0->nextNode->value < pn->value)
            p0 = p0->nextNode;
        else { pn->nextNode = p0->nextNode; break;}
    p0->nextNode = pn;
}


int main(){
    int n;
    array<int, N> arr{};
    array<array<int,2>, N> pre_next{};
    for(int i=0; i<N; i++){
        pre_next[i][0] = i - 1;
        pre_next[i][1] = i + 1;
    }


//    n = 5; arr = {548, 592, 715, 844, 602}; // ans=7742
//    scanf("%d", &n); for(int i=0; i<n; i++) scanf("%d", &(arr[i]));
    n = 10;
    arr = {548 ,592, 715 ,844, 602,
           857, 544 ,847, 423 ,623};
    /**
     * 初始化结点（同时排序）
     */
    Node nodes = Node {INT_MIN, INT_MIN};
    for(int i=0; i<n-1; i++)
        addNode(&nodes, new Node{i, i + 1, arr[i] + arr[i + 1]});

    /**
     * 主程序，一步步合并堆，总共合并n-1趟
     */
    int ans = 0;
    for(int i=0; i<n-1; i++){
         Node * bestBoy = nodes.nextNode;
         int x = bestBoy->first;
         int y1 = bestBoy->second;
         nodes.nextNode = nodes.nextNode->nextNode;       // 解下首结点，注意，还剩余0-2个结点待更新
         ans += arr[x] = bestBoy->value;     // 更新数组左值与答案
         arr[bestBoy->second] = 0;                         // 更新数组右值
         int x2 = pre_next[x][0];                    // 获取左值的前驱
         int y2 = pre_next[x][1] = pre_next[y1][1];  // 更新左值的新后继
         pre_next[y2][0] = x;   // 更新新后继的前驱
         free(bestBoy);         // 释放原最佳结点的内存

         /**
         * 重要，在加入新结点之前，需要把之前涉及到左值与右值的结点重新更新（0-2）
         */
         int toFree = 2 - (x==0) - (y1==n-1);
         Node * head = &nodes;
         while (toFree && head->nextNode){      // 在最后一步，即只剩两个结点时，head->nextNode已为空
             if(head->nextNode->second == x || head->nextNode->first == y1){
                 Node *pToFree = head->nextNode;
                 head->nextNode = head->nextNode->nextNode;
                 free(pToFree);
                 --toFree;
             }else{
                 head = head->nextNode;
             }
         }

         /**
          * 最后，再插入新的结点（1-2）(由于原右值已废弃，基于原右值的结点已删除，所以也不用更新基于原右值与原右值右继的结点）
          */
         if(x > 0)
             addNode(&nodes, new Node{x2, x, arr[x2]+arr[x]});
         if(y2 < n)               // 加入基于左值与新右值的新结点
             addNode(&nodes, new Node{x, y2, arr[x]+arr[y2]});
     }


    printf("%d", ans);
    return 0;
}