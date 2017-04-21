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

void checkKingdomCardCount(int players, struct gameState *deck, int kingdomCards[10]){
	int j;
	int i;
	int found = 0;
	for (i = adventurer; i <= treasure_map; i++){
		printf("Looking for %s....\n", getCardName(i));
		for (j= 0; j < 10; j++){
			if (kingdomCards[j] == i){
				//check if card is a 'Victory' Kingdom card
				found = 1;
    	      if (kingdomCards[j] == great_hall || kingdomCards[j] == gardens)
    		    {
        		  if (players == 2){ 
        		    //state->supplyCount[i] = 8; 
        		    printf("initializeGame(): ");
        		    comp(deck->supplyCount[i], 8);
        		    printf(" %s count with 2 players\n", getCardName(kingdomCards[j]));
        		    //printf(" %d count with 2 players\n", kingdomCards[j]);
        		    break;
        		  }
    		      else
    		      { 
    		      	//state->supplyCount[i] = 12; 
    		      	printf("initializeGame(): ");
    		      	comp(deck->supplyCount[i], 12);
    		      	printf(" %s or gardens count with > 2 players\n", getCardName(kingdomCards[j]));
    		      	//printf(" %d count with > 2 players\n", kingdomCards[j]);
    		      	break;
    		      }
    		    }
    	      else
    		    {
    		      //state->supplyCount[i] = 10;
    		      printf("initializeGame(): ");
    		      comp(deck->supplyCount[i], 10);
    		      printf(" %s in deck count\n", getCardName(kingdomCards[j]));
    		      //printf(" %d in deck\n", kingdomCards[j]);
    		      break;
    		    }
			}
			/*
			else    //card is not in the set choosen for the game
    	  	{
    	     	****There may be a bug in the initializeGame() function here!****
    	  	}
    	  	*/
		}
		if (found == 0){
			printf("initializeGame(): ");
    		comp(deck->supplyCount[i], -1);
    		printf(" %s not in deck count\n", getCardName(kingdomCards[i]));
    	}
    	else{
    		//card has been found. Reset found to false
    		found = 0;
    	}
		
	}
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


/*
void checkTreasureCards(int playerCount, variable, value){
	printf("initializeGame(): ");
	comp(variable, value);
	printf(" coppers with %d players\n", playerCount);
}
*/

int main(){
	int i;
	struct gameState G;
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
/*
			///Kingdom cards///
			printf("\n");
			printf("*******Checking kingdom cards with %d players\n", players);
			printf("Kindom cards in deck: ");
			for (i = 0; i < 10; i++){
				printf("%s, ", getCardName(k[i]));
			}
			printf("\n");
			checkKingdomCardCount(players, &G, k);
*/
			//Loaded decks
			verifyInitialDecks(players, &G);
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
/*
			///Kingdom cards///
			printf("\n");
			printf("*******Checking kingdom cards with %d players\n", players);
			printf("Kindom cards in deck: ");
			for (i = 0; i < 10; i++){
				printf("%s, ", getCardName(k[i]));
			}
			printf("\n");
			checkKingdomCardCount(players, &G, k);
*/
			//Loaded decks
			verifyInitialDecks(players, &G);
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
/*
			///Kingdom cards///
			printf("\n");
			printf("*******Checking kingdom cards with %d players\n", players);
			printf("Kindom cards in deck: ");
			for (i = 0; i < 10; i++){
				printf("%s, ", getCardName(k[i]));
			}
			printf("\n");
			checkKingdomCardCount(players, &G, k);
*/
			//Loaded decks
			verifyInitialDecks(players, &G);
		}
		players++;
	}


return 0;
}