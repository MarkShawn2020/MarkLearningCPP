//
// Created by 南川 on 2021/1/18.
//
#include "vector"
#include "map"
#include "string"
#include "fstream"
#include "sstream"
#include "iostream"
using namespace std;

class Solution {
public:
    int Find(vector<int> & fa, int x){
        return fa[x] == x ? x : fa[x] = Find(fa, fa[x]);
    }

    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        const int N = accounts.size();

        map<string, int> mp;
        vector<int> fa(N);
        vector<vector<string>> ans(N);
        for(int i=0; i<N; ++i)
            ans[i].emplace_back(accounts[i][0]);

        for (int i = 0; i < N; ++i)
            fa[i] = i;

        for (int i = 0; i < N; ++i)
            for (int j = 1; j < accounts[i].size(); ++j)
                if(mp.find(accounts[i][j]) == mp.end())
                    mp[accounts[i][j]] = i;
                else if (mp[accounts[i][j]] != fa[i])
                    fa[Find(fa, mp[accounts[i][j]])] = i;

        for(auto [s, i]: mp)
            ans[Find(fa, i)].emplace_back(s);

        ans.erase(remove_if(ans.begin(), ans.end(),
                            [](const vector<string> & vs) -> bool {return vs.size()<=1;}),
                  ans.end());
        return ans;
    }
};

int main()
{
//    freopen("/Users/mark/CLionProjects/MarkLearningCPP/LC721/case1.txt", "r", stdin);
    ifstream f("/Users/mark/CLionProjects/MarkLearningCPP/LC721/case1.txt");
//    char * s;
//    scanf("%s", &s);
    string s;
    f >> s;
    for(int i=0; i<s.size()-3; ++i)
        if(s[i]==']' && s[i+1]==',' && s[i+2]=='[')
            s[i+1] = ' ';
    stringstream ss;
    ss << s;
    string s2;
    vector<vector<string>> accounts;
    while (ss >> s2){
        for(char &c: s2)
            if(c==',' || c=='[' || c==']' || c=='"')
                c = ' ';
        accounts.emplace_back(vector<string>{});
        stringstream ss2;
        ss2 << s2;
        while (ss2 >> s2){
            accounts[accounts.size()-1].emplace_back(s2);
        }
        for(auto & i : accounts[accounts.size()-1]){
            cout << i << '\t';
        }
        cout << endl;
    }

    Solution slt;
    slt.accountsMerge(accounts);
    return 0;
}