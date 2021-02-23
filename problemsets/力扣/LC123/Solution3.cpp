//
// Created by 南川 on 2021/1/9.
//

class Solution {
public:

    void chipChains(vector<int>& trades)
    {
        int min_i = 0;
        int min_v = trades[0] + trades[1];
        for(int i=1; i<trades.size()-1; i++)
        {
            if(trades[i]+trades[i+1]<min_v)
            {
                min_i = i;
                min_v = trades[i]+trades[i+1];
            }
        }
        trades.erase(trades.begin()+min_i, trades.begin()+min_i+2);
        cout << endl;
    }

    int maxProfit(vector<int>& prices) {
        int b0 = 0;
        int b1 = -prices[0];
        int s1 = 0;
        int b2 = -prices[0];
        int s2 = 0;
        if(prices.size()<2) return 0;

        for(int i=1;i<prices.size(); i++)
        {
            b1 = max()

        }
    }
};