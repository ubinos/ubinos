/*
 * Copyright (c) 2020 Sung Ho Park and CSOS
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ubinos/ubik_test.h>

#if !(UBINOS__UBIK_TEST__EXCLUDE_CBUF_TEST == 1)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define UBIK_TEST_CBUF_BUF_SIZE 8

static uint8_t _g_buf[UBIK_TEST_CBUF_BUF_SIZE * 4];

cbuf_def_init(_g_cbuf, UBIK_TEST_CBUF_BUF_SIZE);

static void ubik_test_cbuf_print(cbuf_pt cbuf)
{
    assert(cbuf != NULL);

    printf("    size = %6ld, head = %6ld, tail = %6ld, len = %6ld\n", cbuf->size, cbuf->head, cbuf->tail, cbuf_get_len(cbuf));
    printf("        data :");
    for (uint32_t i = 0; i < UBIK_TEST_CBUF_BUF_SIZE; i++)
    {
        printf("%c", cbuf->buf[i]);
    }
    printf("\n");
}

static ubi_err_t ubik_test_cbuf_test_00_func(cbuf_pt cbuf)
{
    ubi_err_t uerr;
    uint8_t *buf;
    uint32_t len;
    uint32_t written, read;

    buf = _g_buf;

    sprintf((char*) buf, "abcd");
    len = strlen((char*) buf);
    uerr = cbuf_write(cbuf, buf, len, &written);
    assert(uerr == UBI_ERR_OK);
    printf("cbuf: 01: write: %ld\n", written);
    ubik_test_cbuf_print(cbuf);
    printf("\n");

    sprintf((char*) buf, "efg");
    len = strlen((char*) buf);
    uerr = cbuf_write(cbuf, buf, len, &written);
    assert(uerr == UBI_ERR_OK);
    printf("cbuf: 02: write: %ld\n", written);
    ubik_test_cbuf_print(cbuf);
    printf("\n");

    memset(buf, 0, UBIK_TEST_CBUF_BUF_SIZE);
    len = 5;
    uerr = cbuf_read(cbuf, buf, len, &read);
    assert(uerr == UBI_ERR_OK);
    buf[read] = 0;
    printf("cbuf: 03: read : %ld: %s\n", read, (char*) buf);
    ubik_test_cbuf_print(cbuf);
    printf("\n");

    sprintf((char*) buf, "hijk");
    len = strlen((char*) buf);
    uerr = cbuf_write(cbuf, buf, len, &written);
    assert(uerr == UBI_ERR_OK);
    printf("cbuf: 04: write: %ld\n", written);
    ubik_test_cbuf_print(cbuf);
    printf("        buf addr   : 0x%08x\n", (uintptr_t) cbuf->buf);
    printf("        head addr  : 0x%08x\n", (uintptr_t) cbuf_get_head_addr(cbuf));
    printf("        contig. len: %ld\n", cbuf_get_contig_len(cbuf));
    printf("\n");

    memset(buf, 0, UBIK_TEST_CBUF_BUF_SIZE);
    len = 4;
    uerr = cbuf_read(cbuf, buf, len, &read);
    assert(uerr == UBI_ERR_OK);
    buf[read] = 0;
    printf("cbuf: 05: read : %ld: %s\n", read, (char*) buf);
    ubik_test_cbuf_print(cbuf);
    printf("\n");

    memset(buf, 0, UBIK_TEST_CBUF_BUF_SIZE);
    len = 4;
    uerr = cbuf_read(cbuf, buf, len, &read);
    assert(uerr == UBI_ERR_OK);
    buf[read] = 0;
    printf("cbuf: 06: read : %ld: %s\n", read, (char*) buf);
    ubik_test_cbuf_print(cbuf);
    printf("\n");

    sprintf((char*) buf, "lmnopqrstuvwxyz");
    len = strlen((char*) buf);
    uerr = cbuf_write(cbuf, buf, len, &written);
    assert(uerr == UBI_ERR_OK);
    printf("cbuf: 07: write: %ld\n", written);
    ubik_test_cbuf_print(cbuf);
    printf("\n");

    memset(buf, 0, UBIK_TEST_CBUF_BUF_SIZE);
    len = 12;
    uerr = cbuf_read(cbuf, buf, len, &read);
    assert(uerr == UBI_ERR_OK);
    buf[read] = 0;
    printf("cbuf: 08: read : %ld: %s\n", read, (char*) buf);
    ubik_test_cbuf_print(cbuf);
    printf("\n");

    sprintf((char*) buf, "stuvw");
    len = strlen((char*) buf);
    uerr = cbuf_write(cbuf, buf, len, &written);
    assert(uerr == UBI_ERR_OK);
    printf("cbuf: 09: write: %ld\n", written);
    ubik_test_cbuf_print(cbuf);
    printf("\n");

    uerr = cbuf_clear(cbuf);
    assert(uerr == UBI_ERR_OK);
    printf("cbuf: 10: clear\n");
    ubik_test_cbuf_print(cbuf);
    printf("\n");

    uerr = UBI_ERR_OK;

    return uerr;
}

ubi_err_t ubik_test_cbuf_test_00()
{
    ubi_err_t uerr;
    cbuf_pt cbuf;

    uerr = cbuf_create(&cbuf, UBIK_TEST_CBUF_BUF_SIZE);
    assert(uerr == UBI_ERR_OK);
    memset(cbuf->buf, 0, cbuf->size);
    printf("cbuf: create\n");
    ubik_test_cbuf_print(cbuf);
    printf("\n");

    uerr = ubik_test_cbuf_test_00_func(cbuf);
    assert(uerr == UBI_ERR_OK);

    uerr = cbuf_delete(&cbuf);
    assert(uerr == UBI_ERR_OK);
    printf("cbuf: delete\n");
    printf("\n");

    printf("\n");
    printf("\n");

    cbuf = _g_cbuf;
    memset(cbuf->buf, 0, cbuf->size);
    printf("cbuf: static\n");
    ubik_test_cbuf_print(cbuf);
    printf("\n");

    uerr = ubik_test_cbuf_test_00_func(cbuf);
    assert(uerr == UBI_ERR_OK);

    uerr = UBI_ERR_OK;

    return uerr;
}

#endif /* !(UBINOS__UBIK_TEST__EXCLUDE_CBUF_TEST == 1) */

