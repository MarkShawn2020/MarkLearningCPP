//
// Created by 南川 on 2021/1/17.
//

/**
4
1 3 5 2
**/

#include "cstdio"
#include "vector"
#include "array"
using namespace std;

static const int N = 300;


struct Node {
    int first;
    int second;
    Node * nextNode;
};

void addNode(array<int, N>arr, Node *p, Node *np, int lFirst, int lSecond){
    while (p->nextNode){
        // 释放结点全在这里完成
        if(p->nextNode->first==lFirst || p->nextNode->second==lFirst
        || p->nextNode->first==lSecond || p->nextNode->second==lSecond){
            Node * pp = p->nextNode;
            p->nextNode = p->nextNode->nextNode;
            free(pp);
        }
        else if(arr[p->nextNode->first] + arr[p->nextNode->second] < arr[np->first] + arr[np->second])
            p = p->nextNode;
        else
            break;
    }
    if(p->nextNode) np->nextNode = p->nextNode;
    p->nextNode = np;
}

void printEpoch(array<int, N> arr, Node* pp, int ans){
    printf("ans: %d\n", ans);
    for(int j=0; j<5; j++)
        printf("%d\t", arr[j]);
    printf("\n");
    while (pp->nextNode){
        printf("(%d, %d)\t", pp->nextNode->first, pp->nextNode->second);
        pp = pp->nextNode;
    }
    printf("\n");
}

int main(){

    array<int, N> arr{};
    int n;

//    scanf("%d", &n);
//    for(int i=0; i<n; i++) scanf("%d", &(arr[i]));
//    n = 4;
//    arr = {1, 3, 5, 2};
    n = 5;
    arr = {548, 592, 715, 844, 602};

    Node p =Node {INT_MIN, INT_MIN};
    for(int i=0; i<n-1; i++){
        Node* np = new Node{i, i+1};
        addNode(arr, &p, np, -1, -1);
    }

    int ans = 0;
    Node * pp = &p;
    for(int i=0; i<n-1; i++){
        Node * firstNode = p.nextNode;

        printf("period: %d\n", i);
        printEpoch(arr, pp, ans);
        printf("[%d, %d]\n", firstNode->first, firstNode->second);

        ans += arr[firstNode->first] = arr[firstNode->first] + arr[firstNode->second];      // 更新合并的左边数的值
        arr[firstNode->second] = 0;                                                         // 更新合并的右边数的值

        if(firstNode->first > 0)
            addNode(arr, &p, new Node{firstNode->first - 1, firstNode->first}, firstNode->first, firstNode->second);       // 插入因合并后左侧新更新的结点
        if(firstNode->second < n-1)
            addNode(arr, &p, new Node{firstNode->first, firstNode->second + 1}, firstNode->first, firstNode->second);    // 重新因合并后右侧新更新的结点

        printEpoch(arr, pp, ans);
        printf("-------\n");
    }

    printf("%d", ans);
//    printf("ANS is %d", ans);
    return 0;
}