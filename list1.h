#ifndef LIST1_H
#define LIST1_H
#include "pub.h"

class Solution2 {
public:
    // list 5
    ListNode* endOfFirstHalf(ListNode* head);
    // list 4
    bool isPalindrome(ListNode* head);
    // list 3
    ListNode* reverseList(ListNode* head);
    // list 2: {1,1,2,3} -> {2,3}
    ListNode* deleteDuplicates2(ListNode* head);
    // list 1: {1,1,2,3} -> {1,2,3}
    ListNode* deleteDuplicates1(ListNode* head);
};

#endif // LIST_H
