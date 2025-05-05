
#include "../vec.h"

#include "stdlib.h"
#include "string.h"

#include "assert.h"


inline Vec vec_new(OciAllocator *alloc) {
	return (Vec) {
		.buf = NULL,
		.cap = 0,
		.len = 0,
		.alloc = alloc,
	};
}

inline void vec_free(Vec *v) {
	if (v->buf != NULL) {
		oci_free(v->alloc, v->buf, v->cap);
		v->buf = NULL;
	}
}

void vec_reserve_exact(Vec *v, usize capacity) {
	if (capacity <= v->cap) {
		return;
	}

	void *newbuf = oci_malloc(v->alloc, capacity);

	if (v->buf != NULL) {
		if (v->len > 0) {
			memcpy(newbuf, v->buf, v->len);
		}
		oci_free(v->alloc, v->buf, v->cap);
	}

	v->buf = newbuf;
	v->cap = capacity;
}

void vec_reserve(Vec *v, usize capacity) {
	usize newcap = v->cap;
	if (newcap < 4) {
		newcap = 4;
	}
	while (newcap < capacity) {
		newcap *= 2;
	}
	vec_reserve_exact(v, newcap);
}

inline void *vec_ptr(const Vec *vec) {
	return vec->buf;
}

inline usize vec_cap(const Vec *vec, usize stride) {
	return vec->cap / stride;
}

inline usize vec_len(const Vec *vec, usize stride) {
	return vec->len / stride;
}

inline void vec_len_set(Vec *vec, usize stride, usize len) {
	vec->len = len / stride;
}

inline void *vec_index(const Vec *v, usize stride, usize index) {
	assert(v->buf != NULL);
	assert(index * stride < v->len);
	return (u8*)v->buf + index * stride;
}

inline void *vec_push(Vec *v, usize stride) {
	if (v->len + stride > v->cap) {
		vec_reserve(v, v->len + stride);
	}
	usize oldlen = v->len;
	v->len += stride;
	return (u8*)v->buf + oldlen;
}

inline void *vec_pop(Vec *v, usize stride) {
	assert(v->buf != NULL);
	assert(v->len != 0);
	v->len -= stride;
	return (u8*)v->buf + v->len;
}

inline void *vec_insert(Vec *v, usize stride, usize index) {
	void *ptr = vec_index(v, stride, index);
	memcpy(vec_push(v, stride), ptr, stride);
	return ptr;
}

inline void vec_remove(Vec *v, usize stride, usize index) {
	memcpy(vec_index(v, stride, index), vec_index(v, stride, vec_len(v, stride) - 1), stride);
	vec_pop(v, stride);
}

