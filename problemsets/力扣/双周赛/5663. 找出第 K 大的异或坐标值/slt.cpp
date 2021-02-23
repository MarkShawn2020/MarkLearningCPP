//
// Created by 南川 on 2021/1/24.
//
#include "vector"
#include "set"
using namespace std;
class Solution {
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        const int rows = matrix.size();
        const int cols = matrix[0].size();

        vector<vector<int>> m2(matrix);
        set<int, greater<>> st;
        vector<int> singleRow(cols);

        for(int row=0; row<rows; row++)
            for(int col=0; col<cols; col++)
            {
                singleRow[col] = col ?  singleRow[col-1] ^ matrix[row][col] :matrix[row][col];
                st.insert(m2[row][col] = row ? m2[row-1][col] ^ singleRow[col] : singleRow[col]);
            }

        auto iter = st.begin();
        advance(iter, k-1);
        return *iter;
    }
};