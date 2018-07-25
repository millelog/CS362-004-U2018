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
    int k[10] = {adventurer, council_room, gold, silver, mine
                , remodel, smithy, copper, baron, great_hall};
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
        testG.hand[p][0] = adventurer;
        
        memcpy(&G, &testG, sizeof(struct gameState));


        cardEffect(adventurer, 0, 0, 0, &testG, 0, 0);

        if(testG.coins <= G.coins){
            printf("ERROR: Coins were not added to the hand after adventurer was played. \n");
        }
        assert(testG.deckCount[p]+testG.handCount[p]+testG.discardCount[p] == G.deckCount[p] + G.handCount[p] + G.discardCount[p]); 


        printf("Test when deck is populated for player %d\n", p);
        memset(&testG, 23, sizeof(struct gameState));
        initializeGame(numPlayer, k, seed, &testG);
        testG.deckCount[p] = 0;
        testG.discardCount[p] = deckCount;
        for(i=0; i<deckCount; i++){
            testG.discard[p][i] = k[i%10];
        }
        testG.handCount[p] = 1;
        testG.hand[p][0] = adventurer;
        
        memcpy(&G, &testG, sizeof(struct gameState));


        cardEffect(adventurer, 0, 0, 0, &testG, 0, 0);

        if(testG.coins <= G.coins){
            printf("ERROR: Coins were not added to the hand after adventurer was played. \n");
        }

        assert(testG.deckCount[p]+testG.handCount[p]+testG.discardCount[p] == G.deckCount[p] + G.handCount[p] + G.discardCount[p]); 

    }
     printf("---------- TESTING drawCard() COMPLETE ----------\n\n\n");

}


