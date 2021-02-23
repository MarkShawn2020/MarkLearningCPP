//
// Created by 南川 on 2021/1/9.
//


class Solution {
public:
    vector<int> findState(vector<vector<int>>& s, int low){
        int states[4] = {s[0][1]-s[0][0], s[0][1]-s[1][0], s[1][1]-s[1][0], s[1][1]-low};
        int low_i = 0;
        int low_v = 1e5+1;
        for(int i=0; i<4; i++){
            if(states[i] < low_v)
            {
                low_i=i;
                low_v = states[i];
            }
        }
        return {low_i, low_v};
    }

    int maxProfit(vector<int>& prices) {
        int N = prices.size();
        if(N<2) return 0;

        vector<vector<int>> s;
        bool bought = false;

        int low = prices[0];
        int p;

        for(int i=1; i<N; i++)
        {
            p = prices[i];
            if(bought)
            {
                if(p>=s[s.size()-1][1]) { // 在更高点卖出
                    s[s.size()-1] = {low, p};
                }
                else{   // 新的一轮买点
                    bought = false;
                    low = p;
                }
            }else{
                if(p<=low) low = p;
                else{
                    // cout <<  "i=" << i << ", low=" << low << ", p=" << p <<  endl;
                    if(s.size()<2)
                    {
                        s.push_back({low, p});
                        bought = true;
                    }
                    else{
                        vector<int> preState = findState(s, low);
                        // for(int i=0; i<s.size(); i++)
                        //     {
                        //         cout << "{" << s[i][0] << "," << s[i][1] << "}, ";
                        //     }
                        // cout << "low: " << low << ", p: " << p;
                        // cout << endl;
                        // cout << "preState: " << preState[0] << ": " << preState[1] << endl;

                        if(p-low>preState[1]){
                            bought = true;
                            switch(preState[0]){
                                case 0:{
                                    s.erase(s.begin()+0);
                                    s.push_back({low, p});
                                    break;
                                }
                                case 1:{
                                    s.push_back({s[0][0], s[1][1]});
                                    s.erase(s.begin()+0, s.begin()+2);
                                    s.push_back({low, p});
                                    break;
                                }
                                case 2:{
                                    s.erase(s.begin()+1);
                                    s.push_back({low, p});
                                    break;
                                }
                                case 3:{
                                    s.push_back({s[1][0], p});
                                    s.erase(s.begin()+1);
                                    break;
                                }
                            }
                        }

                    }
                }
            }
        }

        // 计算盈利
        int ans = 0;
        for(int i=0; i<s.size(); i++)
        {
            ans+= s[i][1] - s[i][0];
            // cout << "{" << s[i][0] << "," << s[i][1] << "}, ";
        }
        return ans;
    }
};