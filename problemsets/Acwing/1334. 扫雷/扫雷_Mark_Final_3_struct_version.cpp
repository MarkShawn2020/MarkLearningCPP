// Created by 南川 on 2021/2/8.

#include "cstdio"
#include "array"
#include "ctime"
#include "algorithm"
#define test true
using namespace std;

int n, m, kToSweep = 0, kSteps = 0, kInQue = 0;
const int N = 1000 + 2;
struct Cell {
    int isBom : 1;
    int flagd : 1;
    int swept : 1;
    int booms : 4;
} cells[N][N];
array<array<int, 2>, 8> offset = {{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}};
array<array<int, 2>, N * N> que;

bool outputSweep() {
    if(!kInQue) return printf("no cell detected\n") && false;
    printf("%d cell(s) detected\n", kInQue);
    sort(begin(que), begin(que) + kInQue);
    for(int qi=0; qi < kInQue; qi++)
        printf("%d %d %d\n", que[qi][0], que[qi][1], cells[que[qi][0]][que[qi][1]].booms);
    kInQue = 0;                             // reset
    return kToSweep == 0 && printf("finish\n");
}

// it's named "safe" sweep since we have done specific handle with those operation which would trigger booms
void safeSweepNonRecursive(int x, int y) {
    if(x <= 0 || x > n || y <= 0 || y > m || cells[x][y].swept || cells[x][y].isBom) return;
    cells[x][y].flagd = 0;                  // clear flag
    --kToSweep; ++cells[x][y].swept;        // mark swept
    que[kInQue][0] = x, que[kInQue][1] = y, kInQue++; // add into que
    for(auto & u: offset)                   // calculate and update adjacent booms
        if(cells[x + u[0]][y + u[1]].isBom)
            ++cells[x][y].booms;
    if(!cells[x][y].booms)                  // continue to sweep if no adjacent booms
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

bool checkDSweep(int x, int y, bool & isSafe)
{
    int diff = 0;
    for(auto & u : offset) {
        int i = x + u[0], j = y + u[1];
        if(cells[i][j].isBom ^ cells[i][j].flagd) isSafe = false;
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
}

// 1000 * 1000 就是一百万的输入，我们可以只遍历一趟，得到炸弹数/待拆数
void runAll() {
    scanf("%d %d", &n, &m); char s[N], ops[7];
    for(int i=1; i<=n; i++) {
        scanf("%s", s + 1);
        for(int j=1; j<=m; j++)
            s[j] == '.' ? ++kToSweep : ++cells[i][j].isBom;
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
