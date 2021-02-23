//
// Created by 南川 on 2021/2/15.
//

#include "cstdio"
#include "ctime"
#include "cstring"
using namespace std;

/**
 * for global
 */
const int N_SEQS = 8;           // 每个测例最大的串数
const int N_LENS = 5;           // 每串最大长度
int nCases;                     // 测例数

/**
 * for each case
 */
int nSeqs;                      // 输入串数
int seqs[N_SEQS][N_LENS];       // 每个串的压缩存储
int lens[N_SEQS];               // 每个串的长度
int minAns;                     // 记录答案

/**
 * 将输入的字符快速转化为数字的函数
 * A: 0
 * C: 1
 * G: 2
 * T: 3
 */
inline int ch2int(char ch)
{
    int val = ch - '?';
    int ind = -1;
    while (val >>= 1)
        ++ind;
    return ind;
}

/**
 * 深度递归过程中的状态信息，用于回溯
 */
struct State {
    int steps;
    int pos[N_SEQS];
    int freq[4][N_SEQS];

    int checkSurplus()
    {
        int surplus = 0;
        for(auto & row : freq)
        {
            int idStep = 0;
            for(int i=0; i<nSeqs; ++i)
                if(row[i] > idStep)
                    idStep = row[i];
            surplus += idStep;
        }
        return surplus;
    }
} state;

/**
 * 【主函数】每个case的递归求解
 */
bool recurSolve()
{
    int surplus = state.surplusSteps();
//    printf("minAns: %d, steps: %d, surplus: %d\n", minAns, state.steps, surplus);
    if(!surplus) return true;                           // 完成
    if(state.steps + surplus > minAns) return false;    // 剪枝

    for(int id=0; id<4; ++id)                           // ACGT
    {
        int changed = 0;                                // 标记是否变动
        State stateBack(state);                         // backup
        for(int i=0; i<nSeqs; ++i)
            if(state.pos[i] < lens[i] && seqs[i][state.pos[i]] == id)
            {
                ++changed;
                ++state.pos[i];
                --state.freq[id][i];
            }
        if(!changed) continue;                          // 没有字符匹配
        ++state.steps;                                  // 更新步数
        if(recurSolve()) return true;                        // 深递归
        state = stateBack;                              // rollback
    }
    return false;
}

/**
 * 求解每个case的框架函数
 */
void solveCase()
{
    minAns = 0;                                            // reset ans
    state = State{};                                       // reset state
    scanf("%d", &nSeqs);
    char seq[N_LENS];
    for(int i=0; i<nSeqs; i++)
    {
        scanf("%s", seq);
        lens[i] = strlen(seq);                              // 记录每个字符串长度
        for(int j=0; j<lens[i]; j++)
        {
            const int & id = ch2int(seq[j]);                // 将字符串转为数字存储
            ++state.freq[id][i];
            seqs[i][j] = id;
        }
    }
    minAns = state.surplusSteps();                          // 初始迭代层数
    while (!recurSolve())
        ++minAns;                                           // 当无解时，迭代加深
    printf("%d\n", minAns);
}

/**
 * 求解全部case的框架函数
 */
int main()
{
    freopen("/Users/mark/MarkLearningCPP/HDOJ/1560. DNA sequence/case1.txt", "r", stdin);

    auto s = clock();

    scanf("%d", &nCases);
    while (nCases--) solveCase();

    auto t = clock();
    printf("time: %.4f", double (t-s)/CLOCKS_PER_SEC*1000);

    return 0;
}
