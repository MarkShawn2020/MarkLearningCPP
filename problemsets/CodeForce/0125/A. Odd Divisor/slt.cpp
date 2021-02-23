//
// Created by 南川 on 2021/1/25.
//

#include <bits/stdc++.h>

using namespace std;


int main()
{
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/CodeForce/0125/A. Odd Divisor/case1.txt", "r", stdin);

    unordered_set<long long > st;
    long long i = 2;
    for(int j=0; j<62; i<<=1, j++)
        st.insert(i);

    int n;
    scanf("%d", &n);
    long long v;
    while (n--)
    {
        scanf("%lld", &v);
        st.find(v) != st.end() ? printf("NO") : printf("YES");
        if(n) printf("\n");
    }
}

