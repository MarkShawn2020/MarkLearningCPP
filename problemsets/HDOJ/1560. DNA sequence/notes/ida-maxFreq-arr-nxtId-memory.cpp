//
// Created by 南川 on 2021/2/17.
// Problem - 1560 - http://acm.hdu.edu.cn/showproblem.php?pid=1560
//
#include "ctime"
#include "cstdio"
#include "cstring"
using namespace std;

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

int freqSeq[N_TYPE + 1];
int freqAll[N_TYPE + 1];

/**
 * stats
 */
int kRecur, kBackUp, kMove, kHash, kNotHash;

/**
 * 深度递归过程中的状态信息，用于回溯
 */
struct State {
    int steps;                      // 基于steps与surplus判退
    int pos[N_SEQS];                // 记录位置便宜，必须
    int nxt[N_TYPE+1];

/**
 * 这个函数是本程序的估价函数，非常重要，用于初始化答案、剪枝与最终答案的确定
 * 它统计接下来每种字符在所有子序列中的最大值的汇总，代表接下来至少还需多少步完成
 * 当它将至0时说明已经找到了一个解（结合iddfs，就是最优解）
 * 而当它与已走步数相加，超过给定步数限制时，则进行剪枝
 * @return
 */
    inline int checkSurplus() { // 最大四步
        ++kNotHash;
        memset(freqAll, 0, sizeof freqAll);
        for (int i=0; i<nSeqs; ++i)
        {
            memset(freqSeq, 0, sizeof freqSeq);
            for(int j=pos[i]; j<lens[i]; ++j)
                ++freqSeq[seqs[i][j]];
            for(int id=1; id<=4; ++id)
                if(freqAll[id] < freqSeq[id])
                    freqAll[id] = freqSeq[id];
        }
        return freqAll[1] + freqAll[2] + freqAll[3] + freqAll[4];
    }

    void reset() {
        steps = 0;
        memset(pos, 0, sizeof pos);
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
                --nxt[seqs[i][pos[i]]];
                if(++pos[i] < lens[i])
                    ++nxt[seqs[i][pos[i]]];
                ++kMove;
            }
    }
}state;

/**
 * 【主函数】每个case的递归求解
 */
bool recurSolve()
{
    ++kRecur;
    for(int id = 1; id <= 4; ++id)
    {
        if(!state.nxt[id]) continue;                // 避免不必要的的备份

        ++kBackUp;
        State stateBack(state);                         // backup
        state.offsetPos(id);                            // update
        int surplus = state.checkSurplus();             // check
//        printf("minAns: %d, steps: %d, surplus: %d\n", minAns, state.steps, surplus);
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
        ++state.nxt[dict[seq[0]-'A']];
        for(int j = 0; j < lens[i]; ++j)
            seqs[i][j] = dict[seq[j] - 'A'];
    }

//    minAns = state.checkSurplus();                      // 初始化答案
    minAns = 8;
    while (!recurSolve()) ++minAns;                     // 当无解时，迭代加深
    printf("%d\n", state.steps);
}

/**
 * 求解全部case的框架函数
 */
int main()
{
    freopen("/Users/mark/MarkLearningCPP/HDOJ/1560. DNA sequence/case4.txt", "r", stdin);
    auto s = clock();

    scanf("%d", &nCases);
    while (nCases--) solveCase();

    auto t = clock();
    printf("time: %.4f, kRecur: %d, kBackUp: %d, kMove: %d, kHash: %d, kNotHash: %d\n",
           double (t-s)/CLOCKS_PER_SEC*1000, kRecur, kBackUp, kMove, kHash, kNotHash);

    return 0;
}
