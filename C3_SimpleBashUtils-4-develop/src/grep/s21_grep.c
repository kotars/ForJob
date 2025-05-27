#include "s21_grep.h"

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
  if (argc > 1) {
    int len_e = 0, len_f = 0, check = 1;
    char*** mass = malloc(sizeof(char**) * 2);
    mass[0] = malloc(sizeof(char*) * 1024);
    mass[1] = malloc(sizeof(char*) * 1024);
    for (int i = 0; i < 1024; i++) {
      mass[0][i] = malloc(sizeof(char) * 1024);
      mass[1][i] = malloc(sizeof(char) * 1024);
    }

    s21_grep flags;
    InitFlags(&flags);
    ParseFlags(&flags, argc, argv, mass, &len_e, &len_f, &check);
    if (check == 0) {
      printf("n/a");
    }

    ProcessGrep(&flags, argc, argv, mass, len_e, len_f);
    FreeMemmory(mass);
  }
  return 0;
}
int InitFlags(s21_grep* flag) {
  flag->flag_c = 0;
  flag->flag_e = 0;
  flag->flag_f = 0;
  flag->flag_h = 0;
  flag->flag_i = 0;
  flag->flag_l = 0;
  flag->flag_n = 0;
  flag->flag_o = 0;
  flag->flag_s = 0;
  flag->flag_v = 0;
  return 0;
}
void ParseFlags(s21_grep* flags, int argc, char** argv, char*** mass,
                int* len_e, int* len_f, int* check) {
  int rez = 0;
  while ((rez = getopt(argc, argv, "e:idvclnhsf:o")) != -1) {
    switch (rez) {
      case 'e':
        flags->flag_e = 1;
        strcpy(mass[0][*len_e], optarg);
        *len_e = *len_e + 1;
        break;
      case 'i':
        flags->flag_i = 1;
        break;
      case 'v':
        flags->flag_v = 1;
        break;
      case 'c':
        flags->flag_c = 1;
        break;
      case 'l':
        flags->flag_l = 1;
        break;
      case 'n':
        flags->flag_n = 1;
        break;
      case 'f':
        flags->flag_f = 1;
        strcpy(mass[1][*len_f], optarg);
        *len_f = *len_f + 1;
        break;
      default:
        *check = 0;
        break;
    }
  }
  if (flags->flag_e == 0 && flags->flag_f == 0) {
    flags->flag_e = 1;
    strcpy(mass[0][*len_e], argv[optind]);
    *len_e = *len_e + 1;
    optind++;
  }
}

int FreeMemmory(char*** mass) {
  for (int i = 0; i < 1024; i++) free(mass[0][i]);
  for (int i = 0; i < 1024; i++) free(mass[1][i]);
  free(mass[0]);
  free(mass[1]);
  free(mass);
  return 0;
}

void TemplateRegex(s21_grep* flag, char*** mass, int len_e, char* buffer,
                   int* result) {
  for (int i = 0; i < len_e; i++) {
    regex_t template;
    int val = -1;
    if (flag->flag_i == 1)
      val = regcomp(&template, mass[0][i],
                    REG_EXTENDED | REG_ICASE | REG_NEWLINE);
    else
      val = regcomp(&template, mass[0][i], REG_EXTENDED | REG_NEWLINE);
    if (val == 0 && regexec(&template, buffer, 0, NULL, 0) == 0) {
      *result = 1;
    }
    regfree(&template);
  }
}

