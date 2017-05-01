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
	for (i = 0; i < 9; i++){
		printf("%s\n", getCardName(G->deck[0][i]));
	}
	printf("\n");

	printf("Player 1's hand: \n");
	for (i = 0; i < 9; i++){
		printf("%s\n", getCardName(G->hand[0][i]));
	}

	printf("Player 1's discard: \n");
	for (i = 0; i < 9; i++){
		printf("%s\n", getCardName(G->discard[0][i]));
	}
}

int main(){
	int i;
	int ret;
	int drawntreasure = 0;
	int players = 2;
	struct gameState G;
	struct gameState G2;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	           sea_hag, great_hall, smithy};

	ret = initializeGame(players, k, 10, &G);

	if (ret != 0){
		printf("adventurerFunction(): FAILED to initialize game\n");
	}

	G.deck[0][0] = smithy;
	G.deck[0][1] = estate;
	G.deck[0][2] = silver;
	G.deck[0][3] = embargo;
	G.deck[0][4] = mine;
	G.deck[0][5] = duchy;
	G.deck[0][6] = gold;
	G.deck[0][7] = mine;
	G.deck[0][8] = estate;

	memcpy (&G2, &G, sizeof(struct gameState));

	adventurerFunction(0, &G, drawntreasure);

	for (i = 0; i < 9; i++){
		if (G.deck[0][i] != G2.deck[0][i]){
			drawntreasure++;
		}
	}

	if(drawntreasure < 2){
		printf("adventurerFunction(): FAIL drawing treasure from deck\n");
		printf("adventurerFunction(): TEST FAILED\n");
	}
	else{
		printf("adventurerFunction(): PASS drawing treasure from deck\n");
	}

	

	return 0; 
}