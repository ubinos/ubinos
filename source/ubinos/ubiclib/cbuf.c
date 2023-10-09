/*
 * Copyright (c) 2020 Sung Ho Park and CSOS
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "_ubiclib.h"

#if !(UBINOS__UBICLIB__EXCLUDE_CBUF == 1)

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#undef LOGM_CATEGORY
#define LOGM_CATEGORY LOGM_CATEGORY__UBICLIB

static ubi_err_t cbuf_read_advan(cbuf_pt cbuf, uint8_t *buf, uint32_t len, uint32_t *read_p, uint8_t reserve);

ubi_err_t cbuf_create(cbuf_pt *cbuf_p, uint32_t size)
{
    ubi_err_t ubi_err;
    cbuf_pt cbuf;
    assert(cbuf_p != NULL);
    assert(size > 0);

    do
    {
        cbuf = malloc(sizeof(cbuf_t) + size);
        if (cbuf == NULL)
        {
            logme("no memory");
            ubi_err = UBI_ERR_NO_MEM;
            break;
        }

        cbuf->head = 0;
        cbuf->tail = 0;
        cbuf->size = size;
        cbuf->buf = (uint8_t*) ((uintptr_t) cbuf + sizeof(cbuf_t));

        *cbuf_p = cbuf;

        ubi_err = UBI_ERR_OK;
    } while (0);

    return ubi_err;
}

ubi_err_t cbuf_delete(cbuf_pt *cbuf_p)
{
    assert(cbuf_p != NULL);
    assert(*cbuf_p != NULL);

    free(*cbuf_p);
    *cbuf_p = NULL;

    return UBI_ERR_OK;
}

ubi_err_t cbuf_write(cbuf_pt cbuf, const uint8_t *buf, uint32_t len, uint32_t *written_p)
{
    ubi_err_t ubi_err;
    uint32_t head, tail, size;
    uint32_t size1, size2;
    uint32_t offset1, offset2;
    uint32_t len1, len2;
    assert(cbuf != NULL);

    head = cbuf->head;
    tail = cbuf->tail;
    size = cbuf->size;

    do
    {
        if (len == 0)
        {
            if (written_p)
            {
                *written_p = 0;
            }
            ubi_err = UBI_ERR_OK;
            break;
        }

        if (head <= tail)
        {
            if (head == 0)
            {
                size1 = size - tail - 1;
                size2 = 0;
            }
            else
            {
                size1 = size - tail;
                size2 = head - 1;
            }
            offset1 = tail;
            offset2 = 0;
        }
        else
        {
            size1 = head - tail - 1;
            size2 = 0;
            offset1 = tail;
            offset2 = size;
        }
        len1 = min(size1, len);
        len2 = min(size2, len - len1);

        if (buf)
        {
            if (len1 > 0)
            {
                memcpy(&cbuf->buf[offset1], &buf[0], len1);
            }
            if (len2 > 0)
            {
                memcpy(&cbuf->buf[offset2], &buf[len1], len2);
            }
        }

        cbuf->tail = (cbuf->tail + len1 + len2) % size;

        if (written_p)
        {
            *written_p = len1 + len2;
        }

        if (len != (len1 + len2))
        {
            ubi_err = UBI_ERR_BUF_FULL;
        }
        else
        {
            ubi_err = UBI_ERR_OK;
        }
    } while (0);

    return ubi_err;
}

static ubi_err_t cbuf_read_advan(cbuf_pt cbuf, uint8_t *buf, uint32_t len, uint32_t *read_p, uint8_t reserve)
{
    ubi_err_t ubi_err;
    uint32_t head, tail, size;
    uint32_t offset1, offset2;
    uint32_t len1, len2;

    assert(cbuf != NULL);

    head = cbuf->head;
    tail = cbuf->tail;
    size = cbuf->size;

    do
    {
        if (len == 0)
        {
            if (read_p)
            {
                *read_p = 0;
            }
            ubi_err = UBI_ERR_OK;
            break;
        }

        if (head <= tail)
        {
            offset1 = head;
            offset2 = size;
            len1 = min(tail - head, len);
            len2 = 0;
        }
        else
        {
            offset1 = head;
            offset2 = 0;
            len1 = min(size - head, len);
            len2 = min(tail, len - len1);
        }

        if (buf)
        {
            if (len1 > 0)
            {
                memcpy(&buf[0], &cbuf->buf[offset1], len1);
            }
            if (len2 > 0)
            {
                memcpy(&buf[len1], &cbuf->buf[offset2], len2);
            }
        }

        if (!reserve)
        {
            cbuf->head = (cbuf->head + len1 + len2) % size;
        }

        if (read_p)
        {
            *read_p = len1 + len2;
        }

        if (len != (len1 + len2))
        {
            ubi_err = UBI_ERR_BUF_EMPTY;
        }
        else
        {
            ubi_err = UBI_ERR_OK;
        }
    } while (0);

    return ubi_err;
}

ubi_err_t cbuf_read(cbuf_pt cbuf, uint8_t *buf, uint32_t len, uint32_t *read_p)
{
    return cbuf_read_advan(cbuf, buf, len, read_p, 0);
}

ubi_err_t cbuf_view(cbuf_pt cbuf, uint8_t * buf, uint32_t len, uint32_t * read_p)
{
    return cbuf_read_advan(cbuf, buf, len, read_p, 1);
}

ubi_err_t cbuf_clear(cbuf_pt cbuf)
{
    assert(cbuf != NULL);

    cbuf->head = cbuf->tail;

    return 0;
}

uint32_t cbuf_get_len(cbuf_pt cbuf)
{
    uint32_t head, tail, size;
    uint32_t len;
    assert(cbuf != NULL);

    head = cbuf->head;
    tail = cbuf->tail;
    size = cbuf->size;

    if (head <= tail)
    {
        len = tail - head;
    }
    else
    {
        len = size - head + tail;
    }

    return len;
}

uint32_t cbuf_get_empty_len(cbuf_pt cbuf)
{
    uint32_t head, tail, size;
    uint32_t len;
    assert(cbuf != NULL);

    head = cbuf->head;
    tail = cbuf->tail;
    size = cbuf->size;

    if (head <= tail)
    {
        len = tail - head;
    }
    else
    {
        len = size - head + tail;
    }

    return size - len - 1;
}

uint8_t cbuf_is_full(cbuf_pt cbuf) {
    uint8_t is_full;
    assert(cbuf != NULL);

    if (cbuf_get_len(cbuf) == (cbuf->size - 1))
    {
        is_full = 1;
    }
    else
    {
        is_full = 0;
    }

    return is_full;
}

uint8_t* cbuf_get_head_addr(cbuf_pt cbuf)
{
    assert(cbuf != NULL);

    return &cbuf->buf[cbuf->head];
}

uint8_t * cbuf_get_tail_addr(cbuf_pt cbuf)
{
    assert(cbuf != NULL);

    return &cbuf->buf[cbuf->tail];
}

uint32_t cbuf_get_contig_len(cbuf_pt cbuf)
{
    uint32_t head, tail, size;
    uint32_t contiglen;
    assert(cbuf != NULL);

    head = cbuf->head;
    tail = cbuf->tail;
    size = cbuf->size;

    if (head <= tail)
    {
        contiglen = tail - head;
    }
    else
    {
        contiglen = size - head;
    }

    return contiglen;
}

uint32_t cbuf_get_contig_empty_len(cbuf_pt cbuf)
{
    uint32_t head, tail, size;
    uint32_t contiglen;
    assert(cbuf != NULL);

    head = cbuf->head;
    tail = cbuf->tail;
    size = cbuf->size;

    if (head <= tail)
    {
        if (head == 0)
        {
            contiglen = size - tail - 1;
        }
        else
        {
            contiglen = size - tail;
        }
    }
    else
    {
        contiglen = head - tail - 1;
    }

    return contiglen;
}

uint8_t cbuf_align_head(cbuf_pt cbuf, uint8_t align)
{
    uint8_t aligned;
    uint32_t head, tail, size;
    uint32_t align_2;
    uint32_t head_addr;
    uint32_t head_addr_aligned;
    uint32_t diff;
    assert(cbuf != NULL);
    assert(align > 0);

    head = cbuf->head;
    tail = cbuf->tail;
    size = cbuf->size;
    aligned = 0;
    align_2 = align - 1;

    if (head == tail)
    {
        head_addr = (uint32_t) &cbuf->buf[head];
        head_addr_aligned = (head_addr + align_2) &  ~align_2;
        diff = head_addr_aligned - head_addr;
        if((head + diff) < size)
        {
            head = head + diff;
            tail = head;
        }
        else
        {
            head_addr = (uint32_t) &cbuf->buf[0];
            head_addr_aligned = (head_addr + align_2) &  ~align_2;
            diff = head_addr_aligned - head_addr;
            assert(diff < size);
            head = diff;
            tail = head;
        }
        cbuf->head = head;
        cbuf->tail = tail;
        aligned = 1;
    }

    return aligned;
}

#endif /* !(UBINOS__UBICLIB__EXCLUDE_CBUF == 1) */