void TemplateRegexInFile(s21_grep* flag, char*** mass, int len_f, char* buffer,
                         int* result) {
  for (int i = 0; i < len_f; i++) {
    FILE* f = fopen(mass[1][i], "r");
    int len = 0;
    char *string = malloc(sizeof(char) * (len + 1)), c = fgetc(f);
    while (!feof(f)) {
      if (c == '\n' || c == '\0') {
        string[len] = '\0';
        regex_t template;
        int val = -1;
        if (flag->flag_i == 1)
          val = regcomp(&template, string,
                        REG_EXTENDED | REG_ICASE | REG_NEWLINE);
        else
          val = regcomp(&template, string, REG_EXTENDED | REG_NEWLINE);
        if (val == 0 && regexec(&template, buffer, 0, NULL, 0) == 0) {
          *result = 1;
        }
        regfree(&template);
        len = 0;
        free(string);
        string = malloc(sizeof(char) * (len + 1));
      } else {
        string[len] = c;
        len++;
        string = realloc(string, sizeof(char) * (len + 1));
      }
      c = fgetc(f);
    }
    string[len] = '\0';
    regex_t template;
    int val = -1;
    if (flag->flag_i == 1)
      val = regcomp(&template, string, REG_EXTENDED | REG_ICASE | REG_NEWLINE);
    else
      val = regcomp(&template, string, REG_EXTENDED | REG_NEWLINE);
    if (val == 0 && regexec(&template, buffer, 0, NULL, 0) == 0) {
      *result = 1;
    }
    regfree(&template);
    free(string);
  }
}
void FindMatchedStrings(s21_grep* flag, char*** mass, int len_e, int len_f,
                        FILE* f, int check_some_files_h, char* file_name) {
  char* strings = malloc(sizeof(char) * 1024);
  int count = 1, count_c = 0, check_l = 0;
  while (fgets(strings, 1024, f)) {
    int result = 0;
    TemplateRegex(flag, mass, len_e, strings, &result);
    if (result == 0 && flag->flag_f == 1) {
      TemplateRegexInFile(flag, mass, len_f, strings, &result);
    }
    if ((result == 1 && flag->flag_v == 0) ||
        (result == 0 && flag->flag_v == 1)) {
      if (flag->flag_c == 0 && flag->flag_l == 0) {
        if (flag->flag_h == 0 && check_some_files_h == 1)
          printf("%s:", file_name);
        if (flag->flag_n == 1 && (flag->flag_c == 0 || flag->flag_l == 0))
          printf("%d:", count);
        printf("%s", strings);
      }
      if (flag->flag_l == 1) {
        check_l = 1;
      }
      if (flag->flag_c == 1) {
        count_c++;
      }
    }
    count++;
  }
  if (flag->flag_l == 1) {
    if (check_l == 1) printf("%s\n", file_name);
  } else if (flag->flag_c == 1) {
    if (flag->flag_h == 0 && check_some_files_h == 1) printf("%s:", file_name);
    printf("%d\n", count_c);
  }
  free(strings);
}
void ProcessGrep(s21_grep* flag, int argc, char** argv, char*** mass, int len_e,
                 int len_f) {
  int check_some_files_h = 0;
  if (optind < argc - 1) check_some_files_h = 1;
  while (optind != argc) {
    FILE* f = fopen(argv[optind], "r");
    if (f == NULL) {
      if (flag->flag_s == 0) {
        printf("No such file or directory\n");
      }
    } else
      FindMatchedStrings(flag, mass, len_e, len_f, f, check_some_files_h,
                         argv[optind]);
    fclose(f);
    optind++;
  }
}

void PrintAll(char** matched_strings, int len, s21_grep* flag, char** argv,
              int check) {
  for (int i = 0; i < len; i++) {
    if (strcmp(matched_strings[i], "\0") != 0) {
      if (flag->flag_h == 0 && check == 1) printf("%s:", argv[optind]);
      if (flag->flag_n == 1 && (flag->flag_c == 0 || flag->flag_l == 0))
        printf("%d:", i + 1);
      printf("%s", matched_strings[i]);
    }
  }
}
void PrintWithL(char** matched_strings, int len, char** argv) {
  for (int i = 0; i < len; i++) {
    if (strcmp(matched_strings[i], "\0") != 0) {
      printf("%s\n", argv[optind]);
      break;
    }
  }
}
void PrintWithC(char** matched_strings, int len, s21_grep* flag, char** argv,
                int check) {
  int count = 0;
  for (int i = 0; i < len; i++) {
    if (strcmp(matched_strings[i], "\0") != 0) {
      count++;
    }
  }
  if (flag->flag_h == 0 && check == 1) printf("%s:", argv[optind]);
  printf("%d\n", count);
}
