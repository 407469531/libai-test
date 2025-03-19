#include "list1.h"
/*********************测试例子构造***********************/
void reverseListTest(){
    Solution2 so;
    ListNode* node1 = new ListNode(1);
    ListNode* node2 = new ListNode(2);
    ListNode* node3 = new ListNode(3);
    ListNode* node4 = new ListNode(4);
    ListNode* node5 = new ListNode(5);
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;

    so.reverseList(node1);
}

void isPalindromeTest(){
    Solution2 so;
    ListNode* node1 = new ListNode(1);
    ListNode* node2 = new ListNode(2);
    ListNode* node3 = new ListNode(3);
    ListNode* node4 = new ListNode(2);
    ListNode* node5 = new ListNode(1);
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;

    so.isPalindrome(node1);
}

void deleteDuplicates1Test(){
    Solution2 so;
    ListNode* node1 = new ListNode(1);
    ListNode* node2 = new ListNode(1);
    ListNode* node3 = new ListNode(2);
    ListNode* node4 = new ListNode(3);
    ListNode* node5 = new ListNode(4);
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;

    ListNode* ret1 =  so.deleteDuplicates1(node1);
    pList(ret1,"deleteDuplicates1");
}

void deleteDuplicates2Test() {
    Solution2 so;
    ListNode* node1 = new ListNode(1);
    ListNode* node2 = new ListNode(1);
    ListNode* node3 = new ListNode(2);
    ListNode* node4 = new ListNode(3);
    ListNode* node5 = new ListNode(4);
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;

    ListNode* ret2 =  so.deleteDuplicates2(node1);
    pList(ret2,"deleteDuplicates2");
}
// list test enter
void listtest(){
    deleteDuplicates1Test();
    deleteDuplicates2Test();
    reverseListTest();
    isPalindromeTest();
}

/********************* 234.回文链表 ***************/
ListNode* Solution2::endOfFirstHalf(ListNode* head) {
    ListNode* fast = head;
    ListNode* slow = head;
    while(fast->next != nullptr && fast->next->next != nullptr){
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}
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

/********************* 206.反转链表***************/
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
/*********** 82.删除排序链表中的重复元素2 *********/
// {1,1,2,3} -> {2,3}
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
/*********** 83.删除排序链表中的重复元素1 *********/
// {1,1,2,3} -> {1,2,3}
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
