//
// Created by 南川 on 2021/1/11.
//

#include "vector"
#include "iostream"
using namespace std;

int main(){
    vector<int>v(3);
    v.push_back('a');

    for(int i=0; i<v.size(); i++)
    {
        v.erase(v.begin()+i);
        cout << "i=" << i << ", v=" << v[i] <<endl;
    }
    return 0;
}