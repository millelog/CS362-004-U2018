#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

int main(){
    int i, p;
    int seed = 1110;
    int numPlayer=2;
    int deckCount=15;
    int k[10] = {adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, baron, great_hall};
    struct gameState testG;



    for(p=0; p<numPlayer; p++){
        printf("----- test if drawcard with no deck works -----\n");
        memset(&testG, 23, sizeof(struct gameState));
        initializeGame(numPlayer, k, seed, &testG);
        testG.deckCount[p] = 0;
        testG.discardCount[p] = deckCount;
        for(i=0; i<deckCount; i++){
            testG.discard[p][i] = k[i%10];
        }
        drawCard(p, &testG);
        assert(testG.deckCount[p] == deckCount-1);
        assert(testG.discardCount[p] == 0);  


        printf("----- Test if drawCard works with existing deck -----\n");
        memset(&testG, 23, sizeof(struct gameState));
        initializeGame(numPlayer, k, seed, &testG);
        testG.deckCount[p] = deckCount;

        for(i=0; i<deckCount; i++){
            testG.deck[p][i] = k[i%10];
        }
        drawCard(p, &testG);
        assert(testG.deckCount[p] == deckCount-1);
    }
     printf("---------- TESTING drawCard() COMPLETE ----------\n\n\n");

}


