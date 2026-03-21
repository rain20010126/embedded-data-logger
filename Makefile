CC = gcc
CFLAGS = -Iinclude -Wall -Wextra 

CORE = src/core/ring_buffer.c src/core/logger.c

# main app
APP = app
APP_SRC = $(CORE) src/main.c

# test
TEST = test_rb
TEST_SRC = src/core/ring_buffer.c test/test_ring_buffer.c

.PHONY: all run run_app clean

# default = run app
all: $(APP)

# build app
$(APP):
	$(CC) $(CFLAGS) $(APP_SRC) -o $(APP)

# run app
run: $(APP)
	./$(APP)

# build test
test:
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST)

run_test: test
	./$(TEST)

clean:
	rm -f $(APP) $(TEST)