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
		printf("mine(): PASS choice %d not a valid card\n", choice);
	}
	else{
		printf("mine(): FAIL choice %d not a valid card\n", choice);
	}
}

int main(){
	int i;
	int failDiscard = 0;
	int passGainCard = 0;
	int ret;
	int players = 2;
	struct gameState G;
	int bonus = 0;
	int handPos = 0;
	int choice1;
	int choice2;
	int choice3 = 0;
	int card;
	//int testCards[10] = {mine, adventurer, estate, gold, duchy, gardens, silver, copper, estate, smithy};
	int gameCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	           sea_hag, great_hall, smithy};

	ret = initializeGame(players, gameCards, 10, &G);

	if (ret != 0){
		printf("mine(): FAILED to initialize game\n");
	}

	card = mine;

	G.whoseTurn = 0;

	choice1 = 0;
	choice2 = 1;
	//test choice 1 < copper
	ret = cardEffect(card, choice1, choice2, choice3, &G, handPos, &bonus);

	checkReturnValue(ret, 1);

	choice1 = 2;
	choice2 = 1;
	//test choice 1 > gold
	ret = cardEffect(card, choice1, choice2, choice3, &G, handPos, &bonus);

	checkReturnValue(ret, 1);

	choice1 = 1;
	choice2 = estate;
	//test valid choice 1, invalid choice 2
	ret = cardEffect(card, choice1, choice2, choice3, &G, handPos, &bonus);

	checkReturnValue(ret, 2);

	choice1 = 1;
	choice2 = copper;
	ret = cardEffect(card, choice1, choice2, choice3, &G, handPos, &bonus);

	checkReturnValue(ret, 2);

	choice1 = 2;
	choice2 = gold;
	//test passing choice 1 + 3 > choice 2
	ret = cardEffect(card, choice1, choice2, choice3, &G, handPos, &bonus);

	if (ret == -1){
		printf("mine(): FAIL value of choice1 + 3 > choice2\n");
	}
	else{
		printf("mine(): PASS value of choice1 + 3 > choice2\n");
	}

	choice1 = 0;
	choice2 = gold;
	//test passing choice 1 + 3 < choice 2
	ret = cardEffect(card, choice1, choice2, choice3, &G, handPos, &bonus);

	if (ret == -1){
		printf("mine(): PASS value of choice1 + 3 < choice2\n");
	}
	else{
		printf("mine(): FAIL value of choice1 + 3 < choice2\n");
	}

	//test
	choice1 = 2;
	choice2 = gold;
	ret = cardEffect(card, choice1, choice2, choice3, &G, handPos, &bonus);

	for (i = 0; i < 5; i++){
		if (G.hand[0][i] == smithy){
			failDiscard = 1;
		}

		if (G.hand[0][i] == gold){
			passGainCard = 1;
		}
	}

	if (failDiscard == 0 && passGainCard == 1){
		printf("mine(): PASS trashing card from hand and receiving selected treasure card\n");
	}
	else{
		printf("mine(): FAIL trashing card from hand and receiving selected treasure card\n");
	}

	return 0;
}
