//
// Created by 南川 on 2021/1/14.
//

#include "fstream"
#include "sstream"
#include "iostream"

#include "vector"
#include "unordered_map"

#include "algorithm"

using namespace std;

enum Operator{Sweep, DSweep, Flag, Quit};
enum CellStatus{Unknown, Swept, Flagged};
enum OperateStatus{Safe, Finish, GameOver, GiveUp};

struct Operate{
    Operator op;
    int x = 0;
    int y = 0;
};

struct Cell{
    bool isBoom = false;
    int kBooms = 0;
    int kFlags = 0;
    CellStatus status = Unknown;
};

struct CellSwept{
    int x;
    int y;
    int c;
};

struct SweepHistory{
    bool isSafe = true;
    bool isFinished = false;
    int kToSweep = 0;
    vector<CellSwept> cellsSwept;
};

template <typename T>
void readCase(
    T & f,
    int & n, int & m, SweepHistory & sh,
    vector<vector<Cell>> & cells,
    vector<Operate> & ops
    )
{
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
            if(ch == '.') {
                cells[i][j].isBoom = false;
                ++sh.kToSweep;
            }
            else if(ch == '*') cells[i][j].isBoom = true;
        }
    }

    // 初始化每个单元格的周围炸弹数
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
        {
            int kBooms = 0;
            for(int p=max(i-1, 0); p<min(i+2, n); p++)
                for(int q=max(j-1, 0); q<min(j+2, m); q++)
                    if(cells[p][q].isBoom)
                        ++kBooms;
            cells[i][j].kBooms = kBooms;
        }

    // 初始化所有的输入操作序列
    string op;
    int x, y;
    unordered_map<string, Operator> OperatorMap = {
            {"Sweep", Sweep},
            {"DSweep", DSweep},
            {"Flag", Flag},
            {"Quit", Quit}
    };
    while (f >> op)
    {
        Operator Op = OperatorMap[op];
        if(Op==Quit) {
            ops.emplace_back(Operate{Op});
            break;
        }
        f >> x >> y;
        ops.emplace_back(Operate{OperatorMap[op], x-1, y-1});
    }
}


void readCaseFromFile(
    int & n, int & m, SweepHistory & sh,
    vector<vector<Cell>> & cells,
    vector<Operate> & ops
    )
{
    string fp = "/Users/mark/CLionProjects/MarkLearningCPP/2017扫雷/case3.txt";
    ifstream f(fp);
    readCase(f, n, m, sh, cells, ops);
}

void readCaseFromStdIO(
    int & n, int & m, SweepHistory & sh,
    vector<vector<Cell>> & cells,
    vector<Operate> & ops
    )
{
    readCase(cin, n, m, sh, cells, ops);
}


void runFinish(OperateStatus operateStatus, int totalSteps)
{
    switch (operateStatus) {
        case Finish:
            cout << "finish" << endl;
            break;
        case GameOver:
            cout << "boom" << endl;
            cout << "game over" << endl;
            break;
        case GiveUp:
            cout << "give up" << endl;
            break;
        case Safe:
            exit(-1);
    }
    cout << "total step " << totalSteps;
}

void runSweepOne(
        vector<vector<Cell>> & cells,
        const int n, const int m, SweepHistory & sh,
        int x, int y, bool clearFlag
        )
{
    Cell* pCell = & cells[x][y];
    // 清除flag标记
    if(clearFlag && pCell->status==Flagged) pCell->status = Unknown;
    if(pCell->status != Unknown) return;
    if(pCell->isBoom)  {
        sh.isSafe = false;
        return;
    }
    pCell->status = Swept;
    sh.cellsSwept.emplace_back(CellSwept{x, y, cells[x][y].kBooms});
    if(--(sh.kToSweep) == 0) {
        sh.isFinished = true;
        return;
    }
    if(pCell->kBooms==0)
        for(int i=max(x-1, 0); i<min(x+2, n); i++)
            for(int j=max(y-1, 0); j<min(y+2, m); j++)
                if(sh.isSafe && !sh.isFinished && cells[i][j].status==Unknown)
                    runSweepOne(cells, n, m, sh, i, j, true);
}

