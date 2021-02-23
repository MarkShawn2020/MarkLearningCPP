//
// Created by 南川 on 2021/1/25.
//
#include "cstdio"
#include "vector"

using std::vector;

class SegmentTree{
private:
    const int n;
    const int size;
    vector<int> data;

public:
    explicit SegmentTree(int n): n(n), size(2*n+2), data(size, 0){}

    void add(int i, int v)
    {
        data[i+n] = v;
    }

    void construct()
    {
        for(int i=n; i>0; i--)
            data[i] = data[i << 1] + data[i << 1 | 1];
    }

    void update(int i, int v)
    {
        for(i=i+n; i>0; i>>=1)
            data[i] += v;
    }

};

int main()
{
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/洛谷/P3372 【模板】线段树 1/case1.txt", "r", stdin);

    int n, m, r1, r2, r3, r4;
    scanf("%d %d", &n, &m);

    /**
     * construct
     */
    SegmentTree st(n);
    for(int i=1; i<=n; i++)
        scanf("%d", &r1), st.add(i, r1);
    st.construct();

    for(int i=1; i<=m; i++)
    {
        scanf("%d %d %d", &r1, &r2, &r3);
        if(r1 == 1)
        {
            scanf("%d", &r4);
            while (r2 <= r3)
                st.add(r2, r4), ++r2;
        } else if(r1 == 2)
        {

        }

    }





    return 0;



}