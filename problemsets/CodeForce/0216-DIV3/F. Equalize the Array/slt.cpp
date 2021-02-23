//
// Created by 南川 on 2021/2/17.
//


#include "cstdio"
#include "cstring"
#include "cmath"
#include "cassert"

#include "string"
#include "iostream"
#include "fstream"
#include "algorithm"

#include "vector"
#include "stack"
#include "list"
#include "queue"
#include "set"
#include "unordered_set"
#include "map"
#include "unordered_map"

using namespace std;

typedef long long ll;

template <typename T>
void run(T & cin)
{
    int tt;
    cin >> tt;
    while (tt--)
    {
        unordered_map<int, int> mp;
        ll ans = 0x3f3f3f3f;
        int n;
        cin >> n;
        while (n--)
        {
            int v;
            cin >> v;
            ++mp[v];
        }
        const int N = mp.size();
        vector<int> freqs(N, 0);
        int k = -1;
        for(auto & item: mp)
            freqs[++k] = item.second;
        sort(freqs.begin(), freqs.end());
        vector<bool> vis(2e5+1, false);
        for(int i=0; i<N; i++)
        {
            if(vis[freqs[i]]) continue;
            vis[freqs[i]] = true;
            ll cur = 0;
            for(int j=0; j<N; j++)
                if(freqs[j] < freqs[i])
                    cur += freqs[j];
                else
                    cur += freqs[j] - freqs[i];
            ans = min(ans, cur);
        }
        printf("%lld\n", ans);
    }

}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    // read from local case if possible, otherwise from console
    ifstream fin("/Users/mark/MarkLearningCPP/CodeForce/0216-DIV3/F. Equalize the Array/case1.txt");
    run(fin.good() ? fin : cin);
}

