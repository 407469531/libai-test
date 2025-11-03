#include "pub.h"

TEST(container_test, container_size)
{
    set<int> s{1,2,3};
    multiset<int> ms{1,2,3,1};
    unordered_set<int> us{1,2,3};
    unordered_multiset<int> ums{1,2,3,1};

    cout<<"set                size:"<<sizeof(s)<<endl;
    cout<<"multiset           size:"<<sizeof(ms)<<endl;
    cout<<"unordered_set      size:"<<sizeof(us)<<endl;
    cout<<"unordered_multiset size:"<<sizeof(ums)<<endl;

    map<string,int> m{{"str1",1},{"str2",2},{"str3",3}};
    multimap<string,int> mm{{"str1",1},{"str2",2},{"str3",3}};
    unordered_map<string,int> um{{"str11",1},{"str22",2},{"str33",3}};
    unordered_multimap<string,int> umm{{"str11",1},{"str22",2},{"str33",3}};

    cout<<"map                size:"<<sizeof(m)<<endl;
    cout<<"multimap           size:"<<sizeof(mm)<<endl;
    cout<<"unordered_map      size:"<<sizeof(um)<<endl;
    cout<<"unordered_multimap size:"<<sizeof(umm)<<endl;

    vector<int> v={1,2,3,4};
    array<int,4> a={1,2,3,4};
    deque<int> d={1,2,3,4};
    forward_list<int> fl={1,2,3,4};
    list<int> l={1,2,3,4};
    stack<int> myStack;
    myStack.push(1);
    myStack.push(2);
    queue<int> myQueue;
    priority_queue<int> myPriorityQueue;

    cout<<"vector         size:"<<sizeof(v)<<endl;
    cout<<"array          size:"<<sizeof(a)<<endl;
    cout<<"deque          size:"<<sizeof(d)<<endl;
    cout<<"forward_list   size:"<<sizeof(fl)<<endl;
    cout<<"list           size:"<<sizeof(l)<<endl;
    cout<<"stack          size:"<<sizeof(myStack)<<endl;
    cout<<"queue          size:"<<sizeof(myQueue)<<endl;
    cout<<"priority_queue size:"<<sizeof(myPriorityQueue)<<endl;
}

