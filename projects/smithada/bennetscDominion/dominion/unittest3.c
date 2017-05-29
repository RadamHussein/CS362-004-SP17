#include "dominion.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(){
	struct gameState G;
	int ret;
	int i;
	int x;
	int randNum;
	int zeroCount;
	time_t t;

	///////Test1: Depleted province cards. Game should end///////

	//set province cards to 0
	G.supplyCount[province] = 0;

	ret = isGameOver(&G);

	if (ret == 1){
		printf("isGameOver(): PASS depleted province cards\n");
	}
	else{
		printf("isGameOver(): FAIL depleted province cards\n");
	}

	///////Test2: Refill province cards and randomly deplete stacks of supply cards///////

	//set province count higher than 0
	G.supplyCount[province] = 8;

	/* Intializes random number generator */
	srand((unsigned) time(&t));

	for (x = 0; x < 5; x++){

		zeroCount = 0;		

		for (i = 0; i < 25; i++){
			randNum = rand() % 9;
			if (randNum == 0){
				zeroCount++;
			}
			G.supplyCount[i] = randNum;
		}

		ret = isGameOver(&G);

		if(zeroCount < 3){
			if (ret == 0){
				printf("isGameOver(): PASS less than 3 supply piles depleted\n");
			}
			else{
				printf("isGameOver(): FAIL less than 3 supply piles depleted\n");
			}
		}
		else{
			if (ret == 1){
				printf("isGameOver(): PASS 3 supply piles depleted\n");
			}
			else{
				printf("isGameOver(): FAIL 3 supply piles depleted\n");
			}
		}
	}
	return 0;
}