#include "s21_grep.h"

void parser(int argc, char *argv[], struct opt *opt) {
  int c = 0;

  while (c != -1) {
    c = getopt(argc, argv, "e:ivclnshf:");
    switch (c) {
      case 'e':
        opt->e = 1;
        snprintf(opt->templates[opt->temp_c++], 1024, "%s", optarg);
        break;
      case 'i':
        opt->i = 1;
        break;
      case 'v':
        opt->v = 1;
        break;
      case 'c':
        opt->c = 1;
        break;
      case 'l':
        opt->l = 1;
        break;
      case 'n':
        opt->n = 1;
        break;
      case 's':
        opt->s = 1;
        break;
      case 'h':
        opt->h = 1;
        break;
      case 'f':
        opt->f = 1;
        opt->e = 1;
        f_flag(optarg, opt);
        break;
      case '?':
        fprintf(stderr, "bad pattern");
        break;
      default:
        break;
    }
  }
  if (opt->e == 0) {
    snprintf(opt->templates[opt->temp_c++], 300, "%s", argv[optind++]);
  }
}

int is_find_pattern(const char *text, struct opt template) {
  regex_t reegex;
  int c = 0;
  char coppy_text[1024];
  strcpy(coppy_text, text);
  for (int i = 0; i < template.temp_c; i++) {
    char *str_temp = template.templates[i];
    if (template.i == 1) {
      to_lower_str(str_temp);
      to_lower_str(coppy_text);
    }

    int value = regcomp(&reegex, str_temp, 0);
    if (value == 0) {
      int res = regexec(&reegex, coppy_text, 0, NULL, 0);
      if (res == 0) {
        c = 1;
      }
    }
    regfree(&reegex);
  }

  return c;
}

void find_pattern_in_file(const char *filePath, int flag, struct opt option) {
  FILE *stream = fopen(filePath, "r");
  int match = 1;
  if (stream) {
    char buffer[1024];
    int countLine = 0;
    int matches = 0;
    while (fgets(buffer, 1024, stream) != NULL) {
      countLine++;
      if (option.i == 1) i_flag(buffer, option, &match);
      if (option.v == 1) v_flag(buffer, option, &match);
      if (option.v == 0 && option.i == 0)
        match = is_find_pattern(buffer, option);

      if (match) {
        matches++;
        if (option.l == 1) {
          l_flag(filePath);
          break;
        } else if (option.n == 1 && option.c == 0) {
          n_flag(filePath, buffer, countLine, flag);
        } else if (option.c == 0) {
          no_flag(filePath, buffer, flag);
        }
      }
    }
    if (option.c == 1 && option.l == 0) {
      c_flag(filePath, matches, flag);
    }
    fclose(stream);
  } else {
    if (option.s == 0) {
      fprintf(stderr, "grep: %s: No such file or directory\n", filePath);
    }
  }
}

void no_flag(const char *filePath, const char *buffer, int flag) {
  if (flag) {
    printf("%s:%s", filePath, buffer);
  } else {
    printf("%s", buffer);
  }
  if (buffer[strlen(buffer) - 1] != '\n') {
    printf("%c", '\n');
  }
}

void n_flag(const char *filePath, const char *buffer, int countLine, int flag) {
  if (flag) {
    printf("%s:%d:%s", filePath, countLine, buffer);
  } else {
    printf("%d:%s", countLine, buffer);
  }
  if (buffer[strlen(buffer) - 1] != '\n') {
    printf("%c", '\n');
  }
}
void c_flag(const char *filePath, int matches, int flag) {
  if (flag) {
    printf("%s:%d\n", filePath, matches);
  } else {
    printf("%d\n", matches);
  }
}

void l_flag(const char *filePath) { printf("%s\n", filePath); }

void f_flag(const char *filePath, struct opt *option) {
  FILE *stream = fopen(filePath, "r");
  if (stream) {
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), stream) != NULL) {
      buffer[strcspn(buffer, "\n")] = 0;
      snprintf(option->templates[option->temp_c++], sizeof(buffer), "%s",
               buffer);
    }
    fclose(stream);
  } else {
    printf("grep: %s: No such file or directory\n", filePath);
  }
}

void read_all_files(int agrc, char *argv[], struct opt option) {
  int flag = 0;
  if ((agrc - optind) > 1) {
    flag = 1;
  }
  if (option.h == 1) {
    flag = 0;
  }
  for (; optind < agrc; optind++) {
    find_pattern_in_file(argv[optind], flag, option);
  }
}

void to_lower_str(char *str) {
  for (unsigned int i = 0; i < strlen(str); i++) {
    str[i] = tolower(str[i]);
  }
}

void i_flag(const char *buffer, struct opt option, int *match) {
  if (is_find_pattern(buffer, option)) {
    *match = 1;
  } else {
    *match = 0;
  }
}

void v_flag(const char *buffer, struct opt option, int *match) {
  if (!is_find_pattern(buffer, option)) {
    *match = 1;
  } else {
    *match = 0;
  }
}