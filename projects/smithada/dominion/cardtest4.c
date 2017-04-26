#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void buildHand(struct gameState *G){
	G->hand[0][0] = treasure_map;
	G->hand[0][1] = copper;
	G->hand[0][2] = smithy;
	G->hand[0][3] = gold;
	G->hand[0][4] = duchy;
}

int main(){
	int foundTreasureMap = 0;
	int treasureAdded = 0;
	int i;
	int ret;
	struct gameState G;
	int players = 2;
	int gameCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	           sea_hag, great_hall, smithy};
	
	ret = initializeGame(players, gameCards, 10, &G);

	if (ret != 0){
		printf("adventurerFunction(): FAILED to initialize game\n");
	}

	//test hand with only 1 treasure map
	ret = treasuremapFunction(0, &G, 0);

	if (ret == -1){
		printf("treasuremapFunction(): PASS hand with only 1 treasure map\n");
	}
	else{
		printf("treasuremapFunction(): FAIL hand with only 1 treasure map\n");
	}

	//test that 1 treasure map was removed from hand
	for (i = 0; i < 5; i++){
		if (G.hand[0][i] == treasure_map){
			foundTreasureMap = 1;
		}
	}

	if (foundTreasureMap == 1){
		printf("treasuremapFunction(): FAIL removing single treasure_map from hand\n");
		foundTreasureMap = 0;
	}
	else{
		printf("treasuremapFunction(): PASS removing single treasure_map from hand\n");
	}

	//Now add a second treasure map to the hand
	G.hand[0][2] = treasure_map;

	//test with 2 treasure maps
	ret = treasuremapFunction(0, &G, 0);

	for (i = 0; i < 5; i++){
		if (G.hand[0][i] == treasure_map){
			foundTreasureMap = 1;
		}
	}

	//does the function return 1 for success and find no more treasure maps in the hand
	if (ret == 1 && foundTreasureMap == 0){
		printf("treasuremapFunction(): PASS hand with 2 treasure maps\n");
	}
	else{
		printf("treasuremapFunction(): FAIL hand with 2 treasure maps\n");
	}

	for (i = 0; i < 11; i++){
		if (G.deck[0][i] == gold){
			treasureAdded = 1;
		}
	}

	if (treasureAdded == 1){
		printf("treasuremapFunction(): PASS gold added to deck\n");
	}
	else{
		printf("treasuremapFunction(): FAIL gold added to deck\n");
	}



	return 0;
}