//
// Created by 南川 on 2021/2/17.
//
#include "ctime"
#include "cstdio"
#include "cstring"
using namespace std;

/**
 * for global
 */
const int N_SEQS = 8 + 1;           // 每个测例最大的串数
const int N_LENS = 5 + 1;           // 每串最大长度
int nCases;                     // 测例数

const int dict[20] = {          // 字符转数字
        0, 0, 1, 0, 0, 0, 2,    // A, C, G
        0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 3        // T
};

int adj[4][4];

bool isConnected(int s, int t)
{
    if(adj[s][t]) return true;
    for(int k=0; k<4; k++)
        if(adj[s][k] && s != k)
        {
            if(adj[k][t]) return true;
            for(int u=0; u<4; u++)
                if(adj[k][u] && u != k &&adj[u][t]) return true;
        }
    return false;
}

void initRow(const int row[N_LENS], int L, int & minAns)
{
    // 统计每个字符串内出现的最大频次
    int freq[4] = {0, 0, 0, 0};
    for(int i=0; i<L; i++)
        ++freq[row[i]];
    for(int i=0; i<4; i++)
        if(freq[i] > adj[i][i])
            adj[i][i] = freq[i];

    // 统计逆序对
    for(int i=0, j=1; j<L; i++, j++)
        if(!isConnected(row[i], row[j]))
            adj[row[i]][row[j]] = true,
            ++minAns;
}

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

/**
 * 深度递归过程中的状态信息，用于回溯
 */
struct State {
    int steps;
    int pos[N_SEQS];
    int freqs[4][N_SEQS];
    int nxtFreq[4];

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
    for(int id=0; id<4; ++id)                           // ACGT
    {
        if(!state.nxtFreq[id]) continue;                // 避免不必要的的备份
        ++kBackUp;
        State stateBack(state);                         // backup
        ++state.steps;
        for(int i=0; i<nSeqs; ++i)                      // 更新位置与频度
            if(state.pos[i] < lens[i] && seqs[i][state.pos[i]] == id)
            {
                --state.freqs[id][i];
                --state.nxtFreq[id];
                if(++state.pos[i] < lens[i])
                    ++state.nxtFreq[seqs[i][state.pos[i]]];
            }
        const int surplus = state.getSurplus();             // 检测
        if(state.steps + surplus > minAns) state = stateBack;                              // rollback
        else if(!surplus || recurSolve()) return true;
        state = stateBack;
    }
    return false;
}

/**
 * 求解每个case的框架函数
 */
void solveCase()
{
    minAns = 0;
    memset(adj, 0, sizeof adj);
    state = State{};                                    // reset state
    scanf("%d", &nSeqs);
    char seq[N_LENS];
    for(int i=0; i<nSeqs; i++)
    {
        scanf("%s", seq);
        lens[i] = strlen(seq);                          // 记录每个字符串长度
        ++state.nxtFreq[dict[seq[0] - 'A']];
        for(int j=0; j<lens[i]; j++)
        {
            const int & id = dict[seq[j] - 'A'];        // 将字符串转为数字存储
            ++state.freqs[id][i];
            seqs[i][j] = id;
        }
        initRow(seqs[i], lens[i], minAns);                  // 统计序列对
    }
    for(int i=0; i<4; i++)
        minAns += adj[i][i] - 1;
//    printf("start minAns: %d\n", minAns);
    while (!recurSolve()) ++minAns;               // 当无解时，迭代加深
    printf("%d\n", minAns);
}

/**
 * 求解全部case的框架函数
 */
int main()
{
//    freopen("/Users/mark/MarkLearningCPP/HDOJ/1560. DNA sequence/case4.txt", "r", stdin);
//    auto s = clock();

    scanf("%d", &nCases);
    while (nCases--) solveCase();

//    auto t = clock();
//    printf("time: %.4f, kRecur: %d, kBackUp: %d, kCalc: %d\n",
//           double (t-s)/CLOCKS_PER_SEC*1000, kRecur, kBackUp, kCalc);
//
    return 0;
}
