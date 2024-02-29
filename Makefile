# Write a Makefile for this project.
# The Makefile should have the following targets:
# all (default) - builds the project
# clean - removes all generated files
# run - runs the project
# test - runs the tests
# format - formats the code
# check - checks for formatting issues


CC = g++
CFLAGS = -Wall -std=c++20 -g
GTEST_LIBS = -lgtest -lgtest_main -pthread

SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests
TEST_OUT = build/tests

BUILD_DIR = build

SRC_FILES := $(wildcard $(SRC_DIR)/**/**/*.cpp $(SRC_DIR)/**/*.cpp)
INCLUDE_FILES := $(wildcard $(INCLUDE_DIR)/**/**/*.hpp $(INCLUDE_DIR)/**/*.hpp)
TEST_FILES := $(wildcard $(TEST_DIR)/**/**/*cpp $(TEST_DIR)/**/*cpp $(TEST_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
TEST_EXE := $(patsubst $(TEST_DIR)/test_%.cpp,$(BUILD_DIR)/tests/%,$(TEST_FILES))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE_DIR)/%.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(OBJ_FILES)

$(TEST_OUT)/%: $(TEST_DIR)/test_%.cpp 
	$(CC) $(CFLAGS) -o $@ $< $(OBJ_FILES) ${GTEST_LIBS}
	@echo 

all_tests: $(TEST_EXE)

check: 
	@echo "INCLUDE_FILES" $(INCLUDE_FILES) '\n'
	@echo "SRC_FILES" $(SRC_FILES) '\n'
	@echo "OBJ_FILES" $(OBJ_FILES)'\n'
	@echo "TEST_FILES" $(TEST_FILES)'\n'
	@echo "TEST_EXE" $(TEST_EXE)'\n'


all_test: $(TEST_EXE)

run_all_tests: all_test
	@for test in $(TEST_EXE); do \
		$$test; \
	done

clean_tests:
	rm -f $(TEST_EXE)

clean:
	rm -f $(OBJ_FILES)