/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *deleteDuplicates(ListNode *head) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode *ret = head;
        while (head != NULL) {
            while (head -> next != NULL && head -> val == head -> next -> val) {
                head -> next = head -> next -> next;
            }
            head = head -> next;
        }
        return ret;
    }
};
