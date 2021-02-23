//
// Created by 南川 on 2021/2/14.
//
/**
 * TLE：5000MS
 */
#include "queue"
#include "iostream"
#include "algorithm"
using namespace std;
int nCases, nSeqs;


class DNASeq {
private:
    int k = 1;
    int nSeqs;
    string seq;
    vector<string> seqs;
    queue<string> Q;

    void mergeSeqs(const string & s1, const string & s2, const string & s, int p1, int p2)
    {
        if(s.size() > k) return;  // 剪枝
        else if(p1 >= s1.size() && p2 >= s2.size()) Q.push(s);   // 存储
        else if(p1 < s1.size() && p2 >= s2.size())
            mergeSeqs(s1, s2, s + s1.substr(p1, 1), p1 + 1, p2);
        else if(p1 >= s1.size() && p2 < s2.size())
            mergeSeqs(s1, s2, s + s2.substr(p2, 1), p1, p2 + 1);
        else if(s1[p1] == s2[p2])
            mergeSeqs(s1, s2, s + s1.substr(p1, 1), p1 + 1, p2 + 1);
        else {
            mergeSeqs(s1, s2, s + s1.substr(p1, 1), p1 + 1, p2);
            mergeSeqs(s1, s2, s + s2.substr(p2, 1), p1, p2 + 1);
        }
    }

    void mergeSeqs(string & s1, string & s2)
    {
        mergeSeqs(s1, s2, "", 0, 0);
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

    bool handleK()
    {
//        cout << "K: " << k << endl;
        while (!Q.empty())  // reset
            Q.pop();
        Q.push(seqs[0]);
        for(int i=1; i<nSeqs; i++)
            if(!addSeq(seqs[i]))
                return false;
        return true;
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
        while(!handleK())
            k++;
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
