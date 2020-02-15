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

#define max(a,b) \
 ({ __typeof__ (a) _a = (a); \
     __typeof__ (b) _b = (b); \
   _a > _b ? _a : _b; })

typedef struct {
  unsigned value, weight;
} Item;

unsigned knapsack(unsigned c, unsigned n, Item items[]) {
  unsigned (*map)[c+1] = malloc(sizeof(unsigned[n+1][c+1]));
  unsigned i, w;
  for (i = 0; i <= c; i++)
    map[0][i] = 0;
  for (i = 1; i < n+1; i++) {
    Item cur = items[i-1];
    for (w = 0; w <= c; w++) {
      if (cur.weight > w)
	map[i][w] = map[i-1][w];
      else
	map[i][w] = max(map[i-1][w],
			map[i-1][w-cur.weight]+cur.value);
    }
  }

  return map[n][c-1];
}

int main(int argc, char *argv[]) {
  if (argc < 2)
    exit(2);
  unsigned c, n;
  FILE* f = fopen(argv[1], "r");

  // reading input file
  fscanf(f, "%u,%u\n", &c, &n);
  Item items[n];
  for (int i = 0;
       fscanf(f, "%u,%u\n", &items[i].value, &items[i].weight) > 0;
       ++i);

  printf("%u\n", knapsack(c, n, items));

}
