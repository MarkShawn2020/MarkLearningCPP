//
// Created by 南川 on 2021/2/14.
//
/**
 * TLE：5000MS
 */
#include "queue"
#include "stack"
#include "iostream"
#include "algorithm"
using namespace std;
int nCases, nSeqs;


class DNASeq {
private:
    struct S{
        string s;
        int x, y;
    };

    int k = 1;
    int nSeqs;
    string seq;
    vector<string> seqs;
    queue<string> Q;
    stack<S> st;

    void push(const string & s1, const string & s2, const string & s, int x, int y)
    {
//        printf("stack size: %d, s1: %s, s2: %s, s: %s, x: %d, y: %d\n", (int)st.size(), s1.c_str(), s2.c_str(), s.c_str(), x, y);
        if(s.size() + max(s1.size()-x, s2.size()-y) > k) return; // cut
        else if(x == s1.size() && y == s2.size()) Q.push(s);
        else if(x == s1.size() && y != s2.size()) Q.push(s + s2.substr(y));
        else if(x != s1.size() && y == s2.size()) Q.push(s + s1.substr(x));
        else if(s1[x] == s2[y]) st.push({s + s1.substr(x, 1), x+1, y+1});
        else{
            st.push({s + s1.substr(x, 1), x+1, y});
            st.push({s + s2.substr(y, 1), x, y+1});
        }
    }

    void mergeSeqs(const string & s1, const string & s2)
    {
        push(s1, s2, "", 0, 0);
        while (!st.empty())
        {
            auto cur = st.top();
            st.pop();
            push(s1, s2, cur.s, cur.x, cur.y);
        }
    }

    bool addSeq(string & sNew)
    {
        int size = Q.size();
        while (size--)
        {
            auto & cur = Q.front();
            mergeSeqs(cur, sNew);
            Q.pop();
        }
        return !Q.empty();
    }

public:
    explicit DNASeq(int n): nSeqs(n) {}

    void inputSeq() {
        for(int i=0; i<nSeqs; i++)
            cin >> seq,
            k = max(k, (int)seq.size()),
            seqs.emplace_back(seq);
    }

    void solve()
    {
        Q.push(seqs[0]);
        for(int i=1; i<nSeqs; i++)
        {
            queue<string> Q2(Q);
            while (!addSeq(seqs[i]))
                ++k, Q = Q2;    // roll back
        }
        cout << k << endl;
    }

};



void handleCase()
{
    cin >> nSeqs;
    DNASeq dnaSeq(nSeqs);
    dnaSeq.inputSeq();
    dnaSeq.solve();
}


int main()
{
    freopen("/Users/mark/MarkLearningCPP/HDOJ/1560. DNA sequence/case1.txt", "r", stdin);
    cin >> nCases;
    while (nCases--)
        handleCase();
}
