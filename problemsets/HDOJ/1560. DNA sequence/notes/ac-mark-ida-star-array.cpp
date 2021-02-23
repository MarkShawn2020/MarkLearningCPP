//
// Created by 南川 on 2021/2/17.
// Problem - 1560 - http://acm.hdu.edu.cn/showproblem.php?pid=1560
// 31 ms
//
#include "cstdio"
#include "cstring"
using std::memset;
using std::memcpy;

/**
 * for global
 */
const int N_SEQS = 8;           // 每个测例最大的串数
const int N_LENS = 5;           // 每串最大长度
const int N_TYPE = 4;           // 字符总类
int nCases;                     // 测例数

const int dict[20] = {          // 字符转数字
        1, 0, 2, 0, 0, 0, 3,    // A, C, G
        0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 4        // T
};


/**
 * for each case
 */
int nSeqs;                          // 输入串数
char seq[N_LENS];                   // 接收字符串
int seqs[N_SEQS][N_LENS];           // 每个串的整型存储
int lens[N_SEQS];                   // 每个串的长度
int minAns;                         // 答案


/**
 * 深度递归过程中的状态信息，用于回溯
 */
struct State {
    int steps;                      // 基于steps与surplus判退
    int pos[N_SEQS];                // 记录位置便宜，必须
    int freqs[N_TYPE + 1][N_SEQS];  // 快速统计当前剩余匹配数目，避免较高计算占用
    int maxFreq[N_TYPE + 1];        // 快速统计每类字符最大的频度，用于计算剩余步数
    int nxtFreq[N_TYPE + 1];        // 快速统计下一个可能的字符，避免无效备份State，无需重置，递推更新

    void reset() {
        steps = 0;
        memset(pos,     0, sizeof pos);
        memset(freqs,   0, sizeof freqs);
        memset(maxFreq, 0, sizeof maxFreq);
    }

    /**
     * 该函数将目前的状态里，所有子序列中排头为某id的元素全部去除
     * 是状态更新的关键函数，将影响状态内的所有数据结构（不影响的我也不会加入状态了）
     * @param id
     */
    void offsetPos(const int & id) {
        ++steps;
        for(int i=0; i < nSeqs; ++i)    // 更新位置与频度
            if(pos[i] < lens[i] && seqs[i][pos[i]] == id)
            {
                if(--freqs[id][i] == maxFreq[id] - 1)
                    updateMaxFreq(id);
                --nxtFreq[id];
                if(++pos[i] < lens[i])
                    ++nxtFreq[seqs[i][pos[i]]];
            }
    }

    /**
     * 这个函数的主要原理，就是当某子序列的某id频度是所有子序列中最大的那一个时，
     * 它的变动将可能影响最终所有子序列该id的最大频度，于是对这个id的最大频度重新更新；
     * 而对于其他非最大频度的子序列，它们更新该id值时则不会调用此函数
     * 因此该函数或许可以节省一定的开销（但并不一定，比如当所有子序列某id频度都相等时）
     * @param id
     */
    inline void updateMaxFreq(int id) { // 最大八步
        int r1 = 0;
        for(int i=0; i < nSeqs; ++i)
            if(r1 < freqs[id][i])
                r1 = freqs[id][i];
        maxFreq[id] = r1;
    }

    /**
     * 这个函数是本程序的估价函数，非常重要，用于初始化答案、剪枝与最终答案的确定
     * 它统计接下来每种字符在所有子序列中的最大值的汇总，代表接下来至少还需多少步完成
     * 当它将至0时说明已经找到了一个解（结合iddfs，就是最优解）
     * 而当它与已走步数相加，超过给定步数限制时，则进行剪枝
     * @return
     */
    inline int checkSurplus() { // 最大四步
        int r1 = 0;
        for(int id=1; id<=4; ++id)
            r1 += maxFreq[id];
        return r1;
    }
}state;

/**
 * 【主函数】每个case的递归求解
 */
bool recurSolve()
{
    for(int id = 1; id <= 4; ++id)
    {
        if(!state.nxtFreq[id]) continue;                // 避免不必要的的备份
        State stateBack(state);                         // backup
        state.offsetPos(id);                            // update
        int surplus = state.checkSurplus();             // check
        if(state.steps + surplus <= minAns && (!surplus || recurSolve()))               // 成功退出
            return true;                                // success
        else state = stateBack;                         // rollback
    }
    return false;
}

/**
 * 求解每个case的框架函数
 */
void solveCase()
{
    state.reset();                                      // reset state
    scanf("%d", &nSeqs);
    for(int i = 0; i < nSeqs; ++i)
    {
        scanf("%s", seq);
        lens[i] = strlen(seq);                          // 记录每个字符串长度
        ++state.nxtFreq[dict[seq[0]-'A']];
        for(int j = 0; j < lens[i]; ++j)
        {
            const int & id = dict[seq[j] - 'A'];        // 将字符串转为数字存储
            ++state.freqs[id][i];
            seqs[i][j] = id;
        }
    }
    for(int id = 1; id <= 4; ++id)                      // 更新每类字符的最大频度
        state.updateMaxFreq(id);

    minAns = state.checkSurplus();                      // 初始化答案
    while (!recurSolve()) ++minAns;                     // 当无解时，迭代加深
    printf("%d\n", minAns);
}

/**
 * 求解全部case的框架函数
 */
int main()
{
    freopen("/Users/mark/MarkLearningCPP/HDOJ/1560. DNA sequence/case4.txt", "r", stdin);

    scanf("%d", &nCases);
    while (nCases--) solveCase();
    return 0;
}
