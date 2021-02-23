//
// Created by 南川 on 2021/2/21.
//
//
#include "vector"
#include "algorithm"
#include "iostream"
#include "stack"
#include "iomanip"
#include "unordered_map"
#include "algorithm"
using namespace std;

template<typename A> ostream & operator << (ostream & cout, vector<A> const &v) {
    cout << "["; for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << setw(2) << v[i];} return cout << "]";
}

#include "sstream"
vector<int> readIntVector1D(string s)
{
    vector<int> ret;

    for(char & ch: s)
        if(!isdigit(ch) && ch!='-' && ch!='+')
            ch = ' ';

    std::stringstream ss;
    ss << s;
    int t;
    while (ss >> t)
        ret.push_back(t);
    return ret;
}

vector<vector<int> > readIntVector2D(string s)
{
    vector<vector<int> > ret;

    for(int i=0; i<s.size()-2; i++)
        if(s[i]==']' && s[i+1]==',' && s[i+2]=='[')
            s[i+1] = ' ';

    stringstream ss;
    ss << s;
    while (ss >> s)
        ret.push_back(readIntVector1D(s));
    return ret;
}

class Solution {
    static const int N = 1e5;
    int Prime[51][51], Track[51], Depth[N + 1];     // ans support
    int Head[N + 1], EgTo[N + 1], EgNx[N + 1];      // chain pre star ds
    int vis[N + 1]{1};                              // build tree support

    void dfs(vector<int> & ans, vector<int> & nums, int u) {
        int depth = -1, node_id = -1;
        for(int i=1; i<=50; ++i)
            if(Prime[nums[u]][i] && Track[i] && Depth[Track[i]-1] > depth)
                depth = Depth[node_id = Track[i] - 1];
        ans[u] = node_id;                   // save ans
        printf("u: %2d, num: %2d, depth: %2d, node_id: %2d, ans: %2d\n" , u, nums[u], depth, node_id, ans[u]);
        int record = Track[nums[u]];        // backup
        Track[nums[u]] = u + 1;             // update dict
        for(int v = Head[u]; ~v; v = EgNx[v])
            dfs(ans, nums, EgTo[v]);
        Track[nums[u]] = record;            // rollback dict
    }
public:
    vector<int> getCoprimes(vector<int>& nums, vector<vector<int>>& edges) {
        const int n = nums.size();
        for(int i=0; i<n; ++i) Head[i] = -1;
        for(int i=1; i<=50; ++i) for(int j=1; j<=50; ++j) Prime[i][j] = __gcd(i, j) == 1;
        for(int i=0; i<edges.size(); ++i) {
            int & x = edges[i][0], & y = edges[i][1];
            if(!vis[x]) x ^= y ^= x ^= y; ++vis[y];         // after swap, x is always y's father
            Depth[y] = Depth[x]+1;                          // depth update
            EgTo[i] = y, EgNx[i] =  Head[x], Head[x] = i;   // pre star add edge
        }
        vector<int> ans(n); dfs(ans, nums, 0); return ans;
    }
};


int main()
{
    freopen("/Users/mark/MarkLearningCPP/力扣/5670. 互质树/case3.txt", "r", stdin);
    string s1, s2, s3;
    cin >> s1 >> s2 >> s3;
    vector<int> nums = readIntVector1D(s1);
    cout << "nums: " << nums << endl;
    vector<vector<int>> edges = readIntVector2D(s2);
    cout << "edges: ";
    for(auto & edge: edges) cout << edge << " ";
    cout << endl;

    Solution slt;
    vector<int> ans = slt.getCoprimes(nums, edges);
    vector<int> ids(nums.size()); for(int i=0; i<nums.size(); ++i) ids[i] = i;
    cout << ids << endl;
    cout << nums << " (Raw)" << endl;
    cout << ans << " (My Ans)" << endl;
    cout << readIntVector1D(s3) << " (Standard Ans)";
}