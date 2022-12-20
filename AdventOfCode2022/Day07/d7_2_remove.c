#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 64
#define NAME_SIZE 32
#define NEEDED_SIZE 30000000
#define SYSTEM_SIZE 70000000

struct File;

struct Dir {
  char id[NAME_SIZE];
  struct Dir *parent;
  struct Dir *children;
  struct Dir *next;
  struct File *files;
};

struct File {
  size_t size;
  char id[NAME_SIZE];
  struct Dir *parent;
  struct File *next;
};

size_t get_int(char *str, int *p) {
  size_t i = 0;
  while (('0' <= str[*p]) && (str[*p] <= '9')) {
    i = i * 10 + str[*p] - '0';
    *p += 1;
  }
  *p += 1; // To easily get next int in a CSV.
  return i;
}

void add_dir(struct Dir *dir, char *name) {
  struct Dir *new_dir = (struct Dir *)malloc(sizeof(struct Dir));
  strncpy(new_dir->id, name, NAME_SIZE);
  new_dir->parent = dir;
  new_dir->children = NULL;
  new_dir->next = NULL;
  new_dir->files = NULL;
  struct Dir *tmp = dir->children;
  if (tmp == NULL) {
    dir->children = new_dir;
  } else {
    while (tmp->next != NULL) {
      tmp = tmp->next;
    }
    tmp->next = new_dir;
  }
}

void add_file(struct Dir *dir, char *info) {
  struct File *new_file = (struct File *)malloc(sizeof(struct File));
  int p = 0;
  new_file->size = get_int(info, &p);
  strncpy(new_file->id, info + p, NAME_SIZE);
  new_file->parent = dir;
  new_file->next = NULL;
  struct File *tmp = dir->files;
  if (tmp == NULL) {
    dir->files = new_file;
  } else {
    while (tmp->next != NULL) {
      tmp = tmp->next;
    }
    tmp->next = new_file;
  }
}

struct Dir *cd(struct Dir *dir, char *name) {
  if ((name[0] == '.') && (name[1] == '.')) {
    return dir->parent;
  }
  struct Dir *tmp = dir->children;
  while (strcmp(tmp->id, name) != 0) {
    tmp = tmp->next;
  }
  return tmp;
}

size_t read_dir(struct Dir *root, size_t *smallest, size_t tot_size) {
  size_t sum = 0;
  struct File *file = root->files;
  while (file != NULL) {
    sum += file->size;
    file = file->next;
  }
  /* printf("\nRead dir %s, direct file size %li, ", root->id, sum); */
  struct Dir *dir = root->children;
  while (dir != NULL) {
    sum += read_dir(dir, smallest, tot_size);
    dir = dir->next;
  }
  /* printf("\n and including %s 's child size %li\n", root->id, sum); */
  if (((SYSTEM_SIZE - tot_size) + sum >= NEEDED_SIZE) && (sum < *smallest)) {
    *smallest = sum;
  }
  return sum;
}

int main(int argc, char **argv) {
  (void)argc;
  FILE *fd = fopen(argv[1], "r");
  char input[BUFFER];

  fgets(input, BUFFER, fd);
  struct Dir *root = (struct Dir *)malloc(sizeof(struct Dir));
  strncpy(root->id, "/", NAME_SIZE);
  root->parent = NULL;
  root->children = NULL;
  root->next = NULL;
  root->files = NULL;
  struct Dir *pwd = root;
  while (fgets(input, BUFFER, fd) != NULL) {
    if (input[0] == '$') {
      if (input[2] == 'c') {
        // Change dir.
        pwd = cd(pwd, input + 5);
      }
      // If "ls", then do nothing and read next line.
    } else if (input[0] == 'd') {
      // Dir listed, add to structure.
      add_dir(pwd, input + 4);
    } else {
      // Only remaining possibility is file, add that.
      add_file(pwd, input);
    }
  }

  size_t smallest = SIZE_MAX;
  // First call to get total used space.
  size_t tot_size = read_dir(root, &smallest, 0);

  smallest = SIZE_MAX;
  // Second call to find the smallest dir needed.
  read_dir(root, &smallest, tot_size);
  printf("\nResult: %li\n", smallest);

  return 0;
}
