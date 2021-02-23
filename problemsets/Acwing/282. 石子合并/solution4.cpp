//
// Created by 南川 on 2021/1/17.
//

#include "climits"
#include "cstdio"
#include "array"
#include "vector"
using namespace std;

static const int N = 300;

int cost(const vector<int>& arr){
    if(arr.size() == 1) return arr[0];
    if(arr.size() == 2) return arr[0] + arr[1];
    
}

int main(){
    int ans = 0;
    int n;
    array<int, N> arr{};
    array<array<int,2>, N> pre_next{};
    for(int i=0; i<N; i++){
        pre_next[i][0] = i - 1;
        pre_next[i][1] = i + 1;
    }

//    n = 5; arr = {548, 592, 715, 844, 602}; // ans=7742
//    scanf("%d", &n); for(int i=0; i<n; i++) scanf("%d", &(arr[i]));
    n = 10;
    arr = {548 ,592, 715 ,844, 602,
           857, 544 ,847, 423 ,623};




    printf("%d", ans);
    return 0;
}