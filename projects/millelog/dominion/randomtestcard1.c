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

   	}
}