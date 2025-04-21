#include "pub.h"
/* test 1 ****************** 94.二叉树的中序遍历 *************************/
// 给定一个二叉树的根节点 root ，返回 它的 中序 遍历 。
void inorder(TreeNode* root, vector<int>& res){
    if(root){
        inorder(root->left, res);
        res.emplace_back(root->val);
        inorder(root->right, res);
    }
}

vector<int> inorderTraversal(TreeNode* root) {
    vector<int> res;
    inorder(root, res);
    return res;
}

TEST(tree_test, test1_inorderTraversal){
    TreeNode t3(3);
    TreeNode t2(2, &t3, nullptr);
    TreeNode root(1, nullptr, &t2);

    vector<int> res = inorderTraversal(&root);
    vector<int> right = {1,3,2};
    EXPECT_EQ(res, right);
}


