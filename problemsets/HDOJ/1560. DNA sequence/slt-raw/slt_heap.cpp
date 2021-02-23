//
// Created by 南川 on 2021/2/15.
//

#include "cstdio"
#include "queue"
#include "ctime"
#include "cstring"
using namespace std;

const int MAX_SEQS = 8 + 1;
const int MAX_LENS = 5 + 1;
int nCases, nSeqs, todo;
char seqs[MAX_SEQS][MAX_LENS];
int lens[MAX_SEQS];
char chars[4] = {'A', 'C', 'G', 'T'};

struct Item{
    int todo;
    int len;
    int pos[MAX_SEQS];
};
queue<Item> Q;

void print_item(Item & cur)
{
    printf("todo: %d, len: %d, pos: ", cur.todo, cur.len);
    for(auto i: cur.pos) printf("%d ", i);
    printf("\n");
}

bool step()
{
    Item & cur = Q.front();
//    print_item(cur);
    for(const char & ch: chars)
    {
        Item nxt(cur);
        ++nxt.len;
        for(int i=0; i<nSeqs; i++)
            if(cur.pos[i] < lens[i] && ch == seqs[i][cur.pos[i]])
                if(++nxt.pos[i] && --nxt.todo == 0)
                    return printf("%d\n", nxt.len);
        Q.push(nxt);
    }
    Q.pop();
    return false;
}

void solveCase()
{
    todo = 0;                   // reset
    while (!Q.empty()) Q.pop(); // reset
    scanf("%d", &nSeqs);
    for(int i=0; i<nSeqs; i++)
        scanf("%s", seqs[i]),
        lens[i] = strlen(seqs[i]),
        todo += lens[i];
    Q.push({todo});
    while (!step());
}


int main()
{
    freopen("/Users/mark/MarkLearningCPP/HDOJ/1560. DNA sequence/case1.txt", "r", stdin);

    auto s = clock();

    scanf("%d", &nCases);
    while (nCases--) solveCase();

    auto t = clock();
    printf("time: %.4f", double (t-s)/CLOCKS_PER_SEC*1000);
}
