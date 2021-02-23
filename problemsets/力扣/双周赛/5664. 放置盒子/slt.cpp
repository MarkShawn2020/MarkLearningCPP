//
// Created by 南川 on 2021/1/24.
//
#include "cmath"
#include "iostream"

using namespace std;

class Solution {
public:
    int minimumBoxes(int n) {
        if(n < 4) return n;

        int kBase = int(pow(n, 1.0 / 3) * pow(6, 1.0 / 3)) - 1;
        int nBase = ceil(1.0 / 6 * kBase * (kBase+1) * (kBase+2));
        int ans = ceil(1.0 / 2 * kBase * (kBase+1));

        int i = 0;
        while(nBase < n)
            nBase += ++i, ++ans;

        return ans;
    }
};


int main()
{
    Solution slt;
    cout << slt.minimumBoxes(615);
}

