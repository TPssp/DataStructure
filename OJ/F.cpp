#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int Status;

#define OK 1
#define OVERFLOW -1
#define ERROR 0
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct BiTNode {
	char data;
	struct BiTNode* lchild,* rchild;
}BiTNode,*BiTree;

typedef struct {
	BiTNode* base;
	BiTNode* top;
	int stacksize;
}SqStack;

void createT(BiTNode** T);
Status PreorderTravers(BiTNode* T);
Status INorderTravers(BiTNode* T);
Status PostorderTravers(BiTNode* T);
int LeadCount(BiTNode* T);
int Depth(BiTNode* T);
Status INorderTravers2(BiTNode* T);
Status InitStack(SqStack* S);
Status pushS(SqStack* S, BiTNode *a);
Status popS(SqStack* S, BiTNode* e);
Status DestroyStack(SqStack* S);
int StackEmptyS(SqStack* S);

int main() {
	BiTree T;
	createT(&T);
	PreorderTravers(T);
	printf("\n");
	INorderTravers(T);
	printf("\n");
	PostorderTravers(T);
	printf("\n");
	printf("%d",LeadCount(T));
	printf("\n");
	printf("%d", Depth(T));
	printf("\n");
	INorderTravers2(T);
	return 0;
}

//创造树
void createT(BiTNode** T) {
	int ch;
	ch = getchar();
	if (ch != '\n') {
		if (ch == '#') {
			*T = NULL;
		}
		else {
			*T = (BiTree)malloc(sizeof(BiTNode));
			if (!(*T)) exit(OVERFLOW);
			(*T)->data = ch;
			createT(&(*T)->lchild);
			createT(&(*T)->rchild);
		}
	}
	else return;
}
//先序遍历
Status PreorderTravers(BiTNode *T) {
	if (T == NULL) return OK;
	else {
		printf("%c", T->data);
		PreorderTravers(T->lchild);
		PreorderTravers(T->rchild);
	}
}
//中序遍历
Status INorderTravers(BiTNode* T) {
	if (T == NULL) return OK;
	else {
		INorderTravers(T->lchild);
		printf("%c", T->data);
		INorderTravers(T->rchild);
	}
}
//后序遍历
Status PostorderTravers(BiTNode* T) {
	if (T == NULL) return OK;
	else {
		PostorderTravers(T->lchild);
		PostorderTravers(T->rchild);
		printf("%c", T->data);
	}
}
//求叶子结点数量
int LeadCount(BiTNode* T) {
	if (T == NULL)
		return 0;
	if (T->lchild == NULL && T->rchild == NULL)
		return 1;
	else
		return LeadCount(T->lchild) + LeadCount(T->rchild);
}
//求深度
int Depth(BiTNode* T) {
	if (T == NULL)return 0;
	else {
		int m = Depth(T->lchild);
		int n = Depth(T->rchild);
		if (m > n) return(m + 1);
		else return(n + 1);
	}
}
//中序非递归遍历
Status INorderTravers2(BiTNode* T) {
	BiTNode* p=T;
	BiTNode q;
	SqStack S;
	InitStack(&S);
	while (p || !StackEmptyS(&S)) {
		if (p) {
			pushS(&S,p);
			p = p->lchild;
		}
		else {
			popS(&S, &q);
			printf("%c", q.data);
			p = q.rchild;
		}
	}
	DestroyStack(&S);
}
//初始化一个栈
Status InitStack(SqStack* S) {
	S->base = (BiTNode*)malloc(STACK_INIT_SIZE * sizeof(BiTNode));
	if (!S->base) exit(OVERFLOW);
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
	return OK;
}
//向栈中插入元素
Status pushS(SqStack* S, BiTNode *a) {
	if (S->top - S->base >= S->stacksize) {
		S->base = (BiTNode*)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(BiTNode));
		if (!S->base) exit(OVERFLOW);
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT;
	}
	*(S->top) = *a;
	S->top++;
	return OK;
}
//从栈中删除元素
Status popS(SqStack* S, BiTNode* e) {
	if (S->top == S->base)
		return ERROR;
	*e = *(--S->top);
	return OK;
}
//销毁栈
Status DestroyStack(SqStack* S) {
	if (S->base) {
		free(S->base);
		S->stacksize = 0;
		S->base = S->top = NULL;
	}
	return OK;
}
//检查栈非空
int StackEmptyS(SqStack* S) {
	if (S->top == S->base)
		return 1;
	else
		return 0;
}