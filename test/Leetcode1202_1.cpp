//
// Created by 南川 on 2021/1/11.
//

#include "iostream"
#include "vector"
#include "queue"

using namespace std;

vector<int> traverse(vector<vector<bool> > & tb, vector<bool> & visited, int start)
// bfs
{
    queue<int> q;
    vector<int> nodes;
    nodes.push_back(start);

    for(int i=0; i<tb.size(); i++)
        if(tb[start][i] && !visited[i])
        {
            nodes.push_back(i);
            q.push(i);
        }

    while(!q.empty())
    {
        int next = q.front();
        q.pop();
        visited[next] = true;
        for(int i=0; i<tb.size(); i++)
            if(tb[next][i] && !visited[i])
            {
                nodes.push_back(i);
                q.push(i);
            }
    }
    return nodes;
}

void sort(string s, vector<int> & nodes, int start, int end)
// quickSort
{
    if(end<=start) return;

    int pivot = s[nodes[start]];
    while(start<end)
    {
        if(s[nodes[end]]<pivot)
        {
            swap(s[nodes[start]], s[nodes[end]]);
            end--;
        }
        else if(nodes[start]>pivot)
        {
            swap(s[nodes[start]], s[nodes[end]]);
            start++;
        }
    }
    s[nodes[start]] = pivot;
    sort(s, nodes, 0, start-1);
    sort(s, nodes, start+1, nodes.size()-1);
}

string smallestStringWithSwaps(string s, vector<vector<int> > & pairs) {

    vector<bool> visited(s.size(), false);
    vector<vector<bool> > tb(s.size(), vector<bool>(s.size(), false));

    for(int i=0; i<pairs.size(); i++)
    {
        tb[pairs[i][0]][pairs[i][1]] = true;
        tb[pairs[i][1]][pairs[i][0]] = true;
    }

    for(int i=0; i<pairs.size(); i++)
    {
        if(!visited[i])
        {
            visited[i] = true;
            vector<int> nodes = traverse(tb, visited, i);

            for(int j=0; j<nodes.size(); j++)
            {
                cout << nodes[j] << '\t';
            }
            cout << endl;

            if(!nodes.empty()) sort(s, nodes, 0, nodes.size()-1);
        }
    }

    return s;
}

int main()
{
    string s = "dcab";
    vector<vector<int> > pairs = {{0, 3}, {1, 2}};
    smallestStringWithSwaps(s, pairs);
    return 0;
}