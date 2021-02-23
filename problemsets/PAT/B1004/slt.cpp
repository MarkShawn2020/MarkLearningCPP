//
// Created by 南川 on 2021/1/23.
//

#include "cstdio"
#include "vector"
#include "queue"

using namespace std;

int n, m;

struct Node
{
    int id;
    int K;
    vector<int> ch;
};

vector<Node*> ds;
vector<int> ans;


void layerTraverse(int & layer, vector<int> & ids)
{
    vector<int> nextIds;
    for(int id: ids)
        if(ds[id])
            nextIds.insert(nextIds.end(), ds[id]->ch.begin(), ds[id]->ch.end());
        else
            ++ans[layer];

    if(!nextIds.empty())
        layerTraverse(++layer, nextIds);
}


int main()
{

    freopen("/Users/mark/CLionProjects/MarkLearningCPP/PAT/B1004/case1.txt", "r", stdin);

    scanf("%d %d", &n, &m);
    ds = vector<Node*>(n+1);
    ans = vector<int>(n+1);

    for(int i=0; i<m; ++i)
    {
        int id, K, chId;
        scanf("%d %d", &id, &K);
        ds[id] = new Node{id, K, vector<int>(K)};

        for(int j=0; j<K; j++)
            scanf("%d", &ds[id]->ch[j]);
    }

    queue<Node*> Q;
    Q.push(ds[1]);

    int layer = 0;
    vector<int> sIds = {1};
    layerTraverse(layer, sIds);
    for(int i=0; i<=layer; i++){
        printf("%d", ans[i]);
        if(i<layer)
            printf(" ");
    }
    printf("\n");

}