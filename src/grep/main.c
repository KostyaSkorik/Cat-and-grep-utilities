#include "s21_grep.h"

int main(int argc, char *argv[]) {
  struct opt option = {0};
  parser(argc, argv, &option);
  read_all_files(argc, argv, option);
  return 0;
}