//
// Created by 南川 on 2021/1/19.
//

#include "cstdio"

#include "vector"

using namespace std;

void initPrevNext(vector<int> & prev, vector<int> & next, const vector<int> & data, const int n, const int avg){
    int prevPos, prevNeg, firstPos, firstNeg;
    for(int i=1; i<=n; i++){
        if(data[i] < avg){
            if(!firstNeg) firstNeg = i;
            if(!prevNeg) prevNeg = i;
            else {
                prev[i] = prevNeg;
                prevNeg = next[prevNeg] = i;
            }
        }else if(data[i] > avg){
            if(!firstPos) firstPos = i;
            if(!prevPos) prevPos = i;
            else {
                prev[i] = prevPos;
                prevPos = next[prevPos] = i;
            }
        }else
            prev[i] = next[i] = 0;
    }

    prev[firstPos] = prevPos; prev[firstNeg] = prevNeg;
    next[prevPos] = firstPos; next[prevNeg] = firstNeg;

}


int main()
{

    freopen("/Users/mark/CLionProjects/MarkLearningCPP/Acwing/ACW122/case1.txt", "r", stdin);

    int n;
    scanf("%d", &n);

    vector<int> data(n+1);
    int sum = 0;
    for(int i=1; i<=n; i++){
        scanf("%d", &data[i]);
        sum += data[i];
    }
    int avg = sum / n;

    vector<int> prev(n+1);
    vector<int> next(n+1);

    initPrevNext(prev, next, data, n, avg);




    return 0;
}