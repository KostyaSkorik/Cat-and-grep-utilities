#ifndef CAT
#define CAT
#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct opt {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
};

void n_flag(const char *str, int *flag);
void b_flag(const char *str, int *flag);
void E_flag(const char *str, int *flag);
void v_flag(const char *str, int *flag);
void s_flag(const char *str, int *flag);
void T_flag(const char *str, int *flag);
void move_file(const char *from, const char *to, int *flag);
void parser(int argc, char *argv[], struct opt *opt, int *flag);
void coppy_file(const char *filePath, int *flag);
void make_common_file(int argc, char *argv[], int *flag);
int empty_flags(struct opt flags);
void read_file(const char *filePath, int *flag);
#endif
