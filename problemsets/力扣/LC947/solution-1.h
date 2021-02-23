//
// Created by 南川 on 2021/1/15.
//

#ifndef MARKLEARNINGCPP_SOLUTION_1_H
#define MARKLEARNINGCPP_SOLUTION_1_H

#endif //MARKLEARNINGCPP_SOLUTION_1_H


class Solution {
public:
    vector<int> Find(vector<vector<int>> & f, vector<int> & p, int axis){
        return f[p[axis]][axis] == p[axis] ? f[p[axis]] : f[p[axis]] = Find(f, f[p[axis]], axis);
    }

    int Union(vector<vector<int>> & rows, vector<vector<int>> & cols,
              vector<int> & wRows, vector<int> & wCols, vector<int> p){
        // 祖先的恒定条件： rows[x][0] == x; cols[y][1] == y;
        if(rows[p[0]][0] == -1) rows[p[0]] = p;
        if(cols[p[1]][1] == -1) cols[p[1]] = p;
        vector<int> fx = Find(rows, p, 0);
        vector<int> fy = Find(cols, p, 1);

        if(fx == fy) {
            ++wRows[fx[0]]; ++wCols[fy[1]]; return p==fx;
        }
        if(p==fx) {
            ++wCols[fy[1]]; rows[fx[0]] = fy; return 0;
        }
        if(p==fy) {
            ++wRows[fx[1]]; cols[fy[1]] = fx; return 0;
        }
        if(wRows[fx[0]] > wCols[fy[1]]) swap(fx, fy);
        wCols[fy[1]] += wRows[fx[0]]; rows[fx[0]] = cols[fx[1]] = fy; return -1;
    }

    int removeStones(vector<vector<int>>& stones) {
        int GridSize = 10e4+1;
        int stonesLength = stones.size();
        vector<vector<int>> rows(GridSize, vector<int>(2, -1));
        vector<vector<int>> cols(GridSize, vector<int>(2, -1));
        vector<int> wRows(GridSize, 1);
        vector<int> wCols(GridSize, 1);
//        for(int i=0; i<GridSize; i++)
//            rows[i] = cols[i] = {i, i};

        int nGraphs = 0;
        for(auto stone: stones)
            nGraphs += Union(rows, cols, wRows, wCols, stone);
        return stonesLength - nGraphs;
    }
};
