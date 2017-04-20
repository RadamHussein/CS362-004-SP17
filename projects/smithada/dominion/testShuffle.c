#include "dominion.h"
#include <stdio.h>
#include <assert.h>

int compare(const int* a, const int* b);

int main () {
  struct gameState G;
  struct gameState G2;

  // Initialize G.

  memcpy (&G2, &G, sizeof(struct gameState));
/*
  int ret = shuffle(0,&G);

  if (G.deckCount[0] > 0) {
    if (ret != -1){
      printf("deckCount[0] > 0: TRUE\n");
    }
    else {
      printf("deckCount[0] > 0: FALSE\n");
    }
    
    qsort ((void*)(G.deck[0]), G.deckCount[0], sizeof(int), compare);
    qsort ((void*)(G2.deck[0]), G2.deckCount[0], sizeof(int), compare);    
  } else
    if (ret == -1){
      printf("ret == -1: TRUE\n");
    }

  if (memcmp(&G, &G2, sizeof(struct gameState)) == 0){
      printf("Structs are equal: TRUE\n");
  }
  else{
    printf("Structs are equal: FALSE\n");
  }
*/
}
