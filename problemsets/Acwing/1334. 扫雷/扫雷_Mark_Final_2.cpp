//
// Created by 南川 on 2021/2/8.
//
#include "cstdio"
#include "array"
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

int n, m, nSwept = 0, nBooms = 0, nSteps = 0, q = 0, isSafe = 0, isOver = 0;
array<array<int, 2>, 8> xy = {{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}};
array<array<int, 2>, 8> nnn{};
array<array<int, 2>, MAX_SIZE * MAX_SIZE> que;


bool outputSweep()
{
    if(!q) return printf("no cell detected\n") && false;
    printf("%d cell(s) detected\n", q);
    sort(begin(que), begin(que) + q);
    for(int qi=0; qi<q; qi++)
        printf("%d %d %d\n", que[qi][0], que[qi][1], cells[que[qi][0]][que[qi][1]].booms);
    q = 0;                                      // reset
    return nSwept + nBooms == n * m;
}

void safeSweepNonRecursive(int X, int Y)
{
    que[q++] = {x, y};
    for(int p=0; p<q; ++p) {
        int x = que[p][0], y = que[p][1];
        cells[x][y].swept = true; ++nSwept;

        int kkk = 0;
        for(auto & u : xy) {
            int i = x + u[0], j = y + u[1];
            if (i <= 0 || i > n || j <= 0 || j > m) continue;
            if (cells[i][j].isBom) ++cells[x][y].booms;
            if (!cells[i][j].swept) nnn[kkk++] = {i, j};
        }

        if(!cells[x][y].booms)
            for(int u=0; u<kkk; u++)
                que[q++] = nnn[u];
    }

}

bool runSafeSweep(int x, int y)
{
    coreSweep(x, y);
    return outputSweep();
}

bool runSafeDSweep(int X, int Y)
{
    for(auto & u : xy) {
        int i = X + u[0], j = Y + u[1];
        if (i <= 0 || i > n || j <= 0 || j > m) continue;
        if(!cells[i][j].swept && !cells[i][j].flagd)
            X = i, Y = j,
            coreSweep(X, Y);
    }
    return outputSweep();
}

bool checkDSweep(int X, int Y)
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
    while (!isOver){
        scanf("%s", ops); const char & op = ops[0];
        if(op == 'Q')                   printf("give up\n"), ++isOver;
        ++nSteps; int x, y; scanf("%d %d", &x, &y);
        if (op == 'F')
            if(cells[x][y].swept)       printf("swept\n");
            else                        printf((cells[x][y].flagd ^= 1) ? "success\n" : "cancelled\n");
        else if(op == 'S')
            if(cells[x][y].swept)       printf("swept\n");
            else if(cells[x][y].flagd)  printf("flagged\n");
            else if(cells[x][y].isBom)  printf("boom\ngame over\n"), ++isOver;
            else runSafeSweep(x, y) &&  (printf("finish\n"), ++isOver);
        else
            if(!cells[x][y].swept)      printf("not swept\n");
            else if(!cells[x][y].booms || !isDSweepEqual(x, y)) printf("failed\n");
            else if(!isSafe)            printf("boom\ngame over\n"), ++isOver;
            else runSafeDSweep(x, y) && (printf("finish\n"), ++isOver);
    }
    printf("total step %d", nSteps);
}

int main()
{
    if(freopen("/Users/mark/MarkLearningCPP/Acwing/1334. 扫雷/case3.txt", "r", stdin)) {
        auto start = clock();
        runAll();
        auto end = clock();
        printf("\ntime: %.4f ms", (double)(end-start) / CLOCKS_PER_SEC * 1000);
    } else
        runAll();
    return 0;
}
