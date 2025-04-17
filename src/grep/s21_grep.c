#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 4096

typedef struct _flags {
  int e, i, v, c, l, n, h, s, f, o;
  char **pattern;
  int patterns_counter;
} _flags;

void flags_definition(int argc, char *argv[], _flags *arguments);
void flags_announcement(int opt, _flags *arguments);
void grep(char *filename, int files_counter, _flags arguments);
regex_t *compile(_flags arguments);
int print(int reg, int line_number, char *line, int *counter, int files_counter,
          char *filename, _flags arguments, regex_t *regex, FILE *fp);
int count_files(int argc, char *argv[], _flags arguments);
void flag_o(regex_t *regex, char *word, FILE *fp, _flags arguments);
void flag_h(int files_counter, char *filename, _flags arguments);
void read_file(char *filename, _flags *arguments);
void clean(_flags arguments, regex_t *regex, FILE *fp);

int main(int argc, char *argv[]) {
  _flags arguments = {0};

  flags_definition(argc, argv, &arguments);

  int files_counter = count_files(argc, argv, arguments);

  if (arguments.e || arguments.f) {
    for (int j = optind; j < argc; j++) {
      grep(argv[j], files_counter, arguments);
    }

    for (int i = 0; i < arguments.patterns_counter; i++) {
      free(arguments.pattern[i]);
    }
    free(arguments.pattern);

  } else {
    arguments.pattern = malloc(sizeof(char *));
    arguments.pattern[0] = strdup(argv[optind]);
    arguments.patterns_counter = 1;
    for (int i = optind + 1; i < argc; i++) {
      grep(argv[i], files_counter, arguments);
    }

    free(arguments.pattern[0]);
    free(arguments.pattern);
  }

  return 0;
}

void flags_definition(int argc, char *argv[], _flags *arguments) {
  int opt;

  opterr = 0;
  while ((opt = getopt(argc, argv, "+e:ivclnhsf:o")) != -1) {
    flags_announcement(opt, arguments);
  }
}

void flags_announcement(int opt, _flags *arguments) {
  switch (opt) {
    case 'e':
      arguments->e = 1;
      arguments->pattern = realloc(
          arguments->pattern, ++arguments->patterns_counter * sizeof(char *));
      arguments->pattern[arguments->patterns_counter - 1] = strdup(optarg);
      break;
    case 'i':
      arguments->i = 1;
      break;
    case 'v':
      arguments->v = 1;
      break;
    case 'c':
      arguments->c = 1;
      break;
    case 'l':
      arguments->l = 1;
      break;
    case 'n':
      arguments->n = 1;
      break;
    case 'h':
      arguments->h = 1;
      break;
    case 's':
      arguments->s = 1;
      break;
    case 'f':
      arguments->f = 1;
      read_file(optarg, arguments);
      break;
    case 'o':
      arguments->o = 1;
      break;
    case '?':
      fprintf(stderr, "grep: illegal option -- %c\n", optopt);
      exit(1);
      break;
    default:
      fprintf(stderr, "Unexpected error\n");
      exit(1);
      break;
  }
}

void read_file(char *filename, _flags *arguments) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    !arguments->s
        ? fprintf(stderr, "grep: %s: No such file or directory\n", filename)
        : 0;
    exit(1);
  }

  char line[MAX_LINE_LENGTH];

  while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
    if (line[strlen(line) - 1] == '\n' && strlen(line) > 1) {
      line[strlen(line) - 1] = '\0';
    }
    arguments->pattern = realloc(
        arguments->pattern, ++arguments->patterns_counter * sizeof(char *));
    arguments->pattern[arguments->patterns_counter - 1] = strdup(line);
  }

  fclose(fp);
}

int count_files(int argc, char *argv[], _flags arguments) {
  int files_counter = 0;
  int flag = (arguments.f || arguments.e) ? 0 : 1;

  for (int i = optind + flag; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");
    if (fp != NULL) {
      fclose(fp);
      files_counter++;
    }
  }

  return files_counter;
}

void grep(char *filename, int files_counter, _flags arguments) {
  regex_t *regex = compile(arguments);

  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    if (!arguments.s) {
      fprintf(stderr, "grep: %s: No such file or directory\n", filename);
    }

    clean(arguments, regex, fp);
    return;
  }

  char line[MAX_LINE_LENGTH];
  int counter = 0, line_number = 1;

  while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
    int found_reg = 1;

    for (int i = 0; i < arguments.patterns_counter; i++) {
      if (!regexec(&regex[i], line, 0, NULL, 0)) {
        found_reg = 0;
        break;
      }
    }

    print(found_reg, line_number, line, &counter, files_counter, filename,
          arguments, regex, fp);
    ++line_number;
  }

  if (arguments.c) {
    flag_h(files_counter, filename, arguments);
    arguments.l ? printf("1\n") : printf("%d\n", counter);
  }

  if (arguments.l && counter > 0) {
    printf("%s\n", filename);
  }

  clean(arguments, regex, fp);
}

regex_t *compile(_flags arguments) {
  int flag_i = arguments.i ? REG_ICASE : 0;

  regex_t *reg_comp =
      (regex_t *)malloc(arguments.patterns_counter * sizeof(regex_t));

  for (int i = 0; i < arguments.patterns_counter; i++) {
    regcomp(&reg_comp[i], arguments.pattern[i], flag_i);
  }

  return reg_comp;
}

int print(int reg, int line_number, char *line, int *counter, int files_counter,
          char *filename, _flags arguments, regex_t *regex, FILE *fp) {
  int printed = 0;
  if ((!reg && !arguments.v) || (reg && arguments.v)) {
    printed = 1;
    ++(*counter);

    if (!arguments.c && !arguments.l) {
      flag_h(files_counter, filename, arguments);

      if (arguments.n) {
        printf("%d:", line_number);
      }

      if (arguments.o) {
        flag_o(regex, line, fp, arguments);
      } else {
        printf("%s", line);
      }
    }

    if (feof(fp) && (!arguments.c && !arguments.l)) {
      printf("\n");
    }
  }

  return printed;
}

void flag_o(regex_t *regex, char *word, FILE *fp, _flags arguments) {
  regmatch_t match;
  char *pos = word;

  while (1) {
    int found_reg = 1;

    for (int i = 0; i < arguments.patterns_counter; i++) {
      !regexec(&regex[i], pos, 1, &match, 0) ? found_reg = 0 : 0;
    }

    if (found_reg) {
      break;
    }

    printf("%.*s", (int)(match.rm_eo - match.rm_so), pos + match.rm_so);
    pos += match.rm_eo;

    if (!feof(fp)) {
      printf("\n");
    }
  }
}

void flag_h(int files_counter, char *filename, _flags arguments) {
  if (!arguments.h && files_counter > 1) {
    printf("%s:", filename);
  }
}

void clean(_flags arguments, regex_t *regex, FILE *fp) {
  for (int i = 0; i < arguments.patterns_counter; i++) {
    regfree(&regex[i]);
  }
  free(regex);
  fclose(fp);
}
