OS := $(shell uname)

ifeq ($(OS),Linux)
#TEST_LIBS = -lcheck -lm -lpthread -lrt -lsubunit -fprofile-arcs -ftest-coverage
OPA = xdg-open
PLAY = ./sc_qmake
else
#TEST_LIBS = -lcheck -lm -lpthread -fprofile-arcs -ftest-coverage
PLAY = open sc_qmake.app
OPA = open
endif

CC=gcc
CFLAGS= -Wall -Wextra -Werror -std=c11
main=sc/
SRC_C= smartcalc.c smartcalc.h sortir.c validator_2.c reshala.c token.c
PAT=../build/
DIST=../dist/
TEST=$(SRC_C) test.c

all : dvi s21_smartcalc

s21_smartcalc:
	make install && make openapp

openapp :
	cd build/opt/sc_qmake/bin/ && $(PLAY)

install :
	mkdir build
	cd sc/ && qmake -o Makefile "sc_qmake.pro" && make install INSTALL_ROOT=$(PAT)

uninstall:
	cd sc/ && make uninstall INSTALL_ROOT=$(PAT)
	rm -rf build

test:
	cd sc/ && $(CC) $(CFLAGS) $(TEST) -l check -lm -o s21_test && ./s21_test
clean:
	rm -rf dist
	cd sc/ && make clean
	cd sc/ && rm -rf *.gcda *.gcno s21_test sc_qmake
	rm -rf *.o
	rm -rf *.info
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.gcov
	rm -rf report
	rm -rf s21_test
	rm -rf sc.tgz

style:
	clang-format -style=Google -n sc/*.c
	clang-format -style=Google -n sc/*.h
	clang-format -style=Google -n sc/*.cpp

install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

install_qmake:
	brew install qt

dvi:
	$(OPA) README.md

gcov_report: clean
	cd sc/ && gcc -fprofile-arcs -ftest-coverage $(TEST) -o s21_test -l check -lm
	cd sc/ && ./s21_test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report/ test.info
	$(OPA) ./report/index.html

rebuild: clean uninstall s21_smartcalc

dist: clean
	mkdir dist
	chmod 777 dist
	cd sc && qmake -o Makefile "sc_qmake.pro" && make install INSTALL_ROOT=$(DIST)
	tar -czf sc.tgz dist