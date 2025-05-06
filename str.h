#ifndef OCI_STR_H
#define OCI_STR_H

#include "type.h"
#include "vec.h"

// internal vector type
typedef v_vec(char) _vecstr;

// heap allocated, immutable string type.
// garanteed to be null terminated.
typedef struct oci_string {
	_vecstr vec;
} oci_string;

// string slice.
// may or may not be correctly null terminated.
typedef struct str {
	const char *ptr;
	usize len;
} str;


oci_string string_new(oci_allocator *alloc);
oci_string string_from(oci_allocator *alloc, str s);
void string_free(oci_string *string);

const char *string_ptr(const oci_string *string);
usize string_len(const oci_string *string);

void string_append(oci_string *string, str other);
oci_string string_concat(oci_allocator *alloc, str a, str b);

str str_from(const char *chr, usize len);
str str_c(const char *chr);
str str_s(const oci_string *string);
oci_string str_to_string(oci_allocator *alloc, str s);

const char *str_ptr(str s);
usize str_len(str s);

void str_split(str s, usize mid, str *out0, str *out1);

str str_trim_start(str s);
str str_trim_end(str s);
str str_trim(str s);

bool str_eq(str a, str b);


#endif
