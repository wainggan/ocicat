#ifndef OCI_ARENA_H
#define OCI_ARENA_H

#include "type.h"
#include "alloc.h"


typedef struct OciArena {
	void *buf;
	void *end;
	void *ptr;
	OciAllocator *alloc;	
} OciArena;

OciArena oci_arena_new(OciAllocator *alloc, usize size);
void oci_arena_free(OciArena *arena);
OciAllocator oci_arena_allocator(OciArena *arena);

void *oci_arena_alloc(OciArena *arena, usize size);


#endif
