#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 学生结构体定义
typedef struct {
    char id[7];      // 学号
    char name[9];    // 姓名
    int score;       // 成绩
} Student;

// 比较函数，用于qsort排序
int compare(const void* a, const void* b) {
    const Student* studentA = (const Student*)a;
    const Student* studentB = (const Student*)b;

    // 根据指定列进行排序
    int result;
    if (studentA->score == studentB->score) {
        // 当成绩相同时，按学号递增排序
        result = strcmp(studentA->id, studentB->id);
    } else {
        // 按成绩递增排序
        result = studentA->score - studentB->score;
    }

    return result;
}

int main() {
    int N, C;
    scanf("%d %d", &N, &C);

    Student* students = (Student*)malloc(N * sizeof(Student));

    // 读入学生信息
    for (int i = 0; i < N; ++i) {
        scanf("%s %s %d", students[i].id, students[i].name, &students[i].score);
    }

    // 使用qsort进行排序
    qsort(students, N, sizeof(Student), compare);

    // 输出排序后的结果
    for (int i = 0; i < N; ++i) {
        printf("%s %s %d\n", students[i].id, students[i].name, students[i].score);
    }

    // 释放内存
    free(students);

    return 0;
}
