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

void buildHand(struct gameState *G){
	G->hand[1][0] = treasure_map;
	G->hand[1][1] = copper;
	G->hand[1][2] = smithy;
	G->hand[1][3] = gold;
	G->hand[1][4] = duchy;

	G->handCount[1] = 5;
}

int main(){
	int foundTreasureMap = 0;
	int treasureAdded = 0;
	int i;
	int ret;
	struct gameState G;
	int players = 2;
	int passCount = 0;
	int failCount = 0;
	int gameCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	           sea_hag, great_hall, smithy};

	ret = initializeGame(players, gameCards, 10, &G);

	if (ret != 0){
		printf("adventurerFunction(): FAILED to initialize game\n");
	}

	buildHand(&G);

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

	//test hand with only 1 treasure map
	ret = playTreasureMap(&G, 1, 0);

	if (ret == -1){
		printf("treasuremapFunction(): PASS hand with only 1 treasure map\n");
		passCount++;
	}
	else{
		printf("treasuremapFunction(): FAIL hand with only 1 treasure map\n");
		failCount++;
	}

	//Now add a second treasure map to the hand
	G.hand[1][2] = treasure_map;

	//test with 2 treasure maps
	ret = playTreasureMap(&G, 1 ,0);

	for (i = 0; i < 5; i++){
		if (G.hand[1][i] == treasure_map){
			foundTreasureMap = 1;
		}
	}

	//does the function return 1 for success and find no more treasure maps in the hand
	if (ret == 1 && foundTreasureMap == 0){
		printf("treasuremapFunction(): PASS hand with 2 treasure maps\n");
		passCount++;
	}
	else{
		printf("treasuremapFunction(): FAIL hand with 2 treasure maps\n");
		failCount++;
	}

	treasureAdded = 0;
	for (i = 0; i < 15; i++){
		if (G.deck[1][i] == gold){
			treasureAdded++;
		}
	}

	if (treasureAdded == 4){
		printf("treasuremapFunction(): PASS gold added to deck\n");
		passCount++;
	}
	else{
		printf("treasuremapFunction(): FAIL gold added to deck\n");
		failCount++;
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
