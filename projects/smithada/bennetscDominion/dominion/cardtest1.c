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
	int ret;
	int temphand[MAX_HAND];
	int players = 4;
	int passCount = 0;
	int failCount = 0;
	struct gameState G;
	struct gameState G2;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	           sea_hag, great_hall, smithy};

	srand(time(NULL));

	ret = initializeGame(players, k, 10, &G);

	if (ret != 0){
		printf("FAILED to initialize game\n");
	}

	memcpy (&G2, &G, sizeof(struct gameState));

	G.hand[1][0] = smithy;
	G.hand[1][1] = adventurer;
	G.hand[1][2] = gold;
	G.hand[1][3] = estate;
	G.hand[1][4] = copper;

	G.handCount[1] = 5;

	G.deck[1][0] = gardens;
	G.deck[1][1] = sea_hag;
	G.deck[1][2]	= silver;
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

	playAdventurer(&G, temphand, 1);

	if(G.handCount[1] == 7){
		printf("playAdventurer(): PASSED handCount\n");
		passCount++;
	}
	else{
		printf("playAdventurer(): FAILED handCount\n");
		failCount++;
	}

	if(G.deckCount[1] == 5){
		printf("playAdventurer(): PASSED deckCount\n");
		passCount++;
	}
	else{
		printf("playAdventurer(): FAILED deckCount\n");
		failCount++;
	}

	if(G.discardCount[1] == 4){
		printf("playAdventurer(): PASSED discardCount\n");
		passCount++;
	}
	else{
		printf("playAdventurer(): FAILED discardCount\n");
		failCount++;
	}

	if(passCount == 3){
		printf("playAdventurer(): TESTS PASSED\n");
	}
	else{
		printf("playAdventurer(): TESTS FAILED\n");
	}


	return 0;
}
