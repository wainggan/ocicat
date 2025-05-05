
#include "../alloc.h"

#include "stdlib.h"


inline void *oci_malloc(OciAllocator *alloc, usize size) {
	return alloc->alloc(alloc->data, NULL, 0, size);
}

inline void *oci_realloc(OciAllocator *alloc, void* ptr, usize old, usize new) {
	return alloc->alloc(alloc->data, ptr, old, new);
}

inline void oci_free(OciAllocator *alloc, void *ptr, usize old) {
	alloc->alloc(alloc->data, ptr, old, 0);
}


static void *inner_cstd_alloc(void *data, void *ptr, usize old, usize new) {
	(void)data;
	(void)old;
	if (ptr == NULL) {
		return malloc(new);
	} else if (new == 0) {
		free(ptr);
		return NULL;
	} else {
		return realloc(ptr, new);
	}
}

OciAllocator oci_cstd_allocator() {
	return (OciAllocator) {
		.alloc = inner_cstd_alloc,
		.data = NULL,
	};
}

