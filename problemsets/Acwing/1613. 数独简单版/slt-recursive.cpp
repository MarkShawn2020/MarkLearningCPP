#include "iostream"
#include "fstream"
#include "cstdio"
#include "string"
#include "array"
#include "tuple"

using namespace std;

const int N = 9;
string raw[N];
bool row[10][10], col[10][10], grid[10][10];
int epoch = 0;


inline int gridId(int i, int j) {return i/3*3 + j/3 + 1;}

void printRaw(bool toAnswer = true, int x=0, int y=0)
{
    for(int i=0; i<N; i++)
        if(toAnswer)
            cout << raw[i] << endl;
        else if(x-1 != i)
            for(int j=0; j<N; j++)
                cout << " " << raw[i][j] << (j==N-1 ? "\n" : " ");
        else
        {
            for(int j=0; j<N; j++)
                if(j+1 == y)
                    cout << "[" << raw[i][j] << "]";
                else
                    cout << " " << raw[i][j] << " ";
            cout << endl;
        }
    if(!toAnswer) cout << endl;
}


pair<int, int> iter_next()
{
    int next_x=0, next_y=0, min_todo = 9;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
        {
            if(raw[i][j] != '.') continue;  // no need to fill again

            int todo = 9;
            for(int u=1; u<=9; u++)
                todo -= row[i+1][u] | col[j+1][u] | grid[gridId(i, j)][u];
            
            if(todo == 0)
                return make_pair(-1, -1);

            if(todo < min_todo)
                min_todo = todo,
                next_x = i+1,
                next_y = j+1;
        }
    return make_pair(next_x, next_y);
}


bool dfs()
{
    int x, y;
    tie(x, y) = iter_next();
    if(x == -1 && y == -1)  // backtrak
        return false;
    if(x== 0 && y == 0)     // success
        return true;

    for(int u=1; u<=N; u++)
        if(!row[x][u] && !col[y][u] && !grid[gridId(x-1, y-1)][u])
        {
            // handle
            raw[x-1][y-1] = '0' + u;
            row[x][u] = col[y][u] = grid[gridId(x-1, y-1)][u] = true;
            // cout << "Epoch: " << ++epoch << endl;
            // printRaw(false, x, y);

            // recursive
            if(dfs()) return true;

            // backtrack
            raw[x-1][y-1] = '.';
            row[x][u] = col[y][u] = grid[gridId(x-1, y-1)][u] = false;
            // cout << "---  BACKTRACK!  ---" << endl;
            // printRaw(false, x, y);
        }
    return false;
}


/**
 * init row, col, grid
 */
void init()
{
    int v;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            if(raw[i][j] != '.' && 0 < (v = raw[i][j] - '0'))
                row[i+1][v] = col[j+1][v] = grid[gridId(i, j)][v] = true;
}
 
int main()
{
    // input
    ifstream cin("/Users/mark/MarkLearningCPP/Acwing/1613. 数独简单版/case4.txt");
    for(auto & i : raw) cin >> i;
        
    // printRaw(false);
    
    init();

    dfs();
    
    printRaw(true);
}