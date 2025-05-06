
#include "../arena.h"

#include "stdlib.h"


oci_arena oci_arena_new(oci_allocator *alloc, usize size) {
	void *buf = oci_malloc(alloc, size);
	void *end = (u8*)buf + size;
	return (oci_arena) {
		.buf = buf,
		.end = end,
		.ptr = buf,
		.alloc = alloc,
	};
}

void oci_arena_free(oci_arena *arena) {
	oci_free(arena->alloc, arena->buf, (usize)arena->end - (usize)arena->ptr);
	arena->buf = NULL;
}

void *oci_arena_alloc(oci_arena *arena, usize size) {
	const usize align = 0xf;
	usize aligned = ((usize)arena->ptr + align) & ~align;
	usize newptr = aligned + size;
	if (newptr >= (usize)arena->end) {
		return NULL;
	}
	arena->ptr = (void*)newptr;
	return (void*)aligned;
}

void *inner_arena_alloc(void *data, void *ptr, usize old, usize new) {
	(void)ptr;
	(void)old;
	if (new == 0) {
		return NULL;
	}
	oci_arena *arena = (oci_arena*)data;
	return oci_arena_alloc(arena, new);
}

oci_allocator oci_arena_allocator(oci_arena *arena) {
	return (oci_allocator) {
		.alloc = inner_arena_alloc,
		.data = arena,
	};
}
