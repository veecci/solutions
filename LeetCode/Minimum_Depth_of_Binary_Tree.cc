/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int const inf = 0x3f3f3f3f;
    int minDepth(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int ret = inf;
        if (root == NULL) return 0;
        if (root -> left != NULL) ret = min(ret, minDepth(root -> left) + 1);
        if (root -> right != NULL) ret = min(ret, minDepth(root -> right) + 1);
        if (ret == inf) return 1;
        else return ret;
    }
};
