#include "set"
#include "unordered_set"
#include "vector"
#include "ctime"
#include "iostream"
#include "cstdio"
#include "functional"
#include "array"

using namespace std;

void ctime(function<void()> f, const char * fn)
{
    clock_t b = clock();
    f();
    printf("%30s: seconds: %.4f\n", fn, float((clock() - b)) / CLOCKS_PER_SEC);
}


int main()
{
    const int N = 2e6;

    

    printf("Ttest set/insert efficience（including declaration） with N: %d\n--------\n", N);

    ctime(function<void()>( [](){int ds1[N];                for(int i=0; i<N; i++) ds1[i] = i;       } ), "default array(preSized)");
    ctime(function<void()>( [](){vector<int> vs2(N);        for(int i=0; i<N; i++) vs2[i] = i;       } ), "vector(preSized)");
    ctime(function<void()>( [](){array<int, N> as1;         for(int i=0; i<N; i++) as1[i] = i;       } ), "stl array(preSized)");
    ctime(function<void()>( [](){vector<int> vs1;           for(int i=0; i<N; i++) vs1.push_back(i); } ), "vector(default with push)");
    ctime(function<void()>( [](){unordered_set<int> us2(N); for(int i=0; i<N; i++) us2.insert(i);    } ), "unordered_set(preSized)");
    ctime(function<void()>( [](){unordered_set<int> us1;    for(int i=0; i<N; i++) us1.insert(i);    } ), "unordered set(defualt)");
    ctime(function<void()>( [](){set<int> os1;              for(int i=0; i<N; i++) os1.insert(i);    } ), "set(default)");
     
}