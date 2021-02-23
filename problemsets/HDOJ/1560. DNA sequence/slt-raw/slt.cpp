//
// Created by 南川 on 2021/2/13.
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

const int MAX_CASES = 8 + 1;
int nCases, n;
string seqs[MAX_CASES];
struct Str{
    string s;
    int x, y;
};
queue<Str> Q;

bool pushNext(string & s1, string & s2, string s, int x, int y)
{
    if(x == s1.size() && y == s2.size()) return true;
    else if(x == s1.size() && y < s2.size())
        Q.push({s += s2.substr(y, 1), x, ++y});
    else if(x < s1.size() && y == s2.size())
        Q.push({s += s1.substr(x, 1), ++x, y});
    else if(s1[x] == s2[y])
        Q.push({s += s1.substr(x, 1), ++x, ++y});
    else
        Q.push({s + s1.substr(x, 1), x + 1, y}),
        Q.push({s + s2.substr(y, 1), x, y + 1});
    return false;
}

vector<string> genSeqs(string & s1, string & s2)
{
    vector<string> ret;
    bool finished = pushNext(s1, s2, "", 0, 0);
    while (!Q.empty() && !finished)
        for(int i=0; i<Q.size(); i++) {
            auto & cur = Q.front();
            if(pushNext(s1, s2, cur.s, cur.x, cur.y))
                finished = true,
                ret.emplace_back(cur.s);
            Q.pop();
        }
    while (!Q.empty()) Q.pop(); // reset
    return ret;
}


template <typename T>
void run(T & cin)
{
    cin >> nCases >> n;
    for(int i=0; i<n; i++) cin >> seqs[i], cout << seqs[i] << endl;

    for(auto & s: genSeqs(seqs[0], seqs[1])) {
        cout << s << endl;
    }

}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    // read from local case if possible, otherwise from console
    ifstream fin("/Users/mark/MarkLearningCPP/HDOJ/1560. DNA sequence/case1.txt");
    run(fin.good() ? fin : cin);
}

