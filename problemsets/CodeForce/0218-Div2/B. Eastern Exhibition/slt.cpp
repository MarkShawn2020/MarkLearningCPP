//
// Created by 南川 on 2021/2/18.
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

#define Min(a, b) if((b)<(a)) (a) = (b)
#define Max(a, b) if((b)>(a)) (a) = (b)

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> pi;
typedef vector<pair<int, int>> vpi;

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "(" << p.f << ", " << p.s << ")"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) {
    cout << "["; for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";
}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) {
    cin >> p.first;
    return cin >> p.second;
}

ll tt, n, v, r1, r2, r3, x, y, ans;

template <typename T>
ll runCase(T & cin)
{
    cin >> n;
    vector<int> xs(n);
    vector<int> ys(n);
    for (int i = 0; i < n; ++i) {
        cin >> xs[i];
        cin >> ys[i];
    }
    if(n & 1) return 1;

    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    x = xs[n >> 1] - xs[(n >> 1) - 1] + 1;
    y = ys[n >> 1] - ys[(n >> 1) - 1] + 1;
    ans = x * y;
    return ans;
}


template <typename T>
void run(T & cin)
{
    cin >> tt;
    while (tt--)
    {
        cout << runCase(cin) << endl;
    }

}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    // read from local case if possible, otherwise from console
    ifstream fin(
            "/Users/mark/MarkLearningCPP/CodeForce/0218-Div2/B. Eastern Exhibition/case1.txt"
    );
    run(fin.good() ? fin : cin);
}

