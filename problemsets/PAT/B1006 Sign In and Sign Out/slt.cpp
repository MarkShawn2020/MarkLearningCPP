//
// Created by 南川 on 2021/1/23.
//

#include "cstdio"
#include "cstring"

bool Greater(const char s1[], const char s2[])
{
    for(int i=0; i<9; i++)
        if(s1[i] > s2[i])
            return true;
        else if(s1[i] < s2[i])
            return false;
    return false;
}

int main()
{
    int n;
    scanf("%d", &n);

    char name1[16], name2[16];
    char time1[9] = "23:59:59", time2[9] = "00:00:00";

    for(int i=0; i<n; i++)
    {
        char name[16], t1[9], t2[9];
        scanf("%s %s %s", name, t1, t2);
        if(Greater(time1, t1))
            strcpy(time1, t1), strcpy(name1, name);
        if(Greater(t2, time2))
            strcpy(time2, t2), strcpy(name2, name);
    }

    printf("%s %s\n", name1, name2);
}