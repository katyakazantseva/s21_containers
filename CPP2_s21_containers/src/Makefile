.PHONY: all test gcov_report style clean docker install_lcov leaks
TEST_FLAGS= -lgtest_main -pthread -lgtest
GCC= gcc -lstdc++ -Wall -Wextra -Werror -std=c++17 -pedantic
GCO= --coverage
VECTOR=vector/*.cc
STACK=stack/*.cc
LIST= list/*.cc
QUEUE=queue/*.cc
MAP=map/*.cc
SET=set/*.cc
ARRAY=array/*.cc
MULTISET=multiset/*.cc

FUNC_SRC := $(wildcard */*.h && */*.cc)

RM_RULE= rm -rf main test *.dSYM report_f res *.info *.gcda *.gcno report ./list/debug ./list/debug.asbdfn leak.txt

UNAME := $(shell uname)

FILES= $(wildcard *.cc)
OBJ=$(patsubst %.cc,%.o,${FILES})

all: clean gcov_report

test:
	$(GCC) $(TEST_FLAGS) -g -o test $(VECTOR) $(STACK) $(QUEUE) $(LIST) $(SET) $(MAP) $(ARRAY) $(MULTISET)
	./test

clean: style
	$(RM_RULE)
	cd queue && $(RM_RULE)
	cd array && $(RM_RULE)
	cd list && $(RM_RULE)
	cd vector && $(RM_RULE)
	cd stack && $(RM_RULE)
	cd map && $(RM_RULE)
	cd set && $(RM_RULE)
	cd multiset && $(RM_RULE)
	cd avl_tree && $(RM_RULE)
	clear

gcov_report: clean
	$(GCC) $(TEST_FLAGS) $(GCO) -o report_f $(VECTOR) $(STACK) $(QUEUE) $(LIST) $(SET) $(MAP) $(ARRAY) $(MULTISET)
	./report_f
	@mkdir ./report
	@mv *.g* ./report
	@lcov --ignore-errors mismatch -c -q -d ./report -o ./report/coverage.info
	@genhtml -q ./report/coverage.info -o ./report
	@open report/index.html

docker:
	docker build -t my_image .
	docker run -d -p 80:80 --name my_container my_image bash -c "cd /TEST_VALGRIND && make test && valgrind ./test"
	docker logs -f my_container
	docker stop my_container
	docker rm my_container
	docker rmi my_image

style:
	@cp ../materials/linters/.clang-format .
	clang-format -n $(FUNC_SRC) s21_containers.h
	@rm -rf .clang-format

install_lcov:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

leaks: clean test
	@-leaks -atExit -- ./test > ./leak.txt
	@-grep -A 2 "leaks Report Version" ./leak.txt
