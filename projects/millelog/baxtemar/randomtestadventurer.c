#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "rngs.h"

#define TESTCARD "adventurer"


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
    	//randomly populate the cards for this test
    	for(i=0; i<10; i++){
    		k[i]=allCards[abs(rand()%27)];
    	}

	    for(p=0; p<numPlayer; p++){

	    	seed = abs(rand()%2000)+1;
	        memset(&testG, 23, sizeof(struct gameState));
	        initializeGame(numPlayer, k, seed, &G);
	        //Half of max size to ensure doesn't go over if they have to be shuffled into one
	        G.deckCount[p] = abs(rand()%(MAX_DECK/2));
	        G.handCount[p] = abs(rand()%(MAX_HAND-4)); //for smithy to add later and the three to draw from smithy effect
	        G.discardCount[p] = abs(rand()%(MAX_DECK/2));
	        //Randomly fill the gamestate
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
	        //add adventurer to hand
	        G.handCount[p]++;
	        G.hand[p][G.handCount[p]-1] = adventurer;

	        memcpy(&testG, &G, sizeof(struct gameState));
	        adventurerEffect(&testG);

			//cardEffectAdventurer(adventurer, 0, 0, 0, &testG, testG.handCount[p]-1, 0, p);
			//ensure discard/deck counts and hand count
			//assert(testG.deckCount[p]+testG.discardCount[p] == G.discardCount[p]+G.deckCount[p]-2);
	        assert(testG.handCount[p] == G.handCount[p]+2);

	        //ensure cards added are treasure
	        for(i=testG.handCount[p]-2; i<testG.handCount[p]; i++){
	        	assert(testG.hand[p][i] == copper || testG.hand[p][i] == silver || testG.hand[p][i] == gold);
	        }

	        //ensure nothing else in the hand was mutated
	        for(i=0; i<G.handCount[p]-1; i++){
	        	assert(testG.hand[p][i] == G.hand[p][i]);
	        }
	   	}
	    printf("Test: %d ", j);
	    if(j%10==0){
	    	printf("\n");
	    }
    }
    printf("\nAll %d tests for cardEffect%s are valid.\n", numTests, TESTCARD);
}