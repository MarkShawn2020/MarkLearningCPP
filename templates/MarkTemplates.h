//
// Created by 南川 on 2021/2/23.
//
#include "cstdio"
#include "cstring"
#include "cmath"
#include "cassert"

#include "string"
#include "iostream"
#include "fstream"
#include "algorithm"

#include "vector"
#include "stack"
#include "list"
#include "queue"
#include "set"
#include "unordered_set"
#include "map"
#include "unordered_map"
#include "iterator"

using namespace std;

#define Min(a, b) if((b)<(a)) (a) = (b)
#define Max(a, b) if((b)>(a)) (a) = (b)

#include "io/MarkReadCase.h"
#include "ds/prestar/MarkPreStar.h"

template<typename A> ostream & operator << (ostream & cout, vector<A> const &v) { cout << "["; for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]"; }

namespace mark {
    template<typename T> void printSTL(T A, T B, const char * name="STL") {cout << setw(10) << name << ": [";while(A!=B) cout<<*A<<", ", ++A; cout << "\b\b]\n";}
    void printIntArray(int *arr, int n, const char * name="");
    void printIdArray(int n, const char * name="");
}

