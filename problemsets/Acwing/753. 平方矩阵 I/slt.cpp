//
// Created by 南川 on 2021/1/18.
//

#include "cstdio"
#include "vector"

using namespace std;


void out(int k)
{
    vector<vector<int>> arr(k, vector<int>(k, 0));
    for(int offset=0; offset<k; offset+=1)
        for(int i=offset; i<k-offset; i++)
            for(int j=offset; j<k-offset; j++)
                arr[i][j] += 1;
    for(int i=0; i<k; i++){
        for(int j=0; j<k; j++){
            printf("%d", arr[i][j]);
            if(j!=k-1)
                printf(" ");
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/Acwing/ACW753/case1.txt", "r", stdin);
    int k;
    while(true){
        scanf("%d", &k);
        if(k)
            out(k);
        else
            break;
    }
}