#include "iostream"

using namespace std;

const int H = 1e5 + 1;
const int N = 1e5 + 1;
int n, hi, last, ans, arr[N];

void print(int stt, int end)
{
    printf("ans: %d, stt: %d, end: %d, arr: ", ans, stt, end);
    for(int i=0; i<n; i++) cout << arr[i] << " ";
    cout << endl;
}


int main()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/507. 积木大赛/case3.txt", "r", stdin);
    cin >> n;
    while(n--)
    {
        cin >> hi;
        if(hi > last) 
            ans += hi - last;
        last = hi;
    }
    cout << ans;
}