#include "iostream"
#include "ctime"
#include "vector"

using namespace std;

int dp[5] {3, 1, 2, 5, 4};
vector<int> dp2{3, 1, 2, 5, 4};


void testRun(void func(), int epochs)
{
    clock_t stt = clock(), end;
    while(epochs--) func();
    end = clock();
    cout << "time used: " << (float)(end - stt) / CLOCKS_PER_SEC << endl;
}

void iter_by_ind()
{
    int i, v;
    for(int i=0; i<dp2.size(); i++)
        i = i, v = dp2[i];
}

void iter_by_val()
{
    int i, v;
    for(int & x: dp2)
        i = &x-&dp2[0], v = x;
}

int main()
{
    const int Epochs = 1e8;
    testRun(iter_by_ind, Epochs);
    testRun(iter_by_val, Epochs);
}