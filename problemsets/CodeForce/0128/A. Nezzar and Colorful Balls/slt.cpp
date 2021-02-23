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

template <typename T>
void run(T & cin)
{
    const int N = 100 + 1;
    int n, m, r1;
    cin >> n;
    while (n--)
    {
        cin >> m;
        vector<int> dta(m+1, 0);
        for(int i=1; i<=m; i++)
        {
            cin >> r1;
            dta[r1]++;
        }
        int ans = 0;
        while (true)
        {
            int d = 0;
            for(int & deg: dta)
            {
                if(deg > 0)
                {
                    deg--;
                    d++;
                }
            }
            if(d == 0)
                break;
            else
                ans++;
        }
        cout << ans << endl;

    }

}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    // read from local case if possible, otherwise from console
    ifstream fin("../CodeForce/0128/A. Nezzar and Colorful Balls/case1.txt");
    run(fin.good() ? fin : cin);
}

