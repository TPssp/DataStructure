#include <stdio.h>
#include <stdlib.h>

// 定义二叉树结点结构
typedef struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 根据先序和中序序列还原二叉树
TreeNode* buildTree(char* preorder, char* inorder, int N) {
    if (N <= 0) {
        return NULL;
    }

    // 创建根节点
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = preorder[0];
    root->left = root->right = NULL;

    // 在中序序列中找到根节点的位置
    int rootIndex;
    for (rootIndex = 0; rootIndex < N; ++rootIndex) {
        if (inorder[rootIndex] == root->data) {
            break;
        }
    }

    // 递归构建左子树和右子树
    root->left = buildTree(preorder + 1, inorder, rootIndex);
    root->right = buildTree(preorder + 1 + rootIndex, inorder + rootIndex + 1, N - 1 - rootIndex);

    return root;
}

// 计算二叉树的高度
int treeHeight(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int main() {
    int N;
    scanf("%d", &N);

    char preorder[50], inorder[50];
    scanf("%s", preorder);
    scanf("%s", inorder);

    // 构建二叉树
    TreeNode* root = buildTree(preorder, inorder, N);

    // 计算二叉树高度并输出
    int height = treeHeight(root);
    printf("%d\n", height);

    return 0;
}
