#!/bin/bash

# -e txt
./s21_grep -e txt tests.sh > s21_grep_e.txt
grep -e txt tests.sh > grep_e.txt
diff -s s21_grep_e.txt grep_e.txt
rm s21_grep_e.txt grep_e.txt

# -i case-insensitive 
./s21_grep -i txt tests.sh > s21_grep_i.txt
grep -i txt tests.sh > grep_i.txt
diff -s s21_grep_i.txt grep_i.txt
rm s21_grep_i.txt grep_i.txt

# -v inverse
./s21_grep -v txt tests.sh > s21_grep_v.txt
grep -v txt tests.sh > grep_v.txt
diff -s s21_grep_v.txt grep_v.txt
rm s21_grep_v.txt grep_v.txt

# -c count lines
./s21_grep -c txt tests.sh > s21_grep_c.txt
grep -c txt tests.sh > grep_c.txt
diff -s s21_grep_c.txt grep_c.txt
rm s21_grep_c.txt grep_c.txt

# -l list files
./s21_grep -l txt tests.sh > s21_grep_l.txt
grep -l txt tests.sh > grep_l.txt
diff -s s21_grep_l.txt grep_l.txt
rm s21_grep_l.txt grep_l.txt

# -n line numbers
./s21_grep -n txt tests.sh > s21_grep_n.txt
grep -n txt tests.sh > grep_n.txt
diff -s s21_grep_n.txt grep_n.txt
rm s21_grep_n.txt grep_n.txt

# -h hides files
./s21_grep -h txt tests.sh > s21_grep_h.txt
grep -h txt tests.sh > grep_h.txt
diff -s s21_grep_h.txt grep_h.txt
rm s21_grep_h.txt grep_h.txt

# -s no error messages
./s21_grep -s txt tests.sh > s21_grep_s.txt
grep -s txt tests.sh > grep_s.txt
diff -s s21_grep_s.txt grep_s.txt
rm s21_grep_s.txt grep_s.txt

# -f get regular expression from file
./s21_grep -f file tests.sh > s21_grep_f.txt
grep -f file tests.sh > grep_f.txt
diff -s s21_grep_f.txt grep_f.txt
rm s21_grep_f.txt grep_f.txt

# -o only matching lines
./s21_grep -o txt tests.sh > s21_grep_o.txt
grep -o txt tests.sh > grep_o.txt
diff -s s21_grep_o.txt grep_o.txt
rm s21_grep_o.txt grep_o.txt

# -i -n
./s21_grep -i -n txt test_file.txt > s21_grep_i_n.txt
grep -in txt test_file.txt > grep_i_n.txt
diff -s s21_grep_i_n.txt grep_i_n.txt
rm s21_grep_i_n.txt grep_i_n.txt

# -v -c
./s21_grep -v -c txt test_file.txt > s21_grep_v_c.txt
grep -vc txt test_file.txt > grep_v_c.txt
diff -s s21_grep_v_c.txt grep_v_c.txt
rm s21_grep_v_c.txt grep_v_c.txt

# -i -v
./s21_grep -i -v txt test_file.txt > s21_grep_i_v.txt
grep -iv txt test_file.txt > grep_i_v.txt
diff -s s21_grep_i_v.txt grep_i_v.txt
rm s21_grep_i_v.txt grep_i_v.txt

# -l -e
./s21_grep -l -e txt test_file.txt > s21_grep_l_e.txt
grep -le txt test_file.txt > grep_l_e.txt
diff -s s21_grep_l_e.txt grep_l_e.txt
rm s21_grep_l_e.txt grep_l_e.txt

# -l -c
./s21_grep -l -c txt test_file.txt > s21_grep_l_c.txt
grep -lc txt test_file.txt > grep_l_c.txt
diff -s s21_grep_l_c.txt grep_l_c.txt
rm s21_grep_l_c.txt grep_l_c.txt

# TXT
# tXt