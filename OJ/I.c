#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef int Status;

#define ERROR 0
#define OK 1
#define OVERFLOW -1

int num=1;

//线索
typedef enum PointerTag {
	Link, Thread
}PointerTag;
//树节点
typedef struct TreeNode {
	char data;
	struct TreeNode* lchild,*rchild;
	PointerTag LTag, RTag;
}TreeNode,*TreePtr;

TreePtr pre;

//根据先缀表达式创造树
void createT(TreeNode** T) {
	int ch;
	ch = getchar();
	if (ch != '\n') {
		if (ch == '#') {
			*T = NULL;
		}
		else {
			*T = (TreePtr)malloc(sizeof(TreeNode));
			if (!(*T)) exit(OVERFLOW);
			(*T)->data = ch;
			(*T)->LTag = (*T)->RTag = Link;
			createT(&(*T)->lchild);
			createT(&(*T)->rchild);
		}
	}
	else return;
}
//中序线索化树
void Inthreading(TreeNode** T) {
	if (*T) {
		Inthreading(&((*T)->lchild));
		if (!(*T)->lchild) {
			(*T)->LTag = Thread;
			(*T)->lchild = pre;
		}
		if (!pre->rchild) {
			pre->RTag = Thread;
			pre->rchild = *T;
		}
		pre = *T;
		Inthreading(&((*T)->rchild));
	}
}
//将树线索化并设置头节点
TreeNode* InorderThreading(TreeNode*T){
	TreeNode* Thrt = (TreePtr)malloc(sizeof(TreeNode));
	Thrt->LTag = Link;
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;
	if (!T)Thrt->lchild = Thrt;
	else {
		Thrt->lchild = T;
		pre = Thrt;
		Inthreading(&T);
		pre->RTag = Thread;
		pre->rchild = Thrt;
		Thrt->rchild = pre;
	}
	return Thrt;
}
void visit(TreeNode* T) {
	printf("%c", T->data);
	if (T->LTag + T->RTag == 1)
		num++;
}
//中序非递归遍历线索二叉树
Status InorderTraverse_Thr(TreeNode*T) {
	TreeNode* p = T->lchild;
	while (p != T) {
		while (p->LTag == Link)p = p->lchild;
		visit(p);
		while (p->RTag == Thread && p->rchild != T) {
			p = p->rchild;
			visit(p);
		}
		p = p->rchild;
	}
	return OK;
}

int main() {
	TreePtr T;
	createT(&T);
	TreeNode* Thrt = InorderThreading(T);
	InorderTraverse_Thr(Thrt);
	printf("\n");
	printf("%d", num);
	return 0;
}
