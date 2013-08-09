class Solution {
public:
    pair <int, int> num[11111];
    vector<int> twoSum(vector<int> &numbers, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int n = numbers.size();
        for (int i = 0; i < n; ++i) {
            num[i] = make_pair(numbers[i], i + 1);
        }
        sort(num, num + n);
        int p = 0, q = n - 1;
        while (p < q) {
            if (num[p].first + num[q].first == target) {
                vector <int> ret;
                ret.push_back(num[p].second);
                ret.push_back(num[q].second);
                if (ret[0] > ret[1]) swap(ret[0], ret[1]);
                return ret;
            }
            while (num[p].first + num[q].first > target) --q;
            while (num[p].first + num[q].first < target) ++p;
        }
    }
};
