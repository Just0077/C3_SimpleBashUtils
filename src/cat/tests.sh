#!/bin/bash

# -b Конкатенация файлов с нумерацией строк
./s21_cat -b text.txt > s21_cat.txt
cat -b text.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

# -e конец строки
./s21_cat -e text.txt > s21_cat.txt
cat -e text.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

# Флаг "n" - выводить номера строк
./s21_cat -n text.txt > s21_cat.txt
cat -n text.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

# Флаг "s" - сжимает несколько смежных пустых строк 
./s21_cat -s text.txt > s21_cat.txt
cat -s text.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

# Флаг "t" - выводить символы табуляции в виде "^I"
./s21_cat -t text.txt > s21_cat.txt
cat -t text.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

# Флаг "v" - выводить непечатные символы
./s21_cat -v text.txt > s21_cat.txt
cat -v text.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

# Флаг "b" - выводить нумерацию только для непустых строк
./s21_cat -b text.txt > s21_cat.txt
cat -b text.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

# -e конец строки
./s21_cat -e text.txt text2.txt > s21_cat.txt
cat -e text.txt text2.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

# Флаг "n" - выводить номера строк
./s21_cat -n text.txt text2.txt > s21_cat.txt
cat -n text.txt text2.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

# Флаг "s" - сжимает несколько смежных пустых строк
./s21_cat -s text.txt text2.txt > s21_cat.txt
cat -s text.txt text2.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

# Флаг "t" - выводить символы табуляции в виде "^I"
./s21_cat -t text.txt text2.txt > s21_cat.txt
cat -t text.txt text2.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

# Флаг "v" - выводить непечатные символы
./s21_cat -v text.txt text2.txt > s21_cat.txt
cat -v text.txt text2.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

# Нет файла
./s21_cat -b nofile.txt > s21_cat.txt
cat -b nofile.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

# Тест: Конкатенация файлов с номерами строк и подавлением пустых строк (-b, -s)
./s21_cat -b -s text.txt > s21_cat.txt
cat -b -s text.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

# Тест: Вывод номеров строк и символов табуляции (-n, -t)
./s21_cat -n -t text.txt > s21_cat.txt
cat -n -t text.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

# Тест: Вывод номеров строк и непечатных символов (-n, -v)
./s21_cat -n -v text.txt > s21_cat.txt
cat -n -v text.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

# Тест: Поиск текста, вывод номеров строк и символов табуляции (-e, -n, -t)
./s21_cat -e -n -t text.txt > s21_cat.txt
cat -e -n -t text.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

# Тест: Поиск текста, подавление пустых строк и вывод непечатных символов (-e, -s, -v)
./s21_cat -e -s -v text.txt > s21_cat.txt
cat -e -s -v text.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

# Тест: Поиск текста, вывод номеров строк и подавление вывода пустых строк (-e, -n, -s)
./s21_cat -e -n -s text.txt > s21_cat.txt
cat -e -n -s text.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt