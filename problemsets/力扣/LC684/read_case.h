//
// Created by 南川 on 2021/1/13.
//

#ifndef MARKLEARNINGCPP_READ_CASE_H
#define MARKLEARNINGCPP_READ_CASE_H

#endif //MARKLEARNINGCPP_READ_CASE_H

#include "iostream"
#include "fstream"
#include "sstream"
#include "vector"
using namespace std;

vector<vector<int>> readCase(const string& fp)
{
    vector<vector<int>> vv;
    string s;
    fstream f(fp);
    f >> s;
    for(auto & i: s) if(!isdigit(i))  i=' ';
    stringstream ss;
    ss << s;
    int k1, k2;
    while (ss >> k1 >> k2)
        vv.emplace_back(vector<int>{k1, k2});
    return vv;
}