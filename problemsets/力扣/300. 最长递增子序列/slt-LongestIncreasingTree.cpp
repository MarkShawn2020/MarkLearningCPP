//
// Created by 南川 on 2021/2/19.
//

#include "vector"
#include "iostream"
#include "stack"

using namespace std;

#include "sstream"
vector<int> readIntVector1D(string s)
{
    vector<int> ret;

    for(char & ch: s)
        if(!isdigit(ch) && ch!='-' && ch!='+')
            ch = ' ';

    std::stringstream ss;
    ss << s;
    int t;
    while (ss >> t)
        ret.push_back(t);
    return ret;
}

template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) {
    cout << "["; for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";
}


/**
 * 最终证明，这个类的设计是失败的
 * 主要原因在于，从根到叶的路径有多条，难以确定会更新哪一条
 * 实际应该从多个栈的栈顶开始比较，也就是树中的叶子
 */
class LongestIncreasingTree {
    struct Node {
        int val;
        int height;
        Node * father;
        Node * child;
        Node * brother;
    } root{} ;

    void cutNodes (Node * p)
    {
        if(!p) return;
        cutNodes(p->child);
        cutNodes(p->brother);
        delete p;
    }

    void updateHeights(Node * p, int h) {
        Node * pLast = p;   // 也可以不赋值，初始时h肯定比p高的
        while (p && p->height < h)
        {
            p->height = h++;
            pLast = p;
            p = p->father;
        }
        if(p && p->height == h)
        {
            cutNodes(p->child->child);
            delete p->child;
            p->child = pLast;       // 减去左枝
        }
    }

    void iterAddNode(Node *pLast, Node * p, int v)
    {
        if(!p) {
            pLast->child = new Node{v, 0, pLast};
            updateHeights(pLast, 1);
            return;
        }
//        if(v == p->val) return; // 往下的时候可以不判等
        if(v == p->val) {
            if(p->brother && p->brother->val < v)
                return iterAddNode(p, p->brother, v);
            return;
        }
        if(v > p->val) return iterAddNode(p, p->child, v);
        if(!p->child) {p->val = v; return;}

        while (true){
            pLast = p;
            p = p->brother;
            if(!p) {
                pLast->brother = new Node{v, 0, pLast};
                pLast->brother->father = pLast->father;
                return;
            }
            if(v == p->val)return;  // 往右的时候需要判等
            if(v > p->val) {
                pLast = p;
                p = p->child;
                return iterAddNode(pLast, p, v);
            }
        }
    }

public:
    LongestIncreasingTree () {
        root.height = 0;
        root.val = -1e9;
    }

    void addNode(int v)
    {
        cout << "v: " << v << endl;
        iterAddNode(nullptr, &root, v);
        print();
    }

    int getDepth() const {
        return root.height;
    }

    void print() {
        struct PNode {
            Node * p;
            vector<int> s;
        };
        stack<PNode> st;
        st.push({root.child, {}});
        while (!st.empty())
        {
            auto cur = st.top();
            st.pop();
            vector<int> curV(cur.s);
            if(cur.p->brother) st.push({cur.p->brother, curV});
            curV.push_back(cur.p->val);
            if(cur.p->child) st.push({cur.p->child, curV});
            if(!cur.p->child) {
                cout << curV << endl;
            }
        }
    }
};


int main ()
{
    freopen("/Users/mark/MarkLearningCPP/力扣/300. 最长递增子序列/case5.txt", "r", stdin);

    string s;
    cin >> s;
    vector<int> nums = readIntVector1D(s);
    cout << "Input: " << nums << endl;
    int ans;
    cin >> ans;

    LongestIncreasingTree lit;
    for(auto & num: nums)
        lit.addNode(num);
    cout << "Height: " << lit.getDepth() << endl;
    cout << "Ans: " << ans << endl;
    lit.print();
}


