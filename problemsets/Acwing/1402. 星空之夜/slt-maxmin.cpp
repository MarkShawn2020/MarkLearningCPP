//
// Created by 南川 on 2021/1/28.
//

#include "fstream"
#include "iostream"
#include "vector"
#include "cstring"

using namespace std;

template <typename T>
void run(T &);

const int N = 100 + 2;

static char dta[N][N];
static bool vis[N][N];

int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    // read from local case if possible, otherwise from console
    ifstream fin("../Acwing/1402. 星空之夜/case1.txt");
    run(fin.good() ? fin : cin);
}

class Group{
public:
    char id = 'a';
    int x{}, y{}, count{}, min_i{}, max_i{}, min_j{}, max_j{}, h{}, w{};
    vector<vector<bool>> arr{};
    vector<pair<int, int>> points{};

    explicit Group(int x, int y): count(0), x(x), y(y), min_i(0), max_i(0), min_j(0), max_j(0), h(1), w(1){};

    void create()   // 高始终比宽要小
    {
        bool SWAP = false;
        h = max_i - min_i + 1;
        w = max_j - min_j + 1;
        if(h > w) SWAP = true, swap(h, w);
        arr.resize(h, vector<bool>(w, false));
        for(auto & point : points)
            if(!SWAP)
                arr[point.first - min_i][point.second - min_j] = true;
            else
                arr[point.second - min_j][point.first - min_i] = true;
    }
};

void traverse(Group & g, const int x, const int y, int i, int j)
{
    vis[x+i][y+j] = true;
    g.count++;
    g.max_i = max(g.max_i, i);
    g.max_j = max(g.max_j, j);
    g.min_i = min(g.min_i, i);
    g.min_j = min(g.min_j, j);
    g.points.emplace_back(i, j);
    for(int k=0; k<8; k++)
        if(!vis[x+i+dx[k]][y+j+dy[k]] && dta[x + i + dx[k]][y + j + dy[k]] == '1')
            traverse(g, x, y, i+dx[k], j+dy[k]);
}

bool comp(Group & g1, Group & g2, int di, int dj)
{
    int w = g1.w, h = g1.h;
    for(int i=0; i<h; i++)
        for(int j=0; j<w; j++)
            switch (di + dj) {
                case 3:
                    if(g1.arr[i][j] != g2.arr[i][j]) return false;
                    break;
                case 1:
                    if(g1.arr[i][j] != g2.arr[i][w - j - 1]) return false;
                    break;
                case -1:
                    if(g1.arr[i][j] != g2.arr[h - i - 1][j]) return false;
                    break;
                case -3:
                    if(g1.arr[i][j] != g2.arr[h - i - 1][w - j - 1]) return false;
                    break;
            }
    return true;
}

bool operator == (Group & g1, Group & g2)
{
    // 总数相等
    if(g1.count != g2.count) return false;

    // 横宽对应（已保证h<=w）
    if(g1.h != g2.h || g1.w != g2.w) return false;

    // 遍历对应
    if(comp(g1, g2, 1, 2)) return true;
    if(comp(g1, g2, 1, -2)) return true;
    if(comp(g1, g2, -1, 2)) return true;
    if(comp(g1, g2, -1, -2)) return true;
    return false;
}

bool operator != (Group & g1, Group & g2)
{
    return !(g1 == g2);
}

void set_id(vector<Group> & gs, Group & g)
{
    int i = 0;
    for(; i<gs.size() && gs[i] != g; i++);
    g.id = (char)('a' + i);
    if(i == gs.size())
        gs.emplace_back(g);
}

template <typename T>
void run(T & cin)
{
    int W, H;
    cin >> W >> H;
    for(int i=1; i<=H; i++)
        for(int j=1; j<=W; j++)
            cin >> dta[i][j];

    memset(vis, 0, sizeof vis);
    vector<Group> gs;
    for(int i=1; i<=H; i++)
        for(int j=1; j<=W; j++)
            if(!vis[i][j] && dta[i][j] == '1')
            {
                Group g(i, j);
                traverse(g, i, j, 0, 0);
                g.create();

                // set id
                set_g_id(gs, g);

                // modify arr
                for(auto & point: g.points)
                    dta[g.x + point.first][g.y + point.second] = g.id;

            }
    for(int i=1; i<=H; i++){
        for(int j=1; j<=W; j++)
            cout << dta[i][j];
        cout << endl;
    }

}