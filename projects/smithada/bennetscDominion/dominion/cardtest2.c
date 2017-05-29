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
	int ret;
	int players = 2;
	int originalDeckCount;
	int originalHandCount;
	int passCount = 0;
	int failCount = 0;
	struct gameState G;
	struct gameState G2;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	           sea_hag, great_hall, smithy};

	ret = initializeGame(players, k, 10, &G);

	if (ret != 0){
		printf("playSmithy(): FAILED to initialize game\n");
	}

	//initialize player's hand
	G.hand[1][0] = copper;
	G.hand[1][1] = adventurer;
	G.hand[1][2] = gold;
	G.hand[1][3] = estate;
	G.hand[1][4] = copper;

	G.handCount[1] = 5;

	//initialize player's deck
	G.deck[1][0] = gardens;
	G.deck[1][1] = sea_hag;
	G.deck[1][2] = silver;
	G.deck[1][3] = province;
	G.deck[1][4] = mine;
	G.deck[1][5] = copper;
	G.deck[1][6] = adventurer;
	G.deck[1][7] = great_hall;
	G.deck[1][8] = village;
	G.deck[1][9]= copper;
	G.deck[1][10] = mine;

	G.deckCount[1] = 11;
	G.discardCount[1] = 0;

	originalDeckCount = G.deckCount[1];
	originalHandCount = G.handCount[1];

	//make a copy of the initial struct
	memcpy(&G2, &G, sizeof(struct gameState));

	for (i = 0; i < 5; i++){
		G.hand[1][i] = smithy;

		/*
		printf("-------------------------------------\n");
		printf("Hand before call to smithy: \n");
		displayHand(1, &G, 5);
		*/

		//play smithy
		playSmithy(&G, 1, i);

		/*
		printf("-------------------------------------\n");
		printf("Hand after call to smithy: \n");
		displayHand(1, &G, 8);

		printf("-------------------------------------\n");
		printf("Playing smithy from hand position %d...\n", i+1);
		printf("handCount: %d\n", G.handCount[1]);
		printf("deckCount: %d\n", G.deckCount[1]);
		*/
		if (G.deckCount[1] == (originalDeckCount - 3) && G.handCount[1] == (originalHandCount + 2)){
			printf("playSmithy(): PASS gaining 3 cards from deck and removing smithy from hand\n");
			passCount++;
		}
		else{
			printf("playSmithy(): FAIL gaining 3 cards from deck and removing smithy from hand\n");
			failCount++;
		}

		//copy initial struct back into G
		memcpy(&G, &G2, sizeof(struct gameState));
		G.deckCount[1] = originalDeckCount;
		G.handCount[1] = originalHandCount;
	}

	printf("-------TESTS COMPLETE-------\n");
	if (failCount == 0){
		printf("PASSED: all tests\n");
	}
	else{
		printf("FAILED: one or more tests\n");
	}

	return 0;
}
