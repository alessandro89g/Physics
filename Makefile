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

BUILD_DIR = build

SRC_FILES := $(wildcard $(SRC_DIR)/**/**/*cpp $(SRC_DIR)/**/*cpp $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(OBJ_FILES)

check: 
	@echo $(SRC_FILES)
	@echo $(OBJ_FILES)


TEST_DIR = tests
TEST_OUT = build/tests
$(TEST_OUT)/test_angle: $(TEST_DIR)/test_angle.cpp $(BUILD_DIR)/maths/angle.o
	$(CC) $(CFLAGS) -o $@ $(TEST_DIR)/test_angle.cpp $(BUILD_DIR)/maths/angle.o ${GTEST_LIBS}


tests_run: tests/*
	./${TEST_OUT}/test_angle

clean:
	rm -f main main.o test_angle