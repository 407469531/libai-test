#include "pub.h"

list<int> toList(ListNode* res){
    list<int> tmp;
    while(res){
        tmp.push_back(res->val);
        res = res->next;
    }
    return tmp;
}
// 创建链表
ListNode* createList(vector<int> vals){
    if(vals.empty())
        return nullptr;
    ListNode* node1 = new ListNode(vals[0]);
    ListNode* p = node1;

    ListNode* tmp = node1;
    int size = vals.size();
    for(int i = 1; i<size; ++i){
        ListNode* node = new ListNode(vals[i]);
        tmp->next = node;
        tmp = tmp->next;
    }
    return p;
}
// 释放链表
void deleteList(ListNode* head){
    ListNode* tmp;
    while(head){
        tmp = head;
        head = head->next;
        delete tmp;
    }
}
void connectLists(ListNode *listA, ListNode *listB, ListNode *intersect) {
    ListNode *current = listA;
    while (current->next) {
        current = current->next;
    }
    current->next = intersect;

    current = listB;
    while (current->next) {
        current = current->next;
    }
    current->next = intersect;
}
/* 链表1 ****************** 160.相交链表 *************************/
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    if (headA == nullptr || headB == nullptr) {
        return nullptr;
    }
    ListNode *pA = headA, *pB = headB;
    while (pA != pB) {
        pA = pA == nullptr ? headB : pA->next;
        pB = pB == nullptr ? headA : pB->next;
    }
    return pA;
}

TEST(list_test, getIntersectionNode){
    vector<int> vals1={9,5};
    ListNode* node1 = createList(vals1);
    vector<int> vals2={7,8};
    ListNode* node2 = createList(vals2);
    vector<int> vals3={1,2,3};
    ListNode* intersect = createList(vals3);
    connectLists(node1, node2, intersect);

    ListNode*  res = getIntersectionNode(node1,node2);
    list<int> tmp = toList(res);
    list<int> rightResult = {1,2,3};
    EXPECT_TRUE(std::equal(tmp.begin(),tmp.end(),rightResult.begin()));

    ListNode *temp = node1;
    while (temp->next != intersect) temp = temp->next;
    temp->next = nullptr;

    temp = node2;
    while (temp->next != intersect) temp = temp->next;
    temp->next = nullptr;

    deleteList(intersect);
    deleteList(node1);
    deleteList(node2);
}

/* 链表2 ****************** 206.反转链表 *************************/
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
TEST(list_test, reverseList){
    vector<int> vals={1,2,3,4,5};
    ListNode* node = createList(vals);

    pList(node,"reverseList input");
    ListNode* res = reverseList(node);
    pList(res,"reverseList output");

    list<int> tmp = toList(res);
    list<int> rightResult = {5,4,3,2,1};
    EXPECT_TRUE(std::equal(tmp.begin(),tmp.end(),rightResult.begin()));
    deleteList(res);
}
/* 链表3 ******************** 234.回文链表 ***************/
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
TEST(list_test, test2_isPalindrome){
    vector<int> vals={1,2,3,2,1};
    ListNode* node = createList(vals);

    pList(node,"isPalindrome input");
    EXPECT_EQ(isPalindrome(node), true);
    deleteList(node);
}
/* test 3 ********** 83.删除排序链表中的重复元素1 *********/
// {1,1,2,3} -> {1,2,3}
ListNode* deleteDuplicates1(ListNode* head) {
    ListNode* cur = head;
    while(cur->next){
        if(cur->val == cur->next->val){
            ListNode* tmp = cur->next;
            cur->next = cur->next->next;
            delete tmp;
        } else {
            cur = cur->next;
        }
    }
    return head;
}
TEST(list_test, test3_deleteDuplicates1){
   vector<int> vals={1,1,2,3,4};
   ListNode* node = createList(vals);

    pList(node,"deleteDuplicates1 input");
    ListNode* res = deleteDuplicates1(node);
    pList(res,"deleteDuplicates1 output");

    list<int> tmp = toList(res);
    list<int> rightResult = {1,2,3,4};
    EXPECT_TRUE(std::equal(tmp.begin(),tmp.end(),rightResult.begin()));
    deleteList(res);
}
/* test 4 ********** 82.删除排序链表中的重复元素2 *********/
// {1,1,2,3} -> {2,3}
ListNode* deleteDuplicates2(ListNode* head) {
    ListNode dummy = ListNode(0,head);
    ListNode* cur = &dummy;
    while(cur->next && cur->next->next){
        if(cur->next->val == cur->next->next->val){
            int x=cur->next->val;
            while(cur->next && x == cur->next->val){
                ListNode* tmp2 = cur->next;
                cur->next = cur->next->next;
                delete tmp2;
            }
        } else
            cur = cur->next;
    }
    return dummy.next;
}
TEST(list_test, test4_deleteDuplicates2){
    vector<int> vals={1,1,2,3,4};
    ListNode* node = createList(vals);

    pList(node,"deleteDuplicates2 input");
    ListNode* res = deleteDuplicates2(node);
    pList(res,"deleteDuplicates2 output");

    list<int> tmp = toList(res);
    list<int> rightResult = {2,3,4};
    EXPECT_TRUE(std::equal(tmp.begin(),tmp.end(),rightResult.begin()));
    deleteList(res);
}
