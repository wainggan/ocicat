#ifndef OCI_ALLOC_H
#define OCI_ALLOC_H

#include "type.h"

typedef void *(OciAlloc)(void *data, void *ptr, usize old, usize new);

typedef struct OciAllocator {
	OciAlloc *alloc;
	void *data;
} OciAllocator;

void *oci_malloc(OciAllocator *alloc, usize size);
void *oci_realloc(OciAllocator *alloc, void* ptr, usize old, usize new);
void oci_free(OciAllocator *alloc, void* ptr, usize old);

OciAllocator oci_cstd_allocator();


#endif
