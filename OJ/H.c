#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef int Status;

#define OK 1
#define ERROR 0
#define OVERFLOW -1

//树
typedef struct TreeNode {
	char data;
	struct TreeNode* lchild, * rchild;
}TreeNode,*BiTree;
//创造树节点
TreeNode* creatTreeNode(char data) {
	TreeNode* new = (BiTree)malloc(sizeof(TreeNode));
	if (!new) exit(OVERFLOW);
	new->data = data;
	new->lchild = new->rchild = NULL;
	return new;
}
//创造树
TreeNode* creatTree(char str[],int start,int end) {
	if (start > end) {
		return NULL;
	}
	int i;
	int parentheses = 0;
	int lowestpriority = 3;
	int lowestoperetorlndex = -1;
	for (i = start; i <= end; i++) {
		if (str[i] == '(')
			parentheses++;
		else if(str[i] == ')')
			parentheses--;
		else if (parentheses == 0 ) {
			if (str[i] == '+' || str[i] == '-') {
				if (lowestpriority > 1) {
					lowestpriority = 1;
					lowestoperetorlndex = i;
				}
			}
			else if(str[i] == '*' || str[i] == '/') {
				if (lowestpriority > 2) {
					lowestpriority = 2;
					lowestoperetorlndex = i;
				}
			}
		}
	}
	if (lowestoperetorlndex != -1) {
		TreeNode* T = creatTreeNode(str[lowestoperetorlndex]);
		T->lchild = creatTree(str, start, lowestoperetorlndex - 1);
		T->rchild = creatTree(str, lowestoperetorlndex + 1, end);
		return T;
	}
	else {
		if (str[start] == '(' && str[end] == ')')
			return creatTree(str, start + 1, end - 1);
		return creatTreeNode(str[start]);
	}
}
//先序遍历树
Status preorderTraversal(TreeNode* T) {
	if (T != NULL) {
		printf("%c", T->data);
		preorderTraversal(T->lchild);
		preorderTraversal(T->rchild);
		return OK;
	}
	else
		return ERROR;
}
//中序遍历树
Status inorderTraversal(TreeNode* T) {
	if (T != NULL) {
		inorderTraversal(T->lchild);
		printf("%c", T->data);
		inorderTraversal(T->rchild);
		return OK;
	}
	else
		return ERROR;
}
//后序遍历树
Status postorderTraversal(TreeNode* T) {
	if (T != NULL) {
		postorderTraversal(T->lchild);
		postorderTraversal(T->rchild);
		printf("%c", T->data);
		return OK;
	}
	else
		return ERROR;
}

int main() {
	char str[100];
	scanf("%s", str);
	int len = strlen(str);
	TreeNode* T = creatTree(str,0,len-1);
	preorderTraversal(T);
	printf("\n");
	inorderTraversal(T);
	printf("\n");
	postorderTraversal(T);
	return 0;
}
