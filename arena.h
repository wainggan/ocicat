#ifndef OCI_ARENA_H
#define OCI_ARENA_H

#include "type.h"
#include "alloc.h"


typedef struct oci_arena {
	void *buf;
	void *end;
	void *ptr;
	oci_allocator *alloc;	
} oci_arena;

oci_arena oci_arena_new(oci_allocator *alloc, usize size);
void oci_arena_free(oci_arena *arena);
oci_allocator oci_arena_allocator(oci_arena *arena);

void *oci_arena_alloc(oci_arena *arena, usize size);


#endif
