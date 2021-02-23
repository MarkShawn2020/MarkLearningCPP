//
// Created by 南川 on 2021/1/27.
//

#include "fstream"
#include "iostream"
#include "vector"
#include "queue"

using namespace std;

template <typename T>
void run(T &);

int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    // read from local case if possible, otherwise from console
    ifstream fin("../POJ/P2367-Genealogical tree/case1.txt");
    run(fin.good() ? fin : cin);
}

template <typename T>
void run(T & cin)
{
    const int N = 100 + 1;
    int degIn[N] = {0};
    vector<vector<int> > adjOut(N);
    int n, r1;
    cin >> n;
    for(int i=1; i<=n; i++)
        while (cin >> r1 && r1)
            ++degIn[r1],
            adjOut[i].push_back(r1);

    queue<int> Q;
    for(int i=1; i<=n; i++)
        if(degIn[i] == 0)
            Q.push(i);

    vector<int> ans;
    ans.reserve(N);
    while (!Q.empty())
    {
        int p = Q.front();
        Q.pop();
        ans.push_back(p);
        for(int i=0; i<adjOut[p].size(); i++)
        {
            int child = adjOut[p][i];
            if(--degIn[child] == 0)
                Q.push(child);
        }
    }

    for(int i=0; i<n; i++)
        cout << ans[i] << " ";
}
