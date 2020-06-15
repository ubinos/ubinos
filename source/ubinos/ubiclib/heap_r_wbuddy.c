/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "_heap.h"

#if !(UBINOS__UBICLIB__EXCLUDE_HEAP == 1)

#if !(UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__WBUDDY == 1)

#define _UBINOS__UBICLIB__HEAP_DIR	1
#define _UBINOS__UBICLIB__HEAP_DIR_r	0

int _heap_r_wbuddy_init_region(
		_heap_pt heap, unsigned int addr, unsigned int size, int locktype,
		unsigned int m, unsigned int fblcount, edlist_pt fbl_p, bitmap_pt fblbm			) {
	#define LOGM_TAG	"_heap_r_wbuddy_init_region       "

	int r;
	unsigned int log2m;
	unsigned int k, w, t;
	_heap_region_pt region;
	unsigned int i;

	m = 2;

	region						= &heap->region[_UBINOS__UBICLIB__HEAP_DIR];

	region->dir					= _UBINOS__UBICLIB__HEAP_DIR;
	region->algorithm			= UBINOS__UBICLIB__HEAP_ALGORITHM__WBUDDY;
	region->locktype			= locktype;

	log2m = uilog2_floor(m);

	_asize_to_kwt(size, k, w, t, log2m, m);
	if (k < 1 || HEAP_G_K_MAX < k) {
		r = -4;
		goto end0;
	}
	if (fblcount < heap_wbuddy_calc_fblcount(size, m)) {
		r = -7;
		goto end0;
	}

	region->m					= m;
	region->log2m				= log2m;
	region->maskm				= ~((unsigned int) (-1) << log2m);
	_asize_to_kwt(HEAP_BLOCK_ASIZE_MIN, k, w, t, log2m, m);
	region->min					= _kwt_to_asize(k, w, t, log2m);

	region->size_min			= _kwt_to_asize(k + 2, 1, 1, log2m);
	region->size				= 0;
	region->k					= 0;
	region->w					= 0;
	region->t					= 0;
	region->addr				= addr + size;
	region->end					= addr + size;

	region->limit				= addr;

	if (region->size_min > size) {
		r = -4;
		goto end0;
	}

	for (i=0; i<fblcount; i++) {
		edlist_init(&fbl_p[i]);
		fbl_p[i].data = (void *) i;
	}
	region->fblcount			= fblcount;
	region->fbloffset	 		= _kwt_to_sn(k, w, t, log2m, m) - 1;
	region->fbl_ap				= fbl_p;
	region->fblbm				= fblbm;

	region->dregs_size			= 0;

	edlist_init(&region->abl);

	region->acount_max			= 0;
	region->asize				= 0;
	region->asize_max			= 0;
	region->rsize				= 0;
	region->rsize_max			= 0;

	region->mutex 				= NULL;

	r = 0;

end0:
	return r;

	#undef LOGM_TAG
}

_heap_block_pt _heap_r_wbuddy_expand(_heap_pt heap, unsigned int asize) {
	#define LOGM_TAG	"_heap_r_wbuddy_expand            "

	bsp_abortsystem();
	return NULL;

	#undef LOGM_TAG
}

int _heap_r_wbuddy_reduce(_heap_pt heap) {
	#define LOGM_TAG	"_heap_r_wbuddy_reduce            "

	bsp_abortsystem();
	return NULL;

	#undef LOGM_TAG
}

_heap_block_pt _heap_r_wbuddy_combine_block(_heap_pt heap, _heap_block_pt block, int endflag) {
	#define LOGM_TAG	"_heap_r_wbuddy_combine_block     "

	bsp_abortsystem();
	return NULL;

	#undef LOGM_TAG
}

_heap_block_pt _heap_r_wbuddy_split_block(_heap_pt heap, _heap_block_pt block, unsigned int asize) {
	#define LOGM_TAG	"_heap_r_wbuddy_split_block       "

	bsp_abortsystem();
	return NULL;

	#undef LOGM_TAG
}

void * _heap_r_wbuddy_allocate_block(_heap_pt heap, unsigned int size) {
	#define LOGM_TAG	"_heap_r_wbuddy_allocate_block    "

	bsp_abortsystem();
	return NULL;

	#undef LOGM_TAG
}

int _heap_r_wbuddy_release_block(_heap_pt heap, void * ptr) {
	#define LOGM_TAG	"_heap_r_wbuddy_release_block     "

	bsp_abortsystem();
	return NULL;

	#undef LOGM_TAG
}

#endif /* !(UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__WBUDDY == 1) */

#endif /* !(UBINOS__UBICLIB__EXCLUDE_HEAP == 1) */
