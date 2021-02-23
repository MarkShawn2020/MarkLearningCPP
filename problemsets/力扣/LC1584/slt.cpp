//
// Created by 南川 on 2021/1/19.
//

#include "vector"
#include "iostream"
#include "string"
#include "sstream"
#include "set"
#include "unordered_set"
#include "queue"
#include "algorithm"

using namespace std;

class Solution {
public:
    int getDis(vector<vector<int>> & points, int i, int j){
        return int(fabs(points[i][0]-points[j][0]) +
            fabs(points[i][1]-points[j][1]));
    }

    int minCostConnectPoints(vector<vector<int>>& points) {
        int N = points.size();
        vector<int> dis(N, INT_MAX);
        int start = 0, ans = 0;

        for(int k=0; k<N-1; ++k){    // 探索N-1次
            dis[start] = 0;
            int min_i=start, min_v=INT_MAX;
            for(int j=0; j<N; j++){
                if(!dis[j]) continue;   // 已探索过
                int newDis = getDis(points, start, j);
                if(newDis < dis[j])
                    dis[j] = newDis;
                if(dis[j] < min_v){
                    min_i = j;
                    min_v = dis[j];
                }
            }
            start = min_i;
            ans += min_v;
        }
        return ans;
    }
};

int main()
{
    const int N = 100000;
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/力扣/LC1584/case4.txt.txt", "r", stdin);
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
    cout << slt.minCostConnectPoints(data);
    return 0;
}