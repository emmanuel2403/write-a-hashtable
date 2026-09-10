CC = cc
CFLAGS = -Wall -Wextra -Wpedantic -g

SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

OBJECTS = $(BUILD_DIR)/hash_table.o \
          $(BUILD_DIR)/prime.o \
          $(BUILD_DIR)/test_hash_table.o

TARGET = $(BUILD_DIR)/test_hash_table

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) -lm

$(BUILD_DIR)/hash_table.o: $(SRC_DIR)/hash_table.c $(SRC_DIR)/hash_table.h
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $(SRC_DIR)/hash_table.c -o $@

$(BUILD_DIR)/prime.o: $(SRC_DIR)/prime.c $(SRC_DIR)/prime.h
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $(SRC_DIR)/prime.c -o $@

$(BUILD_DIR)/test_hash_table.o: $(TEST_DIR)/test_hash_table.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $(TEST_DIR)/test_hash_table.c -o $@

test: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: test clean