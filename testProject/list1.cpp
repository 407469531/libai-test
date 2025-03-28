#include "pub.h"

/* test 1 ******************** 206.反转链表***************/
ListNode* reverseList(ListNode* head) {
    ListNode* newlist = NULL;
    while(head){
        ListNode* next = head->next;
        head->next = newlist;
        newlist = head;
        head = next;
    }
    return newlist;
}

/* test 2 ******************** 234.回文链表 ***************/
ListNode* endOfFirstHalf(ListNode* head) {
    ListNode* fast = head;
    ListNode* slow = head;
    while(fast->next != nullptr && fast->next->next != nullptr){
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}
bool isPalindrome(ListNode* head) {
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


/* test 3 ********** 82.删除排序链表中的重复元素2 *********/
// {1,1,2,3} -> {2,3}
ListNode* deleteDuplicates2(ListNode* head) {
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
/* test 4 ********** 83.删除排序链表中的重复元素1 *********/
// {1,1,2,3} -> {1,2,3}
ListNode* deleteDuplicates1(ListNode* head) {
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

/*********************测试例子构造***********************/

list<int> toList(ListNode* res){
    list<int> tmp;
    while(res){
        tmp.push_back(res->val);
        res = res->next;
    }
    return tmp;
}

TEST(list_test, test1_reverseList){
    ListNode* node1 = new ListNode(1);
    ListNode* node2 = new ListNode(2);
    ListNode* node3 = new ListNode(3);
    ListNode* node4 = new ListNode(4);
    ListNode* node5 = new ListNode(5);
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;

    pList(node1,"reverseList input");
    ListNode* res = reverseList(node1);
    pList(res,"reverseList output");

    list<int> tmp = toList(res);
    list<int> rightResult = {5,4,3,2,1};
    EXPECT_TRUE(std::equal(tmp.begin(),tmp.end(),rightResult.begin()));
}

TEST(list_test, test2_isPalindrome){
    ListNode* node1 = new ListNode(1);
    ListNode* node2 = new ListNode(2);
    ListNode* node3 = new ListNode(3);
    ListNode* node4 = new ListNode(2);
    ListNode* node5 = new ListNode(1);
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;

    pList(node1,"isPalindrome input");
    EXPECT_EQ(isPalindrome(node1), true);
}

TEST(list_test, test3_deleteDuplicates1){
    ListNode* node1 = new ListNode(1);
    ListNode* node2 = new ListNode(1);
    ListNode* node3 = new ListNode(2);
    ListNode* node4 = new ListNode(3);
    ListNode* node5 = new ListNode(4);
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;

    pList(node1,"deleteDuplicates1 input");
    ListNode* res = deleteDuplicates1(node1);
    pList(res,"deleteDuplicates1 output");

    list<int> tmp = toList(res);
    list<int> rightResult = {1,2,3,4};
    EXPECT_TRUE(std::equal(tmp.begin(),tmp.end(),rightResult.begin()));

}

TEST(list_test, test4_deleteDuplicates2){
    ListNode* node1 = new ListNode(1);
    ListNode* node2 = new ListNode(1);
    ListNode* node3 = new ListNode(2);
    ListNode* node4 = new ListNode(3);
    ListNode* node5 = new ListNode(4);
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;

    pList(node1,"deleteDuplicates2 input");
    ListNode* res = deleteDuplicates2(node1);
    pList(res,"deleteDuplicates2 output");

    list<int> tmp = toList(res);
    list<int> rightResult = {2,3,4};
    EXPECT_TRUE(std::equal(tmp.begin(),tmp.end(),rightResult.begin()));
}
