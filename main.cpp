#include <QCoreApplication>

#include "vector1.h"
#include "sort1.h"
#include "list1.h"
#include "string1.h"

void listtest(){
    Solution2 so;

    ListNode* node1 = new ListNode(1);
    ListNode* node2 = new ListNode(2);
    ListNode* node3 = new ListNode(3);
    ListNode* node4 = new ListNode(2);
    ListNode* node5 = new ListNode(1);

    // 链接节点
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;

    so.isPalindrome(node1);

//    so.reverseList(node1);

//    ListNode* ret1 =  so.deleteDuplicates1(node1);
//    pList(ret1);

    ListNode* ret2 =  so.deleteDuplicates2(node1);
    pList(ret2,"deleteDuplicates2");
}

void vectortest(){
    Solution1 so;

//    vector<int> vec6={0,1,0,2,1,0,1,3,2,1,2,1};
//    so.trap(vec6);

//    vector<int> vec5={1,3,-1,-3,5,3,6,7};
//    so.maxSlidingWindow(vec5,3);

//    vector<int> vec4={6,4,3,1};
//    so.subarraySum(vec4,10);

    vector<int> vec1_1={1,1,1};
    so.subarraySum1(vec1_1,2);
    // vector 1

    vector<int> vec3={-1,0,1,2,-1,-4};
    vector<vector<int>> r3 = so.threeSum(vec3);

    vector<int> vec2={1,0,3,0,5};
    so.moveZeroes(vec2);
    pVector(vec2,"moveZeroes");

    vector<int> vec1={1,2,3,4,5};
    vector<int> res = so.twoSum(vec1,9);
    pVector(res,"twoSum");
}

void stringtest(){
    Solution3 so;
//    string s1="pwwkew";
//    string s1="aab";
//    string s1="dvdf";
    string s1="asjrgapa";
    so.lengthOfLongestSubstring(s1);
}


void ioTest(){

   char data[100];

   // 以写模式打开文件
   ofstream outfile;
   outfile.open("afile.dat");

   cout << "Writing to the file" << endl;
   cout << "Enter your name: ";
   cin.getline(data, 100);

   // 向文件写入用户输入的数据
   outfile << data << endl;

   cout << "Enter your age: ";
   cin >> data;
   cin.ignore();

   // 再次向文件写入用户输入的数据
   outfile << data << endl;

   // 关闭打开的文件
   outfile.close();

   // 以读模式打开文件
   ifstream infile;
   infile.open("afile.dat");

   cout << "Reading from the file" << endl;
   infile >> data;

   // 在屏幕上写入数据
   cout << data << endl;

   // 再次从文件读取数据，并显示它
   infile >> data;
   cout << data << endl;

   // 关闭打开的文件
   infile.close();

}

int main()
{
//    stringtest();
//    listtest();
//    vectortest();
    sortTest();
//    ioTest();
}



