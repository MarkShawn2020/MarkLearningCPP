#include "string"
#include "vector"
#include "algorithm"
#include "iostream"
#include "iomanip"
#include "cstdio"

using namespace std;

static const int LW = 10;


void showGraph(int L, int P, int R, char l, char p, char r)
{
    cout << endl;
    cout << setw(LW) << "\t";
    for(int i=0; i<2*P-R; i++) cout << "\t";
    cout << l << "\t";
    for(int i=L; i<P-1; i++) cout << "-\t";
    cout << p << "\t";
    for(int i=P; i<R-1; i++) cout <<"-\t";
    cout << r << "\t";
    cout << endl;
}


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
 
    cout << setw(LW) << "input:\t" << s << endl;
    cout << setw(LW) << "id:\t";
    for(int i=0; i<n; i++) cout << i << "\t";
    cout << setw(10) << "\nmanacher:\t";
    for(auto i: ss) cout << i << "\t";
    showGraph(L, P, R, 'L', 'P', 'R');

    for(int i=0; i<10; i++) cout << " ";
    for(int i=0; i< n; i++) cout << "- - ";
    cout << endl;


    for(int i=2; i<n-2; i++)
    {
        int j = 2 * P - i;

        if(i < R && j - cc[j] != P - cc[P])     // j的左端点与P的左端点不重合
            cc[i] = min(cc[j], R - i - 1);      // i的半径对齐j或者P的半径
        else
        {
            L = 2 * i - R;
            while(ss[L]==ss[R]) --L, ++R;       // 因为有哨兵不用担心越界
            cc[i] = R - i - 1;
            P = i;
        }

        cout << "\n[i = " << setw(2) << setfill(' ') << i <<"]:\t";
        for(int id=0; id<n; id++) 
            if(id+1 == j)
                cout << cc[id] << " ->";
            else if(id == i)
                cout << cc[id] << "<-" << " ";
            else
                cout << cc[id] << "   ";
        
        showGraph(L, P, R, 'L', 'P', 'R');
    }

    cout << endl << setw(LW) << "ans:\t";
    for(int i=0; i<n-2; i++)
    {
        if(i<2) cout << "\t";
        else if(i % 2) cout << cc[i] << "'\t";
        else cout << cc[i] << "\t";
    }
    return cc;
}




int main()
{
    using std::cout;

    string s = "abbab";
    // cin >> s;
    
    mark_manacher(s);
}