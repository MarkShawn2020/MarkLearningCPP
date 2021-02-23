#include <iostream>
using namespace std;

void func_1()
{


    void wrapped_func_1();



    void wrapped_func_1()
    {
        cout << "wrapped_func_1" << endl;
    }

    cout << "func_1" << endl;
}

int main()
{
    func_1();

}