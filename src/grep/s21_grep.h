#ifndef GREP
#define GREP

#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct opt {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int s;
  int h;
  int f;
  int temp_c;
  char templates[50][1024];
};

void parser(int argc, char *argv[], struct opt *opt);
int is_find_pattern(const char *text, struct opt template);
void find_pattern_in_file(const char *filePath, int count_files,
                          struct opt option);
void read_all_files(int agrc, char *argv[], struct opt option);
void to_lower_str(char *str);
void i_flag(const char *buffer, struct opt option, int *match);
void v_flag(const char *buffer, struct opt option, int *match);
void c_flag(const char *filePath, int matches, int flag);
void n_flag(const char *filePath, const char *buffer, int countLine, int flag);
void l_flag(const char *filePath);
void f_flag(const char *filePath, struct opt *option);
void no_flag(const char *filePath, const char *buffer, int flag);
#endif
