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
 * for each case
 */
class SolveCase {
private:
    int nSeqs;                      // 输入串数
    int seqs[N_SEQS][N_LENS];       // 每个串的压缩存储
    int lens[N_SEQS];               // 每个串的长度
    int minAns;                     // 记录答案

    struct State {
        int steps;
        int pos[N_SEQS];
        int freq[4][N_SEQS];
    };

    int surplusSteps(State & s) const
    {
         int surplus = 0;
         for(auto & row : s.freq)
         {
             int idStep = 0;
             for(int i=0; i< nSeqs; ++i)
                 if(row[i] > idStep)
                     idStep = row[i];
             surplus += idStep;
         }
         return surplus;
    }

bool recurSolve(State & state)
{
    int surplus = surplusSteps(state);
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
         if(recurSolve(state)) return true;                        // 深递归
         state = stateBack;                              // rollback
    }
    return false;
}

public:
void solveCase()
{
    minAns = 0;                                            // reset ans
    State state = State{};                                       // reset state
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
    minAns = surplusSteps(state);                          // 初始迭代层数
    while (!recurSolve(state))
        ++minAns;                                           // 当无解时，迭代加深
    printf("%d\n", minAns);
}
};



/**
 * 求解全部case的框架函数
 */
int main()
{
    freopen("/Users/mark/MarkLearningCPP/HDOJ/1560. DNA sequence/case1.txt", "r", stdin);

    auto s = clock();

    int nCases;                     // 测例数
    scanf("%d", &nCases);
    while (nCases--)
    {
        SolveCase sc{};
        sc.solveCase();
    }

    auto t = clock();
    printf("time: %.4f", double (t-s)/CLOCKS_PER_SEC*1000);

    return 0;
}
