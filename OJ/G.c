#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef int Status;

#define OK 1
#define ERROR 0
#define OVERFLOW -1

//树
typedef struct BiTNode {
	char data;
	struct BiTNode* lchild, * rchild;
}BiTNode,*BiTree;

//栈
typedef struct StackNode {
	BiTNode* data;
	struct StackNode* next;
}StackNode,*LinkStack;

//初始化一个栈
Status InitStack(StackNode** S) {
	*S = (LinkStack)malloc(sizeof(StackNode));
	if (!(*S)) exit(OVERFLOW);
	(*S)->next = NULL;
	return OK;
}
//入栈操作
Status push(StackNode** S, BiTNode* T) {
	StackNode* new = NULL;
	InitStack(&new);
	new->data = T;
	new->next = *S;
	*S = new;
	return OK;
}
//出栈操作
BiTNode* pop(StackNode** S) {
	if (*S == NULL)
		return ERROR;
	BiTNode* T = (*S)->data;
	StackNode* temp = *S;
	*S = (*S)->next;
	free(temp);
	return T;
}
//构建二叉树
BiTNode* BuildTree(char str[]) {
	StackNode* S = NULL;
	InitStack(&S);
	int len = strlen(str);
	int i;
	for (i = len - 1; i >= 0; i--) {
		char ch = str[i];
		BiTNode* T = (BiTree)malloc(sizeof(BiTNode));
		T->data = ch;
		T->lchild = T->rchild = NULL;
		if (ch == '+' || ch == '-' || ch == '/' || ch == '*') {
			T->lchild = pop(&S);
			T->rchild = pop(&S);
			push(&S, T);
		}
		else
			push(&S, T);
	}
	return pop(&S);
}
//先序遍历二叉树
Status preorderTraversal(BiTNode* T) {
	if (T != NULL) {
		printf("%c", T->data);
		preorderTraversal(T->lchild);
		preorderTraversal(T->rchild);
		return OK;
	}
	else
		return ERROR;
}
//中序遍历二叉树
Status inorderTraversal(BiTNode* T) {
	if (T != NULL) {
		inorderTraversal(T->lchild);
		printf("%c", T->data);
		inorderTraversal(T->rchild);
		return OK;
	}
	else
		return ERROR;
}
//后序遍历二叉树
Status postorderTraversal(BiTNode* T) {
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
	BiTNode* T = BuildTree(str);
	preorderTraversal(T);
	printf("\n");
	inorderTraversal(T);
	printf("\n");
	postorderTraversal(T);
	return 0;
}