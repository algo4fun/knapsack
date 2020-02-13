/*
 *  Filename:  knapsack0.c
 *   Created:  02/12/2020 11:31:04 PM
 *    Author:  Rafael Gozlan <raf@rible.eu>
 */

#include <stdio.h>
#define _POSIX_C_SOURCE
#define _BSD_SOURCE
#define _SVID_SOURCE
#include <string.h>
#define _GNU_SOURCE
#include <stdlib.h>

typedef struct {
  int value, weight;
} Item;


int main(int argc, char *argv[]) {
  size_t buf_size = 4096;
  char *tmp, *buf = calloc(buf_size, sizeof(char));
  unsigned capacity, n;
  FILE* f = fopen(argv[1], "r");
  // reading input file
  for (unsigned i = 0;
       fread(buf+(buf_size*i), 1, 4096, f) == buf_size;
       ++i) {
    reallocarray(buf, buf_size*i+2, sizeof(char));
  }

  char *line = strtok_r(buf, "\n", &tmp);
  sprintf(line, "%u,%u", capacity, n);
  Item items[n];
  for (int i = 0; i < n; ++i) {
    line = strtok_r(NULL, '\n', &tmp);
    char *tok;
    items[i].value  = atoi(strtok_r(line, ',', &tok));
    items[i].weight = atoi(strtok_r(NULL, ',', &tok));
  }

  for (int i = 0; i < n; ++i)
    printf("%u,%u", items[i].value, items[i].weight);
}
