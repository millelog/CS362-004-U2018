#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

int main(){
    int i, r, p;
    int testCase = 0;
    int seed = 1110;
    int numPlayer=2;
    int deckCount=15;
    int k[10] = {adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;


    memset(&G, 23, sizeof(struct gameState));
    r = initializeGame(numPlayer, k, seed, &G);

    for(p=0; p<numPlayer; p++){
        G.deckCount[p] = deckCount;
        for(i=0; i<deckCount; i++){
            G.deck[p][i] = k[i%10];
        }
        memcpy(&testG, &G, sizeof(struct gameState));
        shuffle(p, &testG);
        i=0;
        while(i<deckCount && testCase==0){
            if(testG.deck[p][i] != G.deck[p][i]){
                printf("---------- Decks differ for player %d ----------\n", p);
                testCase=1;
            }
            i++;
        }
        testCase=0;
    }
     printf("---------- TESTING SHUFFLE() COMPLETE ----------\n");

}


