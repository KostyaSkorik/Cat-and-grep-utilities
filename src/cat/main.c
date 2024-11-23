#include "cat.h"

int main(int argc, char *argv[]) {
  const char *path_to_common_file = "temp.txt";
  struct opt option = {0};

  int flag = 0;
  parser(argc, argv, &option, &flag);
  make_common_file(argc, argv, &flag);
  if (option.b == 1) {
    option.n = 0;
  }
  if (option.s == 1) {
    s_flag(path_to_common_file, &flag);
  }
  if (option.t == 1 && option.v == 0) {
    T_flag(path_to_common_file, &flag);
  }
  if (option.t == 1 && option.v == 1) {
    T_flag(path_to_common_file, &flag);
    v_flag(path_to_common_file, &flag);
  }
  if (option.b == 1) {
    b_flag(path_to_common_file, &flag);
  }
  if (option.e == 1 && option.v == 1) {
    E_flag(path_to_common_file, &flag);
    v_flag(path_to_common_file, &flag);
  }
  if (option.e == 1 && option.v == 0) {
    E_flag(path_to_common_file, &flag);
  }
  if (option.v == 1) {
    v_flag(path_to_common_file, &flag);
  }
  if (option.n == 1) {
    n_flag(path_to_common_file, &flag);
  }

  if (flag) {
    printf("Error");
    remove(path_to_common_file);
  } else {
    read_file(path_to_common_file, &flag);
    remove(path_to_common_file);
  }
  return 0;
}
