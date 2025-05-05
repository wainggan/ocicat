#ifndef OCI_STR_H
#define OCI_STR_H

#include "type.h"
#include "vec.h"

// internal vector type
typedef vec(char) VecStr;

// heap allocated, immutable string type.
// garanteed to be null terminated.
typedef struct String {
	VecStr vec;
} String;

// string slice.
// may or may not be correctly null terminated.
typedef struct str {
	const char *ptr;
	usize len;
} str;


String string_new(OciAllocator *alloc);
String string_from(OciAllocator *alloc, str s);
void string_free(String *string);

const char *string_ptr(const String *string);
usize string_len(const String *string);

void string_append(String *string, str other);
String string_concat(OciAllocator *alloc, str a, str b);

str str_from(const char *chr, usize len);
str str_c(const char *chr);
str str_s(const String *string);
String str_to_string(OciAllocator *alloc, str s);

const char *str_ptr(str s);
usize str_len(str s);

void str_split(str s, usize mid, str *out0, str *out1);

str str_trim_start(str s);
str str_trim_end(str s);
str str_trim(str s);

bool str_eq(str a, str b);


#endif
