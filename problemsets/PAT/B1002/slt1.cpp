//
// Created by 南川 on 2021/1/18.
//

#include "cstdio"

const int K = 1000 + 1;
float a[K];

int main()
{
//    freopen("/Users/mark/CLionProjects/MarkLearningCPP/PAT/B1002/case1.txt", "r", stdin);

    int k1, k2, ni;
    float ai;

    scanf("%d", &k1);
    for(int i=0; i<k1; ++i){
        scanf("%d %f", &ni, &ai);
        a[ni] += ai;
    }

    scanf("%d", &k2);
    for(int i=0; i<k2; ++i){
        scanf("%d %f", &ni, &ai);
        a[ni] += ai;
    }

    int ks = 0;
    for(int i=0; i<K; ++i)
        if(a[i])
            ++ks;
    printf("%d ", ks);

    for(int i=K-1; i>-1; i--)
    {
        if(a[i]){
            printf("%d %.1f", i, a[i]);
            if(--ks)
                printf(" ");
        }
    }
}