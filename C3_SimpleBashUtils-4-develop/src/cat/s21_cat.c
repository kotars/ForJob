#include "s21_cat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv) {
  flags flag;
  InitFlags(&flag);
  int check = CheckFileAndFlags(&flag, argc, argv);
  if (check) {
    fprintf(stderr, "n/a");
  } else {
    PrintFile(flag, argc, argv);
  }
  return 0;
}
int InitFlags(flags *flag) {
  flag->flag_b = 0;
  flag->flag_e = 0;
  flag->flag_tt = 0;
  flag->flag_n = 0;
  flag->flag_s = 0;
  flag->flag_v = 0;
  return 0;
}

int CheckFileAndFlags(flags *flag, int argc, char **argv) {
  int checks = 0;
  for (int i = 0; i < argc; i++) {
    int check = 0;
    if (strcmp(argv[i], "-e") == 0) {
      flag->flag_e = 1;
      flag->flag_v = 1;
    } else if (strcmp(argv[i], "-E") == 0)
      flag->flag_e = 1;
    else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--number") == 0)
      flag->flag_n = 1;
    else if (strcmp(argv[i], "-b") == 0 ||
             strcmp(argv[i], "--number-nonblank") == 0)
      flag->flag_b = 1;
    else if (strcmp(argv[i], "-s") == 0 ||
             strcmp(argv[i], "--squeeze-blank") == 0)
      flag->flag_s = 1;
    else if (strcmp(argv[i], "-t") == 0) {
      flag->flag_tt = 1;
      flag->flag_v = 1;
    } else if (strcmp(argv[i], "-T") == 0)
      flag->flag_tt = 1;
    else if (strcmp(argv[i], "-v") == 0)
      flag->flag_v = 1;
    else
      check = 1;
    if (check) {
      FILE *f = fopen(argv[i], "r");
      if (f == NULL) {
        checks = 1;
        break;
      }
      fclose(f);
    }
  }
  return checks;
}

void PrintfFlagV(char c) {
  if (c > -1 && c < 32 && c != '\n' && c != '\t') {
    fprintf(stdout, "^%c", c + 64);
  } else if (c == 127) {
    fprintf(stdout, "^%c", c - 64);
  } else if (c < 0) {
    fprintf(stdout, "M-");
    char c1 = 128 - (c * -1);
    if (c1 > -1 && c1 < 32 && c != '\t')
      fprintf(stdout, "^%c", c1 + 64);
    else if (c1 == 127)
      fprintf(stdout, "^%c", c1 - 64);
    else
      fprintf(stdout, "%c", c1);
  }
}
void PrintFlags(flags flag, int *count, char c, int empty_str) {
  if (flag.flag_s == 1 && c == '\n' && empty_str == 1) {
    *count = *count - 1;
  } else if (flag.flag_e == 1 && c == '\n') {
    fprintf(stdout, "$\n");
  } else if (flag.flag_tt == 1 && c == '\t') {
    fprintf(stdout, "^I");
  } else if (flag.flag_v == 1 && (c < 32 || c == 127) && c != '\t' &&
             c != '\n') {
    PrintfFlagV(c);
  } else {
    fprintf(stdout, "%c", c);
  }
}
void PrintFile(flags flag, int n, char **argv) {
  char fl[11][25] = {"-b", "-e", "--number-nonblank", "-E", "--number",
                     "-n", "-s", "--squeeze-blank",   "-t", "-T",
                     "-v"};

  int count = 1, len_str = 0, str_b = 0, empty_str = 0;
  for (int i = 1; i < n; i++) {
    int check = 0;
    for (int j = 0; j < 11; j++)
      if (strcmp(argv[i], fl[j]) == 0) check = 1;
    if (!check) {
      FILE *f;
      f = fopen(argv[i], "r");
      char c = fgetc(f);
      while (!feof(f)) {
        if (len_str == 0) {
          if (flag.flag_b == 1 && c != '\n') {
            fprintf(stdout, "%6d	", count - str_b);
          } else if (flag.flag_b == 1 && c == '\n' &&
                     (empty_str == 0 || flag.flag_s == 0)) {
            str_b++;
          } else if (flag.flag_n == 1 && (empty_str == 0 || c != '\n')) {
            fprintf(stdout, "%6d	", count);
          }
        }
        PrintFlags(flag, &count, c, empty_str);
        if (flag.flag_s == 1 && len_str == 0 && c == '\n') {
          empty_str = 1;
          count++;
          len_str = 0;
        } else if (c == '\n') {
          count++;
          len_str = 0;
        } else if (c != '\n') {
          empty_str = 0;
          len_str = 1;
        }
        c = fgetc(f);
      }
      fclose(f);
    }
  }
}