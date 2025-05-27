#pragma once

typedef struct {
  int flag_b, flag_n, flag_e, flag_s, flag_tt, flag_v;
} flags;
int InitFlags(flags *flag);
int CheckFileAndFlags(flags *flag, int argc, char **arg);
void PrintfFlagV(char c);
void PrintFlags(flags flag, int *count, char c, int empty_str);
void PrintFile(flags flag, int n, char **argv);