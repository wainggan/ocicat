
#include "../alloc.h"

#include "stdlib.h"


inline void *oci_malloc(oci_allocator *alloc, usize size) {
	return alloc->alloc(alloc->data, NULL, 0, size);
}

inline void *oci_realloc(oci_allocator *alloc, void* ptr, usize old, usize new) {
	return alloc->alloc(alloc->data, ptr, old, new);
}

inline void oci_free(oci_allocator *alloc, void *ptr, usize old) {
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

oci_allocator oci_cstd_allocator() {
	return (oci_allocator) {
		.alloc = inner_cstd_alloc,
		.data = NULL,
	};
}

