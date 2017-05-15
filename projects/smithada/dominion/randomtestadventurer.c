#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

const char* getCardName(int cardType){
	switch(cardType){
		case estate: return "estate";
		case duchy: return "duchy";
		case province: return "province";
		case copper: return "copper";
		case silver: return "silver";
		case gold: return "gold";
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

void displayDeck(int player, struct gameState *G, int numCards){
	int i;

	printf("Player %d's deck:\n", player);
	for (i = 0; i < numCards; i++){
		printf("%s\n", getCardName(G->deck[player][i]));
	}
	printf("\n");
}

int main(){
	int i;
	int v;
	int ret;
	int drawntreasure = 0;
	int players = 4;
	int currentPlayer;
	int chosenCard;
	int treasureCount;
	int originalHandCount;
	int originalDeckCount;
	int numberOfCardsDrawn;
	int passCount = 0;
	int failCount = 0;
	struct gameState G;
	struct gameState G2;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	           sea_hag, great_hall, smithy};
	int J[16] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
			sea_hag, great_hall, smithy, copper, gold, silver, duchy, province, estate};

	//array holds the location where the first two treasure cards are placed in the initial deck			
	int treasureLocation[2] = {0, 0};


	srand(time(NULL));

	ret = initializeGame(players, k, 10, &G);

	if (ret != 0){
		printf("FAILED to initialize game\n");
	}

	memcpy (&G2, &G, sizeof(struct gameState));

	for (i = 0; i < 2000; i++){
		treasureCount = 0;

		currentPlayer = rand() % 4;

		//get a random handCount number
		originalHandCount = rand() % 498;
		G.handCount[currentPlayer] = originalHandCount;

		//fill player's hand with random cards.
		for(v = 0; v < originalHandCount; v++){
			chosenCard = J[rand() % 16];
			G.hand[currentPlayer][v] = chosenCard;
		}

		//get a random handCount number
		originalDeckCount = rand() % 500;
		G.deckCount[currentPlayer] = originalDeckCount;

		//fill player's deck with random cards. Keep track of the first two treasure cards.
		for(v = 0; v < originalDeckCount; v++){
			chosenCard = J[rand() % 16];
			G.deck[currentPlayer][v] = chosenCard;
			if (chosenCard == copper || chosenCard == gold || chosenCard == silver){
				if (treasureCount < 2){
					treasureLocation[treasureCount] = v;
					treasureCount++;

				}
			}
		}

		//printf("Deck after initialization: \n");
		//printf("treasureCount: %d\n", treasureCount);
		//printf("Card locations: %d, %d\n", treasureLocation[0], treasureLocation[1]);
		

		numberOfCardsDrawn = treasureLocation[1] + 1;
		
		//don't call function if no treasure in deck. Will cause infinite loop.
		if (treasureCount > 0){
			adventurerFunction(currentPlayer, &G, drawntreasure);
		}

		if (treasureCount == 2){
			if(G.handCount[currentPlayer] == originalHandCount + 1 && G.discardCount[currentPlayer] == numberOfCardsDrawn - 2){
				passCount++;
			}
			else{
				failCount++;
			}
		}
		else if(treasureCount == 1){
			if (G.handCount[currentPlayer] == originalHandCount && G.discardCount[currentPlayer] == numberOfCardsDrawn - 1){
				passCount++;
			}
			else{
				failCount++;
			}
		}
		memcpy (&G, &G2, sizeof(struct gameState));
	}

	printf("Test complete: \n");
	printf("PASS.... %d\n", passCount);
	printf("FAIL.... %d\n", failCount);



	return 0;
}