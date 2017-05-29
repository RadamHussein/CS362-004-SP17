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
	int temphand[MAX_HAND];
	//int drawntreasure = 0;
	int players = 4;
	int currentPlayer;
	int chosenCard;
	int treasureCount;
	int originalHandCount;
	int originalDeckCount;
	int originalDiscardCount;
	int twoTreasureCardsInDeck = 0;
	//int numberOfCardsDrawn;
	int handPass = 0;
	int deckPass = 0;
	int discardPass = 0;
	int handFail = 0;
	int deckFail = 0;
	int discardFail = 0;
	int treasureInHand1;
	int treasureInHand2;
	struct gameState G;
	struct gameState G2;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	           sea_hag, great_hall, smithy};
	int J[16] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
			sea_hag, great_hall, smithy, copper, gold, silver, duchy, province, estate};
	int foundTreasureIndices[2] = {0, 0};

	srand(time(NULL));

	ret = initializeGame(players, k, 10, &G);

	if (ret != 0){
		printf("FAILED to initialize game\n");
	}

	memcpy (&G2, &G, sizeof(struct gameState));

	for (i = 0; i < 2000; i++){
		treasureCount = 0;
		twoTreasureCardsInDeck = 0;

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
		for(v = originalDeckCount - 1; v >= 0; v--){
			chosenCard = J[rand() % 16];
			G.deck[currentPlayer][v] = chosenCard;
			if (chosenCard == copper || chosenCard == gold || chosenCard == silver){
				if (treasureCount == 0){
					foundTreasureIndices[0] = v;
				}
				else if (treasureCount == 1){
					foundTreasureIndices[1] = v;
				}
				treasureCount++;
			}
		}

		/******if there are two or more treasure cards in the deck, we will only need to check the deck
		after the call to adventurer******/
		if(treasureCount > 1){
			twoTreasureCardsInDeck = 1;
		}

		//fill player's discard
		originalDiscardCount = rand() % 100;
		G.discardCount[currentPlayer] = originalDiscardCount;
		for (v = 0; v < originalDiscardCount; v++){
			chosenCard = J[rand() % 16];
			G.discard[currentPlayer][v] = chosenCard;
			if (chosenCard == copper || chosenCard == gold || chosenCard == silver){
					treasureCount++;
				}
		}

		//call adventurer
		playAdventurer(&G, temphand, currentPlayer);

		//Check for deck and discard count when we know there were two or more treasure cards already in the deck
		if(twoTreasureCardsInDeck == 1){
			if (G.deckCount[currentPlayer] == foundTreasureIndices[1]){
				deckPass++;
			}
			else{
				deckFail++;
			}

			if (G.discardCount[currentPlayer] == (originalDiscardCount + (originalDeckCount - foundTreasureIndices[1] - 2))){
				discardPass++;
			}
			else{
				discardFail++;
			}
		}

		//check hand when we know there were already two or more treasure cards between deck and discard
		if (treasureCount > 1){
			if (G.handCount[currentPlayer] == originalHandCount + 2){
				treasureInHand1 = G.hand[currentPlayer][G.handCount[currentPlayer]-1];
				treasureInHand2 = G.hand[currentPlayer][G.handCount[currentPlayer]-2];
				if (treasureInHand1 == copper || treasureInHand1 == silver || treasureInHand1 == gold){
					if (treasureInHand2 == copper || treasureInHand2 == silver || treasureInHand2 == gold){
						handPass++;
					}
				}
				else{
					handFail++;
				}
			}
			else{
				handFail++;
			}
		}

		memcpy (&G, &G2, sizeof(struct gameState));
	}

	printf("Tests complete: \n");
	printf("-----------------------------------------\n");
	printf("handCount PASSED: %d\n", handPass);
	printf("handCount FAILED: %d\n", handFail);
	printf("-----------------------------------------\n");
	printf("deckCount PASSED %d\n", deckPass);
	printf("deckCount FAILED %d\n", deckFail);
	printf("-----------------------------------------\n");
	printf("discardCount PASSED %d\n", discardPass);
	printf("discardCount FAILED %d\n", discardFail);
	printf("-----------------------------------------\n");
	printf("TOTAL PASSED: %d\n", handPass + deckPass + discardPass);
	printf("TOTAL FAILED: %d\n", handFail + deckFail + discardFail);

	return 0;
}
