#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 80
#define CHUNKSIZE 80
#define OK 1
#define ERROR 0
#define OVERFLOW -1

typedef int Status;

//串结点
typedef struct Chunk {
	char ch[CHUNKSIZE];
	struct Chunk* next;
}Chunk;
//串的链表结构
typedef struct {
	Chunk* head, * tail;
	int curlen;
}LString;

//函数声明
Status InitLString(LString* S);
Status Push(LString* S, char str[MAX_SIZE]);
Status Detection(LString* S, char goal[MAX_SIZE], int i, int* node, double* similarity);


int main()
{
	int i,len,node;
	char num_str[MAX_SIZE];
	double similarity;
	int number = 0, node_last = 0;
	double similarity_last = 0;
	LString S;
	InitLString(&S);
	fgets(num_str, sizeof(num_str), stdin);
	int num = atoi(num_str);
	for (i = 0; i < num; i++) {
		char str[MAX_SIZE]="0";
		fgets(str, sizeof(str), stdin);
		len = strlen(str);
		if (str[len - 1] == '\n') {
			str[len - 1] = '\0';
			len--;
		}
		Push(&S, str);
	}
	char goal1[MAX_SIZE];
	char goal[MAX_SIZE];
	fgets(goal1, sizeof(goal1), stdin);
	len = strlen(goal1);
	if (goal1[len - 1] == '\n') {
		goal1[len - 1] = '\0';
		len--;
	}
	len = (int)strlen(goal1);  
	goal[0] = (char)len;
	for (i = 1; i <= len; i++) {
		goal[i] = goal1[i - 1];
	}
	for (i = 1; i <= num; i++) {
		Detection(&S,goal, i, &node, &similarity);
		if (similarity > similarity_last) {
			number = i;
			node_last = node;
			similarity_last = similarity;
		}
	}
	printf("%d %d %.2lf%%", number, node_last, similarity_last);
	return 0;
}

//初始化串
Status InitLString(LString* S) {
	S->head = S->tail = NULL;
	S->head = S->tail = (Chunk*)malloc(sizeof(Chunk));
	if (!S->head) exit(OVERFLOW);
	S->head->next = NULL;
	S->curlen = 0;
	return OK;
}
//向串中插入元素
Status Push(LString*S, char str[MAX_SIZE]) {
	Chunk *p=NULL;
	int i;
	p = (Chunk*)malloc(sizeof(Chunk));
	if (!p) return(OVERFLOW);
	for (i = 1; i <= (int)strlen(str); i++) {
		p->ch[0] = (char)strlen(str);
		p->ch[i] = str[i-1];
	}
	p->next = NULL;
	S->tail->next = p;
	S->tail = p;
	S->curlen++;
	return OK;
}
//与基因库进行检测
Status Detection(LString* S, char goal[MAX_SIZE], int i, int* node, double* similarity) {
	Chunk p;
	int i_,i__=1,j=1,i___=0;
	int node_last = 0;
	p = *(S->head->next);
	for (i_ = 1; i_ < i; i_++)
		p = *(p.next);
	while (i__ <= (int)p.ch[0] && j <= (int)goal[0]) {
		if (p.ch[i__] == goal[j]) {
			i__++;
			j++;
		}
		else
		{
			i__ = i__ - j + 2;
			j = 1;
		}
		if (j > node_last) {
			node_last = j;
			i___ = i__ - node_last;
		}
	}
	*node = i___+1;
	node_last--;
	*similarity = ((double)node_last / (double)goal[0])*100;
	return OK;
}