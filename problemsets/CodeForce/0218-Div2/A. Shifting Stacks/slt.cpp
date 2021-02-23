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

int tt, n, r1, r2, r3;



template <typename T>
void run(T & cin)
{
    cin >> tt;
    while (tt--)
    {
        cin >> n;
        int ind = 0, ans = true;
        ll s = 0, v;
        while (n--)
        {
            cin >> v;
            s += v - ind;
            if(s < 0) {ans = false;}
            ++ind;
        }
        cout << (ans ? "YES" : "NO") << endl;
    }
}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    // read from local case if possible, otherwise from console
    ifstream fin(
            "/Users/mark/MarkLearningCPP/CodeForce/0218-Div2/A. Shifting Stacks/case1.txt"
    );
    run(fin.good() ? fin : cin);
}

