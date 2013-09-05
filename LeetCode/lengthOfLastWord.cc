class Solution {
public:
    int lengthOfLastWord(const char *s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int ret = 0, len = strlen(s);
        int now = len - 1;
        while (s[now] == ' ') --now;
        for (int i = now; i >= 0 && s[i] != ' '; --i) ++ret;
        return ret;
    }
};
