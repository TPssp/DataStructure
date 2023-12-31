#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	float number;
	char name[9];
	int grades;
}person, * personPtr;

//快速排序一次
int Partition(personPtr p, int low, int high) {
	float pivotkey;
	pivotkey = p[low].number;
	p[0] = p[low];
	while (low < high) {
		while (low < high && p[high].number >= pivotkey)
			high--;
		p[low] = p[high];
		while (low < high && p[low].number <= pivotkey)
			low++;
		p[high] = p[low];
	}
	p[low] = p[0];
	return low;
}
//快速排序
void QSort(personPtr p, int low, int high) {
	int pivotloc;
	if (low < high) {
		pivotloc = Partition(p, low, high);
		QSort(p, low, pivotloc - 1);
		QSort(p, pivotloc + 1, high);
	}
}
//改进的冒泡排序
void BubbleSort(personPtr p, int n) {
	int i, j, noswap;
	person node;
	for (i = 1; i <= n - 1; i++) {
		noswap = 1;
		for (j = 1; j <= n - i; j++)
			if (strcmp(p[j].name, p[j + 1].name) > 0) {
				node = p[j];
				p[j] = p[j + 1];
				p[j + 1] = node;
				noswap = 0;
			}
			else if (strcmp(p[j].name, p[j + 1].name) == 0) {
				if (p[j].number > p[j + 1].number) {
					node = p[j];
					p[j] = p[j + 1];
					p[j + 1] = node;
					noswap = 0;
				}
			}
		if (noswap)
			break;
	}
}
//简单选择排序
void SelectSort(personPtr p, int num) {
	int i, j, low;
	for (i = 1; i < num; i++) {
		low = i;
		for (j = i + 1; j <= num; j++) {
			if (p[low].grades > p[j].grades)
				low = j;
			else if (p[low].grades == p[j].grades) {
				if (p[low].number > p[j].number)
					low = j;
			}
		}
		if (low != i) {
			p[0] = p[i];
			p[i] = p[low];
			p[low] = p[0];
		}
	}
}
int main() {
	int num, choice, i;
	scanf("%d %d", &num, &choice);
	personPtr p = (personPtr)malloc(sizeof(person) * (num + 1));
	for (i = 1; i <= num; i++)
		scanf(" %f %s %d", &p[i].number, p[i].name, &p[i].grades);
	if (choice == 1)
		QSort(p, 1, num);
	else if (choice == 2)
		BubbleSort(p, num);
	else
		SelectSort(p, num);
	for (i = 1; i <= num; i++) {
		printf("%06.0f %s %d", p[i].number, p[i].name, p[i].grades);
		if (i != num)
			printf("\n");
	}
	return 0;
}