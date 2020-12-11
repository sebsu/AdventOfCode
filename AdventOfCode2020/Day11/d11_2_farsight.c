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

int get_step(int direction, int width) {
  switch (direction) {
  case 0: /* Up left */
    return -width - 1;
  case 1: /* Up */
    return -width;
  case 2: /* Up right */
    return -width + 1;
  case 3: /* Right */
    return 1;
  case 4: /* Down right */
    return width + 1;
  case 5: /* Down */
    return width;
  case 6: /* Down left */
    return width - 1;
  case 7: /* Left */
    return -1;
  }
  return 0;
}

int look(int step, int pos, int width, int height, char *seats) {
  int ul = (step == -1) || (step == -width - 1) || (step == -width);
  int ur = (step == 1) || (step == -width + 1) || (step == -width);
  int dr = (step == 1) || (step == width + 1) || (step == width);
  int dl = (step == -1) || (step == width - 1) || (step == width);
  for (int i = 1; /* All bounds checked inside. */; ++i) {
    int p = pos + i * step;
    /* Check bounds. */
    if (((ul || dl) && ((p % width) > (pos % width))) || /* Left */
        ((ur || dr) && ((p % width) < (pos % width))) || /* Right */
        ((dl || dr) && (p >= width * height)) ||         /* Down */
        ((ul || ur) && (p < 0))) {                       /* Up */
      return 1;
    }
    if (seats[p] == '.') {
      continue;
    } else if (seats[p] == 'L') {
      return 1;
    } else {
      break;
    }
  }
  return 0;
}

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
    for (int s = 0; s < 8; ++s) {
      int step = get_step(s, width);
      char *seating = seats;
      if (step < 0) {
        seating = old;
      }
      free_count +=
          (surrounding[s] == 'L') ? 1 : look(step, i, width, height, seating);
    }

    if ((seats[i] == 'L') && (free_count == 8)) {
      seats[i] = '#';
      ++change;
    } else if ((seats[i] == '#') && ((8 - free_count) >= 5)) {
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
  /* Sum occupied. */
  for (int i = 0; i < width * height; ++i) {
    result += (seats[i] == '#');
  }

  fclose(f);
  printf("\nResult: %li\n", result);

  return 0;
}
