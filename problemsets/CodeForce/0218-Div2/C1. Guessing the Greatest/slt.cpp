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

int tt, n, v, r1, r2, r3;

//int nums[] = {5, 1, 2, 4, 3};
//int nums[] = {1, 2, 3, 4, 5, 6};
vector<int> nums = {6, 5, 4, 3, 2, 1};


int getSecond(int s, int t)
{
    vector<pair<int, int>> ret;
    for(int i=s; i<=t; i++)
        ret.emplace_back(nums[i-1], i);
    sort(ret.begin(), ret.end());
    return ret[t-s-1].second;
}

int ask(int s, int t){
    cout << "? " << s << " " << t << endl;
    v = getSecond(s, t);
    cout << v << endl;
//    cin >> v;
    return v;
}

// 目前正确的区间，与第二大的位置
int ensureStep(int p1, int s, int t)
{
    int m = (s + t) >> 1;
    int p2 = p1 >= m ? ask(m, t) : ask(s, m-1);

    if(t == s + 1)
        return p2 == t ? s : t;

    if(p1 == p2)            // 确定区间正确
        return p1 >= m
        ? ensureStep(p1, m, t)
        : ensureStep(p1, s, m-1);
    else                    // 确定区间在另一遍
        return p1 >= m
        ? ensureStep(ask(s, m-1), s, m-1)
        : ensureStep(ask(m, t), m, t);
}


template <typename T>
void run(T & cin)
{
//    cin >> n;
    n = nums.size();
    cout << "n: " << n << endl;
    cout << "input: " << nums << endl;

    int p1 = ask(1, n);
    int ans = ensureStep(p1, 1, n);
    cout << "! " << ans <<endl;
    cout.flush();

}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    // read from local case if possible, otherwise from console
    ifstream fin(
            "../POJ/P2367-Genealogical tree/case1.tx"
    );
    run(fin.good() ? fin : cin);
}

