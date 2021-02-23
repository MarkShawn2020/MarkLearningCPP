//
// Created by 南川 on 2021/1/28.
//
#include "cstdio"
#include "cstring"
#include "cmath"
#include "cassert"

#include "string"
#include "iostream"
#include "fstream"
#include "algorithm"

#include "vector"
#include "stack"
#include "list"
#include "queue"
#include "set"
#include "unordered_set"
#include "map"
#include "unordered_map"

using namespace std;

const int MAX_N = 10 + 2;            // 扫雷的最大高度与宽度
const int MAX_Q = 60000;                // 最大序列长度
int n, m;                               // (n, m) 扫雷的高度与宽度
int todo = 0, steps = 0;                               // 待翻开数
enum DSweepResult{QUIT, SAFE, INCORRECT, BOOM, FINISH};

int ox[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int oy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

struct Cell{    
    bool isBoom : 1;
    bool isFlag : 1;
    bool isSwept: 1;
    int booms   : 5;
} G[MAX_N][MAX_N];

struct SweptCells {
    int x;
    int y;
    int v;
    bool operator < (SweptCells & b) const {
        return x < b.x || x == b.x && y < b.y;
    }
};

void opFlag(int i, int j)
{
    // 已插旗
    if(G[i][j].isFlag) G[i][j].isFlag = false, cout << "cancelled" << endl;
    // 未探明
    else if(!G[i][j].isSwept) G[i][j].isFlag = true, cout << "success" << endl;
    // 已探明
    else cout << "swept" << endl;
}

bool ending(DSweepResult status)
{
    switch (status) {
        case FINISH:
            cout << "finish" << endl;
            break;
        case QUIT:
            cout << "give up" << endl;
            break;
        case BOOM:
            cout << "boom" << endl;
            break;
    }
    cout << "total step " << steps;
    return false;
}

DSweepResult doSweep(int i, int j, vector<SweptCells> & his)
{
    if(G[i][j].isBoom) {cout << "boom" << endl;return BOOM;}
    G[i][j].isSwept = true;
    his.emplace_back(SweptCells {i, j, G[i][j].booms});
    if(--todo == 0) return FINISH;

    if(G[i][j].booms == 0)
        for(int d=0; d<8; d++)
        {
            int x = i + ox[d];
            int y = j + oy[d];
            G[x][y].isFlag = false;
            if(!G[x][y].isSwept)        // 连锁反应，清除flag，且未访问才访问
                doSweep(x, y, his);
        }
    return SAFE;
}

void printHis(vector<SweptCells> & his)
{
    if(his.empty()) {
        cout << "no cell detected" << endl;
        return;
    }
    cout << his.size() << " cell(s) detected" << endl;
    sort(his.begin(), his.end());
    for(auto & item: his)
        printf("%d %d %d\n", item.x, item.y, item.v);
}

bool opSweep(int i, int j)
{
    // 有旗帜
    if(G[i][j].isFlag) {
        cout << "flagged" << endl;
        return true;
    }
    // 已探明
    if(G[i][j].isSwept) {
        cout << "swept" << endl;
        return true;
    }
    // 执行扫雷
    vector<SweptCells> his;
    DSweepResult ret = doSweep(i, j, his);
    if(ret == BOOM)
        return ending(ret);

    printHis(his);
    return ret != FINISH || ending(ret);
}

DSweepResult checkDSweep(int i, int j)
{
    int miss = 0, flags = 0;
    for(int d = 0; d < 8; d++)
    {
        int x = ox[d] + i;
        int y = oy[d] + j;
        if(G[x][y].isFlag ^ G[x][y].isBoom)
            miss++;
        if(G[x][y].isFlag)
            flags++;
    }
    if(flags != G[i][j].booms) return INCORRECT;
    if(miss != 0) return BOOM;
    return SAFE;
}


bool opDSweep(int i, int j)
{
    // 未探明
    if(!G[i][j].isSwept) {
        cout << "not swept" << endl;
        return true;
    }
    // 0个
    if(G[i][j].booms == 0) {
        cout << "failed" << endl;
        return true;
    }

    DSweepResult ret = checkDSweep(i, j);
    if(ret == INCORRECT)
    {
        cout << "failed" << endl;
        return true;
    }
    if(ret == BOOM)
    {
        cout << "boom" << endl;
        return ending(ret);
    }
    if(ret == SAFE)
    {
        vector<SweptCells> his;
        for(int d=0; d<8; d++)
        {
            int x = i + ox[d];
            int y = j + oy[d];
            if(!G[x][y].isSwept)
                doSweep(x, y, his);
        }


    }
}


template <typename T>
void run(T & cin)
{
    // input data
    char c;
    cin >> n >> m;
    for(int i = 1; i <= n ; i++)
        for(int j = 1; j <= m; j++)
            cin >> c,
            G[i][j] = {c == '*', false, false, 0},
            todo += c == '.';

    // init booms
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            for(int d=0; d<8; d++)
                if(G[i+ox[d]][j+oy[d]].isBoom)
                    G[i][j].booms++;
    
    string op;
    for(int i=1; i<=m; i++)
    {
        cin >> op;
        switch (op[0])
        {
        case 'S':
            break;
        case 'D':
            break;
        case 'F':
            break;
        case 'Q':
            break;
        default:
            throw("Error!");
        }
    }
}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    // read from local case if possible, otherwise from console
    ifstream fin("/Users/mark/MarkLearningCPP/Acwing/1334. 扫雷/case1.txt");
    run(fin.good() ? fin : cin);
}

