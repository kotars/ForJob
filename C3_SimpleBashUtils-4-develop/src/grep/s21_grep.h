#pragma once
#include <stdio.h>
typedef struct {
  int flag_e, flag_i, flag_v, flag_c, flag_l, flag_n, flag_o, flag_h, flag_s,
      flag_f;
} s21_grep;

void ParseFlags(s21_grep* flags, int argc, char** argv, char*** mass,
                int* len_e, int* len_f, int* check);
int CheckFlags(s21_grep* flags, char* argv);
void FindMatchedStrings(s21_grep* flag, char*** mass, int len_e, int len_f,
                        FILE* f, int check_some_files_h, char* file_name);
void TemplateRegex(s21_grep* flag, char*** mass, int len_e, char* buffer,
                   int* result);
void TemplateRegexInFile(s21_grep* flag, char*** mass, int len_f, char* buffer,
                         int* result);
void ProcessGrep(s21_grep* flag, int argc, char** argv, char*** mass, int len_e,
                 int len_f);
int FreeMemmory(char*** mass);
int InitFlags(s21_grep* flag);
void PrintAll(char** matched_strings, int len, s21_grep* flag, char** argv,
              int check);
void PrintWithL(char** matched_strings, int len, char** argv);
void PrintWithC(char** matched_strings, int len, s21_grep* flag, char** argv,
                int check);