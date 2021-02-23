//
// Created by 南川 on 2021/2/17.
//
#include "cstdio"

using namespace std;

const int N = 1000 + 1;
int n, m, k, d;
int sources[N][2];
int destinations[N][3];
int obstacles[N][2];


int


int main()
{
    scanf("%d %d %d %d", &n, &m, &k, &d);
    for(int i=1; i<=m; ++i)
        scanf("%d", &sources[i][0]),
        scanf("%d", &sources[i][1]);
    for(int i=1; i<=k; ++i)
        scanf("%d", &destinations[i][0]),
        scanf("%d", &destinations[i][1]),
        scanf("%d", &destinations[i][2]);
    for(int i=1; i<=d; ++i)
        scanf("%d", &obstacles[i][0]),
        scanf("%d", &obstacles[i][1]);



}