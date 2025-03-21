#include "pub.h"

void pVector(vector<int>& vs,string name){
    printf("%s: ",name.c_str());
    for(auto& v: vs){
        printf("%d,",v);
    }
    printf("\n");
    fflush(stdout);
}

void pList(ListNode* in,string name){
    ListNode* tmp = in;
    printf("%s: ",name.c_str());
    while(tmp){
        printf("%d ",tmp->val);
        tmp = tmp->next;
    }
    printf("\n");
    fflush(stdout);
}
