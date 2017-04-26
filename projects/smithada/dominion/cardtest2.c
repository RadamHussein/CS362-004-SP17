#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void printDeck(int player, struct gameState *G){
	int i;

	printf("Player 1's deck:\n");
	for (i = 0; i < 10; i++){
		printf("%s\n", getCardName(G->deck[0][i]));
	}
	printf("\n");

	printf("Player 1's hand: \n");
	for (i = 0; i < 10; i++){
		printf("%s\n", getCardName(G->hand[0][i]));
	}

	printf("Player 1's discard: \n");
	for (i = 0; i < 10; i++){
		printf("%s\n", getCardName(G->discard[0][i]));
	}

}

int main(){
	int i;
	int ret;
	int players = 2;
	int originalDeckCount;
	int originalHandCount; 
	struct gameState G;
	struct gameState G2;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	           sea_hag, great_hall, smithy};

	ret = initializeGame(players, k, 10, &G);

	if (ret != 0){
		printf("adventurerFunction(): FAILED to initialize game\n");
	}

	//make a copy of the initial struct
	memcpy(&G2, &G, sizeof(struct gameState));

	originalDeckCount = G.deckCount[0];
	originalHandCount = G.handCount[0];

	for (i = 0; i < 5; i++){
		G.hand[0][i] = smithy;

		//play smithy
		smithyFunction(0, 0, &G);

		printf("\n");
		printf("Playing smithy from hand position %d...\n", i+1);
		if (G.deckCount[0] == (originalDeckCount - 3) && G.handCount[0] == (originalHandCount + 2)){
		printf("smithyFunction(): PASS correctly gaining 3 cards and removing smithy from hand\n");
		}
		else{
			printf("smithyFunction(): FAIL correctly gaining 3 cards and removing smithy from hand\n");
		}

		//copy initial struct back into G
		memcpy(&G, &G2, sizeof(struct gameState));
		G.deckCount[0] = originalDeckCount;
		G.handCount[0] = originalHandCount;
	}

	return 0;
}