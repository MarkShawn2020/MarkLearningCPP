//
// Created by 南川 on 2021/2/21.
//
#include "vector"
#include "algorithm"
#include "iostream"
#include "stack"
#include "iomanip"
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
    vector<int> ans;
    bool targets[51][51];
    stack<int> st[51];
    vector<int> adj[10001];
    int depth[10001];

    void dfs(vector<int> & nums, int u) {
        int val = -1;
//        printf("u: %2d, num: %2d, ", u, nums[u]);
        for(int i=1; i<=50; ++i)
            if(targets[nums[u]][i] && !st[i].empty())
            {
                if(val == -1) val = st[i].top();
                else if(depth[st[i].top()] > depth[val]) val = st[i].top();
//                printf("i: %2d, val: %2d, st[i].top: %2d, ", i, val, st[i].top());}
        ans[u] = val;
//        printf("ans[u]: %2d\n", ans[u]);
        st[nums[u]].push(u);
        for(auto & v: adj[u])
            dfs(nums, v);
        st[nums[u]].pop();
    }


public:
    vector<int> getCoprimes(vector<int>& nums, vector<vector<int>>& edges) {
        const int N = nums.size();
        ans.resize(N);
        // build gcd matrix
        for(int i=1; i<=50; i++)
            for(int j=1; j<=50; j++)
                targets[i][j] = __gcd(i, j) == 1;
        // build tree
        vector<int> vis(N); vis[0] = 1;
        for(auto & edge: edges)
        {
            auto & x = edge[0], y = edge[1];
            if(!vis[x]) swap(x, y);
            adj[x].push_back(y);
            depth[y] = depth[x] + 1;
            vis[y] = true;
        }

        dfs(nums, 0);
        return ans;
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
    cout << nums << "(Raw)" << endl;
    cout << ans << " (My Ans)" << endl;
    cout << readIntVector1D(s3) << " (Standard Ans)";
}