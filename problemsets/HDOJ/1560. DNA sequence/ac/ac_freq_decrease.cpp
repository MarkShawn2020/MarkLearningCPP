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
int nChars;                     // 所有字符总数
int chances;                    // 消除每类字符的失败机会
int minAns;                     // 不断加深递归的答案

/**
 * 深度递归过程中的状态信息，用于回溯
 */
struct State {
    int done;           // 已合并的字符个数
    int chances;        // 一次不能消去一个字符种类的犯错次数
    int pos[N_SEQS];    // 当前遍历的位置
    int freq[4];        // 每个字符种类剩余的频次
} state;


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
 * 【主函数】每个case的递归求解
 */
bool recurSolve()
{
//    printf("minAns: %d, steps: %d, surplus: %d\n", minAns, state.steps, surplus);
    if(state.done == nChars) return true;               // 完成
    if(state.chances < 0) return false;                 // 剪枝

    for(int id=0; id<4; ++id)                           // A、C、G、T
    {
        int changed = 0;                                // 标记是否变动
        State stateBack(state);                         // backup
        for(int i=0; i<nSeqs; ++i)
            if(state.pos[i] < lens[i] && seqs[i][state.pos[i]] == id)
            {
                ++changed;
                ++state.done;
                ++state.pos[i];
                --state.freq[id];
            }
        if(!changed) continue;                          // 没有字符匹配
        if(state.freq[id]) --state.chances;             // 没有消除完该字符种类
        if(recurSolve()) return true;                   // 深递归，成功则不用回滚
        state = stateBack;                              // rollback
    }
    return false;
}

/**
 * 求解每个case的框架函数
 */
void solveCase()
{
    nChars = chances = minAns = 0;                          // reset case
    state = State{};                                        // reset state
    scanf("%d", &nSeqs);
    char seq[N_LENS];
    for(int i=0; i<nSeqs; i++)
    {
        scanf("%s", seq);
        nChars += lens[i] = strlen(seq);                    // 记录每个字符串长度
        for(int j=0; j<lens[i]; j++)
        {
            const int & id = ch2int(seq[j]);                // 将字符串转为数字存储
            seqs[i][j] = id;
            if(++state.freq[id] == 1)                       // 更新每种字符频度
                ++minAns;                                   // 记录字符宗磊个数
        }
    }
    while (!recurSolve())                                   // 当无解时，迭代加深
        state.chances = ++chances,                          // 失败机会放宽一次
        ++minAns;                                           // 答案增大一步
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

    auto t = clocxk();
    printf("time: %.4f", double (t-s)/CLOCKS_PER_SEC*1000);

    return 0;
}
