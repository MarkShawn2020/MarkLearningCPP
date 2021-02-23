//
// Created by 南川 on 2021/1/13.
//


class Solution {
public:

    static vector<int> topologicalMapOrder(map<int, set<int>> & mp)
    {
        vector<int> ans;
        map<int, int> inDegree;
        map<int, set<int>> nextVex;
        queue<int> q;
        vector<int> starts;
        for(auto [i, j]: mp)
        {
            nextVex[i].insert({});
            for(auto k: j) nextVex[k].insert(i);
            if((inDegree[i]=j.size())==0) starts.emplace_back(i);
        }
        for(auto start: starts)
        {
            q.push(start);
            while (!q.empty())
            {
                int pre = q.front();
                q.pop();
                ans.emplace_back(pre);
                for(auto next: nextVex[pre])
                    if(--inDegree[next]==0)
                        q.push(next);
            }
        }
        for(auto [i, j]: inDegree) if(j!=0) return {};
        return ans;
    }


    vector<int> sortItems(
            int n, int m,
            vector<int>& group,
            vector<vector<int>>& beforeItems
    )
    {
        for(auto & i: group) if(i==-1) i=m++;

        map<int, set<int>> mBetweenGroups;
        map<int, map<int, set<int>>> mp;
        vector<int> ans;

        for(int i=0; i<beforeItems.size(); i++) // item_index
        {
            mBetweenGroups[group[i]].insert({});
            mp[group[i]][i].insert({});
            for(int j: beforeItems[i])          // pre_item_index
                if(group[i] != group[j])        // same group
                    mBetweenGroups[group[i]].insert(group[j]);
                else
                    mp[group[i]][i].insert(j);
        }

        vector<int> groupOrder = topologicalMapOrder(mBetweenGroups);

        cout << "groupOrder: ";
        for(auto g: groupOrder) cout << g << '\t';
        cout << endl;

        for(int g: groupOrder)
        {

            if(!mp[g].empty())
            {
                vector<int> ansInnerGroup = topologicalMapOrder(mp[g]);
                if(ansInnerGroup.empty()) return {};
                ans.insert(ans.end(), ansInnerGroup.begin(), ansInnerGroup.end());
            }
        }
        return ans;
    }
};
