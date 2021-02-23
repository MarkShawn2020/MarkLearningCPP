//
// Created by 南川 on 2021/2/8.
//

//
// Created by 南川 on 2021/2/7.
//
#include "cstdio"
#include "vector"
#include "algorithm"
#include "iostream"
#include "ctime"
using namespace std;

//const int NN = 2, MM = 1000;
//#define printf(args...)  n==NN && m==MM  ? true : printf(args)
//#define cout  n==NN && m==MM && cout

const int MAX_N = 1000 + 2;
int n, m, nBooms = 0, steps = 0, nSwept = 0;

char rows[MAX_N][MAX_N];
int swept[MAX_N][MAX_N];
int flagd[MAX_N][MAX_N];
int check[MAX_N][MAX_N];
int booms[MAX_N][MAX_N];

struct HisCell {
    int x, y;
    bool operator<(HisCell &b) const {return x<b.x || x==b.x && y<b.y;}
};
vector<HisCell> his;

inline bool isBoom(int i, int j) {return rows[i][j] == '*';}

int dxy[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};


/**
 * Sweep Part
 */
int outputHis()
{
    if(his.empty()) return printf("no cell detected\n") && false;

    nSwept += his.size();
    sort(his.begin(), his.end());
    printf("%d cell(s) detected\n", (int)his.size());
    for(auto & item: his) printf("%d %d %d\n", item.x, item.y, booms[item.x][item.y]);
    his.clear();                                    // reset
    return nSwept + nBooms == m * n;
}

void updateHis(int i, int j)
{
    for(auto & u : dxy) {
        int x = i + u[0], y = j + u[1];
        if(x <= 0 || x > n || y <= 0 || y > m) continue;
        if(isBoom(x, y) && !(check[x][y] = false))
            ++booms[i][j];
    }
    his.push_back({i, j});
    ++swept[i][j];
}

void callSweep(int i, int j)
{
    updateHis(i, j);
    for(int p=0; p < his.size(); p++)   // 这里不能range base，因为his.size会变
        if(!booms[his[p].x][his[p].y])
            for(auto & u : dxy)
            {
                int x = his[p].x + u[0], y = his[p].y + u[1];
                if(x<=0 || x>n || y<=0 || y>m) continue; // 避免写大括号
                if(flagd[x][y]) --flagd[x][y];
                if(!swept[x][y]) updateHis(x, y);

            }
}

int runSafeSweep(int i, int j)
{
    callSweep(i, j);
    return outputHis();
}

int runSafeDSweep(int i, int j)
{
    for(auto & u : dxy) {
        int x = i + u[0], y = j + u[1];
        if (x <= 0 || x > n || y <= 0 || y > m) continue;
        if (!swept[x][y] && !flagd[x][y])
            callSweep(x, y);
    }
    return outputHis();
}

bool isDSweepSame(int i, int j)
{
    int diff = 0;
    for(auto & u : dxy) {
        int x = i + u[0], y = j + u[1];
        if (x <= 0 || x > n || y <= 0 || y > m) continue;
        diff += isBoom(x, y) -flagd[x][y];
    }
    return diff == 0;
}

bool isDSweepSafe(int i, int j)
{
    for(const auto & u : dxy) {
        int x = i + u[0], y = j + u[1];
        if (x <= 0 || x > n || y <= 0 || y > m) continue;
        if (isBoom(x, y) ^ flagd[x][y])
            return false;
    }
    return true;
}


/**
 * Main
 */
int runAll()
{
    scanf("%d %d", &n, &m);
    for(int i=1; i<=n; i++)
    {
        scanf("%s", rows[i]+1);
        for(int j=1;j<=m;j++)
            if(rows[i][j]=='*')
                nBooms++;

    }

//    for(int i=1;i<=n;i++)

    char op_c[7];
    while (scanf("%s", op_c) != EOF)
    {
        if(op_c[0] == 'Q')
            return printf("give up\n");
        int op_x, op_y;
        scanf("%d %d", &op_x, &op_y);
        ++steps;    // update steps
//        cout << op_c[0] << " " << op_x << " " << op_y << ",";
        if(op_c[0] == 'F')
            if (swept[op_x][op_y]) printf("swept\n");
            else
                printf(flagd[op_x][op_y] ? "cancelled\n" : "success\n"),
                        flagd[op_x][op_y] ^= 1;
        else if(op_c[0] == 'S')
            if (swept[op_x][op_y]) printf("swept\n");
            else if (flagd[op_x][op_y]) printf("flagged\n");
            else if (isBoom(op_x, op_y)) return printf("boom\ngame over\n");
            else if (runSafeSweep(op_x, op_y)) return printf("finish\n");
            else;
        else if(op_c[0] == 'D')
            if(!swept[op_x][op_y]) printf("not swept\n");
            else if(!booms[op_x][op_y] || !isDSweepSame(op_x, op_y)) printf("failed\n");
            else if(!isDSweepSafe(op_x, op_y)) return printf("boom\ngame over\n");
            else if(runSafeDSweep(op_x, op_y)) return printf("finish\n");
            else;
        else;
    }
}

int main()
{
     freopen("/Users/mark/MarkLearningCPP/Acwing/1334. 扫雷/case3.txt", "r", stdin);
     clock_t start = clock();
    runAll();
    printf("total step %d", steps);
     clock_t end = clock();
     printf("\ntime: %.4f ms", (double)(end - start) * 1000 / CLOCKS_PER_SEC);
}