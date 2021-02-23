
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

const int N = 2097152;
unordered_map<ll, int> mp;

bool isSumOfCube(ll num)
{
    ll k = log(num) / log(3) / 2;
    if(k ==0 ) k = 1;
    while(true)
    {
        ll kkk = k * k * k;
        if(kkk >= num) break;
        if(mp.find(num - kkk) != mp.end())
            return true;
        ++k;
    }
    return false;
}


template <typename T>
void run(T & cin)
{
    for(ll i=1; i<=N; ++i)
        mp[i * i * i] = i;

    int tt;
    cin >> tt;
    while (tt--)
    {
        ll num;
        cin >> num;
        cout << (isSumOfCube(num) ? "YES" : "NO") << endl;
    }

}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    // read from local case if possible, otherwise from console
    ifstream fin("/Users/mark/MarkLearningCPP/CodeForce/0216-DIV3/C. Sum of Cubes/case1.txt");
    run(fin.good() ? fin : cin);
}

