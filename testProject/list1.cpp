#include "pub.h"

list<int> toList(ListNode* res){
    list<int> tmp;
    while(res){
        tmp.push_back(res->val);
        res = res->next;
    }
    return tmp;
}
// 构造单链表
ListNode* createList(const vector<int>& vals){
    if(vals.empty()) return nullptr;
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
// 释放单链表
void deleteList(ListNode* head){
    ListNode* tmp;
    while(head){
        tmp = head;
        head = head->next;
        delete tmp;
    }
}
// 尾插
void insertList(ListNode* head, int a){
    ListNode* tmp = head;
    while(tmp->next){
        tmp = tmp->next;
    }
    tmp->next = new ListNode(a);
}

// 构造环形链表
ListNode* createCircularList(const vector<int>& vals, int pos){
    if(vals.empty()) return nullptr;
    ListNode* head = new ListNode(vals[0]);
    ListNode* tail = head;
    ListNode* cycleEntry = (pos == 0) ? head : nullptr;
    int size = vals.size();
    for(int i = 1; i<size; ++i){
        tail->next = new ListNode(vals[i]);
        tail = tail->next;
        if(pos == i)
            cycleEntry = tail;
    }
    if(cycleEntry)
        tail->next = cycleEntry;
    return head;
}
// 释放环形链表
void deleteCircularList(ListNode* head){
    if(!head) return;
    ListNode* slow = head;
    ListNode* fast = head;
    bool isCircular = false;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast){
            isCircular = true;
            break;
        }
    }
    if(isCircular){
        slow = head;
        while(slow->next != fast->next){
            slow = slow->next;
            fast = fast->next;
        }
        fast->next = nullptr;
    }
    deleteList(head);
}
// 把intersect分别连接到listA和listB后面
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
//思路：(a+c)+(b+c) == (b+c)+(a+c)
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
    vector<int> vals1={9,5,2};
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
// 思路：快慢指针方法，找到前半部分链表的尾节点。将后半部分链表反转。判断是否是回文。恢复链表。
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
TEST(list_test, isPalindrome){
    vector<int> vals={1,2,3,2,1};
    ListNode* node = createList(vals);

    pList(node,"isPalindrome input");
    EXPECT_EQ(isPalindrome(node), true);
    deleteList(node);
}
/* 链表4 ********** 141.环形链表*********/
bool hasCycle(ListNode *head) {
    ListNode* fast = head;
    ListNode* slow = head;
    while(fast && fast->next){
        fast = fast->next->next;
        slow = slow->next;
        if(slow == fast)
            return true;
    }
    return false;
}
TEST(list_test, hasCycle){
    ListNode* node = createCircularList({1, 2, 3, 4, 5}, 2);
    EXPECT_EQ(hasCycle(node), true);
    deleteCircularList(node);
}
/* 链表7 ********** 2.两数相加*********/
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    int len1(0);
    int len2(0);
    ListNode* tmp1 = l1;
    ListNode* tmp2 = l2;

    while(tmp1->next){
        len1++;
        tmp1 = tmp1->next;
    }
    while(tmp2->next){
        len2++;
        tmp2 = tmp2->next;
    }

    if(len1 > len2){
        for(int i=0;i<len1-len2;++i){
            tmp2->next = new ListNode(0);
            tmp2=tmp2->next;
        }
    } else{
        for(int i=0;i<len2-len1;++i){
            tmp1->next = new ListNode(0);
            tmp1=tmp1->next;
        }
    }
    ListNode* res = new ListNode(-1);
    ListNode* tmp = res;
    bool extent(false);
    while(l1 || l2){
        int val = extent ? (l1->val + l2->val + 1) : (l1->val + l2->val);
        tmp->next = new ListNode(val%10);
        tmp = tmp->next;
        l1 = l1->next;
        l2 = l2->next;
        extent = (val>9) ? true : false;
    }
    if(extent) {
        tmp->next=new ListNode(1);
        tmp=tmp->next;
    }
    return res->next;
}
TEST(list_test, addTwoNumbers){
    {
        vector<int> vals1={2,4,3};
        ListNode* node1 = createList(vals1);
        vector<int> vals2={5,6,4};
        ListNode* node2 = createList(vals2);

        ListNode* res = addTwoNumbers(node1, node2);
        list<int> tmp = toList(res);
        list<int> rightResult = {7,0,8};
        EXPECT_TRUE(std::equal(tmp.begin(),tmp.end(),rightResult.begin()));
        deleteList(node1);
        deleteList(node2);
    }
    {
        vector<int> vals1={9,9,9,9,9,9,9};
        ListNode* node1 = createList(vals1);
        vector<int> vals2={9,9,9,9};
        ListNode* node2 = createList(vals2);

        ListNode* res = addTwoNumbers(node1, node2);
        list<int> tmp = toList(res);
        list<int> rightResult = {8,9,9,9,0,0,0,1};
        EXPECT_TRUE(std::equal(tmp.begin(),tmp.end(),rightResult.begin()));
        deleteList(node1);
        deleteList(node2);
    }
}
/*  ********** 83.删除排序链表中的重复元素1 *********/
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
TEST(list_test, deleteDuplicates1){
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
/*  ********** 82.删除排序链表中的重复元素2 *********/
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
TEST(list_test, deleteDuplicates2){
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
