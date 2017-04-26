#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void buildHand(struct gameState *G){
	G->hand[0][0] = estate;
	G->hand[0][1] = copper;
	G->hand[0][2] = smithy;
	G->hand[0][3] = gold;
	G->hand[0][4] = duchy;
}

void checkReturnValue(int ret, int choice){
	if (ret == -1){
		printf("mineFunction(): PASS choice %d not a valid card\n", choice);
	}
	else{
		printf("mineFunction(): FAIL choice %d not a valid card\n", choice);
	}
}

int main(){
	int i;
	int failDiscard = 0;
	int passGainCard = 0;
	int ret;
	int players = 2;
	struct gameState G;
	//int testCards[10] = {mine, adventurer, estate, gold, duchy, gardens, silver, copper, estate, smithy};
	int gameCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	           sea_hag, great_hall, smithy};
	
	ret = initializeGame(players, gameCards, 10, &G);

	if (ret != 0){
		printf("adventurerFunction(): FAILED to initialize game\n");
	}

	//test choice 1 < copper
	ret = mineFunction(0, 0, 1, &G, 0);

	checkReturnValue(ret, 1);

	//test choice 1 > gold
	ret = mineFunction(0, 2, 1, &G, 2);

	checkReturnValue(ret, 1);

	//test valid choice 1, invalid choice 2
	ret = mineFunction(0, 1, estate, &G, 1);

	checkReturnValue(ret, 2);

	ret = mineFunction(0, 1, copper, &G, 1);

	checkReturnValue(ret, 2);

	//test passing choice 1 + 3 > choice 2
	ret = mineFunction(0, 2, gold, &G, 1);

	if (ret == -1){
		printf("mineFunction(): FAIL value of choice1 + 3 > choice2\n");
	}
	else{
		printf("mineFunction(): PASS value of choice1 + 3 > choice2\n");
	}

	//test passing choice 1 + 3 < choice 2
	ret = mineFunction(0, 0, gold, &G, 1);

	if (ret == -1){
		printf("mineFunction(): PASS value of choice1 + 3 < choice2\n");
	}
	else{
		printf("mineFunction(): FAIL value of choice1 + 3 < choice2\n");
	}

	//test
	ret = mineFunction(0, 2, gold, &G, 0);

	for (i = 0; i < 5; i++){
		if (G.hand[0][i] == smithy){
			failDiscard = 1;
		}

		if (G.hand[0][i] == gold){
			passGainCard = 1;
		}
	}

	if (failDiscard == 0 && passGainCard == 1){
		printf("mineFunction(): PASS trashing card from hand and receiving selected treasure card\n");
	}
	else{
		printf("mineFunction(): FAIL trashing card from hand and receiving selected treasure card\n");
	}

	return 0;
}