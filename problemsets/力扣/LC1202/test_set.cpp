#include <iostream>
#include <set>
#include <string>
using namespace std;

int main()
{
    //创建并初始化set容器
    std::set<std::string> myset  {
        "http://c.biancheng.net/java/",
        "http://c.biancheng.net/stl/",
        "http://c.biancheng.net/python/"
    };
    auto iter = myset.find("http://c.biancheng.net/python/");
    for (;iter != myset.end();iter++)
    {
        cout << *iter << endl;
    }
    return 0;
}
