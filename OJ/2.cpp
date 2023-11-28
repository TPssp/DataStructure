#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define MAX_SIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -1
typedef int Status;

//顺序栈
typedef struct{
	char* base;
	char* top;
	int stacksize;
}SqStack;

//链队列结点
typedef struct QNode {
	char data;
	struct	QNode* next;
}QNode,*QueuePtr;
//链队列头尾指针
typedef struct {
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

//函数声明
Status InitQueue(LinkQueue* Q);
Status pushQ(LinkQueue* Q, char a);
Status popQ(LinkQueue* Q, char* a);
Status InitStack(SqStack *S);
Status pushS(SqStack *S, char a);
Status popS(SqStack *S, char* e);


int main()
{
	int len,i,j=1;
	char s, q;
	LinkQueue Q;
	InitQueue(&Q);
	SqStack S;
	InitStack(&S);
	char str[MAX_SIZE];
	fgets(str,sizeof(str),stdin);
	len = strlen(str);
	if (str[len - 1] == '\n') {
		str[len - 1] = '\0';
		len--;
	}
	for (i = 0; i < len; i++)
	{
		pushQ(&Q, str[i]);
		pushS(&S, str[i]);
	}
	for (i = 0; i < len; i++) {
		popQ(&Q, &q);
		popS(&S, &s);
		if (s != q) {
			j = 0;
			break;
		}
	}

	printf("%d",j);
	return 0;
}

//队列初始化
Status InitQueue(LinkQueue* Q) {
	Q->front = Q->rear = NULL;
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front) exit(OVERFLOW);
	Q->front->next = NULL;
	return OK;
}
//向队列中插入元素
Status pushQ(LinkQueue* Q, char a) {
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) exit(OVERFLOW);
	p->data = a;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
	return OK;
}
//从队列中删除元素
Status popQ(LinkQueue* Q, char* a) {
	if (Q->front == Q->rear) return ERROR;
	QueuePtr p;
	p = Q->front->next;
	*a = p->data;
	Q->front->next = p->next;
	if (p == Q->rear) Q->rear = Q->front;
	free(p);
	return OK;
}
//销毁队列
Status DestroyQueue(LinkQueue* Q) {
	while (Q->front) {
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front=Q->rear;
	}
	return OK;
}

//初始化一个栈
Status InitStack(SqStack* S) {
	S->base = (char*)malloc(STACK_INIT_SIZE * sizeof(char));
	if (!S->base) exit(OVERFLOW);
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
	return OK;
}
//向栈中插入元素
Status pushS(SqStack* S, char a) {
	if (S->top - S->base >= S->stacksize) {
		S->base = (char*)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(char));
		if (!S->base) exit(OVERFLOW);
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT;
	}
	*(S->top) = a;
	S->top++;
	return OK;
}
//从栈中删除元素
Status popS(SqStack* S, char* e) {
	if (S->top == S->base)
		return ERROR;
	*e = *(--S->top);
	return OK;
}