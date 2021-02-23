//
// Created by 南川 on 2021/1/13.
//

class Solution {
public:
    vector<int> topSort(vector<int>& deg, vector<vector<int>>& graph, vector<int>& items) {
        queue<int> Q;
        for (auto& item: items)
            if(deg[item] == 0)
                Q.push(item);

        vector<int> res;
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            res.emplace_back(u);
            for (auto& v: graph[u])
                if (--deg[v] == 0)
                    Q.push(v);
        }
        return res.size() == items.size() ? res : vector<int>{};
    }

    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        /**
         * 第一步：重新初始化组别，并构建group->item一对多的关系
         */
        // 组ID
        vector<int> groupId(n+m);
        for(int i=0; i<n+m; i++) groupId[i] = i;

        // 每个组需要完成的项目
        vector<vector<int>> groupItems(n + m);

        // 组间邻接表与入度表
        vector<vector<int>> groupGraph(n + m);
        vector<int> groupDegree(n + m, 0);

        // 组内邻接表与入度表
        vector<vector<int>> itemGraph(n);
        vector<int> itemDegree(n, 0);

        for (int i = 0; i < n; ++i) {
            // group重新初始化
            group[i] == -1 && (group[i] = m++);
            // 生成group->item的一对多关系
            groupItems[group[i]].emplace_back(i);
        }


        /**
         * 第二步：组间、组内依赖关系建表
         */
        for (int itemId = 0; itemId < n; ++itemId) {
            int curGroupId = group[itemId];
            for (auto& preItem: beforeItems[itemId]) {
                int preGroupId = group[preItem];
                if (preGroupId == curGroupId) {
                    ++itemDegree[itemId];
                    itemGraph[preItem].emplace_back(itemId);
                } else {
                    ++groupDegree[curGroupId];
                    groupGraph[preGroupId].emplace_back(curGroupId);
                }
            }
        }

        /**
         * 第三步：组间排序
         */
        vector<int> groupTopSort = topSort(groupDegree, groupGraph, groupId);
        if(groupTopSort.empty()) return vector<int>{};


        /**
         * 第四步：每个组内排序
         */
        vector<int> ans;
        for (auto& curGroupId: groupTopSort) {
            if(groupItems[curGroupId].empty()) continue;

            vector<int> res = topSort(itemDegree, itemGraph, groupItems[curGroupId]);
            if (res.empty()) return vector<int>{};
            ans.insert(ans.end(), res.begin(), res.end());
        }
        return ans;
    }
};

//作者：LeetCode-Solution
//        链接：https://leetcode-cn.com/problems/sort-items-by-groups-respecting-dependencies/solution/xiang-mu-guan-li-by-leetcode-solution-3e7j/
//来源：力扣（LeetCode）
//著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
