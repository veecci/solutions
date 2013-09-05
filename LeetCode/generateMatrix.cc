class Solution {
public:
    int mp[100][100];
    
    vector<vector<int> > generateMatrix(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function  
        int dir[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
        memset(mp, 0, sizeof mp);
        int x = 0, y = 0, tx, ty, d = 0, m = n * n;
        for (int i = 1; i < m; ++i) {
            mp[x][y] = i;
            tx = x + dir[d][0], ty = y + dir[d][1];
            if (tx >= 0 && tx < n && ty >= 0 && ty < n && mp[tx][ty] == 0) {
                x += dir[d][0], y += dir[d][1];    
            }
            else {
                d = (d + 1) & 3;
                --i;
            }  
        }
        mp[x][y] = m;
        vector<vector<int> > ret;
        for (int i = 0; i < n; ++i) {
            vector<int> tmp;
            for (int j = 0; j < n; ++j) {
                tmp.push_back(mp[i][j]);
            }
            ret.push_back(tmp);
        }
        return ret;
    }
};
