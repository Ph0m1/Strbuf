#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

struct strbuf
{
    int len;   
    int alloc; 
    char *buf;
};

void strbuf_init(struct strbuf *sb, size_t alloc)
{
    sb->len = 0;
    sb->alloc = alloc;
    sb->buf = (char *)malloc(alloc * sizeof(char));
    if (sb->buf == NULL)
    {
        fprintf(stderr, "内存分配失败\n");
        exit(EXIT_FAILURE);
    }
}

// 将字符串填充到 sb 中，长度为 len, 容量为 alloc。
void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc)
{
    if (alloc > sb->alloc)
    {
        sb->alloc = alloc;
        sb->buf = (char *)realloc(sb->buf, alloc * sizeof(char));
        if (sb->buf == NULL)
        {
            fprintf(stderr, "内存重新分配失败\n");
            exit(EXIT_FAILURE);
        }
    }
    sb->buf = (char *)str;
    sb->len = len;
}

// 释放 sb 结构体的内存。
void strbuf_release(struct strbuf *sb)
{
    sb->alloc = 0;
    sb->len = 0;
    free(sb->buf);
}

// 交换两个 strbuf。
void strbuf_swap(struct strbuf *a, struct strbuf *b)
{
    int temp_len = a->len;
    a->len = b->len;
    b->len = temp_len;

    int temp_alloc = a->alloc;
    a->alloc = b->alloc;
    b->alloc = temp_alloc;

    char *temp_buf = a->buf;
    a->buf = b->buf;
    b->buf = temp_buf;
}

// 将 sb 中的原始内存取出，并将 sz 设置为其 alloc 大小 。
char *strbuf_detach(struct strbuf *sb, size_t *sz)
{
    *sz = sb->alloc;
    char *detach_buf = sb->buf;
    sb->buf = NULL;
    sb->len = 0;
    sb->alloc = 0;
    return detach_buf;
}

// 比较两个 strbuf 的内存是否相同。
int strbuf_cmp(const struct strbuf *first, const struct strbuf *second)
{
    if (first->len != second->len)
    {
        return 1;
    }
    return memcmp(first->buf, second->buf, first->len) != 0;
}

// 清空 sb。
void strbuf_reset(struct strbuf *sb)
{
    sb->len = 0;
}
