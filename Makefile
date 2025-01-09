# Variables
PREFIX?=/usr/local
TARGET=mylibrary

SRC_DIR = src
BUILD_DIR = build
TEST_DIR = tests
LIBRARY = $(BUILD_DIR)/lib$(TARGET).a
CC = gcc
CFLAGS = -Wall -g -O2
AR = ar
ARFLAGS = rcs
RM = rm -rf

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
TEST_EXE = $(addprefix $(BUILD_DIR)/, $(basename $(TEST_SRC:.c=.out)))

# Default target: Compile all source files and create static library
default: $(LIBRARY)

# Create the static library by compiling .c to .o and then archiving
$(LIBRARY): $(OBJS)
	$(AR) $(ARFLAGS) $(LIBRARY) $(OBJS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile each .c file in src/ to its respective .o in build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Install the static library (copy to /usr/local/lib or custom location)
install:
	cp $(LIBRARY) $(PREFIX)/lib
	mkdir -p $(PREFIX)/include/$(TARGET)
	cp $(SRC_DIR)/*.h $(PREFIX)/include/$(TARGET)

# Phony target to always rebuild and run the tests
.PHONY: test

# Rule to clean up previous test executables
clean_tests:
	rm -f $(TEST_EXE)
	
test: clean_tests $(LIBRARY) $(TEST_DIR) $(TEST_EXE)

$(BUILD_DIR)/$(TEST_DIR): 
	mkdir -p $(BUILD_DIR)/$(TEST_DIR)

# Rule to build and run each test
$(BUILD_DIR)/$(TEST_DIR)/%: $(TEST_DIR)/%.c | $(BUILD_DIR)/$(TEST_DIR)
	$(CC) $(CFLAGS) $< $(LIBRARY) -o $@ && ./$@

# Clean build files (object files, static library, test executables)
clean:
	$(RM) $(BUILD_DIR)

# Uninstall the static library and header files
uninstall:
	$(RM) $(PREFIX)/lib/lib$(TARGET).a $(PREFIX)/include/$(TARGET)

