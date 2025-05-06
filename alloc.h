#ifndef OCI_ALLOC_H
#define OCI_ALLOC_H

#include "type.h"

typedef void *(oci_allocfn)(void *data, void *ptr, usize old, usize new);

typedef struct oci_allocator {
	oci_allocfn *alloc;
	void *data;
} oci_allocator;

void *oci_malloc(oci_allocator *alloc, usize size);
void *oci_realloc(oci_allocator *alloc, void* ptr, usize old, usize new);
void oci_free(oci_allocator *alloc, void* ptr, usize old);

oci_allocator oci_cstd_allocator();


#endif
