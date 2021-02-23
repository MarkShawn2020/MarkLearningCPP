//
// Created by 南川 on 2021/1/13.
//

//
// Created by 南川 on 2021/1/12.
//
#include "iostream"
#include "fstream"
#include "sstream"

#include "vector"
#include "queue"
#include "map"
#include "unordered_map"

using namespace std;


class Solution{
public:
    struct Node{
        int inDeg = 0;
        vector<int> nextAdj;
        map<int, Node> items;
    };

    vector<int> topologicalSort(map<int, Node> & nodes)
    {
        queue<int> Q;
        vector<int> sequence;
        for(auto [i, node]: nodes)
        {
            if(node.inDeg!=0) continue;
            Q.push(i);
            while (!Q.empty())
            {
                int curNode = Q.front();
                Q.pop();
                sequence.emplace_back(curNode);
                for(int nextNode: nodes[curNode].nextAdj)
                    if(--(nodes[nextNode].inDeg)==0) {
                        Q.push(nextNode);
                        --(nodes[nextNode].inDeg);
                    }
            }
        }
        return sequence.size()==nodes.size() ? sequence : vector<int>();
    }

    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        // 1. 初始化与依赖建
        for(int & i: group) i<0 && (i=m++); // 重新初始化group，并更新m

        map<int, Node> groupNodes;
        for(int i=0; i<m; i++) groupNodes[i] = Node{};
        for(int i=0; i<n; i++) groupNodes[group[i]].items[i] = Node{};

        for(int curItem=0; curItem<n; curItem++)
        {
            int curGroup = group[curItem];
            // 基于良好的初始化，无需考虑无前驱的项目结点
            for(int preItem: beforeItems[curItem])
            {
                int preGroup = group[preItem];
                if(preGroup != curGroup)    // 组间依赖
                {
                    groupNodes[curGroup].inDeg++;
                    groupNodes[preGroup].nextAdj.emplace_back(curGroup);
                }
                else                        // 组内依赖
                {
                    groupNodes[curGroup].items[curItem].inDeg++;
                    groupNodes[curGroup].items[preItem].nextAdj.emplace_back(curItem);
                }
            }
        }

        // 2. 组间循环
        if(groupNodes.empty()) return vector<int>();
        vector<int> groupSequence = topologicalSort(groupNodes);
        if(groupSequence.empty()) return vector<int>();

        // 3. 组内循环
        vector<int> ans;
        for(int groupId: groupSequence)
        {
            auto groupMap = groupNodes[groupId].items;
            if(groupMap.empty()) continue;
            vector<int> itemSequence = topologicalSort(groupMap);
            if(itemSequence.empty()) return vector<int>();
            ans.insert(ans.end(), itemSequence.begin(), itemSequence.end());
        }
        return ans;
    };
};



void readCase(int & n, int & m, vector<int> & group,
              vector<vector<int>> & beforeItems, const string& fp)
{
    fstream f(fp);
    f >> n >> m;

    int tempInt;
    stringstream s;
    string s1, s2, tempS;

    f >> s1 >> s2;
    for(char & i : s1) if(!(isdigit(i) || i=='-')) i=' ';
    s << s1;
    while (s>>tempInt) group.emplace_back(tempInt);
    for(char & i: s2) if(i==']') i=' ';
    s.clear();
    s << s2;
    while (s>>tempS)
    {
        for(char & i:tempS) if(!isdigit(i)) i=' ';
        vector<int> tempItem;
        stringstream ss;
        ss << tempS;
        while (ss>>tempInt) tempItem.emplace_back(tempInt);
        beforeItems.emplace_back(tempItem);
    }
}

int main()
{
    int n, m;
    vector<int> group, ans;
    vector<vector<int>> beforeItems;
    string fp = "/Users/mark/CLionProjects/MarkLearningCPP/LC1203/case1.txt";
    readCase(n, m, group, beforeItems, fp);

    Solution solution;
    ans = solution.sortItems(n, m, group, beforeItems);

    for(auto i: ans) cout << i << '\t';

    return 0;
}