# Directories for source, test, and object files
SRC_DIR := ../src
INC_DIR := ../inc
TEST_DIR := ../test
TEST_SUPPORT_DIR := ../../test_support
OBJ_DIR := $(TEST_DIR)/obj
BIN_DIR := $(TEST_DIR)/bin
COVERAGE_DIR := $(TEST_DIR)/coverage

# Source files (application code)
SRC_FILES := $(SRC_DIR)/mu_thunk.c 

# Test files (unit tests)
TEST_FILES := $(TEST_DIR)/test_mu_thunk.c

# Test support files (Unity framework)
TEST_SUPPORT_FILES := $(TEST_SUPPORT_DIR)/unity.c

# Compiler and flags
CC := gcc
CFLAGS := -Wall -g
DEPFLAGS := -MMD -MP
GCOVFLAGS := -fprofile-arcs -ftest-coverage
LFLAGS := $(GCOVFLAGS)  # Add coverage flags also to linker

# Generate object files paths
SRC_OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_FILES))
TEST_SUPPORT_OBJS := $(patsubst $(TEST_SUPPORT_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_SUPPORT_FILES))

# Test executables
EXECUTABLES := $(patsubst $(TEST_DIR)/%.c, $(BIN_DIR)/%, $(TEST_FILES))

# Ensure object files are not deleted automatically by make
.SECONDARY: $(SRC_OBJS) $(TEST_OBJS) $(TEST_SUPPORT_OBJS)

.PHONY: all tests coverage clean

# Main target: Build all test executables
all: $(EXECUTABLES)
	@echo "make tests to run tests"
	@echo "make coverage to generate coverage info"
	@echo "make clean to clean generated files"

# Run all tests
tests: $(EXECUTABLES)
	@for test in $(EXECUTABLES); do \
		echo "Running $$test..."; \
		./$$test; \
	done

# Generate coverage report
coverage:
	$(MAKE) clean
	$(MAKE) all CFLAGS="$(CFLAGS) $(GCOVFLAGS)"
	@for test in $(EXECUTABLES); do \
		./$$test; \
	done
	lcov --capture --directory $(OBJ_DIR) --output-file coverage.info
	genhtml coverage.info --output-directory $(COVERAGE_DIR)
	@echo "Coverage report generated in $(COVERAGE_DIR)"

# Clean all generated files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(COVERAGE_DIR) coverage.info *.gcda *.gcno

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(DEPFLAGS) -c $< -o $@

# Compile test files to object files
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(TEST_SUPPORT_DIR) $(DEPFLAGS) -c $< -o $@

# Compile test support files to object files
$(OBJ_DIR)/%.o: $(TEST_SUPPORT_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(DEPFLAGS) -c $< -o $@

# Link object files to create test executables
$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(SRC_OBJS) $(TEST_SUPPORT_OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(LFLAGS) $^ -o $@

# Include generated dependency files
-include $(OBJ_DIR)/*.d
