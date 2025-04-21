#include "pub.h"

// 创建二叉树
TreeNode* createBinaryTree(std::vector<int>& nums, int index) {
    int sz = nums.size();
    if(index >= sz || nums[index] == -1)
        return nullptr;
    TreeNode* root = new TreeNode(nums[index]);
    root->left = createBinaryTree(nums, 2 * index + 1);
    root->right = createBinaryTree(nums, 2 * index + 2);
    return root;
}

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
    vector<int> nums={1,-1,2,-1,-1,3,-1};
    TreeNode *root = createBinaryTree(nums,0);
    vector<int> res = inorderTraversal(root);

    vector<int> right = {1,3,2};
    EXPECT_EQ(res, right);
}


