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
	int chosenCard;
	int currentPlayer;
	int currentHandPos;
	int originalDeckCount;
	int originalHandCount;
	int passCount = 0;
	int failCount = 0;
	struct gameState G;
	struct gameState G2;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	           sea_hag, great_hall, smithy};

	int J[16] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
			sea_hag, great_hall, smithy, copper, gold, silver, duchy, province, estate};
	srand(time(NULL));

	ret = initializeGame(players, k, 10, &G);

	if (ret != 0){
		printf("FAILED to initialize game\n");
	}

	//make a copy of the initial struct
	memcpy(&G2, &G, sizeof(struct gameState));

	for (i = 0; i < 2000; i++){
		currentPlayer = rand() % 4;

		//get a random handCount number
		originalHandCount = rand() % 500;
		G.handCount[currentPlayer] = originalHandCount;

		//fill player's hand with random cards. Keep track of the first two treasure_map cards.
		for(v = 0; v < originalHandCount; v++){
			chosenCard = J[rand() % 16];
			G.hand[currentPlayer][v] = chosenCard;
			if(chosenCard == smithy){
				currentHandPos = v;
			}
		}

		//get a random handCount number
		originalDeckCount = rand() % 500;
		G.deckCount[currentPlayer] = originalDeckCount;

		//fill player's hand with random cards. Keep track of the first two treasure_map cards.
		for(v = 0; v < originalDeckCount; v++){
			chosenCard = J[rand() % 16];
			G.hand[currentPlayer][v] = chosenCard;
		}

		//play smithy
		//smithyFunction(currentPlayer, currentHandPos, &G);

		//play smithy()
		playSmithy(&G, currentPlayer, currentHandPos);

		if (G.handCount[currentPlayer] == (originalHandCount + 2)){
			if(G.hand[currentPlayer][currentHandPos] == smithy){
				failCount++;
			}
			else{
				passCount++;
			}

		}
		else{
			failCount++;
		}

		//copy initial struct back into G
		memcpy(&G, &G2, sizeof(struct gameState));
		G.deckCount[currentPlayer] = originalDeckCount;
		G.handCount[currentPlayer] = originalHandCount;
	}
	printf("Test completed:\n");
	printf("PASSED.... %d\n", passCount);
	printf("FAILED.... %d\n", failCount);

	return 0;
}
