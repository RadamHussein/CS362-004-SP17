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

void displayHand(int player, struct gameState *G, int numCards){
	int i; 

	printf("Player %d's hand: \n", player);
	for (i = 0; i < numCards; i++){
		printf("%s\n", getCardName(G->hand[player][i]));
	}
	printf("\n");
}

void displayDiscard(int player, struct gameState *G, int numCards){
	int i;

	printf("Player %d's discard: \n", player);
	for (i = 0; i < numCards; i++){
		printf("%s\n", getCardName(G->discard[player][i]));
	}
	printf("\n");
}

int main(){
	int i;
	int v;
	int ret;
	int players = 4;
	int currentPlayer;
	int numCards;
	int chosenCard;
	int treasureCount;
	int handCount;
	int passCount = 0;
	int failCount = 0;
	int goldCount = 0;
	struct gameState G;
	struct gameState G2;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, treasure_map,
	           sea_hag, great_hall, smithy};
	int J[16] = {adventurer, gardens, embargo, village, minion, mine, treasure_map,
			sea_hag, great_hall, smithy, copper, gold, silver, duchy, province, estate};

	//array holds the location where the first two treasure_map cards are placed in the initial deck			
	int treasureLocation[2] = {0, 0};


	srand(time(NULL));

	ret = initializeGame(players, k, 10, &G);

	if (ret != 0){
		printf("FAILED to initialize game\n");
	}
	
	memcpy (&G2, &G, sizeof(struct gameState));

	for (v = 0; v < 2000; v++){
		treasureCount = 0;

		//get a random player number
		currentPlayer = rand() % 4;

		//get a random handCount number
		numCards = rand() % 500;

		//set current number of cards in chosen player's hand 
		G.handCount[currentPlayer] = numCards;

		//fill player's hand with random cards. Keep track of the first two treasure_map cards.
		for(i = 0; i < numCards; i++){
			chosenCard = J[rand() % 16];
			G.hand[currentPlayer][i] = chosenCard;
			if (chosenCard == treasure_map){
				if (treasureCount < 2){
					treasureLocation[treasureCount] = i;
					treasureCount++;
				}
			}
		}

		//store the handcount before the call to treasuremapFuntion()
		handCount = G.handCount[currentPlayer];	
		
		ret = treasuremapFunction(currentPlayer, &G, treasureLocation[0]);		

			if (treasureCount == 0){
				if (ret == -1){
					goldCount = 0;

					//check that the deck does not contain gold cards
					for (i = 0; i < G.deckCount[currentPlayer]; i++){
						if (G.deck[currentPlayer][i] == gold){
							goldCount++;
						}
					}

					if(goldCount == 0){
						passCount++;
					}
					else{
						failCount++;
					}
				}
				else{
					failCount++;
				}
			}
			else if(treasureCount == 1){
				if (ret == 1 && handCount - 1 == G.handCount[currentPlayer]){
					goldCount = 0;

					//check that the deck does not contain gold cards
					for (i = 0; i < G.deckCount[currentPlayer]; i++){
						if (G.deck[currentPlayer][i] == gold){
							goldCount++;
						}
					}

					if(goldCount == 0){
						passCount++;
					}
					else{
						failCount++;
					}

				}
				else{
					failCount++;
				}
			}
			else {
				//check return value. Check that two treasure cards were removed from hand.
				if (ret == 1 && handCount - 2 == G.handCount[currentPlayer] ){
					goldCount = 0;

					//check that the deck contains 4 gold cards
					for (i = 0; i < G.deckCount[currentPlayer]; i++){
						if (G.deck[currentPlayer][i] == gold){
							goldCount++;
						}
					}
					if (goldCount == 4){
						passCount++;
					}
					else{
						failCount++;
					}
					//displayDeck(currentPlayer, &G, G.deckCount[currentPlayer]);
					//displayDiscard(currentPlayer, &G, G.discardCount[currentPlayer]);
					//printf("hand count: %d\n", G.handCount[currentPlayer]);
				}
				else{
					failCount++;
					printf("Test FAIL: \n");
					printf("treasureCount: %d\n", treasureCount);
				}
			}
			memcpy (&G, &G2, sizeof(struct gameState));
	}

	printf("Test complete: \n");
	printf("PASS.... %d\n", passCount);
	printf("FAIL.... %d\n", failCount);



	return 0;
}