#include "dominion.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void assertNotZero(value){
	if (value != 0){
		printf("PASS");
	}
	else{
		printf("FAIL");
	}
}

void assertZero(value){
	if (value != 0){
		printf("FAIL");
	}
	else{
		printf("PASS");
	}
}

void comp(variable, value){
	if (variable == value){
		printf("PASS");
	}
	else{
		printf("FAIL");
	}
}

const char* getCardName(int cardType){
	switch(cardType){
		case adventurer: return "adventurer";
		case council_room: return "council room";
		case feast: return "feast";
		case gardens: return "gardens";
		case mine: return "mine";
		case remodel: return "remodel";
		case smithy: return "smithy";
		case village: return "village";
		case baron: return "baron";
		case great_hall: return "great_hall";
		case minion: return "minion";
		case steward: return "steward";
		case tribute: return "tribute";
		case ambassador: return "ambassador";
		case cutpurse: return "cutpurse";
		case embargo: return "embargo";
		case outpost: return "outpost";
		case salvager: return "salvager";
		case sea_hag: return "sea hag";
		case treasure_map: return "treasure_map";
	}
	return "unknown_value";
}

void verifyInitialDecks(int players, struct gameState *state){
	int copperCount = 0;
	int estateCount = 0;
	int i;
	int j;
	for (i = 0; i < players; i++){
		for (j = 0; j < 10; j++){
			if (state->deck[i][j] == copper){
				copperCount++;
			}
			else{
				estateCount++;
			}
		}
	}
	if (copperCount == (7 * players) && estateCount == (3 * players)){
		printf("initializeGame(): PASS initial player deck configuration\n");
		//printf("copperCount = %d, estateCount = %d\n", copperCount, estateCount);
	}
	else{
		printf("initializeGame(): FAIL initial player deck configuration\n");
		//printf("copperCount = %d, estateCount = %d\n", copperCount, estateCount);
	}
}

void verifyShuffle(struct gameState *G, int numPlayers){
	int i;
	int j;
	int estateCount = 0;
	int copperCount = 0;

	for (i = 0; i < numPlayers; i++){
		for (j = 0; j < 3; j++){
			if (G->deck[i][j] == estate){
				estateCount++;
			}
		}
		for (j = 3; j < 10; j++){
			if (G->deck[i][j] == copper){
				copperCount++;
			}
		}

		if (copperCount == 7 || estateCount == 3){
		printf("initializeGame(): FAIL shuffle player %d deck\n", i+1);
		}
		else{
			printf("initializeGame(): PASS shuffle player %d deck\n", i+1);
		}
		estateCount = 0;
		copperCount = 0;
	}
}

void verifyPlayerHands(struct gameState *G, int numPlayers){
	int i; 
	int j;
	int count = 0;

	for (i = 0; i < numPlayers; i++){
		for (j = 0; j < 5; j++){
			if (G->hand[i][j] == estate || G->hand[i][j] == copper){
				count++;
			}
		}
		if (count == 5){
			printf("initializeGame(): PASS player %d has 5 cards in hand\n", i+1);
		}
		else{
			printf("initializeGame(): FAIL player %d has 5 cards in hand\n", i+1);
		}
		count = 0;
	}
}

void verifyEmbargoTokens(struct gameState *G){
	int i;
	int count = 0;
	for (i = 0; i <= treasure_map; i++)
    {
    	if (G->embargoTokens[i] == 0){
    		count++;
    	}
    }
    if (count == i){
    	printf("initializeGame(): PASS setting embargoTokens\n");
    }
    else{
    	printf("initializeGame(): FAIL setting embargoTokens\n");
    }
}

