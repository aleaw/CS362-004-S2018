#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
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
    int expectedCurrentPlayer = 0;

    printf ("\n---- TESTING whoseTurn() with 2 players ----\n");
    numPlayer = 2;
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
    memcpy(&testGameState, &G, sizeof(struct gameState));

    for(int i = 0; i<15; i++) {
      printf("player = %d, expected player = %d\n", whoseTurn(&G), expectedCurrentPlayer);
      assertTrue(expectedCurrentPlayer == whoseTurn(&G), "Whose turn");
      printf("End of player %d's turn\n", expectedCurrentPlayer);
      endTurn(&G);

      if(expectedCurrentPlayer == 0)
        expectedCurrentPlayer = 1;
      else
        expectedCurrentPlayer = 0;
    }

    printf ("\n---- TESTING whoseTurn() with 3 players ----\n");
    numPlayer = 3;
    expectedCurrentPlayer = 0;
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game

    for(int i = 0; i<15; i++) {
      printf("player = %d, expected player = %d\n", whoseTurn(&G), expectedCurrentPlayer);
      assertTrue(expectedCurrentPlayer == whoseTurn(&G), "Whose turn");
      printf("End of player %d's turn\n", expectedCurrentPlayer);
      endTurn(&G);

      if(expectedCurrentPlayer == 0)
        expectedCurrentPlayer = 1;
      else if(expectedCurrentPlayer == 1)
        expectedCurrentPlayer = 2;
      else
        expectedCurrentPlayer = 0;
    }

    printf ("\n---- TESTING whoseTurn() with 4 players ----\n");
    numPlayer = 4;
    expectedCurrentPlayer = 0;
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game

    for(int i = 0; i<15; i++) {
      printf("player = %d, expected player = %d\n", whoseTurn(&G), expectedCurrentPlayer);
      assertTrue(expectedCurrentPlayer == whoseTurn(&G), "Whose turn");
      printf("End of player %d's turn\n", expectedCurrentPlayer);
      endTurn(&G);

      if(expectedCurrentPlayer == 0)
        expectedCurrentPlayer = 1;
      else if(expectedCurrentPlayer == 1)
        expectedCurrentPlayer = 2;
      else if(expectedCurrentPlayer == 2)
        expectedCurrentPlayer = 3;
      else
        expectedCurrentPlayer = 0;
    }

    printf("All tests passed!\n");

    return 0;
}
