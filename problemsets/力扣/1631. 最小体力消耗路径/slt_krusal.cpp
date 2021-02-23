//
// Created by 南川 on 2021/1/28.
//

#include "fstream"
#include "iostream"
#include "vector"
#include "queue"
#include "algorithm"
#include "cmath"
#include "/Users/mark/MarkLearningCPP/io/read_case.h"

using namespace std;


class Solution {
public:

    typedef pair<int, pair<int, int> > Pair;

    static void Show(const Pair & pair)
    {
        cout << pair.first << ": (" << pair.second.first << ", " << pair.second.second << ") " << endl;
    }

    static const int N = 100 * 4;

    int Find(int fa[], int x)
    {
        return x == fa[x] ? x : fa[x] = Find(fa, fa[x]);
    }

    void Union(int fa[], int x, int y)
    {
        x = Find(fa, x), y = Find(fa, y);
        if(x == y) return;
        fa[x] = y;
    }

    int minimumEffortPath(vector<vector<int> >& heights) {
        vector<Pair> dta; dta.reserve(N);
        int fa[N]; for(int i=0; i<N; i++) fa[i] = i;

        const int rows = heights.size();
        const int cols = heights[0].size();

        for(int i=0; i<rows; i++)
            for(int j=0; j<cols; j++)
            {
                if(j < cols-1)
                    dta.push_back(Pair(fabs(heights[i][j+1]-heights[i][j]), pair<int, int>(i*cols+j, i*cols+(j+1))));
                if(i < rows-1)
                    dta.push_back(Pair(fabs(heights[i+1][j]-heights[i][j]), pair<int, int>(i*cols+j, (i+1)*cols+j)));
            }
        sort(dta.begin(), dta.end());
        for_each(dta.begin(), dta.end(), Show);

        int ans = 0; 
        for(int i=0; i<N && Find(fa, 0) != Find(fa, rows*cols-1); ++i)
            Union(fa, dta[i].second.first, dta[i].second.second), ans = max(ans, dta[i].first);
        return ans;
    }
};

template <typename T>
void run(T & cin)
{
    string s;
    cin >> s;
    // vector<vector<int> > dta = readIntVector2D(s);
    // Solution slt;
    // cout << slt.minimumEffortPath(dta);
    vector<vector<int> > dta = readIntVector2D(s);
    Solution slt;
    cout << slt.minimumEffortPath(dta);

}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    // read from local case if possible, otherwise from console
    ifstream fin("/Users/mark/CLionProjects/MarkLearningCPP/力扣/1631. 最小体力消耗路径/case4.txt");
    run(fin.good() ? fin : cin);
}

