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
    int k[10] = {adventurer, council_room, feast, gardens, mine,
      remodel, smithy, village, baron, great_hall};
    struct gameState G, testGameState;

    printf ("\n---- TESTING isGameOver() ----\n");

    printf ("\n---- TEST 1: 3 supply piles are empty ----\n");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game

    G.supplyCount[steward] = 0;
    G.supplyCount[village] = 0;
    G.supplyCount[baron] = 0;

    memcpy(&testGameState, &G, sizeof(struct gameState));
    printf("Report if game is over: %d\n", isGameOver(&testGameState));
    assertTrue(isGameOver(&testGameState), "isGameOver");

    printf ("\n---- TEST 2: all provinces are bought ----\n");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game

    G.supplyCount[province] = 0;
    memcpy(&testGameState, &G, sizeof(struct gameState));
    printf("Report if game is over: %d (1 means yes, 0 means no)\n", isGameOver(&testGameState));
    assertTrue(isGameOver(&testGameState), "isGameOver");

    printf ("\n---- TEST 3: only 2 supply piles are empty ----\n");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game

    G.supplyCount[curse] = 0;
    G.supplyCount[copper] = 0;
    G.supplyCount[province] = 1;

    memcpy(&testGameState, &G, sizeof(struct gameState));
    printf("is game over? %d, expected: %d (1 means game is over, 0 means game not over)\n", isGameOver(&testGameState), 0);
    assertTrue(isGameOver(&testGameState) == 0, "isGameOver");

    printf ("\n---- TEST 4: only 2 supply piles are empty but one is province----\n");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game

    G.supplyCount[curse] = 0;
    G.supplyCount[adventurer] = 5;
    G.supplyCount[province] = 0;

    memcpy(&testGameState, &G, sizeof(struct gameState));
    printf("is game over? %d, expected: %d (1 means game is over, 0 means game not over)\n", isGameOver(&testGameState), 1);
    assertTrue(isGameOver(&testGameState), "isGameOver");

    printf("All tests done!\n");

    return 0;
}
