
#include "../str.h"

#include "string.h"

#include "assert.h"


inline oci_string string_new(oci_allocator *alloc) {
	oci_string string = {
		.vec = v_new(_vecstr, alloc),
	};
	return string;
}

oci_string string_from(oci_allocator *alloc, str s) {
	oci_string string = string_new(alloc);
	v_reserve_exact(&string.vec, s.len + 1);

	char *data = v_ptr(&string.vec);
	
	// copy str data to allocated space
	memcpy(data, s.ptr, s.len * sizeof(char));
	v_len_set(&string.vec, s.len);

	// null terminator
	data[s.len] = '\0';
	
	return string;
}

inline void string_free(oci_string *string) {
	assert(string != NULL);
	v_free(&string->vec);
}

inline const char *string_ptr(const oci_string *string) {
	assert(string != NULL);
	return v_ptr(&string->vec);
}
inline usize string_len(const oci_string *string) {
	assert(string != NULL);
	return v_len(&string->vec);
}

void string_append(oci_string *string, str other) {
	usize newlen = v_len(&string->vec) + other.len;

	v_reserve(&string->vec, newlen + 1);

	char *data = v_ptr(&string->vec);
	
	memcpy(data + v_len(&string->vec), other.ptr, other.len * sizeof(char));

	v_len_set(&string->vec, newlen);

	// null terminator
	data[newlen] = '\0';
}

oci_string string_concat(oci_allocator *alloc, str a, str b) {
	oci_string string = string_new(alloc);
	v_reserve_exact(&string.vec, a.len + b.len + 1);

	char *data = v_ptr(&string.vec);
	
	// copy str data to allocated space
	memcpy(data, a.ptr, a.len * sizeof(char));
	memcpy(data + a.len, b.ptr, b.len * sizeof(char));

	v_len_set(&string.vec, a.len + b.len);

	// null terminator
	data[a.len + b.len] = '\0';
	
	return string;
}

inline str str_from(const char *chr, usize len) {
	assert(chr != NULL);
	str s = {
		.ptr = chr,
		.len = len,
	};
	return s;
}

inline str str_c(const char *chr) {
	assert(chr != NULL);
	return str_from(chr, strlen(chr));
}

inline str str_s(const oci_string *string) {
	assert(string != NULL);
	return str_from(string_ptr(string), string_len(string));
}

inline oci_string str_to_string(oci_allocator *alloc, str s) {
	return string_from(alloc, s);
}

inline const char *str_ptr(str s) {
	return s.ptr;
}
inline usize str_len(str s) {
	return s.len;
}

inline void str_split(str s, usize mid, str *out0, str *out1) {
	assert(mid < s.len);
	*out0 = str_from(&s.ptr[0], mid);
	*out1 = str_from(&s.ptr[mid], s.len - mid);
}

bool is_space(char c) {
	return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

inline str str_trim_start(str s) {
	while (is_space(s.ptr[0])) {
		s.ptr += 1;
		s.len -= 1;
	}
	return s;
}

inline str str_trim_end(str s) {
	while (is_space(s.ptr[s.len - 1])) {
		s.len -= 1;
	}
	return s;
}

inline str str_trim(str s) {
	return str_trim_start(str_trim_end(s));
}

bool str_eq(str a, str b) {
	if (a.len != b.len) {
		return false;
	}
	for (usize i = 0; i < a.len; i++) {
		if (a.ptr[i] != b.ptr[i]) {
			return false;
		}
	}
	return true;
}

