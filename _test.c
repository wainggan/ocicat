
#include "alloc.h"
#include "arena.h"
#include "vec.h"
#include "str.h"

#include "stdio.h"

usize __okay = 0;
usize __confirm() {
	if (__okay == 0) {
		printf("all tests passed! :3\n");
	} else {
		printf("%zu tests failed.\n", __okay);
	}
	return __okay;
}

#define __QUALIFY(type) _Generic((type), void*: "%p", i32: "%i", u32: "%ui", usize: "%zu")

#define assert(expr, msg) \
	if (!(expr)) { \
		__okay += 1; printf("failed @ %s:%i ~ %s\n", (char*)__func__, __LINE__, msg); \
	} else { \
		printf("success @ %s:%i!\n", (char*)__func__, __LINE__); \
	}

#define assert_eq(left, right, msg) \
	if ((left) != (right)) { \
		__okay += 1; \
		printf("failed -- "); \
		printf(__QUALIFY(left), (left));\
		printf(" != "); \
		printf(__QUALIFY(right), (right)); \
		printf(" @ %s:%i ~ %s\n", (char*)__func__, __LINE__, msg); \
	} else { \
		printf("success @ %s:%i!\n", (char*)__func__, __LINE__); \
	}



void test_vec() {

	oci_allocator alloc = oci_cstd_allocator();

	v_vec(int) vec = v_new(typeof(vec), &alloc);

	assert_eq(v_cap(&vec), 0, "new vec, capacity != 0");
	assert_eq(v_len(&vec), 0, "new vec, length != 0");

	*v_push(&vec) = 10;
	
	assert(v_cap(&vec) > 0, "vec after push, capacity should be more than 0");
	assert_eq(v_len(&vec), 1, "vec after push, length should be 1");

	*v_push(&vec) = 20;

	assert_eq(v_len(&vec), 2, "vec after push, length should be 1");

	*v_push(&vec) = 30;
	*v_push(&vec) = 40;

	assert(v_cap(&vec) >= 4, "vec after 4 pushes, capacity should be more than 4");
	assert_eq(v_len(&vec), 4, "vec after 4 pushes, length should be 4");

	assert_eq(*v_index(&vec, 0), 10, "vec after 4 pushes, 0th element should be `10`");
	assert_eq(*v_index(&vec, 1), 20, "vec after 4 pushes, 0th element should be `20`");
	assert_eq(*v_index(&vec, 2), 30, "vec after 4 pushes, 0th element should be `30`");
	assert_eq(*v_index(&vec, 3), 40, "vec after 4 pushes, 0th element should be `40`");

	assert_eq(*v_pop(&vec), 40, "vec after 4 pushes, 1st pop should be `40`");
	assert_eq(*v_pop(&vec), 30, "vec after 4 pushes, 2nd pop should be `30`");
	assert_eq(*v_pop(&vec), 20, "vec after 4 pushes, 3rd pop should be `20`");
	assert_eq(*v_pop(&vec), 10, "vec after 4 pushes, 4th pop should be `10`");

}

void test_str() {

	char *whitespacechars = " \t\n  hello  \n\t ";
	str whitespace = str_c(whitespacechars);

	assert_eq((void*)str_ptr(whitespace), (void*)whitespacechars, "str_ptr broken");
	assert_eq(str_len(whitespace), 15, "str_len length broken");

	assert(str_eq(whitespace, str_c(" \t\n  hello  \n\t ")), "str_eq failure");
	
	str lefttrim = str_trim_start(whitespace);
	assert(str_eq(lefttrim, str_c("hello  \n\t ")), "trim_start failure");

	str endtrim = str_trim_end(whitespace);
	assert(str_eq(endtrim, str_c(" \t\n  hello")), "trim_end failure");

	str fulltrim = str_trim(whitespace);
	assert(str_eq(fulltrim, str_c("hello")), "trim failure");
	assert_eq(str_len(fulltrim), 5, "str_len on trim out failed");


	str splitter = str_c("leftright");
	str a;
	str b;
	str_split(splitter, 4, &a, &b);
	assert(str_eq(a, str_c("left")), "split failed: left");
	assert(str_eq(b, str_c("right")), "split failed: right");

	str unsafe = str_from(whitespacechars + 5, 5);
	assert(str_eq(unsafe, str_c("hello")), "split failed: left");

}

void test_string() {

}



int main(void) {

	test_vec();
	test_str();
	test_string();
	
	return __confirm();
}

