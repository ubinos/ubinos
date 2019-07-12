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

#include "_ubiclib.h"

#if !(UBINOS__UBICLIB__EXCLUDE_BITMAP == 1)

#include <stdlib.h>
#include <string.h>

#undef	LOGM_CATEGORY
#define LOGM_CATEGORY 				LOGM_CATEGORY__BITMAP
#undef	LOGM_TAG

#if		(2 == INT_SIZE)	// 16 bit machine

	#define LOG2_INT_BIT_SIZE	4
	#define MASK_INT_BIT_SIZE	0x000F

	#define _set_highbits(bits) {		\
		(bits) |= ((bits) <<  1);		\
		(bits) |= ((bits) <<  2);		\
		(bits) |= ((bits) <<  4);		\
		(bits) |= ((bits) <<  8);		\
	}

	#define _set_lowbits(bits) {		\
		(bits) |= ((bits) >>  1);		\
		(bits) |= ((bits) >>  2);		\
		(bits) |= ((bits) >>  4);		\
		(bits) |= ((bits) >>  8);		\
	}

#elif	(4 == INT_SIZE)	// 32 bit machine

	#define LOG2_INT_BIT_SIZE	5
	#define MASK_INT_BIT_SIZE	0x0000001F

	#define _set_highbits(bits) {		\
		(bits) |= ((bits) <<  1);		\
		(bits) |= ((bits) <<  2);		\
		(bits) |= ((bits) <<  4);		\
		(bits) |= ((bits) <<  8);		\
		(bits) |= ((bits) << 16);		\
	}

	#define _set_lowbits(bits) {		\
		(bits) |= ((bits) >>  1);		\
		(bits) |= ((bits) >>  2);		\
		(bits) |= ((bits) >>  4);		\
		(bits) |= ((bits) >>  8);		\
		(bits) |= ((bits) >> 16);		\
	}

#else
	#error "Unsupported int size"
#endif

#define INT_BIT_SIZE			(INT_SIZE * 8)

unsigned int bitmap_getmapsize(unsigned int bitsize) {
	#define LOGM_TAG	"bitmap_getmapsize"

	unsigned int mapsize;

	bitsize = uidiv_ceil(bitsize, INT_BIT_SIZE);
	mapsize = bitsize;
	for (;;) {
		if (1 >= bitsize) {
			break;
		}
		bitsize = uidiv_ceil(bitsize, INT_BIT_SIZE);
		mapsize += bitsize;
	}

	return mapsize;

	#undef LOGM_TAG
}

int bitmap_init(bitmap_pt bitmap, unsigned int bitsize, unsigned char * buf, unsigned int bufsize) {
	#define LOGM_TAG	"bitmap_init"

	int i;
	unsigned int offset;
    unsigned int needbufsize;

	if (NULL == bitmap) {
		logme("bitmap is NULL\r\n");
		return -2;
	}

	if (0 >= bitsize) {
		logme("bitsize is wrong\r\n");
		return -3;
	}

	if (NULL == buf) {
		logme("buf is NULL\r\n");
		return -4;
	}

	needbufsize =  bitmap_getmemsize(bitsize);
	if (bufsize < needbufsize) {
		logme("bufsize is too small\r\n");
		return -5;
	}

	bitmap->bitsize 		= bitsize;
	bitmap->map				= (unsigned int *) buf;
	bitmap->map_bytesize	= bufsize;
	bitmap->level_depth		= 0;

	for (i=0;; i++) {
		if (BITMAP_DEPTH_MAX <= i) {
			logme("bit size is too big\r\n");
			return -5;
		}
		offset = bitmap_getmapsize(bitsize) - 1;
		bitmap->level_offset_a[i] = offset;
		if (0 == offset) {
			break;
		}
		bitsize = uidiv_ceil(bitsize, INT_BIT_SIZE);
	}
	bitmap->level_depth = i + 1;

	memset(buf, 0x00, bufsize);

	return 0;

	#undef LOGM_TAG
}

unsigned int bitmap_getmemsize(unsigned int bitsize) {
	#define LOGM_TAG	"bitmap_getmemsize"

	unsigned int mapsize;

	mapsize = bitmap_getmapsize(bitsize);

	return (mapsize * INT_SIZE);

	#undef LOGM_TAG
}

