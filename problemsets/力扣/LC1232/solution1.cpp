//
// Created by 南川 on 2021/1/17.
//

#include "vector"
#include "iostream"

using namespace std;


class Solution {
public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {
        int N = coordinates.size();
        if(N < 3) return true;

        int x0 = coordinates[0][0];
        int y0 = coordinates[0][1];

        if(x0 == coordinates[1][0])  // 横坐标相同，一条纵线
        {
            for(int i=2; i<N; i++)
                if(coordinates[i][0] != x0)
                    return false;
            return true;
        }

        if(y0 == coordinates[1][1])  // 纵坐标相同，一条横线
        {
            for(int i=2; i<N; i++)
                if(coordinates[i][1] != y0)
                    return false;
            return true;
        }

        double k = double (coordinates[1][1] - y0) / double (coordinates[1][0] - x0);
        double b = y0 - k * x0;

        for(int i=2; i<N; i++)
            if(coordinates[i][1] != coordinates[i][0] * k + b)
                return false;
        return true;
    }
};

int main()
{
    vector<vector<int>> coordinates = {{2,1}, {4,2}, {6,3}};
    Solution slt;
    cout.setf(ios_base::fixed);
    cout << slt.checkStraightLine(coordinates);
}