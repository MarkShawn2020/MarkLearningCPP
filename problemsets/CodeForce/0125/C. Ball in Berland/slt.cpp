//
// Created by 南川 on 2021/1/25.
//

#include "cstdio"
#include "vector"
//#include "string"
//using std::fill;
using std::vector;
// 
const int N = 200000 + 1;

int getAns(vector<vector<int> > & G, const int & a, const int & b)
{
    int ans = 0;
    for(int boy1=1; boy1 <= a; boy1++)
    {
        if(!G[boy1].empty())
        {
            for (int girl1: G[boy1])
            {
                for (int boy2 = boy1 + 1; boy2 <= a; boy2++)
                {
                    if (!G[boy2].empty())
                    {
                        for (int girl2: G[boy2])
                        {
                            if (girl2 != girl1)
                                ++ans;
                        }
                    }
                }
            }
        }
    }
    return ans;
}


int main()
{
   freopen(
    "/Users/mark/CLionProjects/MarkLearningCPP/CodeForce/0125/C. Ball in Berland/case1.txt", "r", stdin);

    int n, a, b, k;

    scanf("%d", &n);
    while (n>0)
    {
        n--;
        scanf("%d %d %d", &a, &b, &k);
        vector<int> tempA(k);
        vector<int> tempB(k);
        vector<vector<int>> G(N);
        for(int i=0; i<k; i++)
            scanf("%d", &tempA[i]);
        for(int i=0; i<k; i++)
            scanf("%d", &tempB[i]);
        for(int i=0; i<k; i++)
            G[tempA[i]].emplace_back(tempB[i]);

        printf("%d", getAns(G, a, b));
        if(n) printf("\n");

    }

}
