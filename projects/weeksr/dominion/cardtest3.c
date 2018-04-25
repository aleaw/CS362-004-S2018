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

#define TESTCARD "Adventurer"

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
     int drawnTreasure = 0;
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
  // Reveal cards from your deck until you reveal 2 Treasure cards.
  // Put those Treasure cards into your hand and discard the other revealed cards.

  // check that hand has previous amount of treasure cards + 2
  // make sure all other drawn cards are discarded: handCount = handCount + 2

  memcpy(&testGameState, &G, sizeof(struct gameState));
  cardEffect(adventurer, choice1, choice2, choice3, &testGameState, handpos, &bonus);

  drawnTreasure = 2;
  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  // expected number of new cards
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer] + drawnTreasure - discarded);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer] + shuffledCards - (drawnTreasure + discarded));
  printf("action count = %d, expected = %d\n", testGameState.numActions, G.numActions);
  printf("coin count = %d, expected = %d\n", testGameState.coins, G.coins);


  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer] + drawnTreasure - discarded, "current player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer] - drawnCards + shuffledCards, "current player's deck count");
  assertTrue(testGameState.numActions == G.numActions, "current player's number of actions");


  thisPlayer = 1;
  drawnCards = 0;
  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer]);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  printf("action count = %d, expected = %d\n", testGameState.numActions, G.numActions);

  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer], "noncurrent player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer], "noncurrent player's deck count");
  assertTrue(testGameState.numActions == G.numActions, "noncurrent player's number of actions");

  printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}
