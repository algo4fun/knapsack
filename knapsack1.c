/*
 *  Filename:  knapsack0.c
 *   Created:  02/12/2020 11:31:04 PM
 *    Author:  Rafael Gozlan <raf@rible.eu>
 */

#include <stdbool.h>
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

// UTILS
float ratio(Item i) { return (float)(i.value/i.weight); }

void sort(Item items[], unsigned n) {
  for (unsigned i = 0; i < n; ++i)
    for (unsigned j = i+1; j < n; ++j)
      if (ratio(items[j]) > ratio(items[i])) {
	Item tmp = items[i];
	items[i] = items[j];
	items[j] = tmp;
      }
}

// Stack utils
typedef struct {
  unsigned *bottom, *top;
  unsigned size;
} Stack;

Stack s_init(unsigned n) {
  Stack s = {
    .bottom = malloc(n*sizeof(unsigned)),
    .top = NULL,
    .size = 0,
  };
  s.top = s.bottom;
  return s;
}

void s_push(Stack *s, unsigned i) {
  *(s->top) = i;
  ++(s->top);
  ++(s->size);
}

unsigned s_top(Stack *s) {
  return *(s->top-1);
}

unsigned s_pop(Stack *s) {
  --(s->top);
  --(s->size);
  return *(s->top);
}

void s_print(Stack *s, Item items[]) {
  for (unsigned i = 0; i < s->size; ++i) {
    Item item = items[s->bottom[i]];
    printf("%3u: %3u %3u %3f\n", i, item.value, item.weight, ratio(item));
  }
}

unsigned knapsack(unsigned c, unsigned n, Item items[]) {
  // sort by ratio
  // fill up the bag
  // while parcours toute la list and noswap
  // IF e.value > sum(X.value for X element from the bottom) THEN swap
  // OR
  // IF e.ratio > mean(X.ratio for X element from the bottom) THEN swap
  unsigned i;

  sort(items, n);
  for (i = 0; i < n; ++i) {
    printf("%7u, %7u, %7f\n", items[i].value, items[i].weight, ratio(items[i]));
  }

  Stack s = s_init(n);
  bool in_bag[n];
  for (i = 0; i < n; ++i) {
    in_bag[i] = false;
  }
  // Push elements with highest ratio
  for (i = 0; c > 0 && i < n; ++i) {
    if (!in_bag[i] && c >= items[i].weight) {
      s_push(&s, i);
      c = c - items[i].weight;
      in_bag[i] = true;
    }
  }

  while (true) {
    s_print(&s, items);
    for (i = 0; c > 0 && i < n; ++i) {
      if (in_bag[i])
	continue;
      // Sum the bottom elements to see what we can swap with the current item
      Item sum = { .value = 0, .weight = 0 };
      unsigned items_to_pop = 0;
      while (c + sum.weight < items[i].weight &&
	     items_to_pop <= s.size) {
	unsigned tmp = *(s.top-items_to_pop-1);
	sum.weight += items[tmp].weight;
	sum.value += items[tmp].value;
	++items_to_pop;
      }
      // If the current item has a better ratio then swap
      if (ratio(sum) < ratio(items[i])) {
	for (unsigned j = 0; j < items_to_pop; ++j) {
	  unsigned item = s_pop(&s);
	  in_bag[item] = false;
	  c += items[item].weight;
	}
	s_push(&s, i);
	in_bag[i] = true;
	c -= items[i].weight;
	continue;
      }
    }
    break;
  }
  s_print(&s, items);

  Item sum = { .value = 0, .weight = 0 };
  for (i = 0; i < s.size; ++i) {
    unsigned tmp = s.bottom[i];
    sum.weight += items[tmp].weight;
    sum.value += items[tmp].value;
  }

  return sum.value;
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
