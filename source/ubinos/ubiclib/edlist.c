/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "_ubiclib.h"

#include <stdlib.h>

void * _edlist_setcur(edlist_pt edlist, void * cur)
{
	(edlist)->cur = cur;

	return cur;
}

void * _edlist_getcur(edlist_pt edlist)
{
	if (NULL == (edlist)->cur) {
		(edlist)->cur = (edlist)->head;
	}

	return (edlist)->cur;
}
