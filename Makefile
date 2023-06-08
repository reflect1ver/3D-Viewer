CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra -g
SOURCES= matrix.c parser.c alpines.c 
OBJECTS=$(SOURCES:.c=.o)
OS = $(shell uname)
TEST_FILE_NAME = tests_viewer.c

ifeq ($(OS), Darwin)
	TEST_LIBS=-lcheck
else
	TEST_LIBS=-lcheck -lsubunit -pthread -lrt -lm
endif

all: gcov_report install

install:  uninstall  compile
	mkdir build
	cd build && cmake build ../3D-Viewer
	make -C ./build
	open ./build/3D-Viewer.app/Contents/MacOs/3D-Viewer

uninstall:
	rm -rf build/
	rm -rf 3D-Viewer.tar
	rm -rf $(OBJECTS)

compile:
	$(CC) -c -o matrix.o matrix.c
	$(CC) -c -o parser.o parser.c
	$(CC) -c -o alpines.o alpines.c

dist:
	tar -cf ./3D-Viewer.tar ./build/3D-Viewer.app/Contents/MacOs/3D-Viewer

3D-Viewer.a: clean $(OBJECTS)
	ar -rcs 3D-Viewer.a $(OBJECTS)

tests: $(TEST_FILE_NAME) 3D-Viewer.a
	$(CC) $(CFLAGS) $(TEST_FILE_NAME) $(SOURCES) -o test $(TEST_LIBS) -L. --coverage
	./test

gcov_report: tests
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

dvi:
	open ReadMe.md

clean:
	make uninstall
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css test report *.txt test.info test.dSYM *.tar