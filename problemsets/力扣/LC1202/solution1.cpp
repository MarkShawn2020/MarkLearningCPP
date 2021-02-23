//
// Created by 南川 on 2021/1/12.
//
#include "set"

class Solution {
public:

    int find(vector<int> & f, int x) {
        return f[x] == x ? x : f[x] = find(f, f[x]);
    }

    void unionSet(vector<int> & f, vector<int> & rank, int x, int y) {
        int fx = find(f, x), fy = find(f, y);
        if (fx == fy) return;
        if (rank[fx] < rank[fy]) swap(fx, fy);
        rank[fx] += rank[fy];
        f[fy] = fx;
    }

    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int N = s.size();
        vector<int> f(N), rank(N, 1);
        for(int i=0; i<N; i++) f[i] = i;
        for(auto& pair : pairs) unionSet(f, rank, pair[0], pair[1]);

        unordered_map<int, multiset<int, greater<int>> mp;
        for(int i=0; i<N; i++) mp[find(f, i)].insert(s[i]);
        for(int i=0; i<N; i++) {
            int x = find(f, i);
            s[i] = mp[x][mp[x].end()-rank[x]--];
        }

        return s;
    };
};