int bitmap_create(bitmap_pt * bitmap_p, unsigned int bitsize) {
	#define LOGM_TAG	"bitmap_create"

	int r;
	bitmap_pt bitmap;
	unsigned char * buf;
	unsigned int bufsize;

	if (NULL == bitmap_p) {
		logme("bitmap_p is NULL\r\n");
		return -2;
	}

	if (0 >= bitsize) {
		logme("bitsize is wrong\r\n");
		return -3;
	}

	bitmap = malloc(sizeof(bitmap_t));
	if (NULL == bitmap) {
		logme("malloc(...) fail\r\n");
		return -1;
	}

	bufsize = bitmap_getmemsize(bitsize);
	buf = malloc(bufsize);
	if (NULL == buf) {
		logme("malloc(...) fail\r\n");
		free(bitmap);
		return -1;
	}

	r = bitmap_init(bitmap, bitsize, buf, bufsize);
	if (0 != r) {
		logme("fail at bitmap_init\r\n");
		free(buf);
		free(bitmap);
		return -1;
	}

	*bitmap_p = bitmap;

	return 0;

	#undef LOGM_TAG
}

int bitmap_delete(bitmap_pt * bitmap_p) {
	#define LOGM_TAG	"bitmap_delete"

	bitmap_pt bitmap;

	if (NULL == bitmap_p) {
		logme("bitmap_p is NULL\r\n");
		return -2;
	}

	if (NULL == *bitmap_p) {
		logme("*bitmap_p is NULL\r\n");
		return -2;
	}

	bitmap = *bitmap_p;

	if (NULL == bitmap->map) {
		logme("map is NULL\r\n");
		return -2;
	}

	free(bitmap->map);
	free(bitmap);

	*bitmap_p = NULL;

	return 0;

	#undef LOGM_TAG
}

unsigned int bitmap_getlsb(bitmap_pt bitmap) {
	#define LOGM_TAG	"bitmap_getlsb"

	unsigned int offset;
	unsigned int l;
	unsigned int bi;
	unsigned int tmp;

	if (NULL == bitmap) {
		logme("bitmap is NULL\r\n");
		return -2;
	}

	if (0 == bitmap->level_depth) {
		logme("depth is 0\r\n");
		return -2;
	}

	bi = 0;
	l = bitmap->level_depth - 1;
	for (;;) {
		offset = bitmap->level_offset_a[l];
		tmp = bitmap->map[offset - bi];
		if (0 == tmp) {
			return 0;
		}
		bi = (bi << LOG2_INT_BIT_SIZE) + uilog2_floor(uilsb(tmp));
		if (0 == l) {
			break;
		}
		l--;
	}

	return (bi + 1);

	#undef LOGM_TAG
}

unsigned int bitmap_getlsb2(bitmap_pt bitmap, unsigned int index) {
	#define LOGM_TAG	"bitmap_getlsb2"


	unsigned int offset;
	unsigned int l;
	unsigned int bi;
	unsigned int tmp;
	unsigned int mask;

	if (NULL == bitmap) {
		logme("bitmap is NULL\r\n");
		return -2;
	}

	if (0 == bitmap->level_depth) {
		logme("depth is 0\r\n");
		return -2;
	}

	if (0 >= index || bitmap->bitsize < index) {
		logme("index is wrong\r\n");
		return 0;
	}

	index--;

	bi = 0;
	l = bitmap->level_depth - 1;
	for (;;) {
		tmp = index >> (LOG2_INT_BIT_SIZE * l);
		if (bi > (tmp >> LOG2_INT_BIT_SIZE)) {
			mask = -1;
		}
		else {
			mask = 0x1 << (tmp & MASK_INT_BIT_SIZE);
			_set_highbits(mask);
		}
		offset = bitmap->level_offset_a[l];
		tmp = bitmap->map[offset - bi] & mask;
		if (0 == tmp) {
			if (bitmap->level_depth - 1 == l) {
				return 0;
			}
			else if (0 == index % (0x1 << (LOG2_INT_BIT_SIZE * (l+1)))) {
				return 0;
			}
			else {
				index = (bi+1) << (LOG2_INT_BIT_SIZE * (l+1));
				bi = 0;
				l = bitmap->level_depth - 1;
				continue;
			}
		}
		bi = (bi << LOG2_INT_BIT_SIZE) + uilog2_floor(uilsb(tmp));
		if (0 == l) {
			break;
		}
		l--;
	}

	return (bi + 1);

	#undef LOGM_TAG
}

