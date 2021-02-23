//
// Created by 南川 on 2021/1/28.
//

#include "fstream"
#include "iostream"
#include "vector"
#include "cstring"
#include "unordered_map"

using namespace std;

const int N = 100 + 2;

char dta[N][N];     // data input -> output as well
bool vis[N][N];     // dfs visited

const int A = 11, B = 13, C = 17, D = 19;   // some prime nums for hash function

int dx[8] = {-1, -1, -1, 0, 1, 0, 1, 1};    // odd for A, even for B
int dy[8] = {-1, 0, 1, -1, -1, 1, 1, 0};

unordered_map<int, char> mp;    // G's hash -> alpha


class Group{
public:
    int maxX, maxY, minX, minY; // Graph's external rectangle for hash
    int count = 0, hash = 0;    // count is the num of points
    vector<int> xs{}, ys{};     // the sequence of points

    Group(int x, int y): maxX(x), minX(x), maxY(y), minY(y){}

    bool operator != (const Group & g2) const {
        if(this->count != g2.count) return true;
        return this->hash != g2.hash;
    }
};

void traverse(Group & g, const int x, const int y)
{
    vis[x][y] = true;
    g.count++;
    g.maxX = max(g.maxX, x), g.minX = min(g.minX, x);
    g.maxY = max(g.maxY, y), g.minY = min(g.minY, y);
    g.xs.emplace_back(x), g.ys.emplace_back(y);
    for(int k=0; k<8; k++)
        if(dta[x+dx[k]][y+dy[k]] == '1')
        {
            g.hash += k % 2 ? A : B;    // hash of adjacent points
            if(!vis[x+dx[k]][y+dy[k]])  // offset
                traverse(g, x+dx[k], y+dy[k]);
        }
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
    for(int x=1; x <= H; x++)
        for(int y=1; y <= W; y++)
            if(!vis[x][y] && dta[x][y] == '1')
            {
                Group g(x, y);

                traverse(g, x, y);              // dfs

                g.hash += g.count * C + (g.maxY-g.minY) * (g.maxX-g.minX) * D; // modify hash again [!important]

                if(mp.find(g.hash) == mp.end())     // set id
                    mp.insert({g.hash, 'a' + mp.size()});
                //  cout << "x: " << x << ", y: " << y << ", hash: " << g.hash << ", group: " << mp[g.hash] << endl;

                for(int k=0; k<g.count; k++)        // modify raw array(dta)
                    dta[g.xs[k]][g.ys[k]] = mp[g.hash];
            }

    for(int i=1; i<=H; i++){
        for(int j=1; j<=W; j++)
            cout << dta[i][j];
        cout << endl;
    }

}

int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    // read from local case if possible, otherwise from console
    ifstream fin("../Acwing/1402. 星空之夜/case4.txt");
    run(fin.good() ? fin : cin);
}
