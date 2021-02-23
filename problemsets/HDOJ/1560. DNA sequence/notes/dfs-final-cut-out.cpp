//
// Created by 南川 on 2021/2/16.
// TLE
//

#include "cstdio"
#include "ctime"
#include "cstring"
#include "algorithm"
#include "functional"
using namespace std;

/**
 * for global
 */
const int N_SEQS = 8;           // 每个测例最大的串数
const int N_LENS = 5;           // 每串最大长度
int nCases;                     // 测例数
char chars[4] = {'A', 'C', 'G', 'T'};
int dict[20] = {                // 字符转数字
        0, 0, 1, 0, 0, 0, 2,    // A, C, G
        0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 3        // T
};

/**
 * for each case
 */
int nSeqs;                      // 输入串数
char seqs[N_SEQS][N_LENS];      // 输入信息
int lens[N_SEQS];
// need reset
int pos[N_SEQS];
int tasks = 0;
int steps = 0;
int minAns = 40;                // 记录答案

inline int & encode(int i, int j) {return dict[seqs[i][j] - 'A'];}

struct CharFreq{
    int freq;
    int ch;
    bool operator > (const CharFreq & cf) const {
        return freq > cf.freq;
    }
} cfs[4];

void updateCFS(CharFreq cfsNew[4])
{
    memcpy(cfsNew, cfs, sizeof cfs);
    for(int i=0; i<N_SEQS; ++i)
        if(pos[i] < lens[i])
            ++cfsNew[encode(i, pos[i])].freq;
    sort(cfsNew, cfsNew+4, greater<CharFreq>());
}

bool solve()
{
    if(steps >= minAns) {return false;}
    if(tasks == 0) {minAns = steps; return true;}

    CharFreq cfsNew[4];
    updateCFS(cfsNew);
    for(int u=0; u<4 && cfsNew[u].freq > 0; ++u)
    {
        int changed = 0;
        int tasksBack = tasks;
        int posBack[N_SEQS];
        memcpy(posBack, pos, sizeof posBack);
        for(int i=0; i<N_SEQS; ++i)
            if(pos[i] < lens[i] && encode(i, pos[i]) == cfsNew[u].ch)
                ++changed, --tasks, ++pos[i];
        if(!changed) continue;

        ++steps;
        solve();
        --steps;
        tasks = tasksBack;
        memcpy(pos, posBack, sizeof posBack);
    }
    return false;
}


/**
 * 求解每个case的框架函数
 */
void solveCase()
{
    minAns = 40;                                    // reset
    steps = 0;
    tasks = 0;
    memset(pos, 0, sizeof pos);

    scanf("%d", &nSeqs);
    for(int i=0; i<nSeqs; i++)
    {
        scanf("%s", seqs[i]);
        lens[i] = strlen(seqs[i]);                  // 记录每个字符串长度
        tasks += lens[i];
    }
    solve();
    printf("%d\n", minAns);
}

/**
 * 求解全部case的框架函数
 */
int main()
{
    for(int i=0; i<4; ++i) cfs[i].ch = i; // init cfs
    scanf("%d", &nCases);
    while (nCases--) solveCase();
}
