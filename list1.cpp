#include "list1.h"

// list 5
ListNode* Solution2::endOfFirstHalf(ListNode* head) {
    ListNode* fast = head;
    ListNode* slow = head;
    while(fast->next != nullptr && fast->next->next != nullptr){
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

// list 4
bool Solution2::isPalindrome(ListNode* head) {
    if(head == nullptr)
        return true;

    ListNode* firstHalfEnd = endOfFirstHalf(head);
    ListNode* sencondHalfStart = reverseList(firstHalfEnd->next);

    ListNode* p1 = head;
    ListNode* p2 = sencondHalfStart;

    bool res(true);

    while(res && p2 != nullptr){
        if(p1->val != p2->val){
            res = false;
        }
        p1 = p1->next;
        p2 = p2->next;
    }

    firstHalfEnd->next = reverseList(sencondHalfStart);
    return res;
}


// list 3
ListNode* Solution2::reverseList(ListNode* head) {
    ListNode* newlist = NULL;
    while(head){
        ListNode* next = head->next;
        head->next = newlist;
        newlist = head;
        head = next;
    }
    return newlist;
}

// list 2: {1,1,2,3} -> {2,3}
ListNode* Solution2::deleteDuplicates2(ListNode* head) {
    ListNode* dummy = new ListNode(0,head);
    ListNode* cur = dummy;
    while(cur->next && cur->next->next){
        if(cur->next->val == cur->next->next->val){
            int x=cur->next->val;
            while(cur->next && x == cur->next->val)
                cur->next = cur->next->next;
        } else
            cur = cur->next;
    }
    return dummy->next;
}
// list 1: {1,1,2,3} -> {1,2,3}
ListNode* Solution2::deleteDuplicates1(ListNode* head) {
    ListNode* cur = head;
    while(cur->next){
        if(cur->val == cur->next->val){
            cur->next = cur->next->next;
        } else {
            cur = cur->next;
        }
    }
    return head;
}
