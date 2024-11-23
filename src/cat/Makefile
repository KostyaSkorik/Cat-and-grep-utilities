GCC=gcc -std=c11 -Wall -Werror -Wextra

all: s21_cat 

s21_cat: main.c cat.c
	$(GCC) $^ -o s21_cat 


clean:
	rm -f s21_cat *.out

rebuild: clean s21_grep
