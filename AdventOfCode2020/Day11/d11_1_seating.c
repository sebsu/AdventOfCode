#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 8192
#define INPUT_SIZE 128

int update_seats(char *seats, int width, int height) {
  char old[INPUT_SIZE * INPUT_SIZE];
  char surrounding[8] = {'#'};
  int change = 0;

  /*
  printf("\n");
  for (int j = 0; j < width * height; ++j) {
    if (j % width == 0) {
      printf("\n");
    }
    printf("%c", seats[j]);
  }
  printf("\n");
  */

  for (int i = 0; i < width * height; ++i) {
    old[i] = seats[i];
    if (seats[i] == '.') {
      continue;
    }

    if ((i % width) == 0) {
      /* Left edge */
      surrounding[0] = 'L';
      surrounding[6] = 'L';
      surrounding[7] = 'L';
    }
    if (i < width) {
      /* Top edge */
      surrounding[0] = 'L';
      surrounding[1] = 'L';
      surrounding[2] = 'L';
    }
    if ((i % width) == (width - 1)) {
      /* Right edge */
      surrounding[2] = 'L';
      surrounding[3] = 'L';
      surrounding[4] = 'L';
    }
    if (i >= (width * (height - 1))) {
      /* Bottom edge */
      surrounding[4] = 'L';
      surrounding[5] = 'L';
      surrounding[6] = 'L';
    }

    uint8_t free_count = 0;
    int p = i - width - 1; /* Top left */
    free_count +=
        (surrounding[0] == 'L') ? 1 : (old[p] == 'L') || (old[p] == '.');
    p = i - width; /* Top */
    free_count +=
        (surrounding[1] == 'L') ? 1 : (old[p] == 'L') || (old[p] == '.');
    p = i - width + 1; /* Top right */
    free_count +=
        (surrounding[2] == 'L') ? 1 : (old[p] == 'L') || (old[p] == '.');
    p = i + 1; /* Right */
    free_count +=
        (surrounding[3] == 'L') ? 1 : (seats[p] == 'L') || (seats[p] == '.');
    p = i + width + 1; /* Bottom right */
    free_count +=
        (surrounding[4] == 'L') ? 1 : (seats[p] == 'L') || (seats[p] == '.');
    p = i + width; /* Bottom */
    free_count +=
        (surrounding[5] == 'L') ? 1 : (seats[p] == 'L') || (seats[p] == '.');
    p = i + width - 1; /* Bottom left */
    free_count +=
        (surrounding[6] == 'L') ? 1 : (seats[p] == 'L') || (seats[p] == '.');
    p = i - 1; /* Left */
    free_count +=
        (surrounding[7] == 'L') ? 1 : (old[p] == 'L') || (old[p] == '.');

    if ((seats[i] == 'L') && (free_count == 8)) {
      seats[i] = '#';
      ++change;
    } else if ((seats[i] == '#') && ((8 - free_count) >= 4)) {
      seats[i] = 'L';
      ++change;
    }

    for (int s = 0; s < 8; ++s) {
      surrounding[s] = '#';
    }
  }

  return change;
}

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  f = fopen(argv[1], "r");

  char str[STR_SIZE];
  char seats[INPUT_SIZE * INPUT_SIZE] = {'.'};
  uint64_t result = 0;
  int width = 0;
  int height = 0;
  int pos = 0;
  while (fgets(str, STR_SIZE, f) != NULL) {
    if (width <= 0) {
      width = strlen(str) - 1; /* -1 to exclude '\n' */
    }
    for (int i = 0; i < width; ++i) {
      seats[pos] = str[i];
      ++pos;
    }
    ++height;
  }

  while (update_seats(seats, width, height) > 0) {
    /* Loop only to call update_seats and read the return. */
  }

  printf("\nDone\n");
  for (int i = 0; i < width * height; ++i) {
    result += (seats[i] == '#');
  }

  fclose(f);
  printf("\nResult: %li\n", result);

  return 0;
}
