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
	int deckCount;
	int treasureLocation;
	int foundTreasureMap = 0;
	int passCount = 0;
	int failCount = 0;
	int oneCardPass = 0;
	int twoCardPass = 0;
	int oneCardFail = 0;
	int twoCardFail = 0;
	int addingGoldPass = 0;
	int addingGoldFail = 0;
	int goldCount = 0;
	struct gameState G;
	struct gameState G2;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, treasure_map,
	           sea_hag, great_hall, smithy};
	int J[16] = {adventurer, gardens, embargo, village, minion, mine, treasure_map,
			sea_hag, great_hall, smithy, copper, gold, silver, duchy, province, estate};

	//array holds the location where the first two treasure_map cards are placed in the initial deck
	//int treasureLocation[2] = {0, 0};


	srand(time(NULL));

	ret = initializeGame(players, k, 10, &G);

	if (ret != 0){
		printf("FAILED to initialize game\n");
	}

	memcpy (&G2, &G, sizeof(struct gameState));

	for (v = 0; v < 2000; v++){
		treasureCount = 0;
		foundTreasureMap = 0;
		goldCount = 0;

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
				//the first treasure_map assigned is going to be the handPos
				if (treasureCount == 0){
					treasureLocation = i;
				}
				treasureCount++;
			}
		}

		//store the handcount before the call to treasuremap()
		handCount = G.handCount[currentPlayer];

		//fill the player's deck with random cards. Make sure deck has no gold cards.
		for (i = 0; i < numCards; i++){
			chosenCard = J[rand() % 16];
			if (chosenCard != gold){
				G.deck[currentPlayer][i] = chosenCard;
			}
		}
		G.deckCount[currentPlayer] = numCards;

		//store the deckCount before call to treasureMap()
		deckCount = numCards;

		//don't call playTreasureMap() if there is no treasure_map in the hand
		if (treasureCount > 0){
			ret = playTreasureMap(&G, currentPlayer, treasureLocation);

			//only 1 treasure card in hand. Should only return -1
			if (treasureCount == 1){
				if (ret == -1){
					//printf("treasuremapFunction(): PASS hand with only 1 treasure map\n");
					passCount++;
					oneCardPass++;
				}
				else{
					//printf("treasuremapFunction(): FAIL hand with only 1 treasure map\n");
					failCount++;
					oneCardFail++;
				}
			}
			//more than 1 treasure card in hand.
			else{
				for (i = 0; i < G.handCount[currentPlayer]; i++){
					if (G.hand[currentPlayer][i] == treasure_map){
						foundTreasureMap++;
					}
				}

				//check that 2 treasure cards were removed from hand
				if (foundTreasureMap == treasureCount - 2){
					//printf("playTreasureMap(): PASS removing 2 treasure maps from hand\n");
					passCount++;
					twoCardPass++;
				}
				else{
					//printf("playTreasureMap(): FAIL removing 2 treasure maps from hand\n");
					failCount++;
					twoCardFail++;
				}

				for (i = 0; i < G.deckCount[currentPlayer]+4; i++){
					if (G.deck[currentPlayer][i] == gold){
						goldCount++;
					}
				}

				//check that 4 gold cards were added to deck
				if (goldCount == 4){
					//printf("playTreasureMap(): PASS adding 4 gold to deck\n");
					passCount++;
					addingGoldPass++;
				}
				else{
					//printf("playTreasureMap() FAIL adding 4 gold to deck\n");
					failCount++;
					addingGoldFail++;
				}
			}
		}
			memcpy (&G, &G2, sizeof(struct gameState));
	}

	printf("-------TESTS COMPLETE-------\n");
	printf("Number of tests with 1 treasure_map in hand:\n");
	printf("PASS: %d\n", oneCardPass);
	printf("Fail: %d\n", oneCardFail);
	printf("Number of tests with 2 treasure_map in hand:\n");
	printf("PASS: %d\n", twoCardPass);
	printf("FAIL: %d\n", twoCardFail);
	printf("Number of tests adding 4 gold cards to deck:\n");
	printf("PASS: %d\n", addingGoldPass);
	printf("FAIL: %d\n", addingGoldFail);
	printf("Total number of tests: \n");
	printf("PASS.... %d\n", passCount);
	printf("FAIL.... %d\n", failCount);



	return 0;
}
