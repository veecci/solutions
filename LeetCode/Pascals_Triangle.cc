class Solution {
public:
    vector<vector<int> > generate(int numRows) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int> > ret;
        vector<int> v0; v0.push_back(1);
        for (int i = 0; i < numRows; ++i) {
            ret.push_back(v0);
            for (int j = 1; j < i; ++j) {
                ret[i].push_back(ret[i-1][j] + ret[i-1][j-1]);
            }
            if (i > 0) ret[i].push_back(1);
        }
        return ret;
    }
};
