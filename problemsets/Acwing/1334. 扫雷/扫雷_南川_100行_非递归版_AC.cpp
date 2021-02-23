// Created by 南川 on 2021/2/8.
// 运行时间： 946 ms; 运行空间： 25944 KB（递归版一般80~100 MB）
#include "cstdio"
#include "tuple"
#include "algorithm"
using namespace std;

const int N = 1000 + 2;
struct Cell{
    bool isBom, flagd, swept;
    int booms;
} cells[N][N];
pair<int, int>que[N * N];

int n, m, kToSweep = 0, kSteps = 0, kInQue = 0; // 使用kInQue标记，因为push_back很慢（emplace_back也不快）
int offset[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

bool outputSweep() {
    if(!kInQue) return printf("no cell detected\n") && false;
    printf("%d cell(s) detected\n", kInQue);
    sort(que,que + kInQue);
    for(int qi=0; qi < kInQue; qi++)
        printf("%d %d %d\n", que[qi].first, que[qi].second, cells[que[qi].first][que[qi].second].booms);
    kInQue = 0;  // reset
    return kToSweep == 0 && printf("finish\n");
}

inline int & calculateBooms(const int x, const int y) {
    for(auto & u: offset)
        if(cells[x+u[0]][y+u[1]].isBom)
            ++cells[x][y].booms;
    return cells[x][y].booms;
}

void safeSweepNonRecursive(int x, int y) {
    if(x<1 || x>n || y<1 || y>m || cells[x][y].swept || cells[x][y].isBom) return;
    que[kInQue++] = {x, y};
    for(int p = kInQue-1; p < kInQue; ++p) {                            // start from last kInQue, DSweep need
        x = que[p].first, y = que[p].second;
        cells[x][y].flagd = false;                                      // clear flag
        --kToSweep; cells[x][y].swept = true;                           // mark swept
        if(!calculateBooms(x, y))                                      // continue to sweep if no adjacent booms
            for(auto & u: offset) {
                int i = x + u[0], j = y + u[1];
                if(i>0 && i<=n && j>0 && j<=m && !cells[i][j].swept )   // swept test need for non-recursive version
                    cells[i][j].swept = true, que[kInQue++] = {i, j};   // swept mutex to avoid duplication
            }
    }
}

// the sweep is safe since we have handled the exceptions in the main procedure part
bool runSafeSweep(int x, int y, bool isDSweep) {
    if(!isDSweep)
        safeSweepNonRecursive(x, y);
    else
        for(auto & u : offset)
            safeSweepNonRecursive(x+u[0], y+u[1]);
    return outputSweep();
}

bool checkDSweep(const int x, const int y, bool & isDSweepSafe) {
    int diff = 0;
    for(auto & u : offset) {
        int i = x + u[0], j = y + u[1];
        if(cells[i][j].isBom ^ cells[i][j].flagd) isDSweepSafe = false;
        diff += cells[i][j].isBom - cells[i][j].flagd;
    }
    return diff == 0;
}

bool isStepOver(const char & op) {
    if(op == 'Q')                   return printf("give up\n");
    ++kSteps; bool isDSweepSafe = true; int x, y; scanf("%d %d", &x, &y);
    if (op == 'F')
        if(cells[x][y].swept)       printf("swept\n");
        else                        printf((cells[x][y].flagd ^= 1) ? "success\n" : "cancelled\n");
    else if(op == 'S')
        if(cells[x][y].swept)       printf("swept\n");
        else if(cells[x][y].flagd)  printf("flagged\n");
        else if(cells[x][y].isBom)  return printf("boom\ngame over\n");
        else                        return runSafeSweep(x, y, false);
    else
        if(!cells[x][y].swept)      printf("not swept\n");
        else if(!cells[x][y].booms || !checkDSweep(x, y, isDSweepSafe)) printf("failed\n");
        else if(!isDSweepSafe)      return printf("boom\ngame over\n");
        else                        return runSafeSweep(x, y, true);
    return false;
}

// 输入规模1000*1000=1百万，序列规模6万，显然不能对每个输入做周边结点的遍历（1百万 * 8）
// 所以周围炸弹数的更新只能等到执行(D)Sweep操作时（甚至，如果不对输入做二层遍历，而在更新时检索炸弹总数，也许更快）
int main() {
    scanf("%d %d", &n, &m); char s[N], ops[7];
    for(int x=1; x<=n; ++x) {
        scanf("%s", s + 1);
        for(int y=1; y<=m; ++y)
            s[y] == '.' ? ++kToSweep : cells[x][y].isBom = true;
    }
    while (scanf("%s", ops) && !isStepOver(ops[0]));
    printf("total step %d", kSteps);
    return 0;
}