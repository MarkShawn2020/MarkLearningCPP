//
// Created by 南川 on 2021/2/15.
//

//
// Created by 南川 on 2021/2/15.
//

#include "cstdio"
#include "cstring"
using namespace std;

/**
 * for global
 */
const int N_SEQS = 8;           // 每个测例最大的串数
const int N_LENS = 5;           // 每串最大长度
int nCases;                     // 测例数
int dict[20];                   // char to int

/**
 * for each case
 */
int nSeqs;                      // 输入串数
char seq[N_LENS];               // temp
int seqs[N_SEQS][N_LENS];       // 每个串的压缩存储
int lens[N_SEQS];               // 每个串的长度
int minAns;                     // 记录答案


/**
 * 深度递归过程中的状态信息，用于回溯
 */
struct State {
    int steps;
    int nxt[4]{};
    int pos[N_SEQS]{};
    int freq[4][N_SEQS]{};

    State(): steps(0) {
        for(auto & s : seqs)
            ++nxt[s[0]];
    }

    int checkSurplus() const
    {
        int surplus = 0;
        for(const auto & row : freq)
        {
            int idStep = 0;
            for(int i=0; i<nSeqs; ++i)
                if(row[i] > idStep)
                    idStep = row[i];
            surplus += idStep;
        }
        return surplus;
    }

};

/**
 * 【主函数】每个case的递归求解
 */
bool recurSolve(State & state)
{
    const int & surplus = state.checkSurplus();
    //    printf("minAns: %d, steps: %d, surplus: %d\n", minAns, state.steps, surplus);
    if(!surplus) return true;                           // 完成
    if(state.steps + surplus > minAns) return false;    // 剪枝

    for(int id=0; id<4; ++id)                           // ACGT
    {
        if(!state.nxt[id]) continue;                    // 判断是否需要改变（原122，288；现122，114）
        State stateBack(state);                         // backup
        for(int i=0; i<nSeqs; ++i)
            if(state.pos[i] < lens[i] && seqs[i][state.pos[i]] == id)
            {
                --state.nxt[id];
                if(++state.pos[i] < lens[i])
                    ++state.nxt[seqs[i][state.pos[i]]];
                --state.freq[id][i];
            }
        ++state.steps;                                  // 更新步数
        if(recurSolve(state)) return true;          // 深递归
        state = stateBack;                              // rollback
    }
    return false;
}

/**
 * 求解每个case的框架函数
 */
void solveCase()
{
    minAns = 0;                                         // reset ans
    State state{};                                      // reset state
    scanf("%d", &nSeqs);
    for(int i=0; i<nSeqs; i++)
    {
        scanf("%s", seq);
        lens[i] = strlen(seq);                          // 记录每个字符串长度
        for(int j=0; j<lens[i]; j++)
        {
            const int & id = dict[seq[j] - 'A'];        // 将字符串转为数字存储
            ++state.freq[id][i];
            seqs[i][j] = id;
        }
    }
    minAns = state.checkSurplus();                      // 初始迭代层数
    while (!recurSolve(state))
        ++minAns;                                       // 当无解时，迭代加深
    printf("%d\n", minAns);
}

/**
 * 求解全部case的框架函数
 */
int main()
{
    dict[ 0] = 0;   // 'A'
    dict[ 2] = 1;   // 'C'
    dict[ 6] = 2;   // 'G'
    dict[19] = 3;   // 'T'
    scanf("%d", &nCases);
    while (nCases--) solveCase();
    return 0;
}
