#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// the below assertTrueTrue function was influenced by http://www.java-samples.com/showtutorial.php?tutorialid=451
#ifndef DEBUG
  #define assertTrue(x, y)
#else
  #define assertTrue(x, y) \
           if (! (x)) \
          { \
             printf("ERROR!! assertTrueTrue failed: (%s),", y); \
             printf(" function %s,", __FUNCTION__); \
             printf(" file: %s,", __FILE__); \
             printf(" line: %d\n", __LINE__); \
          }
#endif

int main() {
    int seed = 1000;
    int numPlayer = 2;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
      remodel, smithy, village, baron, great_hall};
    struct gameState G, testGameState;
    int thisPlayer = 0;
    int handpos = 0;
    int handCount = 9;
    int discarded = 1;


    printf ("\n---- TESTING discardCard() ----\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
    memcpy(&testGameState, &G, sizeof(struct gameState));

    G.hand[thisPlayer][0] = steward;
    G.hand[thisPlayer][1] = copper;
    G.hand[thisPlayer][2] = feast;
    G.hand[thisPlayer][3] = estate;
    G.hand[thisPlayer][4] = adventurer;
    G.hand[thisPlayer][5] = village;
    G.hand[thisPlayer][6] = village;
    G.hand[thisPlayer][7] = sea_hag;
    G.hand[thisPlayer][8] = council_room;

    G.handCount[thisPlayer] = 9;

    for(int j=0; j<10; j++) {
      int discardedCard = G.hand[thisPlayer][j];
      discardCard(j, thisPlayer, &G, 0);
      printf("hand count = %d, expected hand count = %d\n", G.handCount[thisPlayer], handCount - discarded);
      assertTrue(G.handCount[thisPlayer] == handCount - discarded, "Player's handcount after discard");

      // tests that the discarded cards are no longer in the player's hand
      for (int i=0; i<G.handCount[thisPlayer]; i++) {
        printf("(%d)", G.hand[thisPlayer][i]);
        assertTrue(G.hand[thisPlayer][i] != discardedCard, "hand does not contain discarded card");
      }
      handCount--;
    }

    printf("All tests done!\n");

    return 0;
}
