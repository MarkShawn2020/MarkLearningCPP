//
// Created by 南川 on 2021/1/22.
//

#include "cstdio"
#include "string"

using std::string;
using std::to_string;

class T {
    int n = 1;
    int m = 2;

public:
    explicit operator char*() const{
        char * c = new char[25];
        int i = -1;
        c[++i] = 'n';
        c[++i] = '=';
        for(char const & ch: to_string(n))
            c[++i] = ch;
        c[++i] = ',';
        c[++i] = ' ';
        c[++i] = 'm';
        c[++i] = '=';
        for(char const & ch: to_string(m))
            c[++i] = ch;
        c[++i] = '\0';
        return c;
    }
};


int main()
{
    T t;
    printf("%s", (char*) t);
}