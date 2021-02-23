#include "iostream"
#include "fstream"
#include "cstdio"
#include "cstring"
#include "string"
#include "cassert"
#include "numeric"
#include "vector"
#include "array"

using namespace std;

const int N = 9;
string raw[N];
array<int, 20> adj;
int out[N][N][N+1];

/**
 * 不能用引用，由于递归涉及到多层调用，除非使用栈缓存，否则会混乱
 */
array<int, 20> traverse(int i, int j)
{
    int p = -1;
    for(int u = 0; u<9; u++)
        if(u != j)
            adj[++p] = i * 9 + u;

    for(int u = 0; u<9; u++)
        if(u != i)
            adj[++p] = u * 9 + j;

    for(int u1 = i-i%3; u1 < i-i%3+3; u1++)
        for(int u2 = j-j%3; u2 < j-j%3+3; u2++)
            if(u1 != i && u2 != j)
                adj[++p] = u1 * 9 + u2;
    return adj;
}

void dfs(int, int);

void goDfs(int i, int j, int v)
{
    // printf("[go dfs] i: %d, j: %d, v: %d \n", i, j, v);
    
    if(raw[i][j] == '.' && !out[i][j][v])
        if(++out[i][j][v] && --out[i][j][0] == 1)
            dfs(i, j);
}

void exclude(int i, int j, int v)
{
    if(!out[i][j][v])
        ++out[i][j][v],
        --out[i][j][0];
}


/**
 * 只有在out[i][j][0] == 1的情况下才会进入此函数
 */
void dfs(int i, int j)
{   

    assert(accumulate(out[i][j]+1, out[i][j]+10, 0) == 8);
    // if(i == 1 && j == 2)
    if(i == 1 && j == 0)
    {}

    int v = 1;
    while(out[i][j][v]) v++;    // fetch the value of v
    raw[i][j] = '0' + v;        // update * -> char
    ++out[i][j][v];
    --out[i][j][0]; 
    // printf("[dfs] i: %d, j: %d, v: %d \n", i, j, v);
    // printf("(%d, %d) ", i, j);

    
    for(auto & it: traverse(i, j))
        goDfs(it / 9, it % 9, v);
}

 
int main()
{
    ifstream cin("/Users/mark/MarkLearningCPP/Acwing/1613. 数独简单版/case4.txt");
    memset(out, 0, sizeof out);
    for(int i=0; i<N; i++)
        cin >> raw[i];
        
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            cout << raw[i][j] << (j==N-1 ? "\n" : " ");
        
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            if(raw[i][j] == '.' && 0 < (out[i][j][0] = 9))
                for(auto it: traverse(i, j))
                    if(raw[it/9][it%9] != '.')
                        exclude(i, j, raw[it / 9][it % 9] - '0');
            
     for(int i=0; i< N; i++)
        for(int j=0; j<N; j++)
            if(out[i][j][0] == 1)
                dfs(i, j);
    
    for(int i=0; i<N; i++)
        cout << raw[i] << endl;
}