//
// Created by 南川 on 2021/2/14.
//
/**
 * MLE：
 */
#include "cassert"
#include "queue"
#include "iostream"
using namespace std;

#define Min(a, b) if((b) < (a)) (a) = (b)

const int MAX_SEQS = 8 + 1;
int nCases, nSeqs, kLast, kNew;
string seq;
queue<string> Q;

void mergeSeqs(const string & s1, const string & s2, const string & s, int p1, int p2)
{
    if(p1 >= s1.size() && p2 >= s2.size()){
        Q.push(s);
        Min(kNew, s.size());            // 更新kNew，剪枝的关键
    }
    else if(p1 < s1.size() && p2 >= s2.size())
        mergeSeqs(s1, s2, s + s1.substr(p1, 1), p1 + 1, p2);
    else if(p1 >= s1.size() && p2 < s2.size())
        mergeSeqs(s1, s2, s + s2.substr(p2, 1), p1, p2 + 1);
    else if(s1[p1] == s2[p2])
        mergeSeqs(s1, s2, s + s1.substr(p1, 1), p1 + 1, p2 + 1);
    else
        mergeSeqs(s1, s2, s + s1.substr(p1, 1), p1 + 1, p2),
        mergeSeqs(s1, s2, s + s2.substr(p2, 1), p1, p2 + 1);
}

// 对两个字符串进行合并，生成新的多种方案，并依次加入队列中
void mergeSeqs(const string & s1, const string & s2)
{
    // cout << "s1: " << s1 << ", s2: " << s2 << endl;
    mergeSeqs(s1, s2, "", 0, 0);
}

// 处理新的输入串
void addNewSeq(const string & s)
{
    kLast = kNew;
    kNew += s.size();               // 预处理k为能上升的最大长度
    int qSize = Q.size();           // 固定住Que的大小
    if(Q.empty()) {Q.push(s); return;}
    //    while (!Q.empty())        // 不能使用while判空，因为会有新的序列进入
    for(int i=0; i<qSize; i++)   // 使用固定次数的循环，每次弹出一个
    {
        const string & s1 = Q.front();
        if(s1.size() == kLast)      // 剪枝
            mergeSeqs(s1, s);
        Q.pop();
    }
}


void handleCase()
{
    int ans = 40; // 5 * 8
    cin >> nSeqs;
    kLast = kNew = 0;
    while (nSeqs--)
        cin >> seq,
        // cout << ">>> " << seq << ", QSize: " << Q.size() << ", kNew: " << kNew << endl,
        addNewSeq(seq);
    while (!Q.empty()) {
        Min(ans, Q.front().size());
        Q.pop();
    }
    cout << ans << endl;
}


int main()
{
    freopen("/Users/mark/MarkLearningCPP/HDOJ/1560. DNA sequence/case1.txt", "r", stdin);
    cin >> nCases;
    while (nCases--)
        handleCase();
}
