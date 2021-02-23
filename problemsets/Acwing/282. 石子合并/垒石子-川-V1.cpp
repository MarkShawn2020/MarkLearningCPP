//
// Created by 南川 on 2021/1/18.
//

/**
4
1 3 5 2
**/

#include "climits"
#include "cstdio"
#include "array"
using namespace std;

static const int N = 300;

struct Node {
    int first;
    int second;
    Node * nextNode;
};

void addNode(array<int, N>arr, Node *p, Node *np, const int n, int lFirst, int lSecond){
    bool toAdd = true;
    int toFree = 3 - (lFirst==0) - (lSecond==n-1);
    while (p->nextNode && toFree){    // 释放结点全在这里完成
        if(p->nextNode->first==lFirst || p->nextNode->second==lFirst
        || p->nextNode->first==lSecond || p->nextNode->second==lSecond){
            Node * pp = p->nextNode;
            p->nextNode = p->nextNode->nextNode;
            free(pp);
            --toFree;
            continue;
        }
        if(!toAdd) continue;
        if(arr[p->nextNode->first] + arr[p->nextNode->second] < arr[np->first] + arr[np->second])
            p = p->nextNode;
        else{
            // 添加新的结点
            if(p->nextNode) np->nextNode = p->nextNode;
            p->nextNode = np;
            toAdd = false;
        }
    }

}

void printEpoch(array<int, N> arr, Node* pp, int ans, int k){
    printf("ans: %d\n", ans);
    for(int j=0; j<k; j++)
        printf("%d\t", arr[j]);
    printf("\n");
    while (pp->nextNode){
        printf("(%d, %d)\t", pp->nextNode->first, pp->nextNode->second);
        pp = pp->nextNode;
    }
    printf("\n");
}

int main(){
    int n;
    scanf("%d", &n);

    array<int, N> arr{};
    for(int i=0; i<n; i++) scanf("%d", &(arr[i]));

    Node p =Node {INT_MIN, INT_MIN};
    Node * pp = &p;
    for(int i=0; i<n-1; i++){
        Node* np = new Node{i, i+1};
        addNode(arr, &p, np, n, -1, -1);
    }

    int ans = 0;
    for(int i=0; i<n-1; i++){
        Node * firstNode = p.nextNode;

        printf("period: %d\n", i);
        printEpoch(arr, pp, ans, n);
        printf("[%d, %d]\n", firstNode->first, firstNode->second);

        ans += arr[firstNode->first] = arr[firstNode->first] + arr[firstNode->second];      // 更新合并的左边数的值
        arr[firstNode->second] = 0;                                                         // 更新合并的右边数的值

        if(firstNode->first > 0)
            addNode(arr, &p, new Node{firstNode->first - 1, firstNode->first}, n, firstNode->first, firstNode->second);       // 插入因合并后左侧新更新的结点
        if(firstNode->second < n-1)
            addNode(arr, &p, new Node{firstNode->first, firstNode->second + 1}, n, firstNode->first, firstNode->second);    // 重新因合并后右侧新更新的结点
    }

    printEpoch(arr, pp, ans, n);

    printf("%d", ans);
    return 0;
}