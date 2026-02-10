#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void) {
    // 1. 打开文件
    FILE* file = fopen("text.txt", "r");
    if (file == NULL) {
        printf("无法打开文件text.txt\n");
        return 1;
    }

    // 2. 获取文件大小
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    printf("文件大小: %ld 字节\n", file_size);

    // 特殊情况：空文件
    if (file_size == 0) {
        fclose(file);
        printf("=== 文件统计结果 ===\n");
        printf("总字符数: 0\n");
        printf("总行数: 0\n");
        printf("大写字母数: 0\n");
        return 0;
    }

    // 3. 动态分配内存缓冲区
    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        printf("内存分配失败！\n");
        fclose(file);
        return 1;
    }

    // 4. 读取文件内容到缓冲区
    size_t bytes_read = fread(buffer, 1, file_size, file);
    buffer[bytes_read] = '\0';
    fclose(file);

    // 5. 使用指针遍历缓冲区进行统计
    char* p = buffer;
    int char_count = 0;
    int line_count = 0;
    int upper_count = 0;

    while (*p != '\0') {
        char_count++;

        if (isupper((unsigned char)*p)) {  // 安全使用 isupper
            upper_count++;
        }

        if (*p == '\n') {
            line_count++;
        }

        p++;
    }

    // 如果文件非空且最后一个字符不是 '\n'，则还有一行未计入
    if (char_count > 0 && buffer[bytes_read - 1] != '\n') {
        line_count++;
    }

    // 6. 输出统计结果
    printf("=== 文件统计结果 ===\n");
    printf("总字符数: %d\n", char_count);
    printf("总行数: %d\n", line_count);
    printf("大写字母数: %d\n", upper_count);

    // 7. 释放内存
    free(buffer);
    return 0;
}