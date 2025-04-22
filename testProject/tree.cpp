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
// 左根右
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

/* test 2 ****************** 104.二叉树的最大深度 ************************/
int maxDepth(TreeNode* root) {
    if(root == nullptr)
        return 0;
    int left = maxDepth(root->left);
    int right = maxDepth(root->right);
    int cur = max(left, right) + 1;
    return cur;
}

TEST(tree_test, test2_maxDepth){
    std::vector<int> nums = {3, 9, 20, -1, -1, 15, 7};
    TreeNode* root = createBinaryTree(nums, 0);
    int depth = maxDepth(root);
    EXPECT_EQ(depth, 3);
}
/* test 3 ****************** 144.二叉树的前序遍历 *************************/
// 根左右
void preorder(TreeNode* root, vector<int>& res){
    if(root){
        res.emplace_back(root->val);
        preorder(root->left, res);
        preorder(root->right, res);
    }
}

vector<int> preorderTraversal(TreeNode* root) {
    vector<int> res;
    preorder(root, res);
    return res;
}

TEST(tree_test, test3_preorderTraversal){
    vector<int> nums={1,-1,2,-1,-1,3,-1};
    TreeNode *root = createBinaryTree(nums,0);
    vector<int> res = preorderTraversal(root);

    vector<int> right = {1,2,3};
    EXPECT_EQ(res, right);
}
/* test 4 ****************** 145.二叉树的后序遍历 *************************/
// 左右根
void postorder(TreeNode* root, vector<int>& res){
    if(root){
        postorder(root->left, res);
        postorder(root->right, res);
        res.emplace_back(root->val);
    }
}
vector<int> postorderTraversal(TreeNode* root) {
    vector<int> res;
    postorder(root, res);
    return res;
}

TEST(tree_test, test4_postorderTraversal){
    vector<int> nums={1,-1,2,-1,-1,3,-1};
    TreeNode *root = createBinaryTree(nums,0);
    vector<int> res = postorderTraversal(root);

    vector<int> right = {3,2,1};
    EXPECT_EQ(res, right);
}
