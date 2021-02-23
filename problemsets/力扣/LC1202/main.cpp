//
// Created by 南川 on 2021/1/11.
//

#include "iostream"
#include "vector"
#include "queue"
#include "fstream"
#include "sstream"
#include "unordered_map"
#include "map"
#include "set"

using namespace std;
//
//vector<int> traverse(vector<vector<bool> > & tb, vector<bool> & visited, int start)
// bfs
//{
//    queue<int> q;
//    vector<int> nodes;
//    nodes.push_back(start);
//
//    for(int i=0; i<tb.size(); i++)
//        if(tb[start][i] && !visited[i])
//        {
//            nodes.push_back(i);
//            q.push(i);
//        }
//
//    while(!q.empty())
//    {
//        int next = q.front();
//        q.pop();
//        visited[next] = true;
//        for(int i=0; i<tb.size(); i++)
//            if(tb[next][i] && !visited[i])
//            {
//                nodes.push_back(i);
//                q.push(i);
//            }
//    }
//    return nodes;
//}
//
//void sort(string & s, vector<int> & nodes, int start, int end)
// quickSort
//{
//    if(end<=start) return;
//
//    char pivot = s[nodes[start]];
//    while(start<end)
//    {
//            while (start<end && s[nodes[end]]>=pivot) end--;
//            s[nodes[start]] = s[nodes[end]];
//            while (start<end && s[nodes[start]]<=pivot) start++;
//            s[nodes[end]] = s[nodes[start]];
//    }
//    s[nodes[start]] = pivot;
//    sort(s, nodes, 0, start-1);
//    sort(s, nodes, start+1, nodes.size()-1);
//}
//
//string smallestStringWithSwaps(string s, vector<vector<int> > & pairs) {
//    vector<bool> visited(s.size(), false);
//    vector<vector<bool> > tb(s.size(), vector<bool>(s.size(), false));
//
//    for(auto & pair : pairs)
//    {
//        tb[pair[0]][pair[1]] = true;
//        tb[pair[1]][pair[0]] = true;
//    }
//
//    for(int i=0; i<pairs.size(); i++)
//    {
//        if(!visited[i])
//        {
//            visited[i] = true;
//            vector<int> nodes = traverse(tb, visited, i);
//
//            if(!nodes.empty()) sort(s, nodes, 0, nodes.size()-1);
//        }
//    }
//
//    return s;
//}
//
//int main()
//{
// "dcab"
// [[0,3],[1,2],[0,2]]
//    string s = "dcab";
//    vector<vector<int> > pairs = {{0, 3}, {1, 2}, {0, 2}};
//    cout << s << endl;
//    for(auto & pair : pairs)
//    {
//        cout << '{' << pair[0] << ", " << pair[1] << "}\t";
//    }
//    cout << endl;
//    string s2 = smallestStringWithSwaps(s, pairs);
//    cout << s2 << endl;
//    return 0;
//}
//
//struct Item{
//    int l = 0;
//    int h = 0;
//    string s;
//    vector<int> v;
//};
//
//
//void quickSort(string & s, vector<int> & v, int l, int h)
//{
//    if(l>=h) return;
//
//    int start = v[l];
//    char pivot = s[v[l]];
//    while (l<h)
//    {
//        while (l<h && s[v[h]]>=pivot) h--;
//        s[v[l]] = s[v[h]];
//        v[l] = v[h];
//
//        while (l<h && s[v[l]]<=pivot) l++;
//        s[v[h]] = s[v[l]];
//        v[h] = v[l];
//    }
//    s[v[l]] = pivot;
//    v[l] = start;
//
//    quickSort(s, v, 0, l-1);
//    quickSort(s, v, l+1, h);
//}



//void sort(string & s, vector<int> & v)
//{
//     sort(v.begin(), v.end());
//     for(int i=1; i<v.size(); i++)
//     {
//         int j = i;
//         while (s[j]<s[j-1] && j>0)
//         {
//             swap(s[j], s[j-1]);
//             j--;
//         }
//     }
//}


//void Sort(string & s, vector<int> & v)
//{
//    sort(v.begin(), v.end());
//    for(int i=1; i<v.size(); i++)
//    {
//        cout << i << '\t' << v[i] << '\t' << s[v[i]] << endl;
//        int j = i;
//        while (j>0 && s[v[j]]<s[v[j-1]])
//        {
//            cout << "j_1=" << j << endl;
//            swap(s[v[j]], s[v[j-1]]);
//            swap(v[j], v[j-1]);
//            j--;
//            cout << "j_2=" << j << endl;
//        }
//    }
//}

