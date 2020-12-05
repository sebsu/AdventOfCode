#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 8192
#define INPUT_SIZE 350

/* String to int. */
int stoi(char *str, size_t *pos) {
  int out = 0;
  int sign = 1;
  if (str[*pos] == '-') {
    sign = -1;
    ++(*pos);
  }
  while (('0' <= str[*pos]) && (str[*pos] <= '9')) {
    out = (out * 10) + (str[*pos] - '0');
    ++(*pos);
  }
  //++(*pos);
  return sign * out;
}

int valid_byr(char *byr) {
  size_t p = 0;
  int year = stoi(byr, &p);
  if (1920 <= year && year <= 2002) {
    return 1;
  }
  return -1;
}

int valid_iyr(char *iyr) {
  size_t p = 0;
  int year = stoi(iyr, &p);
  if (2010 <= year && year <= 2020) {
    return 1;
  }
  return -1;
}

int valid_eyr(char *eyr) {
  size_t p = 0;
  int year = stoi(eyr, &p);
  if (2020 <= year && year <= 2030) {
    return 1;
  }
  return -1;
}

int valid_hgt(char *hgt) {
  size_t p = 0;
  int height = stoi(hgt, &p);
  if (hgt[p] == 'i' && hgt[p + 1] == 'n') {
    if (59 <= height && height <= 76) {
      return 1;
    }
  } else if (hgt[p] == 'c' && hgt[p + 1] == 'm') {
    if (150 <= height && height <= 193) {
      return 1;
    }
  }
  return -1;
}

int valid_hcl(char *hcl) {
  int len = strlen(hcl);
  if (hcl[0] != '#' || len != 7) {
    return -1;
  }
  for (int i = 1; i < len; ++i) {
    if (!('a' <= hcl[i] && hcl[i] <= 'f') &&
        !('0' <= hcl[i] && hcl[i] <= '9')) {
      return -1;
    }
  }
  return 1;
}

int valid_ecl(char *ecl) {
  char *valid_color[7] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
  for (int i = 0; i < 7; ++i) {
    if (strcmp(ecl, valid_color[i]) == 0) {
      return 1;
    }
  }
  return -1;
}

int valid_pid(char *pid) {
  int len = strlen(pid);
  if (len != 9) {
    return -1;
  }
  for (int i = 0; i < len; ++i) {
    if (!('0' <= pid[i] && pid[i] <= '9')) {
      return -1;
    }
  }
  return 1;
}

int valid_cid(char *cid) {
  (void)cid;
  return 1;
}

int valid_field(char *field, uint8_t *validated) {
  int result = 0;
  char id[3];
  strncpy(id, field, 3);
  if (strcmp(id, "byr") == 0) {
    result = valid_byr(&field[4]);
    *validated |= (result << 7);
  } else if (strcmp(id, "ecl") == 0) {
    result = valid_ecl(&field[4]);
    *validated |= (result << 6);
  } else if (strcmp(id, "eyr") == 0) {
    result = valid_eyr(&field[4]);
    *validated |= (result << 5);
  } else if (strcmp(id, "hcl") == 0) {
    result = valid_hcl(&field[4]);
    *validated |= (result << 4);
  } else if (strcmp(id, "hgt") == 0) {
    result = valid_hgt(&field[4]);
    *validated |= (result << 3);
  } else if (strcmp(id, "iyr") == 0) {
    result = valid_iyr(&field[4]);
    *validated |= (result << 2);
  } else if (strcmp(id, "pid") == 0) {
    result = valid_pid(&field[4]);
    *validated |= (result << 1);
  } else if (strcmp(id, "cid") == 0) {
    result = valid_cid(&field[4]);
    *validated |= (result << 0);
  }
  return result;
}

void find_field(char *passport, size_t *p) {
  while (passport[*p] != ' ' && passport[*p] != '\n') {
    ++*p;
  }
}

int validate_passport(char *passport) {
  uint8_t validated = 0;
  size_t len = strlen(passport);
  size_t end_p = 0;
  size_t start_p = 0;
  while (end_p < len) {
    start_p = end_p;
    char field[STR_SIZE];
    find_field(passport, &end_p);
    // printf("start %li end %li\n", start_p, end_p);
    strncpy(field, &passport[start_p], (end_p - start_p));
    // printf("field .%s.\n", field);
    int res = valid_field(field, &validated);
    // printf("Valid? %i\n", res);
    if (res <= 0) {
      memset(field, 0, (++end_p - start_p));
      //  printf("\n");
      return 0;
    }
    memset(field, 0, (++end_p - start_p));
  }
  //  printf("validated %i\n", validated);
  return (validated >= 254);
}

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  f = fopen(argv[1], "r");

  char str[STR_SIZE];
  int64_t result = 0;
  while (fgets(str, STR_SIZE, f) != NULL) {
    char passport[STR_SIZE];
    strncat(passport, str, strlen(str));
    while (fgets(str, STR_SIZE, f) != NULL) {
      if (str[0] == '\n') {
        break;
      }
      strncat(passport, str, strlen(str));
    }
    result += validate_passport(passport);
    memset(passport, 0, strlen(passport));
  }

  fclose(f);
  printf("Result: %li\n", result);

  return 0;
}
