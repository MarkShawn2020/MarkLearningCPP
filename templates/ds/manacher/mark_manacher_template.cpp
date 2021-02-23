#include "string"
#include "vector"
#include "iostream"

using namespace std;

static inline int min(int a, int b) { return a < b ? a : b; }


vector<int> mark_manacher(string & s)
{
    const int N = s.size();                     // length of input string
    const int n = 2 * N + 3;                    // length of converted array
    enum {SPLIT='#', START='^', END='$'};       // 特殊的标识符
    
    // 初始化回文串
    vector<char> ss(n, SPLIT);                  // n+1个分隔符、端点两个哨兵
    ss[0] = START, ss[n-1] = END;               // ^b#b$ 这种是不能使用n-1个分隔符的反例
    for(int i=1; i<=N; i++)                     // 因为会导致后续处理奇偶的不一致性
        ss[i << 1] = s[i-1];

    // 计算每个字符的最大回文串长度
    vector<int > cc(n, 0);        
    for(int i=2, j=2, P=2, R=3; i<n-2; i++, j=2*P-i)
        if(i < R && j - cc[j] != P - cc[P])         // j的左端点与P的左端点不重合
            cc[i] = min(cc[j], R - i - 1);          // i的半径对齐j或者P的半径
        else
        {
            while(ss[2*i-R] == ss[R]) ++R;          // 因为有哨兵不用担心越界
            cc[P = i] = R - i - 1;
        }

    return vector<int>(cc.begin()+2, cc.end()-2);   // 输出时丢弃首尾的虚结点
}


int main()
{
    string s = "abbab";
    vector<int> ans = mark_manacher(s);
    for(auto & i: ans) cout << i << "\t";
}