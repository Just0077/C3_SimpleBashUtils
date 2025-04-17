#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CountOfFiles 1024

typedef struct flags {
  int b, e, n, s, t, v;
} flags_t;

int flags_definition(int argc, char *argv[], flags_t *flags);
int read_file(char *argv[], flags_t *flags);

int main(int argc, char *argv[]) {
  int err = 1;
  flags_t flags = {
      .b = 0,
      .e = 0,
      .n = 0,
      .s = 0,
      .t = 0,
      .v = 0,
  };
  err = flags_definition(argc, argv, &flags);
  if (flags.b == 1) {
    flags.n = 0;
  }

  while (optind < argc) {
    err = read_file(argv, &flags);
    optind++;
  }
  return err;
}

int flags_definition(int argc, char *argv[], flags_t *flags) {
  int c;
  int ret = 0;
  int index = 0;
  static struct option options[] = {
      {"number-nonblank", 0, 0, 'b'},
      {"number", 0, 0, 'n'},
      {"squeeze-blank", 0, 0, 's'},
      {0, 0, 0, 0},
  };

  while ((c = getopt_long(argc, argv, "+bEnsTvet", options, &index)) != -1) {
    switch (c) {
      case 'b':
        flags->b = 1;
        break;

      case 'E':
        flags->e = 1;
        break;

      case 'n':
        flags->n = 1;
        break;

      case 's':
        flags->s = 1;
        break;

      case 'T':
        flags->t = 1;
        break;

      case 'v':
        flags->v = 1;
        break;

      case 'e': {
        flags->e = 1;
        flags->v = 1;
        break;
      }
      case 't':
        flags->t = 1;
        flags->v = 1;
        break;

      case '?':
        ret = -1;
        break;
    }
  }
  return ret;
}

int read_file(char *argv[], flags_t *flags) {
  FILE *file;
  int ret = 0;

  file = fopen(argv[optind], "r");

  if (file != NULL) {
    int str_count = 1;
    int empty_str_count = 0;
    int last_sym = '\n';

    while (1) {
      int cur_c = fgetc(file);
      if (cur_c == EOF) {
        break;
      }
      if (flags->s && cur_c == '\n' && last_sym == '\n') {
        empty_str_count++;
        if (empty_str_count > 1) {
          continue;
        }
      } else {
        empty_str_count = 0;
      }
      if (last_sym == '\n' && ((flags->b && cur_c != '\n') || flags->n)) {
        printf("%6d\t", str_count++);
      }
      if (flags->t && cur_c == '\t') {
        printf("^");
        cur_c = 'I';
      }
      if (flags->e && cur_c == '\n') {
        printf("$");
      }
      if (flags->v) {
        int flag = 0;

        if (!isascii(cur_c) && !isprint(cur_c)) {
          putchar('M');
          putchar('-');
          cur_c = toascii(cur_c);
        }
        if (iscntrl(cur_c) && cur_c != '\n' && cur_c != '\t') {
          putchar('^');
          putchar(cur_c == 127 ? '?' : cur_c + 64);
          last_sym = cur_c;
          flag = 1;
        }
        if (flag) continue;
      }
      printf("%c", cur_c);
      last_sym = cur_c;
    }
    fclose(file);
  } else {
    ret = -1;
  }
  return ret;
}