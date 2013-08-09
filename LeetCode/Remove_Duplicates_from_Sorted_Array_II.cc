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
        ListNode *ret = head, *pre = head;
        while (head != NULL) {
            if (head -> next != NULL && head -> val == head -> next -> val) {
                int now = head -> val;
                while (head != NULL && head -> val == now) {
                    head = head -> next;
                }
                if (ret -> val == now) ret = head;
                pre -> next = head;
                
            }
            else {
                pre = head;
                head = head -> next;
            }
            
        }
        return ret;
    }
};
