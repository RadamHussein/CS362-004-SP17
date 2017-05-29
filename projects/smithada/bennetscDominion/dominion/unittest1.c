#include "dominion.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

int checkTheDecks(struct gameState *G){
  int copperCount = 0;
  int estateCount = 0;
  int wrongCard = 0;
  int i;

  for (i = 0; i < 10; i++){
    if (G->deck[0][i] == copper){
      copperCount++;
    }
    else if (G->deck[0][i] == estate){
      estateCount++;
    }
    else{
      wrongCard++;
    }
  }
  if (copperCount == 7 && estateCount == 3 && wrongCard == 0){
    return 0;
  }
  else{
    return -1;
  }
}

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

  ///////Test5: Decks are same after shuffle and sort///////
  i = checkTheDecks(&G);
  j = checkTheDecks(&G2);
  printf("shuffle(): ");
  if (i == 0 && j == 0){
    printf("PASS");
  }
  else{
    printf("FAIL");
  }
  printf(" when comparing original and shuffled decks\n");

  return 0;
}
