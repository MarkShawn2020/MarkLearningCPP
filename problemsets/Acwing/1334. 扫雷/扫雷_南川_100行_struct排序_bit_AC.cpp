// Created by 南川 on 2021/2/8.
// (\w*?)\[(\w*)\]\[(\w*)\] -> cells[$2][$3].$1  (regex replace in clion for switch between struct and array version)
#define test true

#include "cstdio"
#include "ctime"
#include "algorithm"
using namespace std;

int n, m, kToSweep = 0, kSteps = 0, kInQue = 0;
const int N = 1000 + 2;
struct Cell{
    int isBom: 1;
    int flagd: 1;
    int swept: 1;
    int booms: 4;
} cells[N][N];
struct Que{
    int x, y, v;
    bool operator < (const Que & b) const {return x < b.x || x == b.x && y < b.y;}
}que[N * N];
int offset[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

bool outputSweep() {
    if(!kInQue) return printf("no cell detected\n") && false;
    printf("%d cell(s) detected\n", kInQue);
    sort(que,que + kInQue);
    for(int qi=0; qi < kInQue; qi++)
        printf("%d %d %d\n", que[qi].x, que[qi].y, que[qi].v);
    kInQue = 0;                             // reset
    return kToSweep == 0 && printf("finish\n");
}

// it's named "safe" sweep since we have done specific handle with those operation which would trigger booms
void safeSweepNonRecursive(int x, int y) {
    if(x <= 0 || x > n || y <= 0 || y > m || cells[x][y].swept || cells[x][y].isBom) return;
    cells[x][y].flagd = 0;                          // clear flag
    --kToSweep; ++cells[x][y].swept;                // mark swept
    for(auto & u: offset)                           // calculate and update adjacent booms
        if(cells[x+u[0]][y+u[1]].isBom)
            ++cells[x][y].booms;
    auto & q = que[kInQue++];
    q.x = x, q.y = y, q.v = cells[x][y].booms;      // add into que
    if(!cells[x][y].booms)                          // continue to sweep if no adjacent booms
        for(auto & u: offset)
            safeSweep(x + u[0], y + u[1]);
}

// it's ok even though swept or being a boom, since both have been excluded in line: 33
inline bool runSafeSweep(int x, int y, bool isDSweep) {
    if(!isDSweep)
        safeSweep(x, y);
    else
        for(auto & u : offset)
            safeSweep(x + u[0], y + u[1]);
    return outputSweep();
}

bool checkDSweep(const int X, const int Y, bool & isSafe)
{
    int diff = 0;
    for(auto & u : offset) {
        int x = X + u[0], y = Y + u[1];
        if(cells[x][y].isBom ^ cells[x][y].flagd) isSafe = false;
        diff += cells[x][y].isBom - cells[x][y].flagd;
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
}

// 输入规模1000*1000=1百万，序列规模6万，显然不能对每个输入再做周边结点的遍历
// 所以周围炸弹数的更新只能等到执行(D)Sweep操作时（甚至，如果不对输入做二层遍历，而在更新时检索炸弹总数，也许更快）
void runAll() {
    scanf("%d %d", &n, &m); char s[N], ops[7];
    for(int x=1; x<=n; ++x) {
        scanf("%s", s + 1);
        for(int y=1; y<=m; ++y)
            s[y] == '.' ? ++kToSweep : ++cells[x][y].isBom;
    }
    while (scanf("%s", ops) && !isStepOver(ops[0]));
    printf("total step %d", kSteps);
}

int main() {
#ifndef test
    runAll(); return 0;
#endif
    freopen("/Users/mark/MarkLearningCPP/Acwing/1334. 扫雷/case3.txt", "r", stdin);
    auto start = clock();
    runAll();
    auto end = clock();
    printf("\ntime: %.4f ms", (double)(end-start) / CLOCKS_PER_SEC * 1000);
    return  0;
}
