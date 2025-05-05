CC="zig cc"
FILES="_test.c src/*"
if [ ! -d "bin" ]; then
	mkdir bin
fi
$CC -std=c23 -Wall -Wextra -Werror -pedantic -fsanitize=undefined -o bin/test $FILES && ./bin/test
