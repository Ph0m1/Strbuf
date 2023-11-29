#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct strbuf
{
    int len;
    int alloc;
    char *buf;
};

// 确保在 len 之后 strbuf 中至少有 extra 个字节的空闲空间可用。
void strbuf_grow(struct strbuf *sb, size_t extra)
{
    if (sb->alloc > sb->len + extra)
        return;
    sb->buf = (char *)realloc(sb->buf, (sb->len + extra) * sizeof(char));
    if (sb->buf = NULL)
    {
        fprintf(stderr, "重新分配内存失败\n");
        return;
    }
    sb->alloc = sb->len + extra;
}

// 向 sb 追加长度为 len 的数据 data。
void strbuf_add(struct strbuf *sb, const void *data, size_t len)
{
    strbuf_grow(sb, len);
    memcpy(sb->buf + sb->len, data, len);
    sb->buf[sb->len + len] = '\0';
    sb->len += len;
}

// 向 sb 追加一个字符 c。
void strbuf_addch(struct strbuf *sb, int c)
{
    strbuf_add(sb, &c, 1);
}

// 向 sb 追加一个字符串 s。
void strbuf_addstr(struct strbuf *sb, const char *s)
{
    strbuf_add(sb, s, strlen(s));
}

// 向一个 sb 追加另一个 strbuf的数据。
void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2)
{
    strbuf_add(sb, sb->buf, sb->len);
}

// 设置 sb 的长度 len。
void strbuf_setlen(struct strbuf *sb, size_t len)
{
    if (len < sb->alloc)
    {
        sb->buf = (char *)realloc(sb->buf, len * sizeof(char));
        sb->alloc = len * sizeof(char);
        sb->len = len;
        return;
    }
    sb->len = len;
    sb->buf[sb->len] = '\0';
}

// 计算 sb 目前仍可以向后追加的字符串长度。
size_t strbuf_avail(const struct strbuf *sb)
{
    size_t tlen;
    tlen = sb->alloc - sb->len - 1;
    return tlen;
}

// 向 sb 内存坐标为 pos 位置插入长度为 len 的数据 data。
void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len)
{
    strbuf_add(sb->buf + pos, data, len);
}
