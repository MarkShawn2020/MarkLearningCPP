//
// Created by 南川 on 2021/1/9.
//

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
        vector<int> trades;
        prices.push_back(-1);
        int N = prices.size();

        bool sellMode = false;
        int b = prices[0];
        int s;
        for(int i=1; i<N; i++)
        {
            if(!sellMode)                    // 买入价格待定模式
            {
                if(prices[i]<=b) b = prices[i];  // 买入价格进一步降低
                else {                           // 买入价格为原先的买价，卖出价格待定
                    sellMode = true;
                    s = prices[i];
                }
            }
            else                             // 卖出价格待定模式
            {
                if(prices[i]>=s) s = prices[i];  // 卖出价格进一步提高
                else{                            // 卖出价格为原先的卖价，交易成功
                    sellMode = false;
                    trades.push_back(-b);
                    trades.push_back(s);
                    b = prices[i];               // 买入价格待定
                }
            }
        }

        while(trades.size()>4) chipChains(trades);  // 剪枝

        int ans = 0;
        for(int i=0; i<trades.size(); i++) ans+= trades[i];
        return ans;
    }
};