# Write a Makefile for this project.
# The Makefile should have the following targets:
# all (default) - builds the project
# clean - removes all generated files
# run - runs the project
# test - runs the tests
# format - formats the code
# check - checks for formatting issues

CC = g++
CFLAGS = -Wall -Werror -std=c++20 -g
GTEST_LIBS = -lgtest -lgtest_main -pthread

all: tests
tests: test_angle

test_angle: tests/angle.cpp include/maths/angle.hpp
	$(CC) $(CFLAGS) -o test_angle tests/angle.cpp ${GTEST_LIBS}

clean:
	rm -f main main.o test_angle