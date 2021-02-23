#include "iostream"
#include "vector"
#include "cstdio"
#include "array"

using namespace std;



int main()
{

    vector<int> v{3, 4, 1, 3, 2};
    arrar<int, 8> a{{1, 2, 3, 4, 5, 6, 7, 8}};

    v.resize(2);
    a.resize(2);

    int i = 0;
    for(auto k: a)
        printf("%d: %d\t", i++, k);
    printf("\n");


}