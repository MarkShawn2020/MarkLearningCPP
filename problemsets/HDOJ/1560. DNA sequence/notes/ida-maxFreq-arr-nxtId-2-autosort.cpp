//
// Created by 南川 on 2021/2/17.
//
#include "ctime"
#include "cstdio"
#include "cstring"
#include "queue"
using namespace std;

/**
 * for global
 */
const int N_SEQS = 8 + 1;           // 每个测例最大的串数
const int N_LENS = 5 + 1;           // 每串最大长度
int nCases;                     // 测例数

const int dict[20] = {          // 字符转数字
        1, 0, 2, 0, 0, 0, 3,    // A, C, G
        0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 4        // T
};


/**
 * for each case
 */
int nSeqs;                      // 输入串数
int seqs[N_SEQS][N_LENS];       // 每个串的压缩存储
int lens[N_SEQS];               // 每个串的长度
int minAns;

/**
 * calculus
 */
int kRecur, kBackUp, kCalc;

struct AutoSortFreq {
    int val[4 + 2]{};
    int key[4 + 2]{};
    int num = 0;

    AutoSortFreq(){
        val[0] = 40;
        val[5] = -1;
        for(int i=1; i<=4; i++)
            key[i] = i;
    }

    void incKey(int id) {
        int k = 1;
        while (key[k] != id) ++k;
        int tempV = ++val[k];
        if(tempV == 1) ++num;
        while (tempV > val[k-1])
            val[k] = val[k-1],
            key[k] = key[k-1],
            --k;
        val[k] = tempV;
        key[k] = id;
    }

    void decKey(int id) {
        int k = 1;
        while (key[k] != id) ++k;
        int tempV = --val[k];
        if(tempV == 0) --num;
        while (tempV < val[k+1])
            val[k] = val[k+1],
            key[k] = key[k+1],
            ++k;
        val[k] = tempV;
        key[k] = id;
    }
};


/**
 * 深度递归过程中的状态信息，用于回溯
 */
struct State {
    int steps;
    int pos[N_SEQS];
    int freqs[4 + 1][N_SEQS];
    AutoSortFreq asf;

    inline int getSurplus() {
        int ans = 0;
        for(auto & row : freqs)
        {
            int cur = 0;
            for(int i=0; i<nSeqs; ++i)
                if(row[i] > cur)
                    cur = row[i];
            ans += cur;
        }
        return ans;
    }
}state;

/**
 * 【主函数】每个case的递归求解
 */
bool recurSolve()
{
//    printf("minAns: %d, steps: %d\n", minAns, state.steps);
    ++kRecur;
    for(int u=1; u<=state.asf.num; u++)
    {
        const int & id = state.asf.key[u];
        ++kBackUp;
        State stateBack(state);                         // backup
        ++state.steps;
        for(int i=0; i<nSeqs; ++i)                      // 更新位置与频度
            if(seqs[i][state.pos[i]] == id)             // pos越界为0
            {
                --state.freqs[id][i];
                state.asf.decKey(id);
                if(++state.pos[i] < lens[i])
                    state.asf.incKey(seqs[i][state.pos[i]]);
            }
        const int surplus = state.getSurplus();             // 检测
        if(state.steps + surplus > minAns) state = stateBack; // rollback
        else if(!surplus || recurSolve()) return true;
        else state = stateBack;
    }
    return false;
}

/**
 * 求解每个case的框架函数
 */
void solveCase()
{
    minAns = 0;
    state = State{};                                    // reset state
    scanf("%d", &nSeqs);
    char seq[N_LENS];
    for(int i=0; i<nSeqs; i++)
    {
        scanf("%s", seq);
        lens[i] = strlen(seq);                          // 记录每个字符串长度
        state.asf.incKey(dict[seq[0]-'A']);
        for(int j=0; j<lens[i]; j++)
        {
            const int & id = dict[seq[j] - 'A'];        // 将字符串转为数字存储
            ++state.freqs[id][i];
            seqs[i][j] = id;
        }
    }
    minAns = state.getSurplus();
    while (!recurSolve()) ++minAns;               // 当无解时，迭代加深
    printf("%d\n", minAns);
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
    printf("time: %.4f, kRecur: %d, kBackUp: %d, kCalc: %d\n",
           double (t-s)/CLOCKS_PER_SEC*1000, kRecur, kBackUp, kCalc);

    return 0;
}
