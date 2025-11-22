#include "pub.h"

void move(vector<int>& src,vector<int>& tar){
    int pan = src.back();
    src.pop_back();
    tar.push_back(pan);
}

void dfs(int i, vector<int>& src,vector<int>& buf,vector<int>& tar){
    if(i == 1){
        move(src, tar);
        return;
    }
    dfs(i-1,src,tar,buf);
    move(src,tar);
    dfs(i-1,buf,src,tar);
}

void solvehanota(vector<int>& A,vector<int>& B,vector<int>& C){
    int n = A.size();
    dfs(n,A,B,C);
}

TEST(hanota_test,test1){
    vector<int> A = {5,4,3,2,1};
    vector<int> B;
    vector<int> C;
    solvehanota(A,B,C);
}

