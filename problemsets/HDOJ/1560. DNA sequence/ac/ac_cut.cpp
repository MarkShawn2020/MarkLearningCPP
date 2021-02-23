//
// Created by 南川 on 2021/2/15.
// (39条消息) HDU1560 DNA sequence IDA* + 强力剪枝 [kuangbin带你飞]专题二_flyawayl的博客-CSDN博客 - https://blog.csdn.net/flyawayl/article/details/55667822
//

#include<cstdio>
#include<cstring>
#include<algorithm>
#include "ctime"
using namespace std;

const int MAX_SEQS = 8 + 1;     // 每个测例，最大的序列数
const int MAX_LENS = 5 + 1;     // 每个序列，最大的长度
int seqs[MAX_SEQS][MAX_LENS];   // 存储每个序列，并转化为0-3
int lens[MAX_SEQS];             // 每个序列的长度
int nCases, nSeqs;              // T个测例，每个测例n个序列， 1 <= n <= 8
int depth;                      // 每个测例iddfs中的深度
int pos[MAX_SEQS];              // 每个序列已经匹配完成"指针"
int eachFreq[4], maxFreq[4];    // 用于cal计算每个字母的频度
int todo;                       // _todo: 最少待匹配数

void cal() {                    //至少还需要匹配的长度
    todo = 0;
    memset(maxFreq, 0, sizeof maxFreq);
    for(int i=0; i<nSeqs; i++)
    {
        memset(eachFreq, 0, sizeof eachFreq);
        for(int j=pos[i]; j<lens[i]; j++)
        {
            const int & id = seqs[i][j];
            if(++eachFreq[id] > maxFreq[id])
                ++maxFreq[id],
                ++todo;
        }
    }
}

bool dfs(int done) {
    cal();              // 计算剩余最少匹配次数
//    printf("done: %d, pos: %d, depth: %d\n", done, todo, depth);
    if(todo == 0) return printf("%d\n", depth);
    if(done + todo > depth) return false;

    int posBack[MAX_SEQS];  // 备份，必须在函数内部定义，外部会污染
    memcpy(posBack, pos, sizeof(posBack));
    for(int j = 0; j < 4; ++j) {
        int flag = 0;
        for(int i = 0; i < nSeqs; ++i)
            if(pos[i] < lens[i] && seqs[i][pos[i]] == j)
                flag = 1, ++pos[i];

        if(flag && dfs(done + 1)) return true;
        memcpy(pos, posBack, sizeof(posBack));  // rollback
    }
    return false;
}

void recurSolve()
{
    while (true)
    {
//        printf(">>> depth: %d\n", depth);
        if(dfs(0))
            break;
        else
            depth++;
    }
}


inline int ch2id(const char & ch) {
    switch (ch) {
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
        default: exit(-1);
    }
}

int main() {
    freopen("/Users/mark/MarkLearningCPP/HDOJ/1560. DNA sequence/case1.txt", "r", stdin);
    auto s = clock();


    scanf("%d", &nCases);
    char seq[MAX_LENS];
    while(nCases--) {
        depth = 0;
        memset(pos, 0, sizeof(pos));
        scanf("%d", &nSeqs);
        for(int i = 0; i < nSeqs; ++i) {
            scanf("%s", seq);
            lens[i] = strlen(seq);
            for(int j=0; j<lens[i]; ++j)
                seqs[i][j] = ch2id(seq[j]);
            depth = max(depth, lens[i]);
        }
        recurSolve();
    }

    auto t = clock();
    printf("time: %.4f", double (t-s)/CLOCKS_PER_SEC*1000);
}