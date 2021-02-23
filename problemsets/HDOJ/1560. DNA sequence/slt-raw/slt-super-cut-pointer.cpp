//
// Created by 南川 on 2021/2/15.
//

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
int dict[20];                   // char to int

/**
 * for each case
 */
int nSeqs;                      // 输入串数
char seq[N_LENS];               // temp
int seqs[N_SEQS][N_LENS];       // 每个串的压缩存储
int lens[N_SEQS];               // 每个串的长度
int minAns;                     // 记录答案

int kRecurSolve, kCopyStruct;


/**
 * 深度递归过程中的状态信息，用于回溯
 */
struct State {
    int steps;
    int * pos;
    int ** freq;

    State(): steps(0) {
        pos = new int [N_SEQS];
        freq = new int *[4];
        memset(pos, 0, sizeof (int) * N_SEQS);
        for(int id=0; id<4; ++id)
        {
            freq[id] = new int [N_SEQS];
            memset(freq[id], 0, sizeof (int) * N_SEQS);
        }
    }

    State(State & s) : steps(s.steps) {
        pos = new int [N_SEQS];
        freq = new int *[4];
        for(int id=0; id<4; ++id)
            freq[id] = new int [N_SEQS];
        memcpy(pos, s.pos, sizeof (int) * N_SEQS);
        memcpy(freq, s.freq, sizeof (int) * N_SEQS * 4);
    }

    ~State() {          // 已经被掏空
        delete pos;
        delete freq;
    }

    State & operator = (State s)  noexcept {
        steps = s.steps;
        pos = s.pos;
        freq = s.freq;
        s.pos = nullptr;
        s.freq = nullptr;
        return *this;
    }

    int checkSurplus() const
    {
        int surplus = 0;
        for(int id=0; id<4; ++id)
        {
            int idStep = 0;
            for(int i=0; i<nSeqs; ++i)
                if(freq[id][i] > idStep)
                    idStep = freq[id][i];
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
    ++kRecurSolve;
    const int & surplus = state.checkSurplus();
//    printf("minAns: %d, steps: %d, surplus: %d\n", minAns, state.steps, surplus);
    if(!surplus) return true;                           // 完成
    if(state.steps + surplus > minAns) return false;    // 剪枝

    for(int id=0; id<4; ++id)                           // ACGT
    {
        ++kCopyStruct;
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
        if(recurSolve(state)) return true;                   // 深递归
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
    minAns = state.checkSurplus();                          // 初始迭代层数
    while (!recurSolve(state))
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

    dict[ 0] = 0;   // 'A'
    dict[ 2] = 1;   // 'C'
    dict[ 6] = 2;   // 'G'
    dict[19] = 3;   // 'T'
    scanf("%d", &nCases);
    while (nCases--) solveCase();

    auto t = clock();
    printf("time: %.4f\n", double (t-s)/CLOCKS_PER_SEC*1000);
    printf("kRecurSolve: %d, kCopyStruct: %d\n", kRecurSolve, kCopyStruct);

    return 0;
}
