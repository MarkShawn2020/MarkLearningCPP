//
// Created by 南川 on 2021/1/21.
//
#include "./MarkReadCase.h"

#include "sstream"
vector<int> readIntVector1D(string s)
{
    vector<int> ret;

    for(char & ch: s)
        if(!isdigit(ch) && ch!='-' && ch!='+')
            ch = ' ';

    std::stringstream ss;
    ss << s;
    int t;
    while (ss >> t)
        ret.push_back(t);
    return ret;
}

vector<vector<int> > readIntVector2D(string s)
{
    vector<vector<int> > ret;

    for(int i=0; i<s.size()-2; i++)
        if(s[i]==']' && s[i+1]==',' && s[i+2]=='[')
            s[i+1] = ' ';

    stringstream ss;
    ss << s;
    while (ss >> s)
        ret.push_back(readIntVector1D(s));
    return ret;
}