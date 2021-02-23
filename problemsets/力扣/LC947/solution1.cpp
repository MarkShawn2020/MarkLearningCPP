//
// Created by 南川 on 2021/1/15.
//

#include "vector"
#include "iostream"
#include "sstream"
#include "fstream"
using namespace std;

class Solution {
public:
    int Find(vector<int> & f, int p){
        if(f[p] == -1) f[p] = p;
        return f[p] == p ? p : f[p] = Find(f, f[p]);
    }

    int Move(vector<int> & f, int x, int y){
        int ret;
        bool xIsNew = f[x] == -1;
        bool yIsNew = f[y] == -1;
        int fx = Find(f, x);
        int fy = Find(f, y);
        if(xIsNew && yIsNew) ret = 1;
        else if(xIsNew || yIsNew || fx == fy) ret = 0;
        else ret = -1;
        f[fy] = fx;
        return ret;
    }

    int removeStones(vector<vector<int>>& stones) {
        int GridSize = 10e4;
        int stonesLength = stones.size();
        vector<int> f(2 * GridSize + 1, -1);

        int nGraphs = 0;
        for(auto stone: stones)
            nGraphs += Move(f, stone[0], stone[1]+GridSize);
        return stonesLength - nGraphs;
    }
};


int main(){
    string raw = "[[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]";
    stringstream ss;
    ss << raw;
//
//    ifstream ss("/Users/mark/CLionProjects/MarkLearningCPP/LC947/case1.txt");
    vector<int> ints;
    int a;
    while (!ss.eof()){
        if(ss>>a) ints.emplace_back(a);
        ss.clear();
        ss.get();
    }
    vector<vector<int>> inputVector;
    for(int i=0; i<ints.size(); i+=2)
        inputVector.emplace_back(vector<int>{ints[i], ints[i+1]});
    Solution slt;
    cout << slt.removeStones(inputVector) << endl;
    
}


//        cout << "xIsNew: " << xIsNew << ", yIsNew: " << yIsNew << ", xySame: " << xySame << endl;
//
//        cout
//                << "p: (" << p[0] << ',' << p[1] << ")"
//                << ", rows[" << p[0] << "]=(" << rows[p[0]][0] << "," << rows[p[0]][1] << ")"
//                << ", cols[" << p[1] << "]=(" << cols[p[1]][0] << "," << cols[p[1]][1] << ")"
//                << "." << endl;