unsigned int bitmap_getmsb(bitmap_pt bitmap) {
	#define LOGM_TAG	"bitmap_getmsb"

	unsigned int offset;
	unsigned int l;
	unsigned int bi;
	unsigned int tmp;

	if (NULL == bitmap) {
		logme("bitmap is NULL\r\n");
		return -2;
	}

	if (0 == bitmap->level_depth) {
		logme("depth is 0\r\n");
		return -2;
	}

	bi = 0;
	l = bitmap->level_depth - 1;
	for (;;) {
		offset = bitmap->level_offset_a[l];
		tmp = bitmap->map[offset - bi];
		if (0 == tmp) {
			return 0;
		}
		bi = (bi << LOG2_INT_BIT_SIZE) + uilog2_floor(uimsb(tmp));
		if (0 == l) {
			break;
		}
		l--;
	}

	return (bi + 1);

	#undef LOGM_TAG
}

int bitmap_getbit(bitmap_pt bitmap, unsigned int index) {
	#define LOGM_TAG	"bitmap_getbit"

	unsigned int offset;

	if (NULL == bitmap) {
		logme("bitmap is NULL\r\n");
		return -2;
	}

	if (0 == bitmap->level_depth) {
		logme("depth is 0\r\n");
		return -2;
	}

	if (0 >= index || bitmap->bitsize < index) {
		logme("index is wrong\r\n");
		return 0;
	}

	index--;

	offset = bitmap->level_offset_a[0];

	return (bitmap->map[offset - (index >> LOG2_INT_BIT_SIZE)] >> (index & MASK_INT_BIT_SIZE)) & 0x1;

	#undef LOGM_TAG
}

int bitmap_setbit(bitmap_pt bitmap, unsigned int index, int value) {
	#define LOGM_TAG	"bitmap_setbit"

	int i;
	unsigned int level;
	unsigned int offset;
	unsigned int bitindex;
	unsigned int mapindex;

	if (NULL == bitmap) {
		logme("bitmap is NULL\r\n");
		return -2;
	}

	if (0 == bitmap->level_depth) {
		logme("depth is 0\r\n");
		return -2;
	}

	if (0 >= index || bitmap->bitsize < index) {
		logme("index is wrong\r\n");
		return 0;
	}

	index--;

	level = bitmap->level_depth - 1;
	bitindex = index & MASK_INT_BIT_SIZE;
	mapindex = index >> LOG2_INT_BIT_SIZE;

	if (0 == value) {
		for (i=0; i<=level; i++) {
			offset = bitmap->level_offset_a[i];
			bitmap->map[offset - mapindex] &= ~(0x1 << bitindex);
			if (0 != bitmap->map[offset - mapindex]) {
				break;
			}

			bitindex = mapindex & MASK_INT_BIT_SIZE;
			mapindex = mapindex >> LOG2_INT_BIT_SIZE;
		}
	}
	else {
		for (i=0; i<=level; i++) {
			offset = bitmap->level_offset_a[i];
			bitmap->map[offset - mapindex] |=  (0x1 << bitindex);

			bitindex = mapindex & MASK_INT_BIT_SIZE;
			mapindex = mapindex >> LOG2_INT_BIT_SIZE;
		}
	}

	return 0;

	#undef LOGM_TAG
}

int bitmap_setbitall(bitmap_pt bitmap, int value) {
	#define LOGM_TAG	"bitmap_setbitall"

	int i, j;
	unsigned int level;
	unsigned int offset;
	unsigned int bitsize;
	unsigned int mapsize;

	if (NULL == bitmap) {
		logme("bitmap is NULL\r\n");
		return -2;
	}

	if (0 == bitmap->level_depth) {
		logme("depth is 0\r\n");
		return -2;
	}

	memset(bitmap->map, 0x00, bitmap->map_bytesize);

	if (1 == value) {
		level = bitmap->level_depth - 1;

		bitsize = bitmap->bitsize % INT_BIT_SIZE;
		if (0 == bitsize) {
			bitsize = INT_BIT_SIZE;
		}
		mapsize = uidiv_ceil(bitmap->bitsize, INT_BIT_SIZE);

		for (i=0; i<level; i++) {
			offset = bitmap->level_offset_a[i+1];
			memset(&bitmap->map[offset + 2], 0xFF, (mapsize - 1) * INT_SIZE);
			for (j=0; j<bitsize; j++) {
				bitmap->map[offset + 1] |= (0x1 << j);
			}

			bitsize = mapsize % INT_BIT_SIZE;
			if (0 == bitsize) {
				bitsize = INT_BIT_SIZE;
			}
			mapsize = uidiv_ceil(mapsize, INT_BIT_SIZE);
		}

		offset = bitmap->level_offset_a[level];
		for (j=0; j<bitsize; j++) {
			bitmap->map[offset] |= (0x1 << j);
		}
	}

	return 0;

	#undef LOGM_TAG
}

#endif /* !(UBINOS__UBICLIB__EXCLUDE_BITMAP == 1) */
