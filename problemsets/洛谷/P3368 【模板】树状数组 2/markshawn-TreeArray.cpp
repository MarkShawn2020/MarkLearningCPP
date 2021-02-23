//
// Created by 南川 on 2021/1/25.
//

#ifndef MARKLEARNINGCPP_TREEARRAY_H
#define MARKLEARNINGCPP_TREEARRAY_H

#include "cstdio"
#include "string"


class TreeArray {

private:
    const int size;
    static inline int lowBit(const int & x){return x & -x;}

protected:
    int pos = 0;
    int * data {} ;

    void add_(int i, int v)
    {
        while (i <= size)
            data[i] += v, i += lowBit(i);
    }

public:
    ~TreeArray()= default;

    explicit TreeArray(int n): size(n){
        data = new int[n];
        std::fill(data, data+n, 0);
    }

    virtual void add(int v)
    {
        add_(++pos, v);
    }

    int getPreSum(int i)
    {
        int ans = 0;
        while (i > 0)   // 暗含gePreSum(0) = 0
            ans += data[i], i -= lowBit(i);
        return ans;
    }

    virtual int getOne(int i)
    {
        return getPreSum(i) - getPreSum(i-1);
    }

    virtual int getRangeSum(int i, int j)
    {
        return getPreSum(j) - getPreSum(i-1);
    }

    void printData()
    {
        for(int i=1; i<=size; i++)
            printf("%d\t", data[i]);
        printf("\n");
    }

};


class DeltaTreeArray: public TreeArray {

private:
    int temp = 0;

public:
    explicit DeltaTreeArray(int n): TreeArray(n){}

    void add(int v) override {
        TreeArray::add(v - temp), temp = v;
    }

    void rangePlus(int i, int j, int v)
    {
        TreeArray::add_(i, v);
        TreeArray::add_(j + 1, -v);
    }

    int getOne(int i) override
    {
        return TreeArray::getPreSum(i);
    }

};

#endif //MARKLEARNINGCPP_TREEARRAY_H


int main()
{
//    freopen("/Users/mark/CLionProjects/MarkLearningCPP/洛谷/P3368 【模板】树状数组 2/case1.txt", "r", stdin);

    int n, m, r1, r2, r3, r4 = 0;
    scanf("%d %d", &n, &m);

    DeltaTreeArray dta(n);

    for(int i=1; i<=n; i++) // 要从1开始
        scanf("%d", &r1), dta.add(r1);

    for(int i=0; i<m; i++)
    {
//        dta.printData();

        scanf("%d %d", &r1, &r2);
        if(r1 == 2)
            printf("%d\n", dta.getOne(r2));
        else
        {
            scanf("%d %d", &r3, &r4);
            dta.rangePlus(r2, r3, r4);
        }

    }

}