void verifyFirstPlayersTurn(struct gameState *G){
  if(G->outpostPlayed != 0){
  	printf("initializeGame(): FAIL initialize first player's turn\n");
  }
  else if(G->phase != 0){
  	printf("initializeGame(): FAIL initialize first player's turn\n");
  }
  else if(G->numActions != 1){
  	printf("initializeGame(): FAIL initialize first player's turn\n");
  }
  else if(G->numBuys != 1){
  	printf("initializeGame(): FAIL initialize first player's turn\n");
  }
  else if(G->playedCardCount != 0){
  	printf("initializeGame(): FAIL initialize first player's turn\n");
  }
  else{
  	printf("initializeGame(): PASS initialize first player's turn\n");
  }
}

void verifyKingdomCardCount(struct gameState *G, int kingdomCards[], int numPlayers){
	int i;
	int j;
	int fail = 0;

	 for (i = adventurer; i <= treasure_map; i++){       	//loop all cards
	      for (j = 0; j < 10; j++)           		//loop chosen cards
	    	{
	    	  if (kingdomCards[j] == i)
	    	  {
	    	      //check if card is a 'Victory' Kingdom card
	    	      if (kingdomCards[j] == great_hall || kingdomCards[j] == gardens)
	    		    {
	        		  if (numPlayers == 2){ 
	        		    if(G->supplyCount[i] != 8){
	        		    	fail = 1;
	        		    } 
	        		  }
	    		      else{ 
	                		if(G->supplyCount[i] != 12){
	                			fail = 1;
	                		} 
	              		}
	    		    }
	    	      else
	    		    {
	    		      if(G->supplyCount[i] != 10){
	    		      	fail = 1;
	    		      }
	    		    }
	    	      break;
	    	  }
	    	  else    //card is not in the set choosen for the game
	    	  {
	    	     if(G->supplyCount[i] != -1){
	    	     	fail = 1;
	    	     }	
	    	  }
	    	}
	    }
	    if (fail == 0){
	    	printf("initializeGame(): PASS set number of kingdom cards\n");
	    }
	    else{
	    	printf("initializeGame(): FAIL set number of kingdom cards\n");
	    }
}

