CC = gcc
CFLAGS = -Iinclude -Wall -Wextra

# core modules
CORE = src/core/ring_buffer.c

# test target
TEST_SRC = $(CORE) test/test_ring_buffer.c
TEST_OUT = test_rb

.PHONY: all test run app clean

# default target
all: test

# build test executable
test: $(TEST_OUT)

$(TEST_OUT): $(TEST_SRC)
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_OUT)

# run test
run: test
	./$(TEST_OUT)

# clean build files
clean:
	rm -f $(TEST_OUT)