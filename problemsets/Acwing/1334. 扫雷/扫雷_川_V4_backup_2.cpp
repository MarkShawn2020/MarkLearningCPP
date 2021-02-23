//
// Created by 南川 on 2021/2/7.
//
#include "cstdio"
#include "array"
#include "algorithm"

using namespace std;

const int MAX_N = 1000 + 2;


struct Cell {
    bool isBoom     : 1;
    bool isSwept    : 1;
    bool isFlagged  : 1;
    int booms       : 4;
} cells[MAX_N][MAX_N];

struct HisCell {
    int x, y;

    bool operator<(HisCell &b) const {
        return x < b.x || x == b.x && y < b.y;
    }
};
array<HisCell, MAX_N * MAX_N> his;

int todos = 0, steps = 0, kHis = 0;

/**
 * iter sugar
 */
int dxs[8] = {-1, -1, -1, 0, 1, 0, 1, 1};
int dys[8] = {-1, 0, 1, -1, -1, 1, 1, 0};
int xs[8], ys[8], x, y, k;

int & iter(int i, int j, int n, int m)
{
    k = 0;
    for(int d=0; d<8; ++d) {
        x = i + dxs[d], y = j + dys[d];
        if(x > 0 && x <=n && y > 0 && y <= m)
            xs[k] = x, ys[k] = y, ++k;
    }
    return k;
}


/**
 * Sweep Part
 */
int outputHis()
{
    if(!kHis){printf("no cell detected\n");return false;}

    sort(his.begin(), his.begin() + kHis);  // sort ???
    printf("%d cell(s) detected\n", kHis);
    for(int i=0; i < kHis; i++)
        printf("%d %d %d\n", his[i].x, his[i].y, cells[his[i].x][his[i].y].booms);
    kHis = 0;                                   // reset kHis
    return todos == 0;
}

void callSweep(int i, int j, int n, int m)
{
    cells[i][j].isSwept = true;
    HisCell & cur = his[kHis++];
    cur.x = i;
    cur.y = j;
    --todos;            // update todos
    for(int p=0; p<kHis; p++)
        if(!cells[his[p].x][his[p].y].booms)
            for(int u=0; u<iter(his[p].x, his[p].y, n, m); u++)
            {
                if(cells[xs[u]][ys[u]].isFlagged)
                    cells[xs[u]][ys[u]].isFlagged = false;
                if(!cells[xs[u]][ys[u]].isSwept) {
                    cells[xs[u]][ys[u]].isSwept = true;
                    HisCell & hc = his[kHis++];
                    hc.x = xs[u];
                    hc.y = ys[u];
                    --todos;
                }
            }
}

int runSafeSweep(int i, int j, int n, int m)
{
    doSafeSweepNonRecursive(i, j, n, m);
    return outputHistory();
}

int runSafeDSweep(int i, int j, int n, int m)
{
    for(int u=0; u<iter(i, j, n, m); u++)
        if(!cells[xs[u]][ys[u]].isSwept && !cells[xs[u]][ys[u]].isFlagged)
            doSafeSweepNonRecursive(xs[u], ys[u], n, m);
    return outputHistory();
}

bool isDSweepSame(int i, int j, int n, int m, int booms)
{
    for(int u=0; u<iter(i, j, n, m); u++)
        booms -= cells[xs[u]][ys[u]].isFlagged;
    return booms == 0;
}

bool isDSweepSafe(int i, int j, int n, int m)
{
    for(int u=0; u<iter(i, j, n, m); u++)
        if(cells[xs[u]][ys[u]].isFlagged ^ cells[xs[u]][ys[u]].isBoom)
            return false;
    return true;
}


/**
 * ending
 */
int runAll(int n, int m)
{
    char s[7];
    int x, y;
    while (scanf("%s", s) != EOF)
    {
        if(s[0] == 'Q') return printf("give up\n");
        scanf("%d %d", &x, &y);
        ++steps;    // update steps
        switch (s[0]) {
            case 'F':
                if(cells[x][y].isSwept) printf("swept\n");
                else printf((cells[x][y].isFlagged ^= 1) ? "success\n" : "cancelled\n");
                break;
            case 'S':
                if(cells[x][y].isSwept) printf("swept\n");
                else if(cells[x][y].isFlagged) printf("flagged\n");
                else if(cells[x][y].isBoom) return printf("boom\ngame over\n");
                else if(runSafeSweep(x, y, n, m)) return printf("finish\n");
                break;
            case 'D':
                if(!cells[x][y].isSwept) printf("not swept\n");
                else if(!cells[x][y].booms || !isDSweepSame(x, y, n, m, cells[x][y].booms)) printf("failed\n");
                else if(!isDSweepSafe(x, y, n, m)) return printf("boom\ngame over\n");
                else if(runSafeDSweep(x, y, n, m)) return printf("finish\n");
                break;
        }
    }
}
/**
 * Main
 */
int main()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/1334. 扫雷/case1.txt", "r", stdin);
    int n, m;
    scanf("%d %d", &n, &m);

    // init cells
    char c[MAX_N];
    for(int i=1; i<=n; i++) {
        scanf("%s", c);
        for(int j=1; j<=m; j++)
            c[j-1] == '*' ? cells[i][j].isBoom = true : ++todos;
    }

    // init booms
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            for(int u=0; u<iter(i, j, n, m); u++)
                if(cells[xs[u]][ys[u]].isBoom)
                    ++cells[i][j].booms;

    runAll(n, m);
    printf("total step %d", steps);
}