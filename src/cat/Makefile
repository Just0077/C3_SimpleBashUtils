.PHONY: all s21_cat test clean rebuild
CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: s21_cat

s21_cat: 
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat

test: 
	sh tests.sh

clean:
	rm -f s21_cat

rebuild: clean all