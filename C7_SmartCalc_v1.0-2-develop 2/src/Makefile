CC=gcc
#CFLAGS=-Wall -Werror -Wextra -std=c11
CFLAGS=-Wall -Werror -Wextra -g -std=c11
GCOVFLAGS = --coverage
LIBS=-lcheck
#TEST_LIBS = -lcheck -lm -lpthread
OS = $(shell uname)
#TEST_FILE_NAME = test.c

ifeq ($(OS), Darwin)
	TEST_LIBS = -lcheck -lm -lpthread
else
	TEST_LIBS=-lcheck -lsubunit -pthread -lrt -lm
endif
TEST_FUNC = 1.c sort.c calculation.c credits.c deposid.c
all: clean s21_calc.a #gcov_report

s21_calc.a:

	$(CC) $(CFLAGS) -c $(TEST_FUNC)
	ar rc s21_calc.a *.o
	ranlib s21_calc.a

test: s21_calc.a
	$(CC) $(CFLAGS) -c -g test.c -o test_calc.o 
	$(CC) test_calc.o s21_calc.a $(TEST_LIBS) -o s21_calc
	./s21_calc

gcov_report: test
	$(CC) $(CFLAGS) $(GCOVFLAGS) credits.c deposid.c test.c 1.c sort.c calculation.c s21_calc.a $(TEST_LIBS) -o gcov_test
	rm -rf u*.gcno
	rm -rf u*.gcda
	rm -rf u*.gcov
	chmod +x *
	./gcov_test
	gcov s21_*.gcda
	rm -rf u*.gcda
	gcovr -b
	gcovr
	gcovr --html-details -o report.html
	lcov -t "test_calc"  -o report.info -c -d .
	genhtml -o report report.info
	open ./report/index.html

clean:
	rm -rf s21_calc
	rm -rf *.o
	rm -rf *.a
	rm -rf *.gcno
	rm -rf *.gcda
	rm -rf *.gcov
	rm -rf *.info
	rm -rf *.html
	rm -rf *.css
	rm -rf test
	rm -rf gcov_test
	rm -rf *.dSYM
	rm -rf RESULT_VALGRIND.txt
	rm -rf report
style:
	clang-format -style=google -n *.c
	clang-format -style=google -n *.h
style_i:
	clang-format -style=google -i *.c
	clang-format -style=google -i *.h
valgrind: s21_calc.a
	CK=FORK=no valgrind --trace-children=yes --track-origins=yes --show-leak-kinds=all --verbose --log-file=RESULT_VALGRIND.txt ./s21_calc
lik: s21_calc.a
	CK_FORK=no leaks -atExit -- ./s21_calc
rebuild: clean all
install:
	mkdir build
	cd untitled && qmake && make && make clean && mv untitled.app ../build/SmartCalc.app && rm -rf untitled.app
unistall:
	rm -rf build
open:
	cd build && open SmartCalc.app
dist:
	rm -rf Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/src
	mv ./build/SmartCalc.app Archive_SmartCalc_v1.0/src/
	tar cvzf Archive_SmartCalc_v1.0.tgz Archive_SmartCalc_v1.0/
	rm -rf Archive_SmartCalc_v1.0/


dvi: description.md
ifeq ($(OS), Darwin)
	open description.md
else
	cat description.md
endif