//void convert(string s2, vector<vector<int>> & pairs)
//{
//    int p = 0;
//    vector<int> temp(2, 0);
//    for(char i : s2)
//    {
//        switch (i) {
//            case '[':
//                temp = {0, 0};
//                p = 0;
//                break;
//            case ']':
//                if(!temp.empty()) pairs.push_back(temp);
//                temp.clear();
//                break;
//            case ',':
//                p= 1;
//                break;
//            default:
//                temp[p] = temp[p] * 10 + (i - '0');
//                break;
//        }
//    }
//}
//
//void convert2(string s2, vector<vector<int>> & pairs)
//{
//    int temp = 0;
//    bool joining = false;
//    int size = 0;
//    for(auto si: s2)
//    {
//        if(si>='0' && si<='9') {
//            temp = temp*10+(si-'0');
//            joining = true;
//        }
//        else {
//            if(joining) {
//                size++;
//                if(size%2==1) pairs.push_back({temp, 0});
//                else pairs[pairs.size()-1][1] = temp;
//            }
//            temp = 0;
//            joining = false;
//        }
//    }
//}
//


//vector<int> traverse(vector<vector<bool> > & tb, vector<bool> & visited, int start)
//// bfs
//{
//    queue<int> q;
//    vector<int> nodes;
//    q.push(start);
//
//    while(!q.empty())
//    {
//        start = q.front();
//        q.pop();
//        if(visited[start]) continue;
//        visited[start] = true;
//        nodes.push_back(start);
//        for(int i=0; i<tb.size(); i++)
//            if(tb[start][i] && !visited[i])
//                q.push(i);
//    }
//
//    return nodes;
//}


//void findGraph(map<int, set<int>> & m, vector<bool> & visited, int start, vector<int> & nodes)
//{
//    visited[start] = true;
//    nodes.push_back(start);
////    cout << "start: " << start << "\ti: ";
////    for(auto i: m[start])
////        cout << i << "\t";
////    cout << endl;
//    for(auto i: m[start])
//    {
//        if(!visited[i])
//        {
////            visited[i] = true;
//            findGraph(m, visited, i, nodes);
//        }
//    }
//}

//void solution1(string s, vector<vector<int>> & pairs)
//{
//    vector<bool> visited(s.size(), false);
//    map<int, set<int>> m;
//
//    for(vector<int>(p): pairs)
//    {
//        m[p[0]].insert(p[1]);
//        m[p[1]].insert(p[0]);
//    }
//
//    for(int i=0; i<visited.size(); i++)
//    {
//        if(!visited[i])
//        {
//            vector<int> nodes = {};
//            findGraph(m, visited, i, nodes);    // travese the connecting nodes
//            countSort(s, nodes);                       // sort the sub sequence of s
//        }
//    }
//}


//void solution2(string s, vector<vector<int>> & (pairs))
//{
//    vector<set<int>> groups;
//    for(const auto& pair: pairs)
//    {
//        if(pair[0] == pair[1]) continue;
//        vector<int> pos(2, -1);
//        for(int i=0; i<2; i++) {
//            for (int j = 0; j < groups.size(); ++j) {
//                if (groups[j].find(pair[i]) != groups[j].end()) {
//                    pos[i] = j;
//                    break;
//                }
//            }
//        }
//        if(pos[0]<0)
//        {
//            if(pos[1]<0) groups.push_back({pair[0], pair[1]});
//            else groups[pos[1]].insert(pair[0]);
//        }
//        else
//        {
//            if(pos[1]<0) groups[pos[0]].insert(pair[1]);
//            else if(pos[0] != pos[1]) // 不在同一集合
//            {
//                if(groups[pos[0]].size() > groups[pos[1]].size())
//                {
//                    for(auto i: groups[pos[1]]) groups[pos[0]].insert(i);
//                    groups.erase(groups.begin()+pos[1]);
//                }
//                else
//                {
//                    for(auto i: groups[pos[0]]) groups[pos[1]].insert(i);
//                    groups.erase(groups.begin()+pos[0]);
//                }
//            }
//        }
//    }
//
//    for(auto & g: groups)
//        countSort(s, g);
//
//}
//
//void solution3()
//{
//    vector<int>ancestors(s.size());
//    for(int i=0; i<s.size(); i++) ancestors[i]=i;
//    vector<int>heights(s.size(), 0);
//
//    for(auto & pair: pairs)
//    {
//        if(pair[0] == pair[1]) continue;
//        int a0 = findAncestor(ancestors, pair[0]);
//        int a1 = findAncestor(ancestors, pair[1]);
//        if(a0 == pair[0])
//        {
//            if(a1 == pair[1])
//            {
//                ancestors[a1] = a0;
//                ++heights[a0];
//            }
//            else
//            {
//                ancestors[a0] = a1;
//            }
//        }
//        else
//        {
//            if(a1 == pair[1])
//            {
//                ancestors[a1] = a0;
//            }
//            else
//            {
//                if(heights[a0]>=heights[a1])
//                {
//                    ++heights[a0];
//                    ancestors[a1] = a0;
//                }
//                else
//                {
//                    ++heights[a1];
//                    ancestors[a0] = a1;
//                }
//            }
//        }
//    }
//
//    unordered_map<int, set<int>> groups;
//    for(int i=0; i<s.size(); i++)
//        groups[findAncestor(ancestors, i)].insert(i);
//
//    for(const auto& g: groups)
//        countSort(s, g.second);
//}


