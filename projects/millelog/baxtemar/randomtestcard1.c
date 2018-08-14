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
	int numTests=2000;
    int i, j, p, seed, numPlayer, k[10];
    int allCards[27] = {adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, baron, great_hall
                , curse, estate, duchy, province, copper, silver, gold
                , minion, steward, tribute, ambassador, cutpurse, embargo
                , outpost, salvager, sea_hag, treasure_map };
    struct gameState G, testG;
    
    srand(time(NULL));

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    for(j=0; j<numTests; j++){

    	numPlayer = abs(rand()%MAX_PLAYERS);

    	for(i=0; i<10; i++){
    		k[i]=allCards[abs(rand()%27)];
    	}

	    for(p=0; p<numPlayer; p++){

	    	seed = abs(rand()%2000)+1;
	        memset(&testG, 23, sizeof(struct gameState));
	        initializeGame(numPlayer, k, seed, &G);

	        G.deckCount[p] = abs(rand()%(MAX_DECK/2));
	        G.handCount[p] = abs(rand()%(MAX_HAND-4)); //for smithy to add later and the three to draw from smithy effect
	        G.discardCount[p] = abs(rand()%(MAX_DECK/2));

	        for(i=0; i<G.deckCount[p]; i++){
	        	G.deck[p][i]=k[abs(rand()%10)];
	        }
	        for(i=0; i<G.handCount[p]; i++){
	        	G.hand[p][i]=k[abs(rand()%10)];
	        }
	        for(i=0; i<G.discardCount[p]; i++){
	        	G.discard[p][i]=k[abs(rand()%10)];
	        }
	        //ensure initial conditions
	        for(i=0; i<7; i++){
	        	G.deckCount[p]++;
	        	G.deck[p][G.deckCount[p]-1] = copper;
	        }
	        for(i=0; i<3; i++){
	        	G.deckCount[p]++;
	        	G.deck[p][G.deckCount[p]-1] = duchy;
	        }
	        //add smithy
	        G.handCount[p]++;
	        G.hand[p][G.handCount[p]-1] = smithy;

	        memcpy(&testG, &G, sizeof(struct gameState));

			cardEffectSmithy(smithy, 0, 0, 0, &testG, testG.handCount[p]-1, 0, p);
			assert(testG.deckCount[p]+testG.discardCount[p] == G.discardCount[p]+G.deckCount[p]-2);
	        assert(testG.handCount[p] == G.handCount[p]+2);


	        for(i=0; i<G.handCount[p]-3; i++){
	        	assert(testG.hand[p][i] == G.hand[p][i]);
	        }
	   	}
	    printf("Test: %d   ", j);
	    if(j%10==0){
	    	printf("\n");
	    }
    }
    printf("\nAll %d tests for cardEffect%s are valid.\n", numTests, TESTCARD);
}