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

SRC_FILES := $(wildcard $(SRC_DIR)/**/**/*cpp $(SRC_DIR)/**/*cpp $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
TEST_FILES := $(patsubst $(TEST_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE_DIR)/%.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(OBJ_FILES)

check: 
	@echo $(SRC_FILES)
	@echo $(OBJ_FILES)



$(TEST_OUT)/test_angle: $(TEST_DIR)/test_angle.cpp $(BUILD_DIR)/maths/angle.o
	$(CC) $(CFLAGS) -o $@ $(TEST_DIR)/test_angle.cpp $(BUILD_DIR)/maths/angle.o ${GTEST_LIBS}

$(TEST_OUT)/test_complex: $(TEST_DIR)/test_complex.cpp $(BUILD_DIR)/maths/complex.o
	$(CC) $(CFLAGS) -o $@ $(TEST_DIR)/test_complex.cpp $(BUILD_DIR)/maths/complex.o ${GTEST_LIBS}

$(TEST_OUT)/physics_units: $(TEST_DIR)/test_physics_units.cpp $(INCLUDE_DIR)/physics/physics_units.hpp
	$(CC) $(CFLAGS) -o $@ $(TEST_DIR)/test_physics_units.cpp  ${GTEST_LIBS}

$(TEST_OUT)/physics_quantity: $(TEST_DIR)/test_physics_quantity.cpp $(INCLUDE_DIR)/physics/physics_quantity.hpp
	$(CC) $(CFLAGS) -o $@ $(TEST_DIR)/test_physics_quantity.cpp ${GTEST_LIBS}


tests_run: tests/*
	# ./${TEST_OUT}/test_angle
	./${TEST_OUT}/test_complex

clean:
	rm -f main main.o test_angle