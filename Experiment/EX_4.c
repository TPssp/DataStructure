#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct {
	char elem[100][100];
	int length;
}SSTable,*SSTPtr;

int main() {
	int num;
	scanf("%d", &num);
	SSTPtr ST = (SSTPtr)malloc(sizeof(SSTable) * (num+1));
	int i,j;
	for (i = 1; i <= num; i++)
	{
		ST[i].length = 0;
	}
	int front, rear,lennum;
	int k;
	for (i = 1; i <= num; i++) {
		char str[100] = { '0' };
		j = 1;
		while (str[0] != '#') {
			scanf(" %s", str);
		
			if (strlen(str) >= 3) {
				for (front = 0, rear = 0; front < strlen(str); front++) {
					k = 0;
					if (!((65 <= str[front] &&90>= str[front]) || (97 <= str[front] && 122 >= str[front]))) {
						if (front-rear >= 3) {
							lennum = rear;
							for (; rear < front; rear++)
							{
								if (rear - lennum + 1 > 10)
									break;
								if (str[rear] >= 65 && str[rear] <= 90)
								{
									ST[i].elem[j][k++] = str[rear] + 32;
								}
								else
									ST[i].elem[j][k++] = str[rear];
							}
							ST[i].length++;
							ST[i].elem[j][k] = '\0';
							j++;
						}
						rear = front + 1;
					}
				}
				if (front-rear>=3) {
					k = 0;
					ST[i].length++;
					lennum = rear;
					for(; rear < front;rear++)
					{
						if (rear - lennum + 1 > 10)
							break;
						if(str[rear]>=65&&str[rear]<=90)
						{
							ST[i].elem[j][k++] = str[rear]+32;
						}
						else
							ST[i].elem[j][k++] = str[rear ];
					}
					ST[i].elem[j][k] = '\0';
					j++;
				}
			}
		}
	}
	int* length = (int*)malloc(sizeof(int) * (num + 1));
	for (i = 1; i <= num; i++)
	{
		length[i] = ST[i].length;
	}
	for(i=1;i<=num;i++)
		for(j=1;j<ST[i].length;j++)
			for(k=j+1;k<=ST[i].length;k++)
				if (strcmp(ST[i].elem[j], ST[i].elem[k]) == 0) {
					strcpy(ST[i].elem[j], "");
					length[i]--;
					break;
				}
	int* find;
	scanf(" %d", &num);
	int num1, num2;
	find = (int*)malloc(sizeof(int) *(2 * num));
	for (i = 0; i < 2*num; i+=2) {
		scanf(" %d %d", &num1, &num2);
		find[i] = num1;
		find[i + 1] = num2;
	}
	float totalnum;
	for (i = 0; i < 2 * num; i += 2) {
		totalnum = 0;
		for (j = 1; j <= ST[find[i]].length; j++) {
			for (k = ST[find[i + 1]].length; k >= 0; k--) {
				if (strcmp(ST[find[i]].elem[j], ST[find[i + 1]].elem[k] )==0&& strcmp(ST[find[i]].elem[j],"")!=0)
				{
					totalnum++;
					break;
				}
			}
		}
		printf("%.1f%%", (totalnum / (length[find[i]] + length[find[i+1]] - totalnum)) * 100);
		if (i != 2 * num - 2)
			printf("\n");
	}

	return 0;
}
