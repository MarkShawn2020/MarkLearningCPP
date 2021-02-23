//
// Created by 南川 on 2021/1/21.
//

#include "vector"
#include "iostream"

using namespace std;

void testAddr(vector<int> a, vector<int> & b)
{
    cout << "func:\n";
    cout << "&a: " << &a << ", &b: " << &b << endl;
}

vector<int> testReturn()
{
    vector<int> a (1);
    cout << "func: \n";
    cout << "&a: " << &a << endl;
    return a;
}


int main()
{
    vector<int> b;

    cout << "main: \n";
    cout << "&b: " << &b << endl;

    b = testReturn();
    cout << "&b: " << &b << endl;



//    vector<int> a(1);
//    vector<int> b(1);
//    cout << "main:\n";
//    cout << "&a: " << &a << ", &b: " << &b << endl;
//    testAddr(a, b);

    return 0;
}