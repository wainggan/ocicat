#ifndef OCI_VEC_H
#define OCI_VEC_H

#include "type.h"
#include "alloc.h"


/*
general purpose vector struct.
this implementation has 4 fields:

- a `void*` to a buffer.
- a `size_t` representing the size of the buffer's allocation in bytes.
- a `size_t` representing the 'length' of the vector in bytes.
- a `oci_allocator*`.

on 64bit machines, this takes 32 bytes. on 32bit machines, it is 16 bytes.
also, please use the `vec_ptr()`, `vec_cap()`, and `vec_len()` for accessing these fields.

vectors should be created using `vec_new()`, then freed with `vec_free()`.

there are also type safe macros of all available functions, such as `v_vec()` for defining a type, `v_new()` for creating a vector, etc.
*/
typedef struct vector {
	void *buf;
	// capacity in bytes
	usize cap;
	// length in bytes
	usize len;
	// associated allocator
	oci_allocator *alloc;
} vector;

/*
creates a new vector using the supplied allocator `alloc`.
no allocation will actually be performed until required, such as for calling `vec_reserve()` or `vec_push()`.

the vector can later be freed using `vec_free()`. you must ensure that `alloc` is still valid until at least this point.
*/
vector vec_new(oci_allocator *alloc);
/*
deallocates any memory a vector might have allocated. 
*/
void vec_free(vector *v);

/*
attempts to (re)allocate such that the vector's capacity is at least `capacity` (in bytes).
if `capacity <= vec_cap(&v, 1)`, this means it may do nothing at all.
*/
void vec_reserve_exact(vector *v, usize capacity);
/*
attempts to (re)allocate such that the vector's capacity is at least `capacity` (in bytes).
this works like `vec_reserve_exact()`, except it may speculatively allocate more memory than requested.
*/
void vec_reserve(vector *v, usize capacity);

// gets a pointer to the vector's allocated memory.
void *vec_ptr(const vector *v);
// gets the vector's allocated capacity.
usize vec_cap(const vector *v, usize stride);
// gets the vector's length.
usize vec_len(const vector *v, usize stride);
/*
sets the vector's length.
UB: this length should never "contain" possibly uninitialized data.
*/
void vec_len_set(vector *v, usize stride, usize len);

/*
returns a pointer to an element of the vector.

UB: `index` must be a valid element, such that `index < vec_len(&v, stride)`.
*/
void *vec_index(const vector *v, usize stride, usize index); 

/*
increments the length of the vector to accomodate for a new element, then returns the pointer to that new space.

UB: you must set this element to valid data.
*/
void *vec_push(vector *v, usize stride);
/*
decrements the length of the vector to accomodate for a new element, then returns the pointer to the old element.
this pointer should be used as soon as possible. `NULL` is returned if `vec_len(&v, stride) == 0`.
*/
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
