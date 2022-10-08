test: test.c list.h
	gcc -o $@ $< -Wall -Og -g3 -fsanitize=address -march=native -fno-omit-frame-pointer -D_DEBUG
	echo "Test $@"
	./$@

fasttest: test.c list.h
	gcc -o $@ $< -Wall -O3 -march=native
	echo "Fast Test $@"
	./$@
