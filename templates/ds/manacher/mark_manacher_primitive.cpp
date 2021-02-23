#include "string"
#include "vector"
#include "algorithm"
#include "iostream"
#include "iomanip"
#include "cstdio"

using namespace std;


vector<int> mark_manacher(string & s)
{
    const int N = s.size();         // length of s
    const int n = 2 * N + 3;        // length of array
    
    /**
     * @brief init array of manacher, with signs inserted into s
     * 
     */
    enum {SPLIT='#', START='^', END='$'};
    vector<char> ss(n, SPLIT);      // 插入n+1个分隔符，再插入两个哨兵
    ss[0] = START, ss[n-1] = END;
    for(int i=1; i<=N; i++) 
        ss[i << 1] = s[i-1];

    /**
     * @brief core manachar algo
     * 
     */
    vector<int> cc(n, 0);
    int L = 1, P = 2, R = 3;            // P(ivot), L(eft), R(ight)
 
    cout << setw(10) << "input:\t" << s << endl;
    cout << setw(10) << "id:\t";
    for(int i=0; i<n; i++) cout << i << "\t";
    cout << setw(10) << "\nmanacher:\t";
    for(auto i: ss) cout << i << "\t";
    printf("P: %2d, R: %2d\n ", P, R);
    for(int i=0; i<10; i++) cout << " ";
    for(int i=0; i< n; i++) cout << "\t-";

    for(int i=2; i<n-2; i++)
    {
        int j = 2 * P - i;
        if(i < R && j - cc[j] != P - cc[P])          // j的左端点与P的左端点不重合
            cc[i] = min(cc[j], R - i - 1);  // i的半径对齐j或者P的半径
        else
        {
            L = 2 * i - R;
            while(ss[L]==ss[R]) --L, ++R;   // 因为有哨兵不用担心越界
            cc[i] = R - i - 1;
            P = i;
        }

        cout << "\n[i = " << setw(2) << setfill(' ') << i <<"]:\t";
        for(auto & i: cc) cout << i << "\t";

        printf("P: %2d, R: %2d ", P, R);
    }
    
    vector<int> ans(N);
    for(int i=1; i<=N; i++) 
        ans[i-1] = cc[i << 1];
    return ans;
}




int main()
{
    using std::cout;

    string s = "abbab";
    vector<int> ans = mark_manacher(s);

    cout << endl;
    for(int i=0; i<10; i++) cout << " ";
    for(int i=0; i< s.size()*2+2; i++) cout << "\t-";
    cout << endl << setw(10) << "ans:\t";
    for(auto i: ans) cout << i << "\t";
}