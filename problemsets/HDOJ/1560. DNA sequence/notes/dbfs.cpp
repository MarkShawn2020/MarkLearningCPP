//
// Created by 南川 on 2021/2/16.
//

//
// Created by 南川 on 2021/2/16.
//

//
// Created by 南川 on 2021/2/15.
//

#include "cstdio"
#include "ctime"
#include "cstring"
#include "queue"
#include "array"
using namespace std;

//#define printf(...) true


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
int ans;
short step;
int nSeqs;                      // 输入串数
char seqs[N_SEQS][N_LENS];      // 输入信息
int lens[N_SEQS];

const int SPACES = 6 * 6 * 6 * 6 * 6 * 6 * 6 * 6;
short hisL[SPACES], hisR[SPACES];
array<int, N_SEQS> posL, posR;
queue<array<int, N_SEQS>> QL, QR;

inline int & encode(int i, int j) {return dict[seqs[i][j] - 'A'];}

void update(const array<int, N_SEQS> & p1, array<int, N_SEQS> & p2, short his[], int k, const bool & toRight)
{
//    printf("update, k: %d\n", k);
    if(k == nSeqs) {
        int key = 0;
        for(int i=0, base=1; i<nSeqs; ++i, base *= 6)
            key += p2[i] * base;
        his[key] = his[key] ? (step < his[key] ? step : his[key]) : step;
        return;
    }
    else if(p1[k] == p2[k]) update(p1, p2, his, k+1, toRight);
    else {
        update(p1, p2, his, k+1, toRight);
        toRight ? --p2[k] : ++p2[k];
        update(p1, p2, his, k+1, toRight);
        toRight ? ++p2[k] : --p2[k];
    }
}

int checkFinish(const array<int, N_SEQS> & p2, const bool & toRight)
{
    int key = 0;
    for(int i=0, base=1; i<nSeqs; ++i, base*=6)
        key += (toRight ? p2[i]-1 : p2[i]+1) * base;
    if(toRight && hisR[key])
        return step + hisR[key];
    if(!toRight && hisL[key])
        return step + hisL[key];
    return 0;
}

bool handle(queue<array<int, N_SEQS>> & Q, const bool & toRight)
{
    int size = Q.size();
//    printf("QSize: %d, toRight: %d\n", size, toRight);
    for(int i=0; i < size; ++i)
    {
        const auto & p = Q.front();
//        printf("p : ");for(int u=0; u<N_SEQS; ++u) printf("%d ", p[u]);printf("\n");

        for(int j=0; j<4; ++j)
        {
            int changed = 0;
            array<int, N_SEQS> p2(p);
            for(int k=0; k<nSeqs; ++k)
                if(p2[k] >= 0 && p2[k] < lens[k] && encode(k, p2[k]) == j)
                    ++changed, toRight ? ++p2[k] : --p2[k];
            if(changed)
            {
//                printf("p2: ");for(int u=0; u<N_SEQS; ++u) printf("%d ", p2[u]);printf("\n");

                ans =checkFinish(p2, toRight);
                if(ans) return true;
                update(p, p2, toRight ? hisL : hisR, 0, toRight);
                Q.push(p2);
            }
        }
        Q.pop();
    }
    return false;
}

/**
 * 求解每个case的框架函数
 */
void solveCase()
{
    ans = 0;
    step = 1;
    memset(hisL, 0, sizeof hisL);
    memset(hisR, 0, sizeof hisR);
    posL = array<int, N_SEQS> {0};
    posR = array<int, N_SEQS> {0};
    scanf("%d", &nSeqs);
    for(int i=0; i<nSeqs; i++)
    {
        scanf("%s", seqs[i]);
        lens[i] = strlen(seqs[i]);                  // 记录每个字符串长度
        posR[i] = lens[i] - 1;
    }
    QL.push(posL);
    QR.push(posR);
    while (true)
    {
//        printf(">>> step: %d\n", step);
        if(!handle(QL, true) && !handle(QR, false))
            ++step;
        else
            break;
    }
    while (!QL.empty()) QL.pop();
    while (!QR.empty()) QR.pop();
    printf("%d\n", ans);
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
    fprintf(stdout, "time: %.4f\n", double (t-s)/CLOCKS_PER_SEC*1000);

    return 0;
}
