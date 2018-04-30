/* -----------------------------------------------------------------------
 * Code was influenced by the Demonstration file cardTests.c that was
 * provided to us.
 * -----------------------------------------------------------------------*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Council Room"

// the below assertTrue function was influenced by http://www.java-samples.com/showtutorial.php?tutorialid=451
#ifndef DEBUG
  #define assertTrue(x, y)
#else
  #define assertTrue(x, y) \
           if (! (x)) \
          { \
             printf("ERROR!! assertTrue failed: (%s),", y); \
             printf(" function %s,", __FUNCTION__); \
             printf(" file: %s,", __FILE__); \
             printf(" line: %d\n", __LINE__); \
          }
#endif

 int main() {
     int drawnCards = 0;
     int discarded = 1;
     int shuffledCards = 0;
     int newActions = 0;
     int newBuys = 0;
     int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
     int seed = 1000;
     int numPlayers = 2;
     int thisPlayer = 0;
 	   struct gameState G, testGameState;
 	   int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
 			sea_hag, tribute, smithy, council_room};

 	// initialize a game state and player cards
 	initializeGame(numPlayers, k, seed, &G);

  printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

  memcpy(&testGameState, &G, sizeof(struct gameState));
  cardEffect(council_room, choice1, choice2, choice3, &testGameState, handpos, &bonus);

  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  // expected number of new cards
  drawnCards = 4;
  newBuys = 1;
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer] + drawnCards - discarded);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer] - drawnCards);
  printf("action count = %d, expected = %d\n", testGameState.numActions, G.numActions);
  printf("buy count = %d, expected = %d\n", testGameState.numBuys, G.numBuys + newBuys);


  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer] + drawnCards - discarded, "current player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer] - drawnCards, "current player's deck count");
  assertTrue(testGameState.numActions == G.numActions, "current player's number of actions");
  assertTrue(testGameState.numBuys == G.numBuys + newBuys, "current player's number of buys");


  thisPlayer = 1;
  drawnCards = 1;
  newBuys = 0;
  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer] + drawnCards);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer] - drawnCards);
  printf("action count = %d, expected = %d\n", testGameState.numActions, G.numActions);
  printf("buy count = %d, expected = %d\n", testGameState.numBuys, G.numBuys + newBuys);


  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer] + drawnCards, "noncurrent player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer] - drawnCards, "noncurrent player's deck count");
  assertTrue(testGameState.numActions == G.numActions, "noncurrent player's number of actions");
  assertTrue(testGameState.numBuys == G.numBuys + newBuys, "noncurrent player's number of buys");


  printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}
