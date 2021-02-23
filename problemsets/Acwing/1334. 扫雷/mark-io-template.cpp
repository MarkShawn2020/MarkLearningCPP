//
// Created by 南川 on 2021/1/28.
//
#include "cstdio"
#include "cstring"
#include "cmath"

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

using namespace std;

template <typename T>
void run(T & cin)
{

}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    // read from local case if possible, otherwise from console
    ifstream fin("../POJ/P2367-Genealogical tree/case1.txt");
    run(fin.good() ? fin : cin);
}

