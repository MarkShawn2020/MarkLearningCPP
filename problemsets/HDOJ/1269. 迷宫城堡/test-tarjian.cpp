//
// Created by 南川 on 2021/2/20.
//


#include "cstdio"
#include "cstring"
#include "cmath"
#include "cassert"

#include "string"
#include "iostream"
#include "fstream"
#include "algorithm"

#include "vector"
#include "stack"
#include "list"
#include "queue"
#include "set"
#include "unordered_set"
#include "map"
#include "unordered_map"

using namespace std;

template<typename A> ostream & operator << (ostream & cout, vector<A> const &v) {
    cout << "["; for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";
}

#define Min(a, b) if((b)<(a)) (a) = (b)
#define Max(a, b) if((b)>(a)) (a) = (b)

const int N = 10000;
int n, m, a, b, cnt, visitId;

vector<int> G[N+1];
int ancId[N + 1], curId[N + 1];
stack<int> st;

void dfs(int cur, int fa)
{
    st.push(cur);
    ancId[cur] = curId[cur] = ++visitId;
    int nChildren = 0;
    printf(">>> cur: %d, fa: %d, time: %d\n", cur, fa, visitId);
    for(auto &child: G[cur])
    {
        if(!curId[child]) // child not visited
        {
            ++nChildren;
            dfs(child, cur);
            // 对孩子递归完成之后，通过孩子更新自己的low值，表示自己往上能连接到的位置
            Min(ancId[cur], ancId[child]);    // update cur(father) using child(nChildren)
        }
        // 处理回退边，访问的下个结点实际上可能是自己的祖先
        else if(curId[child] < curId[cur])
            Min(ancId[cur], curId[child]);
    }
    if(ancId[cur] == curId[cur])
    {
        printf("scc %d: [", cur);
        while (st.top() != cur)
        {
            printf("%d, ", st.top());
            st.pop();
        }
        printf("%d]\n", st.top());
        st.pop();
    }

    printf("cur: [");
    for(int i=1; i<=n; ++i) printf(i<n?"%d, ":"%d", curId[i]);
    printf("]\nanc: [");
    for(int i=1; i<=n; ++i) printf(i<n?"%d, ":"%d", ancId[i]);
    printf("]\n");
    printf("<<<\n");
}

template <typename T>
void run(T & cin)
{
    cin >> n >> m;
    while (m--)
    {
        cin >> a >> b;
        G[a].push_back(b);
        printf("%d->%d ", a, b);
    }
    printf("\n");
    dfs(1, 0);
    cout << (cnt == 1 ? "YES" : "NO") << endl << "-----" << endl << endl;

    for(int i=0; i<=n; ++i) G[i].clear(), ancId[i]=curId[i]=0;
    while (!st.empty()) st.pop();
    cnt = visitId = 0;
    if(n) run(cin);
}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    // read from local case if possible, otherwise from console
    ifstream fin(
            "/Users/mark/MarkLearningCPP/HDOJ/1269. 迷宫城堡/case1.txt"
    );
    run(fin.good() ? fin : cin);
}

