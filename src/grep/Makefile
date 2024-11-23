GCC=gcc -std=c11 -Wall -Werror -Wextra

all: s21_grep 

s21_grep: main.c s21_grep.c
	$(GCC) $^ -o s21_grep 


clean:
	rm -f s21_grep *.out

rebuild: clean s21_grep

