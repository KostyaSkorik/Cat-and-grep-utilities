#include "cat.h"

void n_flag(const char *str, int *flage) {
  FILE *main = fopen(str, "r");
  FILE *res = fopen("result.txt", "w");
  if (main != NULL) {
    int flag = 1;
    char buffer;
    int countLine = 1;
    while ((buffer = fgetc(main)) != EOF) {
      if (flag == 1) {
        fprintf(res, "%6d\t", countLine++);
        flag = 0;
      }
      fputc(buffer, res);
      if (buffer == '\n') {
        flag = 1;
      }
    }

    fclose(main);
    fclose(res);

    move_file("result.txt", "temp.txt", flage);

  } else {
    fclose(res);
    remove("result.txt");
    *flage = 1;
  }
}

void b_flag(const char *str, int *flage) {
  FILE *main = fopen(str, "r");
  FILE *res = fopen("result.txt", "w");
  if (main != NULL) {
    int countLine = 1;
    char buffer;
    int flag = 1;
    while ((buffer = fgetc(main)) != EOF) {
      if (buffer != '\n' && flag == 1) {
        fprintf(res, "%6d\t", countLine++);
        flag = 0;
      }
      fputc(buffer, res);
      if (buffer == '\n') {
        flag = 1;
      }
    }

    fclose(main);
    fclose(res);

    move_file("result.txt", "temp.txt", flage);

  } else {
    *flage = 1;
  }
}

void E_flag(const char *str, int *flag) {
  FILE *main = fopen(str, "r");
  FILE *res = fopen(str, "r+");
  if (main != NULL && res != NULL) {
    char buffer;
    while ((buffer = fgetc(main)) != EOF) {
      if (buffer == '\n') {
        fputc('$', res);
        fputc(buffer, res);
      } else {
        fputc(buffer, res);
      }
    }
    fclose(main);
    fclose(res);
  } else {
    *flag = 1;
  }
}
void T_flag(const char *str, int *flag) {
  FILE *main = fopen(str, "r");
  FILE *res = fopen("result.txt", "w");

  if (main != NULL) {
    char buffer;
    while ((buffer = fgetc(main)) != EOF) {
      if (buffer == '\t') {
        fprintf(res, "^I");
      } else {
        fputc(buffer, res);
      }
    }
    fclose(main);
    fclose(res);

    move_file("result.txt", "temp.txt", flag);

  } else {
    *flag = 1;
  }
}

void v_flag(const char *strr, int *flag) {
  FILE *main = fopen(strr, "r");
  FILE *res = fopen("result.txt", "w");

  if (main != NULL) {
    long buffer;
    while ((buffer = fgetc(main)) != EOF) {
      char str[5] = "";

      if (buffer < 32 && buffer != '\n' && buffer != '\t') {
        strcat(str, "^");
        buffer += 64;
      } else if (buffer > 127 && buffer < 160) {
        strcat(str, "M-^");
      } else if (buffer >= 160) {
        strcat(str, "M-");
      }
      if (buffer > 127) {
        buffer = buffer - 128;
        if (buffer < 32 && buffer != '\n' && buffer != '\t') {
          buffer = buffer + 64;
        }
      }
      if (buffer == 127) {
        fprintf(res, "^?");
      } else {
        fprintf(res, "%s%c", str, (char)buffer);
      }
    }
    fclose(main);
    fclose(res);
    move_file("result.txt", "temp.txt", flag);

  } else {
    *flag = 1;
  }
}

void s_flag(const char *str, int *flage) {
  FILE *main = fopen(str, "r");
  FILE *res = fopen("result.txt", "w");
  if (main != NULL) {
    char buffer;
    char prev = '\n';
    int flag = 0;
    while ((buffer = fgetc(main)) != EOF) {
      if (buffer == '\n' && prev == '\n') {
        flag += 1;
      } else {
        flag = 0;
      }
      if (flag < 2) {
        fputc(buffer, res);
      }
      prev = buffer;
    }
    fclose(main);
    fclose(res);
    move_file("result.txt", "temp.txt", flage);

  } else {
    *flage = 1;
  }
}

void move_file(const char *from, const char *to, int *flag) {
  FILE *source_file = fopen(from, "r");
  FILE *target_file = fopen(to, "w");

  if (!source_file || !target_file) {
    *flag = 1;
  } else {
    char buffer;
    while ((buffer = fgetc(source_file)) != EOF) {
      fputc(buffer, target_file);
    }
    fclose(source_file);
    fclose(target_file);
  }

  remove(from);
}

void parser(int argc, char *argv[], struct opt *opt, int *flag) {
  int c = 0;
  int ind;
  static struct option long_options[] = {
      {"number-nonblank", 0, 0, 'b'},
      {"number", 0, 0, 'n'},
      {"squeeze-blank", 0, 0, 's'},
      {0, 0, 0, 0},
  };

  while (c != -1) {
    c = getopt_long(argc, argv, "+beEnvstT", long_options, &ind);
    switch (c) {
      case 'b':
        opt->b = 1;
        break;
      case 'e':
        opt->e = 1;
        opt->v = 1;
        break;
      case 'n':
        opt->n = 1;
        break;
      case 'v':
        opt->v = 1;
        break;
      case 's':
        opt->s = 1;
        break;
      case 't':
        opt->t = 1;
        opt->v = 1;
        break;
      case 'E':
        opt->e = 1;
        break;
      case 'T':
        opt->t = 1;
        break;
      case '?':
        *flag = 1;
        break;
      default:
        break;
    }
  }
}

void coppy_file(const char *filePath, int *flag) {
  FILE *from_f = fopen(filePath, "r");
  FILE *to_f = fopen("temp.txt", "a+");

  if (from_f != NULL && to_f != NULL) {
    char buffer;
    while ((buffer = fgetc(from_f)) != EOF) {
      fputc(buffer, to_f);
    }
    fclose(from_f);
    fclose(to_f);
  } else {
    *flag = 1;
  }
}
void make_common_file(int argc, char *argv[], int *flag) {
  while (optind != argc) {
    coppy_file(argv[optind], flag);
    optind++;
  }
}

void read_file(const char *filePath, int *flag) {
  FILE *stream = fopen(filePath, "r");
  if (stream) {
    char buffer;
    while ((buffer = fgetc(stream)) != EOF) {
      fputc(buffer, stdout);
    }
    fclose(stream);
  } else {
    *flag = 1;
  }
}
