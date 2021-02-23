//
// Created by 南川 on 2021/2/22.
//
#include "cstdio"
#include "iostream"
#include "map"
#include "string"
#include "cstring"
#include "queue"
using namespace std;

template<typename A> ostream & operator << (ostream & cout, vector<A> const &v) { cout << "["; for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]"; }
inline void Print(int *arr, int n, const char * name= "") { printf("-> %10s: [", name);for(int i=0; i <= n; ++i) printf(arr[i]? "_%d, ": "%2d, ", arr[i]);printf("\b\b]\n"); }
inline void Print(int n=25, const char * name="alphabet") { printf("-> %10s: [", name);for(int i=0; i <= n; ++i) printf("%2c, ", 'a' + i);printf("\b\b]\n"); }


//const int _N = 1000000;
const int _N = 10;
const int maxn = _N + 1;
const int SIGMA_SIZE = 26;
const int maxNode = _N + 1;

int n, ans;
bool vis[maxn];
map<string, int> ms;
int ch[maxNode][SIGMA_SIZE+5];
int val[maxNode];
inline int idx(char & c) {return c - 'a';}

struct Trie {
    int sz;
    Trie() {
        sz = 1;
        memset(ch[0], 0, sizeof ch[0]);
        memset(vis, 0, sizeof vis);
    }
    void insert(char * s) {
        int u = 0, n = strlen(s);
        for(int i=0; i<n; ++i) {
            int c = idx(s[i]);
            if(!ch[u][c]) {
                memset(ch[sz], 0, sizeof ch[sz]);
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u]++;

        printf("s: %s, u: %d, n: %d, sz: %d\n", s, u, n, sz);
        Print();
        for(int i=0; i<u; ++i) {
            char ss[10];
            sprintf(ss, "ch[%d]", i);
            Print(ch[i], 25, ss);
        }
        Print(val, _N, "val");
    }
};


// AC 自动机
int last[maxn], f[maxn];
void print(int j) {
    if(j && !vis[j]) {
        ans += val[j];
        vis[j] = true;
        print(last[j]);
    }
}
/**
 * source: 《算法竞赛入门经典训练指南》，刘汝佳，陈锋，清华大学出版社，3.3.3节，214页
 */
int getFail() {
    queue<int> q;
    f[0] = 0;
    for(int c=0; c < SIGMA_SIZE; ++c) {
        int u = ch[0][c];
        if(u) {
            f[u] = 0;
            q.push(u);
            last[u] = 0;
        }
    }
    while (!q.empty()) {
        int r = q.front();
        q.pop();
        for(int c=0; c<SIGMA_SIZE; ++c) {
            int u = ch[r][c];
            if(!u) {
                ch[r][c] = ch[f[r]][c];
                continue;
            }
            q.push(u);
            int v = f[r];
            while (v && !ch[v][c])
                v = f[v];
            f[u] = ch[v][c];
            last[u] = val[f[u]] ? f[u] : last[f[u]];
        }
    }
}

void find_T(char * T) {
    int n = strlen(T);
    int j = 0;
    for(int i=0; i<n; ++i) {
        int c = idx(T[i]);
        j = ch[j][c];
        if(val[j])
            print(j);
        else if(last[j])
            print(last[j]);
    }
}

char tmp[105];
char text[1000000 + 1000];
int main () {
    freopen("/Users/mark/MarkLearningCPP/HDOJ/2222. Keywords Search/case1.txt", "r", stdin);
    int T;
    cin >> T;
    while (T--) {
        scanf("%d", &n);
        Trie trie;
        ans = 0;
        for(int i=0; i<n; ++i) {
            scanf("%s", tmp);
            printf("i: %d, s: %s\n", i, tmp);
            trie.insert(tmp);
        }
        getFail();
        scanf("%s", text);
        find_T(text);
        cout << ans << endl;
    }

    int sAns;
    cin >> sAns;
    cout << "\nsAns: " << sAns;
    return 0;
}














