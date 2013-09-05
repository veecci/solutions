class Solution {
public:
    vector<int> plusOne(vector<int> &digits) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        reverse(digits.begin(), digits.end());
        ++digits[0];
        for (int i = 0; i < digits.size(); ++i) {
            if (digits[i] == 10) {
                digits[i] = 0;
                if (i == digits.size() - 1) {
                    digits.push_back(1);
                }
                else {
                    ++digits[i+1];
                }
            }
        }
        reverse(digits.begin(), digits.end());
        return digits;
    }
};
