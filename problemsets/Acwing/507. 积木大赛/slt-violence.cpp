#include "iostream"

using namespace std;

const int H = 1e5 + 1;
const int N = 1e5 + 1;
int n, hi, ans, arr[N];
bool finished = false;

void print(int stt, int end)
{
    printf("ans: %d, stt: %d, end: %d, arr: ", ans, stt, end);
    for(int i=0; i<n; i++) cout << arr[i] << " ";
    cout << endl;
}

/**
 * 不判别最后一个，可以通过8个
 * 判别最后一个，可以通过9个
 */ 
void plusAns(int stt, int end)
{
    print(stt, end);
    int i = stt;
    while(i < end)
    {
        while(i < end && arr[i] == 0) i++;
        int j = i;
        while(j < end && arr[j] >  0) arr[j]--, j++;
        if(i < j)
            if(j - i == 1) 
                ans += arr[i] + 1;
            else 
                ans++,
                plusAns(i, j);
        else;
        i = j;
    }
}

int main()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/507. 积木大赛/case3.txt", "r", stdin);
    cin >> n;
    for(int i=0; i<n; i++)
        cin >> arr[i];

    plusAns(0, n);
    cout << ans;
}