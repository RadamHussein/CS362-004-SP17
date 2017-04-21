#include "dominion.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

int compare(const int* a, const int* b);

int main () {
  struct gameState G;
  struct gameState G2;
  int i;
  int j;
  int numPlayers = 2;
  int ret;

  // Initialize G.

  //////Test1: Passing invalid deckCount////////
  G.deckCount[0] = 0;
  ret = shuffle(0, &G);

  printf("shuffle(): ");
  if (ret == -1){
    printf("PASS");
  }
  else{
    printf("FAIL");
  }
  printf(" when passing invalid deckCount\n");

  //set player decks
  for (i = 0; i < numPlayers; i++)
    {
      G.deckCount[i] = 0;
      for (j = 0; j < 3; j++)
      {
        G.deck[i][j] = estate;
        G.deckCount[i]++;
      }
      for (j = 3; j < 10; j++)
      {
        G.deck[i][j] = copper;
        G.deckCount[i]++;    
      }
    }

  memcpy (&G2, &G, sizeof(struct gameState));

  ///////Test2: Decks are the same before shuffling////////
  printf("shuffle(): ");
  if (memcmp(&G, &G2, sizeof(struct gameState)) == 0){
    printf("PASS");
  }
  else{
    printf("FAIL");
  }
  printf(" when comparing un-shuffled decks\n");

  ret = shuffle(0,&G);

  ///////Test3: Expected return value///////
  printf("shuffle(): ");
  if (ret == 0){
    printf("PASS");
  }
  else{
    printf("FAIL");
  }
  printf(" return value check\n");

  ///////Test4: Decks are different after shuffling///////
  printf("shuffle(): ");
  if (memcmp(&G, &G2, sizeof(struct gameState)) == 0){
    printf("FAIL");
  }
  else{
    printf("PASS");
  }
  printf(" when comparing shuffled decks (decks are different)\n");

  qsort ((G.deck[0]), G.deckCount[0], sizeof(int), compare);
  qsort ((G2.deck[0]), G2.deckCount[0], sizeof(int), compare);

  ///////Test5: Decks are same after shuffle and sort///////
  printf("shuffle(): ");
  if (memcmp(&G, &G2, sizeof(struct gameState)) == 0){
    printf("PASS");
  }
  else{
    printf("FAIL");
  }
  printf(" when comparing shuffled and sorted decks\n");

}
