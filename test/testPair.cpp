//
// Created by 南川 on 2021/1/15.
//

#include "vector"
#include "iostream"

using namespace std;

pair<int, int> Find(vector<int> & f, vector<int> & g, int p){
    if(f[p] == p)
        return make_pair(f[p], g[p]);
    else{
        tie(f[p], g[p]) = Find(f, g, f[p]);
        return make_pair(f[p], g[p]);
    }
//    return f[p] == p ? make_pair(f[p], g[p]) : tie(f[p], g[p]) = Find(f, g, p);
}

int main(){
    vector<int> f = {1, 3, 5, 2, 4};
    vector<int> g = {2, 3, 4, 5, 1};
    int p = 3;
    pair<int, int> ans = Find(f, g, p);
    cout << ans.first << "\t" << ans.second << endl;
    return 0;
}