//
// Created by 南川 on 2021/1/28.
//

#include "fstream"
#include "iostream"
#include "vector"
#include "queue"
#include "cstring"

using namespace std;

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

// -------------------------

const int N = 1e5;          // N is the size of input data
const int H = 21;           // (H)eights for the layers, max is (32-1-1=30), the first bit for +/-
const int K = 2;            // K is the choices of 0 / 1
const int Nodes = N * H;    // Nodes is the possible max
int nodes = 0;              // nodes is the real count
int dfa[Nodes][K] = {0};    // (N)odes for the max num of nodes
int ids[Nodes] = {0};       // mark node with id

int Left=0, Right=Nodes, Max=0;

void insert(int pos, int val)
{
    int id = 0;
    for(int i=H-1; i>-1; i--)
    {
        int k = val >> i & 1;
        if(!dfa[id][k])
            dfa[id][k] = ++nodes;
        id = dfa[id][k];
    }
    ids[id] = pos;
}

void getMaxXOR(int pos, int val)    // 贪心获取最大的异或值
{
    if(pos == 1) {Left = Right = 1, Max = val; return;}

    int id = 0, Sum = 0;
    for(int i=H-1; i>-1; i--)
    {
        int k = val >> i & 1;
        if(dfa[id][!k]) Sum += 1 << i, id = dfa[id][!k];
        else id = dfa[id][k];
    }
    if(Sum>Max || Sum==Max && (pos < Right || pos == Right && pos - ids[id] < Right - Left))
        Max = Sum, Left = ids[id], Right = pos;
    cout << "Sum: " << Sum << ", Left: " << ids[id] << ", Right: " << pos << endl;
}



template <typename T>
void run(T & cin)
{
    int n, v, temp = 0; 
    cin >> n;

    for(int i=1; i<=n; i++)
    {
        cin >> v;
        insert(i, temp ^= v);
        getMaxXOR(i, temp);  // 只与前面的前缀和比较，防止重复
    }

    cout << Max << " " << (Right>Left ? ++Left : Left) << " " << Right;
}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    // read from local case if possible, otherwise from console
    ifstream fin("/Users/mark/MarkLearningCPP/Acwing/1414. 牛异或/case4.txt");
    run(fin.good() ? fin : cin);
}

