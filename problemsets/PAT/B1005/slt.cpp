//
// Created by 南川 on 2021/1/23.
//


#include "unordered_map"

using namespace std;

int main()
{
    unordered_map<char, const char*> mp = {
            {'0', "zero"},
            {'1', "one"},
            {'2', "two"},
            {'3', "three"},
            {'4', "four"},
            {'5', "five"},
            {'6', "six"},
            {'7', "seven"},
            {'8', "eight"},
            {'9', "nine"}
    };

    int n = 0;
    char c;
    while (scanf("%c", &c) && c!='\n')
        n += c - '0';

    char cs[11];
    sprintf(cs, "%d", n);
    printf("%s", mp[cs[0]]);
    for(int i=1; cs[i]!=0; ++i)
        printf(" %s", mp[cs[i]]);
    printf("\n");
};