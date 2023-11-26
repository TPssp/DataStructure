#include <stdio.h>
#include <stdlib.h>
#include <cstring>
// 定义二叉树结点结构
typedef struct TreeNode {
    char data;
    struct TreeNode* left;//左子树
    struct TreeNode* right;//右子树
}TreeNode,* Tree;

// 函数用于创建新的二叉树结点
Tree createNode(char data) {
    Tree newNode = (Tree)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 函数用于在中序序列中查找根节点的位置
int findRootIndex(char inorder[], int start, int end, char rootValue) {
    for (int i = start; i <= end; i++) {
        if (inorder[i] == rootValue) {
            return i;
        }
    }
    return -1;  // 根节点未找到
}

// 函数用于构建二叉树
Tree buildTree(char preorder[], char inorder[], int* preIndex, int inStart, int inEnd) {
    if (inStart > inEnd) {
        return NULL;
    }

    // 从先序序列中取出下一个结点的值
    char rootValue = preorder[*preIndex];
    (*preIndex)++;

    // 创建当前根节点
    Tree root = createNode(rootValue);

    // 如果中序序列中还有左子树，递归构建左子树
    int rootIndex = findRootIndex(inorder, inStart, inEnd, rootValue);
    if (rootIndex != -1) {
        root->left = buildTree(preorder, inorder, preIndex, inStart, rootIndex - 1);
        root->right = buildTree(preorder, inorder, preIndex, rootIndex + 1, inEnd);
    }

    return root;
}

// 函数用于计算二叉树的深度
int findDepth(Tree root) {
    if (root == NULL) {
        return 0;
    }

    int leftDepth = findDepth(root->left);
    int rightDepth = findDepth(root->right);

    return (leftDepth > rightDepth) ? (leftDepth + 1) : (rightDepth + 1);
}

// 函数用于计算二叉树的叶子节点数量
int findLeafCount(Tree root) {
    if (root == NULL) {
        return 0;
    }

    if (root->left == NULL && root->right == NULL) {
        return 1;
    }

    int leftLeaves = findLeafCount(root->left);
    int rightLeaves = findLeafCount(root->right);

    return leftLeaves + rightLeaves;
}

int main() {
    char preorder[100];
    char inorder[100];

    // 读取输入的先序和中序序列
    scanf("%s", preorder);
    scanf("%s", inorder);

    int preIndex = 0;
    int inStart = 0;
    int inEnd = strlen(inorder) - 1;

    // 构建二叉树
    Tree root = buildTree(preorder, inorder, &preIndex, inStart, inEnd);

    // 计算深度和叶子节点数量
    int depth = findDepth(root);
    int leafCount = findLeafCount(root);

    printf("%d\n%d\n", depth, leafCount);

    return 0;
}
