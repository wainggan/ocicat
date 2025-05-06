
# ocicat

a tiny, general purpose modern-c library.

```c
oci_allocator libc_alloc = oci_cstd_allocator();

oci_arena arena = oci_arena_new(&libc_alloc, 2048);

oci_allocator arena_alloc = oci_arena_allocator(&arena);


v_vec(int) list = v_new(typeof(list), &arena_alloc);

*v_push(&list) = 10;
*v_push(&list) = 20;
*v_push(&list) = 30;

assert(v_len(&list) == 3);
assert(*v_index(&list, 1) == 20);


str s = str_c("  hello :3  ");
s = str_trim(s);

oci_string string = str_to_string(&arena_alloc, s);
string_append(&string, str_c("... yay"));

assert(str_eq(str_c("hello :3... yay"), str_s(&string)));


oci_arena_free(&arena); // `list` and `string` freed
```


