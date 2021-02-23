//
// Created by 南川 on 2021/1/14. 2021年01月15日22:18:44
//

#include "fstream"
#include "sstream"
#include "iostream"
#include "cstring"

#include "unordered_map"
#include "vector"
#include "algorithm"
#include <cstdio>

using namespace std;


enum CheckFlagResult{Fail, Safe, Boom};
enum StepType{Sweep, DSweep, Flag, Quit};
enum GameStatus{Finish, GiveUp, GameOver, Continue};

int kToSweep;
GameStatus gs = Continue;

struct StepInput{
    StepType stepType;
    int x = 0;
    int y = 0;
};

struct Cell{
    bool isBoom = false;
    bool isSwept = false;
    bool isFlagged = false;
};

struct History{
    int x;
    int y;
    int kBooms;
};

const int tBase[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
int t[8][2];

int traverseAdj(int n, int m, int x, int y){ // 返回新的数组中的个数
    int k = -1;
    for(auto i : tBase){
        int xx = x + i[0];
        int yy = y + i[1];
        if(xx >= 0 && xx < n && yy >=0 && yy < m) {
            t[++k][0] = xx;
            t[k][1] = yy;
        };
    }
    return ++k;
}

int calcBooms(vector<vector<Cell>> & cells, int n, int m, int x, int y){
    int k = 0;
    for(int i=0; i<traverseAdj(n, m, x, y); ++i)
        if(cells[t[i][0]][t[i][1]].isBoom) ++k;
    return k;
}

void runEndingStep(int nSteps)
{
    switch (gs) {
        case Finish:
            cout << "finish" << endl;
            break;
        case GameOver:
            cout << "game over" << endl;
            break;
        case GiveUp:
            cout << "give up" << endl;
            break;
        case Continue:
            exit(-1);
    }
    cout << "total step " << nSteps;
}

void runFlagStep(vector<vector<Cell>> & cells, int x, int y)
{
    if(cells[x][y].isSwept) {cout << "swept" << endl; return;}
    cout << (cells[x][y].isFlagged ? "cancelled" : "success") << endl;
    cells[x][y].isFlagged = !cells[x][y].isFlagged;
}

void doCoreSweep(int n, int m, vector<vector<Cell>> & cells, int x, int y, vector<History> & h)
// 只针对未探明，且不是炸弹的单元格开展
{
    int kBooms = calcBooms(cells, n, m, x, y);
    h.emplace_back(History{x, y, kBooms});
    cells[x][y].isSwept = true;
    if(--kToSweep==0) gs = Finish;
    if(kBooms) return;
    for(int p=0; p<traverseAdj(n, m, x, y); ++p){
        const Cell cell = cells[t[p][0]][t[p][1]];
        if(cell.isFlagged) cells[t[p][0]][t[p][1]].isFlagged = false;
        if(!cell.isSwept) runCoreSweep(n, m, cells, t[p][0], t[p][1], h);
    }
}

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
    cout << h.size() << " cell(s) detected" << endl;
    for(auto item: h)
        printf("%d %d %d\n", item.x+1, item.y+1, item.kBooms);
//        cout << item.x+1 << " " << item.y+1 << " " << item.kBooms << endl;
}

void runSweep(int n, int m, vector<vector<Cell>> & cells, int x, int y)
{
    if(cells[x][y].isSwept) {cout << "swept" << endl; return;}
    if(cells[x][y].isFlagged) {cout << "flagged" << endl; return;}
    if(cells[x][y].isBoom) {cout << "boom" << endl; gs = GameOver; return;}
    vector<History> h;
    runCoreSweep(n, m, cells, x, y, h);
    doOutputHistory(h);
}

CheckFlagResult runCheckFlags(int n, int m, vector<vector<Cell>> & cells, int x, int y)
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
    return isWrong ? Boom : Safe;
}

void runDSweep(int n, int m, vector<vector<Cell>> & cells, int x, int y)
{
    if(!cells[x][y].isSwept) {cout << "not swept" << endl; return;}
    switch (runCheckFlags(n, m, cells, x, y)) {
        case Fail:
            cout << "failed" << endl;
            return;
        case Boom:
            cout << "boom" << endl;
            gs = GameOver;
            return;
        case Safe:
            break;
    }

    vector<History> h;
    for(int i=0; i<traverseAdj(n, m, x, y); ++i){
        int p = t[i][0];
        int q = t[i][1];
        if(!cells[p][q].isSwept && !cells[p][q].isFlagged)
            runCoreSweep(n, m, cells, p, q, h);
    }

    if(h.empty()) cout << "no cell detected" << endl;
    else doOutputHistory(h);
}


void runEachStep(int n, int m, vector<vector<Cell>> & cells, StepInput & step)
{
    switch (step.stepType) {
        case Flag:
            runFlagStep(cells, step.x, step.y);
            break;
        case Sweep:
            runSweep(n, m, cells, step.x, step.y);
            break;
        case DSweep:
            runDSweep(n, m, cells, step.x, step.y);
            break;
        case Quit:
            exit(-2);
    }
}


void runAllSteps(int n, int m, vector<vector<Cell>> & cells, vector<StepInput> & stepSequence)
{
    for(int i=0; i<stepSequence.size(); i++){
        if(stepSequence[i].stepType == Quit){
            gs = GiveUp; runEndingStep(i); return;
        }

        runEachStep(n, m, cells, stepSequence[i]);
        if(gs != Continue) return runEndingStep(i+1);
    }
}


template <typename T>
void readCase(
    T & f, int & n, int & m,
    vector<vector<Cell>> & cells,
    vector<StepInput> & stepSequence
    )
{
//    scanf("%d %d\n", &n, &m);

    f >> n >> m;

    // 初始化每个单元格是否是炸弹
    cells.resize(n);
    char ch;
    for(int i=0; i<n; i++)
    {
        cells[i].resize(m);
        for(int j=0; j<m; j++)
        {
            f >> ch;
//            scanf("%c", &ch);
            if(ch == '.') {cells[i][j].isBoom = false; ++kToSweep;}
            else if(ch == '*') cells[i][j].isBoom = true;
        }
//        scanf("\n");
    }
//    scanf("\n");

    // 初始化所有的输入操作序列
    //    string stepType;
    char stepType[6];
    int x, y;
    unordered_map<string , StepType> stepMap = {
            {"Quit", Quit},
            {"Sweep", Sweep},
            {"DSweep", DSweep},
            {"Flag", Flag}
    };
    while (f >> stepType)
//    while (scanf("%s", stepType))
    {
        if(!strcmp(stepType, "Quit")) {
            stepSequence.emplace_back(StepInput{Quit});
            break;
        }
        f >> x >> y;
//        scanf("%d %d\n", &x, &y);
        stepSequence.emplace_back(StepInput{stepMap[stepType], x-1, y-1});
    }
}


void readCaseFromFile(int & n, int & m,vector<vector<Cell>> & cells,vector<StepInput> & ss)
{
    string fp = "/Users/mark/CLionProjects/MarkLearningCPP/2017扫雷/case1.txt";
    ifstream f(fp);
    readCase(f, n, m, cells, ss);
}

void readCaseFromStdIO(int & n, int & m, vector<vector<Cell>> & cells,vector<StepInput> & ss)
{
    readCase(cin, n, m, cells, ss);
}




int main()
{
   int n, m;
   vector<vector<Cell>> cells;
   vector<StepInput> stepSequence;
   readCaseFromStdIO(n, m, cells,stepSequence);
   runAllSteps(n, m, cells, stepSequence);
   return 0;
}