//
// Created by 南川 on 2021/1/28.
//

//
// Created by 南川 on 2021/1/28.
//

#include "fstream"
#include "iostream"
#include "vector"
#include "queue"

using namespace std;

bool judge(int v, int d)
{
    if(v >= d * 10)
        return true;
    if(v % d == 0)
        return true;
    for(int i=1; i<10; i++)
        if(v < i * d)
            return false;
        else if((v - i * d) % 10 == 0)
            return true;
}

template <typename T>
void run(T & cin)
{
    int tt, q, d, r1;
    cin >> tt;
    while (tt--)
    {
        cin >> q >> d;
        while (q--)
        {
            cin >> r1;
            cout << (judge(r1, d) ? "YES" : "NO") << endl;
        }
//        cout  << endl;
    }

}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    // read from local case if possible, otherwise from console
    ifstream fin("../CodeForce/0128/B. Nezzar and Lucky Number/case1.txt");
    run(fin.good() ? fin : cin);
}

