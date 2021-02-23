//
// Created by 南川 on 2021/1/18.
//
#include "cmath"

const double PI = acos(-1);

const double EPS = 1e-8;

inline bool Equal(const double &a, const double &b) {return fabs(a-b) < EPS;}
inline bool More(const double &a, const double &b) {return a-b > EPS;}
inline bool MoreEqual(const double &a, const double &b) {return a-b > -EPS;}



#include "climits"
#include "vector"
#include "queue"
#include "iostream"

using namespace std;

const int N = 100000;
int width = 1;
int depth = 0;

struct Node {
    int depth = 3;
    int value = INT_MAX;
    vector<Node*> children = {};
} root;

queue<Node *> q;

void insertNode(int v){
    q.push(&root);
    while (!q.empty()){
        Node * front = q.front();
        q.pop();
        for(Node * child: front->children)
            if(child->value >= v)
                q.push(child);
        if(q.empty()){
            if(!front->children.empty()) ++width;
            int curDepth = front->depth + 1;
            front->children.emplace_back(new Node{curDepth});
            depth = max(depth, curDepth);
        }
    }
}

int main()
{
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/洛谷/动态规划/二/P1020/case1.txt", "r", stdin);

    int k; while (cin >> k) insertNode(k);
    cout << depth << endl << width;
    return 0;

}