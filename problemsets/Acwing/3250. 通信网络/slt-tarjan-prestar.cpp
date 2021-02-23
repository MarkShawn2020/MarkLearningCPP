#include "cstdio"
#include "cstring"
#define Min(a, b) if((b) < (a)) (a) = (b)
using namespace std;
inline void Print(int n, const char * name="id") { printf("-> %10s: [", name);for(int i=0; i <= n; ++i) printf("%2d, ", i);printf("\b\b]\n"); }
inline void print(int arr[], int n, const char * name="") { printf("-> %10s: [", name);for(int i=0; i<=n; ++i) printf("%2d, ", arr[i]);printf("\b\b]\n"); }

const int N = 1000, M = 10000;
int n, m, a, b, ans;

struct PreStar {
    int head[N+1]{}, edge_to[M+1]{}, edge_next[M+1]{}, vis[N+1]{};
    inline void addEdge(int i, int u, int v) { edge_to[i] = v, edge_next[i] = head[u], head[u] = i; }
    inline void reset_vis() {memset(vis, 0, sizeof (int) * (n+1));}
    inline void mark_vis(int u) { ++vis[u]; }
    inline bool is_vised(int u) {return vis[u];}
    inline int getHeadEdge(int u) {return head[u];}
    inline int getNextEdge(int e) {return edge_next[e];}
    inline int getNode(int e) {return edge_to[e];}
};

class Tarjan {
    int sccsz[N + 1]{}, sccno[N + 1]{}, low[N + 1]{}, num[N + 1]{}, st[N + 1]{}, step=0, top=0, kScc=0;
    inline void push(int u) {st[top++] = u;}
    inline int pop() {return st[--top];}
    void dfs(PreStar & ps, int u) {
        push(u);
        num[u] = low[u] = ++step;
        for(int e=ps.getHeadEdge(u); e; e=ps.getNextEdge(e)) {
            int v = ps.getNode(e);
            if(!num[v]) {                       // not visited
                dfs(ps, v);
                Min(low[u], low[v]);     // 回溯，用孩子的新序号更新自己
            }
            else if(!sccno[v]) {               // 孩子结点不是scc时，需要用它更新，否则跳过 !important
                Min(low[u], num[v]);     // 回退边，用祖先的序号更新自己
            }
        }
        if(low[u] == num[u]) {
            ++kScc;
            while (true) {
                int v = pop();
                sccno[v] = kScc;
                ++sccsz[u];
                if(u == v) break;
            }
        }
    }
public:
    inline int count(int u){ return sccsz[u]; }
    void operator () (PreStar & ps) {
        for(int i=1; i <= n; ++i)
            if(!num[i])
                top = 0, dfs(ps, i);
//        print(n);
//        print(num, n, "num");
//        print(low, n, "low");
//        print(sccsz, n, "isscc");
//        print(sccno, n, "sccno");
    }
};

class Graph {
    int que[N+1]{}, qi=0, qj=-0;
    inline void push(int u) {que[++qj] = u;}
    inline int pop() {return que[++qi];}
    inline void clear() {qi = qj = 0;}
    inline bool empty() const {return qi == qj;}
    void bfs(PreStar & p, int start) {
        p.reset_vis();
        p.mark_vis(start);
        clear();
        push(start);
//        printf("\nstart:n %d\n", start);
        while (!empty()) {
            int u = pop();
            for(int e=p.getHeadEdge(u); e; e = p.getNextEdge(e)) {
                int v = p.getNode(e);
//                printf("u: %d -> v: %d, e: %d \n", u, v, e);
                if(p.is_vised(v)) continue;
                p.mark_vis(v);
                push(v);
            }
        }
    }
public:
    PreStar ps[2];
    inline void addEdge(int i, int u, int v) {
        ps[0].addEdge(i, u, v);
        ps[1].addEdge(i, v, u);
    }
    bool check(int u) {
        bfs(ps[0], u);
        bfs(ps[1], u);
//        printf("\ncheck u: %d\n", u);
//        print(ps[0].vis, n, "graph +");
//        print(ps[1].vis, n, "graph -");
//        print(ps[1].head, n, "head");
//        print(ps[1].edge_to, n, "edge_to");
//        print(ps[1].edge_next, n, "edge_next");
        for(int i=1; i<=n; ++i)
            if(!ps[0].is_vised(i) && !ps[1].is_vised(i))
                return false;
        return true;
    }
};

int main()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/3250. 通信网络/case2.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    Graph g;
    for(int i=1; i<=m; ++i) {
        scanf("%d %d", &a, &b);
        g.addEdge(i, a, b);
    }
    Tarjan tj;
    tj(g.ps[0]);
    for(int i=1; i<=n; ++i)
        if(tj.count(i))
            ans += g.check(i) * tj.count(i);
    printf("%d\n", ans);
}