//void countSort(string & s, set<int> v)
//{
//    unordered_map<char, int> m(26);
//    for(int i=0; i<26; i++) m.insert({'a'+i, 0});
//    for(int i: v)
//        m[s[i]]++;
//
//    char alpha = 'a';
//    for(int i: v)
//    {
//        while (m[alpha]<=0) alpha++;
//        s[i] = alpha;
//        m[alpha]--;
//    }
//}
//
//int findAncestor(vector<int> & (data), int p)
//{
//    if(data[p] == p) return p;
//    data[p] = findAncestor(data, data[p]); // 查询优化
//    return data[p];
//}
//


class DisjointSetUnion {
private:
    vector<int> f, rank;
    int n;

public:
    explicit DisjointSetUnion(int _n) {
        n = _n;
        rank.resize(n, 1);
        f.resize(n);
        for (int i = 0; i < n; i++) f[i] = i;
    }

    int find(int x) {
        return f[x] == x ? x : f[x] = find(f[x]);
    }

    void unionSet(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) return;
        if (rank[fx] < rank[fy]) swap(fx, fy);
        rank[fx] += rank[fy];
        f[fy] = fx;
    }
};


int find(vector<int> & f, int x) {
    return f[x] == x ? x : f[x] = find(f, f[x]);
}

void unionSet(vector<int> & f, vector<int> & rank, int x, int y) {
    int fx = find(f, x), fy = find(f, y);
    if (fx == fy) return;
    if (rank[fx] < rank[fy]) swap(fx, fy);
    rank[fx] += rank[fy];
    f[fy] = fx;
}


string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
    DisjointSetUnion dsu(s.length());
    for (auto& pair : pairs) dsu.unionSet(pair[0], pair[1]);

    /**
     * multiset方案
     *
        unordered_map<int, multiset<char>> mp;
        for (int i = 0; i < s.length(); i++)    // 每个祖先存储所有成员的字母
            mp[dsu.find(i)].insert(s[i]);

        for (int i = 0; i < s.length(); i++) {
            int x = dsu.find(i);
            s[i] = *mp[x].begin();
            mp[x].erase(mp[x].begin());
        }
     *
     */

//    /**
//     * vector方案
//     */
//     struct M{
//         vector<int> children;
//         int start = 0;
//     };
//     unordered_map<int, M> mp;
//     for(int i=0; i<s.size(); i++) mp[dsu.find(i)].children.emplace_back(s[i]);
//     for(auto & [i, m]: mp) sort(m.children.begin(), m.children.end());
//     for(int i=0; i<s.size(); i++)
//     {
//         int x = dsu.find(i);
//         s[i] = mp[x].children[mp[x].start++];
//     }

/**
 * multiset 2
 */

    int N = s.size();
    vector<int> f(N), rank(N, 1);
    for(int i=0; i<N; i++) f[i] = i;
    for(auto& pair : pairs) unionSet(f, rank, pair[0], pair[1]);

    unordered_map<int, multiset<int, greater<int>>> mp;
    for(int i=0; i<N; i++) mp[find(f, i)].insert(s[i]);
    for(int i=0; i<N; i++) {
        int x = find(f, i);
        s[i] = *(mp[x].crend() + rank[x]--);
//        s[i] = *(mp[x].cend() - rank[x]e--);
    }

    return s;
}

int main()
{
    ifstream f("/Users/mark/CLionProjects/Leetcode1202/case4.txt");
    if(!f.is_open()) exit(-1);

    string s, s2;
    f >> s >> s2;
    s = s.substr(1, s.size()-2);

    for(auto & si: s2) // 将所有非数字字符转换成空格，以方便stringstream输出整数
        if(!isdigit(si)) si = ' ';
    stringstream ss;
    ss << s2;

    vector<vector<int>> pairs;
    int i, j;
    while(ss >> i >> j)  // 每次读入两个整数
        pairs.push_back({i, j});

    string s3 = smallestStringWithSwaps(s, pairs);

//    cout << s  << endl;
    cout << s3 << endl;

    return 0;
}
