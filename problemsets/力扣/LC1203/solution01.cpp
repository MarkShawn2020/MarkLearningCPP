//
// Created by 南川 on 2021/1/13.
//

enum Status{notCovered, covering, covered};
const int Fail = -2;

int traverse(
        vector<int> & group,
        vector<vector<int>> & beforeItems,
        vector<stack<int>> & s,
        vector<vector<int>> & history,
        vector<Status> & status,
        int i) {
    status[i] = covering;
    if(beforeItems[i].empty()) {
        status[i] = covered;
        history[group[i]+1].emplace_back(i);
        return group[i];
    } else {
        int ng;
        for(int j: beforeItems[i]) {
            if(status[j] == covering) return Fail;
            else if(status[j] == notCovered) {
                ng = traverse(group, beforeItems, s, history, status, j);
                if(ng==Fail) return Fail;
            }
        }
        status[i] = covered;
        if(group[i]<0) s[ng+1].push(i);
        else history[ng+1].emplace_back(i);
        return ng;
    }
}

vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
    vector<stack<int>> s(m+1);
    vector<vector<int>> history(m+1);
    vector<Status> status(n, notCovered);
    vector<int> ans;

    // 遍历第一趟
    for(int i=0; i<n; i++)
        if(!status[i])
        {
            int e = traverse(group, beforeItems, s, history, status, i);
            if(e == Fail) return {};
        }


    // 遍历第二趟（剩余结点）
    for(int i=0; i<m+1; i++)
        while (!s[i].empty())
        {
            history[i].emplace_back(s[i].top());
            s[i].pop();
        }

    // 输出结果
    for(int i=1; i<m+2; i++)
        for(int j: history[i % (m+1)])
            ans.emplace_back(j);

    return ans;
}