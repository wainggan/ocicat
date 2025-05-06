#ifndef OCI_VEC_H
#define OCI_VEC_H

#include "type.h"
#include "alloc.h"


// vector struct
typedef struct vector {
	void *buf;
	// capacity in bytes
	usize cap;
	// length in bytes
	usize len;
	// associated allocator
	oci_allocator *alloc;
} vector;

// creates a new Vec. no allocation will be done until neccessary.
vector vec_new(oci_allocator *alloc);
// if the Vec allocated memory, that memory will be freed here.
void vec_free(vector *v);

// attempts to allocate such that the Vec's capacity is at least the size passed in.
void vec_reserve_exact(vector *v, usize capacity);
// like vec_reserve_exact(), except it may over-allocate.
void vec_reserve(vector *v, usize capacity);

// gets a pointer to the Vec's allocated memory.
void *vec_ptr(const vector *v);
// gets the Vec's allocated capacity.
usize vec_cap(const vector *v, usize stride);
// gets the Vec's length.
usize vec_len(const vector *v, usize stride);
// sets the Vec's length.
void vec_len_set(vector *v, usize stride, usize len);

void *vec_index(const vector *v, usize stride, usize index); 

void *vec_push(vector *v, usize stride);
void *vec_pop(vector *v, usize stride);

void *vec_insert(vector *v, usize stride, usize index);
void vec_remove(vector *v, usize stride, usize index);


#define v_vec(type) union { typeof(type) *T; vector _; }

#define OCI_VEC_TYPEOF(v) typeof(*(v)->T)
#define OCI_VEC_DATAOF(v) &(v)->_

#define v_new(t, a) (typeof(t)) { ._ = vec_new(a) }
#define v_free(v) vec_free(OCI_VEC_DATAOF(v))

#define v_as_vec(v) (OCI_VEC_DATAOF(v))

#define v_reserve(v, n) vec_reserve(OCI_VEC_DATAOF(v), n * sizeof(OCI_VEC_TYPEOF(v)))
#define v_reserve_exact(v, n) vec_reserve_exact(OCI_VEC_DATAOF(v), n * sizeof(OCI_VEC_TYPEOF(v)))

#define v_ptr(v) ((OCI_VEC_TYPEOF(v)*) vec_ptr (OCI_VEC_DATAOF(v)))
#define v_cap(v) vec_cap(OCI_VEC_DATAOF(v), sizeof(OCI_VEC_TYPEOF(v)))
#define v_len(v) vec_len(OCI_VEC_DATAOF(v), sizeof(OCI_VEC_TYPEOF(v)))
#define v_len_set(v, n) vec_len_set(OCI_VEC_DATAOF(v), sizeof(OCI_VEC_TYPEOF(v)), n)

#define v_index(v, i) ((OCI_VEC_TYPEOF(v)*) vec_index (OCI_VEC_DATAOF(v), sizeof(OCI_VEC_TYPEOF(v)), i))

#define v_push(v) ((OCI_VEC_TYPEOF(v)*) vec_push (OCI_VEC_DATAOF(v), sizeof(OCI_VEC_TYPEOF(v))))
#define v_pop(v) ((OCI_VEC_TYPEOF(v)*) vec_pop (OCI_VEC_DATAOF(v), sizeof(OCI_VEC_TYPEOF(v))))

#define v_insert(v, i) ((OCI_VEC_TYPEOF(v)*) vec_insert (OCI_VEC_DATAOF(v), sizeof(OCI_VEC_TYPEOF(v)), i))
#define v_remove(v, i) (vec_remove (OCI_VEC_DATAOF(v), sizeof(OCI_VEC_TYPEOF(v)), i))


#endif
