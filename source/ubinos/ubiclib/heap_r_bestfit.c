/*
  Copyright (C) 2009 Sung Ho Park
  Contact: ubinos.org@gmail.com

  This file is part of the lib_ubiclib component of the Ubinos.

  GNU General Public License Usage
  This file may be used under the terms of the GNU
  General Public License version 3.0 as published by the Free Software
  Foundation and appearing in the file license_gpl3.txt included in the
  packaging of this file. Please review the following information to
  ensure the GNU General Public License version 3.0 requirements will be
  met: http://www.gnu.org/copyleft/gpl.html.

  GNU Lesser General Public License Usage
  Alternatively, this file may be used under the terms of the GNU Lesser
  General Public License version 2.1 as published by the Free Software
  Foundation and appearing in the file license_lgpl.txt included in the
  packaging of this file. Please review the following information to
  ensure the GNU Lesser General Public License version 2.1 requirements
  will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.

  Commercial Usage
  Alternatively, licensees holding valid commercial licenses may
  use this file in accordance with the commercial license agreement
  provided with the software or, alternatively, in accordance with the
  terms contained in a written agreement between you and rightful owner.
*/

#include "_heap.h"

#if !(UBINOS__UBICLIB__EXCLUDE_HEAP == 1)

#if !(UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__BESTFIT == 1) || !(UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__FIRSTFIT == 1) || !(UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__NEXTFIT == 1)

#define _UBINOS__UBICLIB__HEAP_DIR	1
#define _UBINOS__UBICLIB__HEAP_DIR_r	0

int _heap_r_bestfit_init_region(
		_heap_pt heap, unsigned int addr, unsigned int size, int locktype,
		unsigned int m, unsigned int fblcount, edlist_pt fbl_p, bitmap_pt fblbm			) {
	#define LOGM_TAG	"_heap_r_bestfit_init_region    "

	int r;
	_heap_region_pt region;
	unsigned int i;

	region						= &heap->region[_UBINOS__UBICLIB__HEAP_DIR];

	region->dir					= _UBINOS__UBICLIB__HEAP_DIR;
	region->algorithm			= UBINOS__UBICLIB__HEAP_ALGORITHM__BESTFIT;
	region->locktype			= locktype;

	if (fblcount < 2) {
		r = -7;
		goto end0;
	}

	region->m					= 0;
	region->log2m				= 0;
	region->maskm				= 0;
	region->min					= HEAP_BLOCK_ASIZE_MIN;

	region->size_min			= 0;
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
	region->fbloffset	 		= 0;
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

_heap_block_pt _heap_r_bestfit_expand(_heap_pt heap, unsigned int asize) {
	#define LOGM_TAG	"_heap_r_bestfit_expand         "

	return NULL;

	#undef LOGM_TAG
}

int _heap_r_bestfit_reduce(_heap_pt heap) {
	#define LOGM_TAG	"_heap_r_bestfit_reduce         "

	return 0;

	#undef LOGM_TAG
}

_heap_block_pt _heap_r_bestfit_combine_block(_heap_pt heap, _heap_block_pt block, int endflag) {
	#define LOGM_TAG	"_heap_r_bestfit_combine_block  "

	return NULL;

	#undef LOGM_TAG
}

_heap_block_pt _heap_r_bestfit_split_block(_heap_pt heap, _heap_block_pt block, unsigned int asize) {
	#define LOGM_TAG	"_heap_r_bestfit_split_block    "

	return NULL;

	#undef LOGM_TAG
}

void * _heap_r_bestfit_allocate_block(_heap_pt heap, unsigned int size) {
	#define LOGM_TAG	"_heap_r_bestfit_allocate_block "

	return NULL;

	#undef LOGM_TAG
}

int _heap_r_bestfit_release_block(_heap_pt heap, void * ptr) {
	#define LOGM_TAG	"_heap_r_bestfit_release_block  "

	return 0;

	#undef LOGM_TAG
}

#endif /* !(UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__BESTFIT == 1) || !(UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__FIRSTFIT == 1) || !(UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__NEXTFIT == 1) */

#endif /* !(UBINOS__UBICLIB__EXCLUDE_HEAP == 1) */