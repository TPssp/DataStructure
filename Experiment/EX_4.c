#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_FILE_COUNT 100
#define MAX_WORD_LENGTH 11  // 考虑到长度不超过10的英文单词，加上终止符

// 哈希表节点定义
typedef struct HashNode {
    char word[MAX_WORD_LENGTH];
    struct HashNode* next;
} HashNode;

// 哈希表定义
typedef struct {
    HashNode* buckets[MAX_FILE_COUNT];  // 假设文件总数不超过100
} HashTable;

// 初始化哈希表
void initHashTable(HashTable* ht) {
    for (int i = 0; i < MAX_FILE_COUNT; ++i) {
        ht->buckets[i] = NULL;
    }
}

// 向哈希表中插入单词
void insertWord(HashTable* ht, int fileIndex, char* word) {
    // 计算哈希值
    unsigned int hashValue = 0;
    for (int i = 0; word[i] != '\0'; ++i) {
        hashValue = (hashValue * 131 + word[i]) % MAX_FILE_COUNT;
    }

    // 查找是否已存在该单词
    HashNode* current = ht->buckets[hashValue];
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            return;  // 单词已存在
        }
        current = current->next;
    }

    // 单词不存在，插入新节点
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    strcpy(newNode->word, word);
    newNode->next = ht->buckets[hashValue];
    ht->buckets[hashValue] = newNode;
}

// 释放哈希表
void freeHashTable(HashTable* ht) {
    for (int i = 0; i < MAX_FILE_COUNT; ++i) {
        HashNode* current = ht->buckets[i];
        while (current != NULL) {
            HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

// 提取单词并插入哈希表
void processFile(HashTable* ht, int fileIndex) {
    char word[MAX_WORD_LENGTH];
    while (scanf("%s", word) == 1 && word[0] != '#') {
        // 将单词转换为小写
        for (int i = 0; word[i] != '\0'; ++i) {
            word[i] = tolower(word[i]);
        }

        // 只考虑长度不小于3且不超过10的英文单词
        int length = strlen(word);
        if (length >= 3 && length <= 10) {
            // 超过10个字符的单词只取前10个
            word[10] = '\0';
            insertWord(ht, fileIndex, word);
        }
    }
}

// 计算相似度
double calculateSimilarity(HashTable* ht, int fileIndex1, int fileIndex2) {
    int commonWords = 0;
    int totalWords1 = 0;
    int totalWords2 = 0;

    for (int i = 0; i < MAX_FILE_COUNT; ++i) {
        HashNode* current = ht->buckets[i];
        while (current != NULL) {
            if (i == fileIndex1) {
                ++totalWords1;
            }
            if (i == fileIndex2) {
                ++totalWords2;
                // 检查在文件2中是否存在相同的单词
                HashNode* searchNode = ht->buckets[fileIndex2];
                while (searchNode != NULL) {
                    if (strcmp(searchNode->word, current->word) == 0) {
                        ++commonWords;
                        break;
                    }
                    searchNode = searchNode->next;
                }
            }
            current = current->next;
        }
    }

    // 计算相似度
    if (totalWords1 == 0 || totalWords2 == 0) {
        return 0.0;
    }

    return (double)commonWords / ((double)totalWords1 + (double)totalWords2 - (double)commonWords) * 100.0;
}

int main() {
    int N, M;
    scanf("%d", &N);

    HashTable ht[MAX_FILE_COUNT];
    for (int i = 0; i < N; ++i) {
        initHashTable(&ht[i]);
        processFile(&ht[i], i);
    }

    scanf("%d", &M);
    for (int i = 0; i < M; ++i) {
        int fileIndex1, fileIndex2;
        scanf("%d %d", &fileIndex1, &fileIndex2);

        double similarity = calculateSimilarity(&ht[fileIndex1 - 1], fileIndex1 - 1, fileIndex2 - 1);
        printf("%.1f%%\n", similarity);
    }

    // 释放哈希表
    for (int i = 0; i < N; ++i) {
        freeHashTable(&ht[i]);
    }

    return 0;
}
