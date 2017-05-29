#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	int i;
	struct gameState G;
	struct gameState G2;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	           sea_hag, great_hall, smithy};
	int cardsNotInGame[10] = {council_room, feast, remodel, baron, steward, tribute, ambassador, outpost,
				salvager, treasure_map};
	char *cardsChanged[3] = {"discard", "deck", "hand"};
	int players = 2;
	int ret;

	ret = initializeGame(players, k, 10, &G);

	if (ret !=0){
		printf("INITIALIZATION FAILED\n");
		return 0;
	}

	///////Test1: Check all cards not in game///////

	for (i = 0; i < sizeof(cardsNotInGame)/sizeof(cardsNotInGame[0]); i++){
		ret = gainCard(cardsNotInGame[i], &G, 1, 1);

		if (ret == -1){
			printf("gainCard(): PASS passing card not in game\n");
		}
		else{
			printf("gainCard(): FAIL passing card not in game\n");
		}
	}

	///////Test2: Check that changes have been made to hands, deck and discard for players///////
	memcpy (&G2, &G, sizeof(struct gameState));

	for (i = 0; i < 3; i++){
		ret = gainCard(adventurer, &G, i, 1);

		if (ret != 0){
			printf("gainCard(): FAIL passing valid game card to %s\n", cardsChanged[i]);
		}
		else{
			if (memcmp(&G, &G2, sizeof(struct gameState)) == 0){
			  printf("gainCard(): FAIL passing valid game card to %s\n", cardsChanged[i]);
			}
			else{
			  printf("gainCard(): PASS passing valid game card to %s\n", cardsChanged[i]);
			  memcpy (&G, &G2, sizeof(struct gameState));			//copy G2 back to G
			}
		}
	}

	
	return 0;
}

	