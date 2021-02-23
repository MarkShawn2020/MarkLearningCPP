
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

template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) {
    cout << "["; for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";
}
template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "(" << p.f << ", " << p.s << ")"; }
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) {
    cin >> p.first;
    return cin >> p.second;
}

int tt, n, v, r1, r2, r3;


template <typename T>
void run(T & cin)
{

}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    // read from local case if possible, otherwise from console
    ifstream fin(
            "../POJ/P2367-Genealogical tree/case1.txt"
            );
    run(fin.good() ? fin : cin);
}

