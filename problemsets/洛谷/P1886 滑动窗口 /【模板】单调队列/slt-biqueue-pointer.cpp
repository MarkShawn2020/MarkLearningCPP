//
// Created by 南川 on 2021/1/22.
//
#include "cstdio"
#include "climits"
#include "string"
#include "tuple"

const int N = 1e6 + 1;


struct Node
{
    int time;
    int value;
    Node * next;
    Node * prev;
};


class BiQueue{
private:
    int T;
    Node root{};

public:

    explicit BiQueue(int t, int firstValue): T(t){
        // 初始化value为无限大，是因为设计从大到小遍历，遇到下一个结点比自己小的即停止，因此根节点可作为哨兵结点
        root.value = INT_MIN;
        // 初始化time为无限大，保证根节点永远最新，不会被弃除
        root.time = INT_MAX;
        // 初始化第一个结点（之后就不需要了）
        Node * f = new Node{0, firstValue};
        root.next = root.prev = f;
        f->next = f->prev = &root;
    }

    std::pair<int, int> addNode(int time, int value)
    {
        Node * head = &root;

        // 遍历结点，找到合适的位置，并弃除过期结点与V字深渊结点
        while (value < head->next->value)  // 新结点比next结点更小则往后移
        {
            head = head->next;
            if(time - head->time >= T)  // 过期结点
            {
                head->next->prev = head->prev;
                head->prev->next = head->next;
                // free(head);          // 如有必要，可以释放结点，但之后的操作要相应更改
            }
        }

        // 此时新结点必定比下一个结点要大（或相等），但比目前结点要小
        Node * p = new Node{time, value};
        p->next = head->next;
        p->prev = head;
        head->next = head->next->prev = p;

        // 从小端开始删除过期结点
        Node * tail = root.prev;
        while (time - tail->time >= T)
        {
            tail->prev->next = tail->next;
            tail->next->prev = tail->prev;
            tail = tail->prev;
        }

        return std::make_pair(root.prev->value, root.next->value);
    }

};


int main()
{
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/洛谷/P1886 滑动窗口 /【模板】单调队列/case1.txt", "r", stdin);

    int n, m;
    scanf("%d %d", &n, &m);

    int ansLe[N], ansGe[N];
    int v, a, b;
    scanf("%d", &v);
    BiQueue bq(m, v);
    for(int i=1; i<n; i++){
        scanf("%d", &v);
        std::tie(a, b) = bq.addNode(i, v);
        if(i >= m-1){
            ansLe[i-m+1] = a;
            ansGe[i-m+1] = b;
        }
    }

    // 小 -> 大
    for(int i=0; i<n-m+1; i++) printf("%d ", ansLe[i]);
    printf("\n");
    for(int i=0; i<n-m+1; i++) printf("%d ", ansGe[i]);

    return 0;

}