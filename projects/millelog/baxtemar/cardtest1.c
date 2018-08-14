#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "smithy"

int main(){
    int i, p;
    int seed = 1110;
    int numPlayer=2;
    int deckCount=15;
    int k[10] = {adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    for(p=0; p<numPlayer; p++){

        printf("Test when deck is empty for player %d\n", p);
        memset(&testG, 23, sizeof(struct gameState));
        initializeGame(numPlayer, k, seed, &testG);
        testG.deckCount[p] = 0;
        testG.discardCount[p] = deckCount;
        for(i=0; i<deckCount; i++){
            testG.discard[p][i] = k[i%10];
        }
        testG.handCount[p] = 1;
        testG.hand[p][0] = smithy;
        
        memcpy(&G, &testG, sizeof(struct gameState));


        smithyEffect(&testG, 0);
        //assert(testG.deckCount[p]+testG.discardCount[p] == deckCount-3);
        assert(testG.discardCount[p] == 0); 
        assert(testG.handCount[p] == G.handCount[p]+2); 


        printf("Test when deck is populated for player %d\n", p);
        memset(&testG, 23, sizeof(struct gameState));
        initializeGame(numPlayer, k, seed, &testG);
        testG.deckCount[p] = deckCount;
        testG.discardCount[p] = 0;
        for(i=0; i<deckCount; i++){
            testG.deck[p][i] = k[i%10];
        }
        testG.handCount[p] = 1;
        testG.hand[p][0] = smithy;
        
        memcpy(&G, &testG, sizeof(struct gameState));


        smithyEffect(&testG, 0);

        //assert(testG.deckCount[p]+testG.discardCount[p] == deckCount-3);
        assert(testG.handCount[p] == G.handCount[p]+2);
    }
     printf("---------- TESTING drawCard() COMPLETE ----------\n\n\n");

}


