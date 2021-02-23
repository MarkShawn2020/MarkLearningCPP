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
    class Solution {
    public:
        typedef vector<vector<bool>> vvb;
        typedef vector<vector<string>> vvs;

        vector<vector<string>> & output(string & s, vvb & dt, int left, int right)
        {
            vvs ans;
            for(int d=0; d<=right-left; d++)
            {
                if(dt[d][left])
                    for(auto out: output(s, dt, 0, left-1))
                    {
                        vector<string> temp;
                        temp.push_back(s.substr(left, d+1));
                        temp.insert(temp.end(), out.begin(), out.end());
                        ans.push_back(temp);
                    }
            }
            return ans;
        }


        vector<vector<string>> partition(string s) {
            const int N = s.size();
            vvb dt(N, vector<bool>(N, true));

            for(int k=1; k<N-1; k++)
                for(int i=0; i<N-k; i++)
                    dt[k][i] = s[i] == s[i+k] && dt[k-1][i+1];

            return output(s, dt, 0, N-1);
        }
    };

}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    // read from local case if possible, otherwise from console
    ifstream fin("../POJ/P2367-Genealogical tree/case1.txt");
    run(fin.good() ? fin : cin);
}

