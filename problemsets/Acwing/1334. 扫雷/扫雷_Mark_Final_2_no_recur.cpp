//
// Created by 南川 on 2021/2/8.
//
#include "cstdio"
#include "array"
#include "vector"
#include "algorithm"
#include "ctime"
using namespace std;

const int MAX_SIZE = 1000 + 2;

struct Cell {
    int isBom : 1;
    int flagd : 1;
    int swept : 1;
    int booms : 4;
} cells[MAX_SIZE][MAX_SIZE];

int n, m, nSwept = 0, nBooms = 0, nSteps = 0, q = 0, isSafe = 0;
array<array<int, 2>, 8> xy = {{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}};
array<array<int, 2>, MAX_SIZE * MAX_SIZE> que;


bool outputSweep()
{
    if(!q) return printf("no cell detected\n");
    printf("%d cell(s) detected\n", q);
    sort(begin(que), begin(que) + q);
    for(int qi=0; qi<q; qi++)
        printf("%d %d %d\n", que[qi][0], que[qi][1], cells[que[qi][0]][que[qi][1]].booms);
    q = 0;                                      // reset
    return nSwept + nBooms != n * m || printf("finish\n") && false;
}

inline void recordSweep(int x, int y){
    cells[x][y].swept = true, ++nSwept;
    que[q][0] = x, que[q][1] = y, ++q;
    for(auto & u : xy) {
        int i = x + u[0], j = y + u[1];
        if (i <= 0 || i > n || j <= 0 || j > m) continue;
        if (cells[i][j].isBom) ++cells[x][y].booms;
    }
}

void safeSweepNonRecursive(int x, int y)
{
    recordSweep(x, y);
    for(int p=0; p < q; ++p)                        // 不断加入新的结点（非递归关键）
        if(!cells[que[p][0]][que[p][1]].booms)
            for(auto & u: xy) {
                int i = que[p][0] + u[0], j = que[p][1] + u[1];
                if(i <= 0 || i > n || j <= 0 || j > m) continue;
                cells[i][j].flagd = 0;
                if(!cells[i][j].swept)
                    recordSweep(i, j);
            }
}

bool runSafeSweep(int x, int y)
{
    coreSweep(x, y);
    return outputSweep();
}

bool runSafeDSweep(int x, int y)
{
    for(auto & u : xy) {
        int i = x + u[0], j = y + u[1];
        if (i <= 0 || i > n || j <= 0 || j > m) continue;
        if(!cells[i][j].swept && !cells[i][j].flagd)
            coreSweep(i, j);
    }
    return outputSweep();
}

bool checkDSweep(int x, int y)
{
    isSafe = true;
    int diff = 0;
    for(auto & u : xy) {
        int i = X + u[0], j = Y + u[1];
        if(i <= 0 || i > n || j <= 0 || j > m) continue;
        if(cells[i][j].isBom ^ cells[i][j].flagd) isSafe = false;
        diff += cells[i][j].isBom - cells[i][j].flagd;
    }
    return diff == 0;
}

bool runOperation(char & op)
{
    if(op == 'Q')                       return printf("give up\n") && false;

    ++nSteps;       // add step since not quit
    int x, y;
    scanf("%d %d", &x, &y);
    switch (op) {
        case 'F':
            if(cells[x][y].swept)       return printf("swept\n");
            else                        return printf((cells[x][y].flagd ^= 1) ? "success\n" : "cancelled\n");
        case 'S':
            if(cells[x][y].swept)       return printf("swept\n");
            else if(cells[x][y].flagd)  return printf("flagged\n");
            else if(cells[x][y].isBom)  return printf("boom\ngame over\n") && false;
            else                        return runSafeSweep(x, y);
        case 'D':
            if(!cells[x][y].swept)      return printf("not swept\n");
            else if(!cells[x][y].booms || !isDSweepEqual(x, y))
                                        return printf("failed\n");
            else if(!isSafe)            return printf("boom\ngame over\n") && false;
            else                        return runSafeDSweep(x, y);
    }
    return true;
}

void runAll()
{
    scanf("%d %d", &n, &m);
    char s[MAX_SIZE];
    for(int i=1; i<=n; i++) {
        scanf("%s", s + 1);
        for(int j=1; j<=m; j++)
            if(s[j] == '*')
                ++cells[i][j].isBom, ++nBooms;
    }
    char ops[7];
    while (scanf("%s", ops) && runOperation(ops[0]));
    printf("total step %d", nSteps);
}

int main()
{
    if(freopen("/Users/mark/MarkLearningCPP/Acwing/1334. 扫雷/case3.txt", "r", stdin))
    {
        auto start = clock();
        runAll();
        auto end = clock();
        printf("\ntime: %.4f ms", (double)(end-start) / CLOCKS_PER_SEC * 1000);
    } else
        runAll();
    return 0;
}
