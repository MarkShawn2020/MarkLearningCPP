//
// Created by 南川 on 2021/1/14. 2021年01月15日22:18:44
//
#include "vector"
#include "algorithm"
#include <cstdio>

using namespace std;

int kToSweep;
const int N = 1001;
struct Cell{ bool isBoom = false; bool isSwept = false; bool isFlagged = false;};
vector<vector<Cell>> cells(N, vector<Cell>(N));

const int tBase[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
int t[8][2]; // 通过tBase数组，结合m，n，x，y，每次经过traverse函数得到一个可迭代的t数组（与长度），记录了next(i, j)

enum DSweepResult{Fail, Safe, Boom};
enum GameStatus{Finish, GiveUp, GameOver, Continue};
GameStatus gs = Continue;

struct History{int x; int y; int kBooms;};

bool sortHistory(const History & a, const History & b){
    if(a.x < b.x) return true;
    if(a.x > b.x) return false;
    if(a.y <= b.y) return true;
    return false;
}

void outputHistory(vector<History> & h)
{
    // 排序，不知道可否改进不
    sort(h.begin(), h.end(), sortHistory);
    printf("%lu cell(s) detected\n", h.size());
    for(auto item: h)
        printf("%d %d %d\n", item.x+1, item.y+1, item.kBooms);
}

int traverseAdj(int n, int m, int x, int y){ // 返回新的数组中的个数
    int k = -1;
    for(auto i : tBase){
        int xx = x + i[0]; int yy = y + i[1];
        if(xx >= 0 && xx < n && yy >=0 && yy < m) {
            t[++k][0] = xx;
            t[k][1] = yy;
        }
    }
    return ++k;
}

int traverseBooms(int n, int m, int x, int y){
    int k = 0;
    for(int i=0; i<traverseAdj(n, m, x, y); ++i)
        if(cells[t[i][0]][t[i][1]].isBoom) ++k;
    return k;
}

void runFlagStep(int x, int y)
{
    if(cells[x][y].isSwept) { printf("swept\n"); return;}
    printf(cells[x][y].isFlagged ? "cancelled\n" : "success\n");
    cells[x][y].isFlagged = !cells[x][y].isFlagged;
}

void coreSweep(int n, int m, int x, int y, vector<History> & h) {
    // 只针对未探明，且不是炸弹的单元格开展
    int kBooms = traverseBooms(n, m, x, y);
    h.emplace_back(History{x, y, kBooms});
    cells[x][y].isSwept = true;
    if(--kToSweep==0) gs = Finish;
    if(kBooms) return;
    for(int p=0; p<traverseAdj(n, m, x, y); ++p){
        const Cell cell = cells[t[p][0]][t[p][1]];
        if(cell.isFlagged) cells[t[p][0]][t[p][1]].isFlagged = false;
        if(!cell.isSwept) coreSweep(n, m, t[p][0], t[p][1], h);
    }
}

int runSweep(int n, int m, int x, int y)
{
    if(cells[x][y].isSwept) return printf("swept\n");
    if(cells[x][y].isFlagged) return printf("flagged\n");
    if(cells[x][y].isBoom) {gs = GameOver; return printf("boom\n");}
    vector<History> h;
    coreSweep(n, m, x, y, h);
    outputHistory(h);
    return 0;
}

DSweepResult traverFlags(int n, int m, int x, int y)
{
    int kBooms = 0;
    int kFlags = 0;
    bool isWrong = false;
    for(int i=0; i<traverseAdj(n, m, x, y); ++i){
        const Cell cell = cells[t[i][0]][t[i][1]];
        if(cell.isFlagged) ++kFlags;
        if(cell.isBoom) ++kBooms;
        if(cell.isFlagged != cell.isBoom) isWrong = true;
    }
    if(!kBooms || kFlags != kBooms) return Fail;
    if(!isWrong) return Safe;
    gs = GameOver;
    return Boom;
}

int runDSweep(int n, int m, int x, int y)
{
    if(!cells[x][y].isSwept) return printf("not swept\n");
    switch (traverFlags(n, m, x, y)) {
        case Fail: return printf("failed\n");
        case Boom: return printf("boom\n");
        case Safe: break;
    }

    vector<History> h;
    for(int i=0; i<traverseAdj(n, m, x, y); ++i){
        int p = t[i][0];
        int q = t[i][1];
        if(!cells[p][q].isSwept && !cells[p][q].isFlagged)
            coreSweep(n, m, p, q, h);
    }

    if(h.empty())  printf("no cell detected\n");
    else outputHistory(h);
    return 0;
}

void runEndingStep(int nSteps)
{
    switch (gs) {
        case Finish: printf("finish\n"); break;
        case GameOver: printf("game over\n"); break;
        case GiveUp: printf("give up\n"); break;
        case Continue: exit(-1);
    }
    printf("total step %d", nSteps);
}

void readCase()
{
    int n, m;
    scanf("%d%d", &n, &m);
    // 初始化每个单元格是否是炸弹
    char line[N];
    for(int i=0; i<n; i++){
        scanf("%s", line);
        for(int j=0; j<m; j++){
            if(line[j] == '.') {cells[i][j].isBoom = false; ++kToSweep;}
            else if(line[j] == '*') cells[i][j].isBoom = true;
        }
    }

    // 初始化所有的输入操作序列
    int totalSteps = 0;
    char stepType[10];
    int x, y;

    while (scanf("%s", stepType))
    {
        if(stepType[0] == 'Q') {gs = GiveUp; return runEndingStep(totalSteps);}
        ++totalSteps;
        scanf("%d%d", &x, &y);
         --x; --y;
        if(stepType[0] == 'F'){runFlagStep(x, y); continue;}
        stepType[0] == 'S' ? runSweep(n, m, x, y) : runDSweep(n, m, x, y);
        if(gs != Continue) return runEndingStep(totalSteps);
    }
}

int main()
{
   readCase();
   return 0;
}