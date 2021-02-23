//
// Created by 南川 on 2021/2/16.
//

//
// Created by 南川 on 2021/2/15.
//

#include "cstdio"
#include "ctime"
#include "cstring"
#include "algorithm"
#include "functional"
using namespace std;

#define printf(...) true


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
    printf("minAns: %d, steps: %d, tasks: %2d, pos: [", minAns, steps, tasks);
    for(int i=0; i<nSeqs; ++i) printf("%d ", pos[i]);
    printf("] \n");

    if(steps >= minAns) {
        printf("------ CUT ------\n");
        return false;
    }
    if(tasks == 0) {
        printf("------ UPDATE, minAns: %d -> %d ------\n", minAns, steps);
        minAns = steps;
        return true;
    }

    CharFreq cfsNew[4];
    updateCFS(cfsNew);
    for(auto & i : cfsNew)
        printf("<%d, %c> ", i.freq, chars[i.ch]);

    for(int u=0; u<4 && cfsNew[u].freq > 0; ++u)
    {
        int changed = 0;
        int tasksBack = tasks;
        int posBack[N_SEQS];
        memcpy(posBack, pos, sizeof posBack);

        for(int i=0; i<N_SEQS; ++i)
            if(pos[i] < lens[i] && encode(i, pos[i]) == cfsNew[u].ch)
            {
                ++changed;
                --tasks;
                ++pos[i];
            }

        if(!changed) continue;
        ++steps;
        printf("ch: %c, ", chars[cfsNew[u].ch]);

        // 由于dfs需要穷尽一切可能，这里即使为true
        //（即已经搜索到一个答案，但也不敢退出，以防漏掉更优的解）
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
    fprintf(stdout, "%d\n", minAns);
}

/**
 * 求解全部case的框架函数
 */
int main()
{
    freopen("/Users/mark/MarkLearningCPP/HDOJ/1560. DNA sequence/case1.txt", "r", stdin);
    auto s = clock();

    for(int i=0; i<4; ++i) cfs[i].ch = i; // init cfs
    scanf("%d", &nCases);
    while (nCases--) solveCase();

    auto t = clock();
    fprintf(stdout, "time: %.4f\n", double (t-s)/CLOCKS_PER_SEC*1000);

    return 0;
}
