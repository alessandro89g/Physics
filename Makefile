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
TEST_FILES := $(wildcard $(TEST_DIR)/**/**/*cpp $(TEST_DIR)/**/*cpp $(TEST_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
TEST_EXE += $(patsubst $(TEST_DIR)/test_%.cpp,$(BUILD_DIR)/tests/%,$(TEST_FILES))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE_DIR)/%.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(OBJ_FILES)

check: 
	@echo "SRC_FILES" $(SRC_FILES) '\n'
	@echo "OBJ_FILES" $(OBJ_FILES)'\n'
	@echo "TEST_FILES" $(TEST_FILES)'\n'
	@echo "TEST_EXE" $(TEST_EXE)'\n'


all_test: $(TEST_OUT)/angle $(TEST_OUT)/complex $(TEST_OUT)/physics_units $(TEST_OUT)/physics_quantity $(TEST_OUT)/physics_constants_quantities $(TEST_OUT)/numbers $(TEST_OUT)/lcm_gcd $(TEST_OUT)/fraction

$(TEST_OUT)/angle: $(TEST_DIR)/test_angle.cpp $(BUILD_DIR)/maths/angle.o
	$(CC) $(CFLAGS) -o $@ $(TEST_DIR)/test_angle.cpp $(BUILD_DIR)/maths/angle.o ${GTEST_LIBS}

$(TEST_OUT)/complex: $(TEST_DIR)/test_complex.cpp $(BUILD_DIR)/maths/complex.o
	$(CC) $(CFLAGS) -o $@ $(TEST_DIR)/test_complex.cpp $(BUILD_DIR)/maths/complex.o ${GTEST_LIBS}

$(TEST_OUT)/physics_units: $(TEST_DIR)/test_physics_units.cpp $(INCLUDE_DIR)/physics/physics_units.hpp
	$(CC) $(CFLAGS) -o $@ $(TEST_DIR)/test_physics_units.cpp  ${GTEST_LIBS}

$(TEST_OUT)/physics_quantity: $(TEST_DIR)/test_physics_quantity.cpp $(INCLUDE_DIR)/physics/physics_quantity.hpp $(BUILD_DIR)/maths/complex.o
	$(CC) $(CFLAGS) -o $@ $(TEST_DIR)/test_physics_quantity.cpp $(BUILD_DIR)/maths/complex.o ${GTEST_LIBS}

$(TEST_OUT)/physics_constants_quantities: $(TEST_DIR)/test_physics_constants_quantities.cpp $(INCLUDE_DIR)/physics/physics_constants_quantities.hpp $(INCLUDE_DIR)/physics/physics_units.hpp $(BUILD_DIR)/maths/complex.o
	$(CC) $(CFLAGS) -o $@ $(TEST_DIR)/test_physics_constants_quantities.cpp $(BUILD_DIR)/maths/complex.o ${GTEST_LIBS}

$(TEST_OUT)/number: $(TEST_DIR)/test_number.cpp $(INCLUDE_DIR)/maths/number.hpp $(BUILD_DIR)/maths/number.o
	$(CC) $(CFLAGS) -o $@ $(TEST_DIR)/test_number.cpp $(BUILD_DIR)/maths/number.o ${GTEST_LIBS}

$(TEST_OUT)/lcm_gcd: $(TEST_DIR)/test_lcm_gcd.cpp $(INCLUDE_DIR)/maths/lcm_gcd.hpp
	$(CC) $(CFLAGS) -o $@ $(TEST_DIR)/test_lcm_gcd.cpp $(BUILD_DIR)/maths/number.o ${GTEST_LIBS}

$(TEST_OUT)/fraction: $(TEST_DIR)/test_fraction.cpp $(INCLUDE_DIR)/maths/lcm_gcd.hpp $(BUILD_DIR)/maths/fraction.o $(BUILD_DIR)/maths/number.o
	$(CC) $(CFLAGS) -o $@ $(TEST_DIR)/test_fraction.cpp $(BUILD_DIR)/maths/fraction.o $(BUILD_DIR)/maths/number.o ${GTEST_LIBS}

clean:
	rm -if $(OBJ_FILES) $(TEST_EXE)