bool sortCellsSwept(CellSwept & c1, CellSwept & c2)
{
    if(c1.x < c2.x) return true;
    if(c1.x > c2.x) return false;
    return c1.y <= c2.y;
}

void handleOperateSweep(SweepHistory & sh, int nOps)
{
    if(!sh.isSafe) return runFinish(GameOver, nOps);

    if(sh.cellsSwept.empty())
        cout << "no cell detected" << endl;
    else
    {
        cout << sh.cellsSwept.size() << " cell(s)"
             << " detected" << endl;
        // 排序！！！
        sort(sh.cellsSwept.begin(), sh.cellsSwept.end(), sortCellsSwept);
        for(auto cellSwept: sh.cellsSwept)
            cout << ++cellSwept.x << " " << ++cellSwept.y << " " << cellSwept.c << endl;
        sh.cellsSwept.clear();
    }
    if(sh.isFinished) return runFinish(Finish, nOps);
}

void runAdjFlags(vector<vector<Cell>> & cells,
             const int n, const int m, int x, int y)
{
    int f = cells[x][y].status == Flagged ? 1 : -1;
    for(int i=max(x-1, 0); i<min(x+1, n); i++)
        for(int j=max(y-1, 0); j<min(y+1, m); j++)
            if(i!=j)
                cells[i][j].kFlags += f;
}

void runByStep(
        vector<vector<Cell>> & cells,
        const int n, const int m,
        SweepHistory & sh,
        Operate op,
        int nOps
    )
{
    Cell* pCell = &cells[op.x][op.y];
    switch (op.op) {
        case Quit:
            runFinish(GiveUp, nOps);
            break;

        case Flag:
            switch (pCell->status) {
                case Swept:
                    cout << "swept" << endl;
                    break;
                case Unknown:
                    cout << "success" << endl;
                    pCell->status = Flagged;
                    runAdjFlags(cells, n, m, op.x, op.y);
                    break;
                case Flagged:
                    cout << "cancelled" << endl;
                    pCell->status = Unknown;
                    runAdjFlags(cells, n, m, op.x, op.y);
                    break;
            }
            break;

        case Sweep:
            switch (pCell->status) {
                case Swept:
                    cout << "swept" << endl;
                    break;
                case Flagged:
                    cout << "flagged" << endl;
                    break;
                case Unknown:
                    runSweepOne(cells, n, m, sh, op.x, op.y, false);
                    handleOperateSweep(sh, nOps);
                    break;
            }
            break;

        case DSweep:
            if(pCell->status != Swept)
            {
                cout << "not swept" << endl;
            }
            else if(pCell->kBooms==0 || pCell->kBooms != pCell->kFlags)
            {
                cout << "failed" << endl;
            }
            else {
                int x = op.x, y = op.y;
                for(int i=max(x-1, 0); i<min(x+2, n); i++)
                    for(int j=max(y-1, 0); j<min(y+2, m); j++)
                        if(cells[i][j].status==Unknown && sh.isSafe && !sh.isFinished)
                            runSweepOne(cells, n, m, sh, i, j, false);
                handleOperateSweep(sh, nOps);
            }
            break;
    }
}

void runAllSteps(
        vector<vector<Cell>> & cells,
        const int n, const int m, SweepHistory& sh,
        vector<Operate> & ops
        )
{
    int nOps = 0;
    for(auto op: ops)
    {
        runByStep(cells, n, m, sh, op, ++nOps);
        if(!sh.isSafe || sh.isFinished) return;
    }
}

int main()
{
   int n, m;
   vector<vector<Cell>> cells;
   vector<Operate> ops;
   SweepHistory operateSweep;
   readCaseFromStdIO(n, m, operateSweep, cells, ops);
   runAllSteps(cells, n, m, operateSweep, ops);

   return 0;
}