int main(){
	struct gameState G;
	struct gameState G2;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	           sea_hag, great_hall, smithy};
	int players;
	int ret;

	///////Test1: Invlaid number of players///////
	players = 1;	//too few players

	ret = initializeGame(players, k, 10, &G);

	printf("initializeGame(): ");
	assertNotZero(ret);
	printf(" when invalid number of players....not enough players\n");

	players = MAX_PLAYERS + 1;	//too many players

	ret = initializeGame(players, k, 10, &G);

	printf("initializeGame(): ");
	assertNotZero(ret);
	printf(" when invalid number of players....too many players\n");

	///////Test2: Duplicate kingdom cards///////
	k[6] = adventurer;
	players = 2;

	ret = initializeGame(players, k, 10, &G);

	printf("initializeGame(): ");
	assertNotZero(ret);
	printf(" when passing array with duplicate kingdom cards\n");

	///////Test3: ///////
	k[6] = cutpurse;
	players = 2;
	memcpy(&G2, &G, sizeof(struct gameState));

	while (players < 5){
		ret = initializeGame(players, k, 10, &G);

		printf("initializeGame(): ");
		assertZero(ret);
		printf(" return value with %d players\n", players);

		if (players == 2){
			printf("\n");
			printf("********** numPlayers: 2 **********\n");
			///Curse cards///
			printf("initializeGame(): ");
			comp(G.supplyCount[curse], 10);
			printf(" curse cards with 2 players\n");

			///victory cards///
			printf("initializeGame(): ");
			comp(G.supplyCount[estate], 8);
			printf(" estate cards with 2 players\n");

			printf("initializeGame(): ");
			comp(G.supplyCount[duchy], 8);
			printf(" duchy cards with 2 players\n");

			printf("initializeGame(): ");
			comp(G.supplyCount[province], 8);
			printf(" province cards with 2 players\n");

			///Treasure Cards///
			printf("initializeGame(): ");
			comp(G.supplyCount[copper], 46);
			printf(" coppers with 2 players\n");

			printf("initializeGame(): ");
			comp(G.supplyCount[silver], 40);
			printf(" silver with 2 players\n");

			printf("initializeGame(): ");
			comp(G.supplyCount[gold], 30);
			printf(" gold with 2 players\n");

			//verify set number of kingdom cards
			verifyKingdomCardCount(&G, k, players);

			//Loaded decks
			verifyInitialDecks(players, &G);

			//is deck shuffled
			verifyShuffle(&G, players);

			//do players have correct five cards in hand
			verifyPlayerHands(&G, players);

			//were embargoTokens set to 0
			verifyEmbargoTokens(&G);

			//verify initialize first player's turn
			verifyFirstPlayersTurn(&G);
		}
		else if (players == 3){
			printf("\n");
			printf("********** numPlayers: 3 **********\n");
			///Curse cards///
			printf("initializeGame(): ");
			comp(G.supplyCount[curse], 20);
			printf(" curse cards with 3 players\n");

			///victory cards///
			printf("initializeGame(): ");
			comp(G.supplyCount[estate], 12);
			printf(" estate cards with 3 players\n");

			printf("initializeGame(): ");
			comp(G.supplyCount[duchy], 12);
			printf(" duchy cards with 3 players\n");

			printf("initializeGame(): ");
			comp(G.supplyCount[province], 12);
			printf(" province cards with 3 players\n");

			///Treasure Cards///
			printf("initializeGame(): ");
			comp(G.supplyCount[copper], 39);
			printf(" coppers with 3 players\n");

			printf("initializeGame(): ");
			comp(G.supplyCount[silver], 40);
			printf(" silver with 3 players\n");

			printf("initializeGame(): ");
			comp(G.supplyCount[gold], 30);
			printf(" gold with 3 players\n");

			//verify set number of kingdom cards
			verifyKingdomCardCount(&G, k, players);

			//Loaded decks
			verifyInitialDecks(players, &G);

			//is deck shuffled
			verifyShuffle(&G, players);

			//do players have correct five cards in hand
			verifyPlayerHands(&G, players);

			//were embargoTokens set to 0
			verifyEmbargoTokens(&G);

			//verify initialize first player's turn
			verifyFirstPlayersTurn(&G);
		}
		else{
			printf("\n");
			printf("********** numPlayers: 4 **********\n");
			///Curse cards
			printf("initializeGame(): ");
			comp(G.supplyCount[curse], 30);
			printf(" curse cards with 4 players\n");

			///victory cards///
			printf("initializeGame(): ");
			comp(G.supplyCount[estate], 12);
			printf(" estate cards with 4 players\n");

			printf("initializeGame(): ");
			comp(G.supplyCount[duchy], 12);
			printf(" duchy cards with 4 players\n");

			printf("initializeGame(): ");
			comp(G.supplyCount[province], 12);
			printf(" province cards with 4 players\n");

			///Treasure Cards///
			printf("initializeGame(): ");
			comp(G.supplyCount[copper], 32);
			printf(" coppers with 3 players\n");

			printf("initializeGame(): ");
			comp(G.supplyCount[silver], 40);
			printf(" silver with 3 players\n");

			printf("initializeGame(): ");
			comp(G.supplyCount[gold], 30);
			printf(" gold with 3 players\n");

			//verify set number of kingdom cards
			verifyKingdomCardCount(&G, k, players);

			//Loaded decks
			verifyInitialDecks(players, &G);

			//is deck shuffled
			verifyShuffle(&G, players);

			//do players have correct five cards in hand
			verifyPlayerHands(&G, players);

			//were embargoTokens set to 0
			verifyEmbargoTokens(&G);

			//verify initialize first player's turn
			verifyFirstPlayersTurn(&G);
		}
		players++;
		memcpy(&G, &G2, sizeof(struct gameState));
	}


return 0;
}