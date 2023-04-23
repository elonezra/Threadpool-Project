.PHONY: all
all: task stdinExample

task:	codec.h basic_main.c
	gcc basic_main.c -L. -l Codec -o encoder -Wl,-rpath

stdinExample:	stdin_main.c
	gcc stdin_main.c -L.  -l Codec -o tester -Wl,-rpath

.PHONY: clean
clean:
	-rm encoder tester 2>/dev/null
