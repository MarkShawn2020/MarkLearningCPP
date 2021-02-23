//
// Created by 南川 on 2021/1/13.
//

#ifndef MARKLEARNINGCPP_SOLUTION1_H
#define MARKLEARNINGCPP_SOLUTION1_H

#endif //MARKLEARNINGCPP_SOLUTION1_H


#include "vector"
using namespace std;

class Solution {
public:

    int Find(vector<int> & f, int i)
    {
        return f[i]==i ? i : f[i]=Find(f, f[i]);
    }

    bool Union(vector<int> & f, vector<int> & w, int i, int j)
    {
        int fi = Find(f, i);
        int fj = Find(f, j);
        if(fi == fj) return true;

        if(w[fi] > w[fj]) swap(fi, fj);
        f[fj] = fi;
        w[fi] += w[fj];

        return false;
    }

    vector<int> findRedundantConnection(vector<vector<int>>& edges)
    {
        int N = edges.size()+1;
        vector<int> f(N);
        vector<int> w(N, 1);
        for(int i=0; i<N; i++) f[i]=i;

        for(auto edge: edges)
            if(Union(f, w, edge[0], edge[1]))
                return edge;

        return vector<int>{};
    }
};