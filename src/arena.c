
#include "../arena.h"

#include "stdlib.h"


OciArena oci_arena_new(OciAllocator *alloc, usize size) {
	void *buf = oci_malloc(alloc, size);
	void *end = (u8*)buf + size;
	return (OciArena) {
		.buf = buf,
		.end = end,
		.ptr = buf,
		.alloc = alloc,
	};
}

void oci_arena_free(OciArena *arena) {
	oci_free(arena->alloc, arena->buf, (usize)arena->end - (usize)arena->ptr);
	arena->buf = NULL;
}

void *oci_arena_alloc(OciArena *arena, usize size) {
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
	OciArena *arena = (OciArena*)data;
	return oci_arena_alloc(arena, new);
}

OciAllocator oci_arena_allocator(OciArena *arena) {
	return (OciAllocator) {
		.alloc = inner_arena_alloc,
		.data = arena,
	};
}
