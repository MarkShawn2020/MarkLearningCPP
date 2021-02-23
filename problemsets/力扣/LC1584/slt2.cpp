//
// Created by 南川 on 2021/1/19.
//

#include "vector"
#include "iostream"
#include "string"
#include "sstream"
#include "set"

using namespace std;

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        const int N = points.size();
        vector<pair<int, int>> qx(N);
        vector<pair<int, int>> qy(N);
        vector<bool> vis(N, false);
        for(int i=0; i<N; i++){
            qx[i] = make_pair(points[i][0], i);
            qy[i] = make_pair(points[i][1], i);
        }
        sort(qx.begin(), qx.end());
        sort(qy.begin(), qy.end());

        for(int i=1, p1=0, p2=N-1; p1<p2; ++p1, --p2, ++i)
        {
            cout << "Period: " << i << endl;
            set<int> st;
            int arr[4] = {qx[p1].second, qy[p1].second, qx[p2].second, qy[p2].second};
            for(int p: arr)
                if(!vis[p]){
                    st.insert(p);
                    vis[p] = true;
                }

            for(auto p: st)
                cout << p << '\t';
            cout << endl;
        }
        return 0;
    }
};


int main()
{
    const int N = 100000;
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/力扣/LC1584/case1.txt", "r", stdin);
    string s;
    cin >> s;
    for(char & ch: s)
        if(ch=='[' || ch==']' || ch==',')
            ch = ' ';
    vector<vector<int>> data;
    stringstream ss;
    ss << s;
    int a1, a2;
    while(ss >> a1 >> a2)
        data.emplace_back(vector<int> {a1, a2});

    Solution slt;
    slt.minCostConnectPoints(data);
    return 0;
}