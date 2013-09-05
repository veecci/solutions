class Solution {
public:
    int minPathSum(vector<vector<int> > &grid) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int n = grid.size(), m = grid[0].size();
        int const inf = 0x3f3f3f3f;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int tmp = inf;
                if (i > 0) tmp = min(tmp, grid[i-1][j]);
                if (j > 0) tmp = min(tmp, grid[i][j-1]);
                if (tmp != inf) grid[i][j] += tmp;
            }
        }
        return grid[n-1][m-1];
    }
};
