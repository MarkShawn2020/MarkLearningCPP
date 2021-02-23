// Created by 南川 on 2021/2/8.

#include "cstdio"
#include "array"
#include "ctime"
#include "algorithm"
#define test true
using namespace std;

int n, m, kToSweep = 0, kSteps = 0, kInQue = 0;
const int N = 1000 + 2;
array<array<int, N>, N> isBom, flagd, swept, booms;
array<array<int, 2>, 8> offset = {{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}};
array<array<int, 3>, N * N> que;

bool outputSweep() {
    if(!kInQue) return printf("no cell detected\n") && false;
    printf("%d cell(s) detected\n", kInQue);
    sort(begin(que), begin(que) + kInQue);
    for(int qi=0; qi < kInQue; qi++)
        printf("%d %d %d\n", que[qi][0], que[qi][1], que[qi][2]);
    kInQue = 0;                             // reset
    return kToSweep == 0 && printf("finish\n");
}

// it's named "safe" sweep since we have done specific handle with those operation which would trigger booms
void safeSweepNonRecursive(int x, int y) {
    if(x <= 0 || x > n || y <= 0 || y > m || swept[x][y] || isBom[x][y]) return;
    flagd[x][y] = 0;                        // clear flag
    --kToSweep; ++swept[x][y];              // mark swept
    for(auto & u: offset)                   // calculate and update adjacent booms
        if(isBom[x + u[0]][y + u[1]])
            ++booms[x][y];
    auto & q = que[kInQue++];               // add into que
    q[0] = x, q[1] = y, q[2] = booms[x][y];
    if(!booms[x][y])                        // continue to sweep if no adjacent booms
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
        if(isBom[x][y] ^ flagd[x][y]) isSafe = false;
        diff += isBom[x][y] - flagd[x][y];
    }
    return diff == 0;
}

bool isStepOver(const char & op) {
    if(op == 'Q')                   return printf("give up\n");

    ++kSteps; bool isDSweepSafe = true; int x, y; scanf("%d %d", &x, &y);
    if (op == 'F')
        if(swept[x][y])       printf("swept\n");
        else                        printf((flagd[x][y] ^= 1) ? "success\n" : "cancelled\n");
    else if(op == 'S')
        if(swept[x][y])       printf("swept\n");
        else if(flagd[x][y])  printf("flagged\n");
        else if(isBom[x][y])  return printf("boom\ngame over\n");
        else                        return runSafeSweep(x, y, false);
    else
        if(!swept[x][y])      printf("not swept\n");
        else if(!booms[x][y] || !checkDSweep(x, y, isDSweepSafe)) printf("failed\n");
        else if(!isDSweepSafe)      return printf("boom\ngame over\n");
        else                        return runSafeSweep(x, y, true);
}

// 1000 * 1000 就是一百万的输入，我们可以只遍历一趟，得到炸弹数/待拆数
void runAll() {
    scanf("%d %d", &n, &m); char s[N], ops[7];
    for(int x=1; x<=n; ++x) {
        scanf("%s", s + 1);
        for(int y=1; y<=m; ++y)
            s[y] == '.' ? ++kToSweep : ++isBom[x][y];
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
