#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "rngs.h"

#define TESTCARD "smithy"

int main(){
	int numberOfTests=5000;
    int i, j, p, seed, numPlayer;
    int k[27] = {adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, baron, great_hall
                , curse, estate, duchy, province, copper, silver, gold
                , minion, steward, tribute, ambassador, cutpurse, embargo
                , outpost, salvager, sea_hag, treasure_map };
    struct gameState G, testG;

    srand(time(NULL));

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    for(j=0; j<numberOfTests; j++){
    	numPlayer = rand()%MAX_PLAYERS;
	    for(p=0; p<numPlayer; p++){
	    	seed = rand()%2000;
	        memset(&testG, 23, sizeof(struct gameState));
	        initializeGame(numPlayer, k, seed, &testG);

	        G.deckCount[p] = rand()%(MAX_DECK/2);
	        G.handCount[p] = rand()%MAX_HAND-4; //for smithy to add later and the three to draw from smithy effect
	        G.discardCount[p] = rand()%(MAX_DECK/2);

	        for(i=0; i<G.deckCount[p]; i++){
	        	G.deck[p][i]=k[rand()%27];
	        }
	        for(i=0; i<G.handCount[p]; i++){
	        	G.hand[p][i]=k[rand()%27];
	        }
	        for(i=0; i<G.discardCount[p]; i++){
	        	G.discard[p][i]=k[rand()%27];
	        }
	        //add smithy
	        G.handCount[p]++;
	        G.hand[p][G.handCount[p]-1] = smithy;

	        memcpy(&G, &testG, sizeof(struct gameState));

			cardEffectSmithy(smithy, 0, 0, 0, &testG, G.handCount[p]-1, 0, p);

			assert(testG.deckCount[p] == G.deckCount[p]-3);
	        assert(testG.handCount[p] == G.handCount[p]+2);

	        for(i=0; i<G.handCount[p]-3; i++){
	        	assert(testG.hand[p][i] == G.hand[p][i]);
	        }
	   	}
    }
    printf("All %d tests for cardEffectSmithy are valid.\n", numberOfTests);
}