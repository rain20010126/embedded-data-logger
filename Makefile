CC = gcc
CFLAGS = -Iinclude -Wall -Wextra 

# source files
CORE_SRC = src/core/ring_buffer.c src/core/logger.c 
SENSOR_SRC = src/sensor/temp_sensor.c
APP_SRC  = src/main.c
TEST_SRC = test/test_ring_buffer.c

# object files
CORE_OBJ = $(CORE_SRC:.c=.o)
SENSOR_OBJ = $(SENSOR_SRC:.c=.o)
APP_OBJ  = $(APP_SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

# output
APP  = app
TEST = test_rb

.PHONY: all run test run_test clean

all: $(APP)

$(APP): $(CORE_OBJ) $(SENSOR_OBJ) $(APP_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST): src/core/ring_buffer.o $(TEST_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

test: $(TEST)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(APP)
	./$(APP)

run_test: $(TEST)
	./$(TEST)

clean:
	rm -f $(APP) $(TEST) $(CORE_OBJ) $(APP_OBJ) $(TEST_OBJ)