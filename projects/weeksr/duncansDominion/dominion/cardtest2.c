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

#define TESTCARD "Smithy"

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
  // smithy is +3 cards

  printf("\n----------------- Testing Smithy with 2 players: ----------------\n");
  // check that current player has +3 cards & noncurrent player doesn't
  memcpy(&testGameState, &G, sizeof(struct gameState));
  cardEffect(smithy, choice1, choice2, choice3, &testGameState, handpos, &bonus);

  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  // expected number of new cards
  drawnCards = 3;
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer] + drawnCards - discarded);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer] - drawnCards + shuffledCards);
  printf("action count = %d, expected = %d\n", testGameState.numActions, G.numActions);

  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer] + drawnCards - discarded, "current player's hand count");
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

  endTurn(&testGameState);

  printf("\n----------------- Testing Smithy with 3 players: ----------------\n");
  numPlayers = 3;
  // initialize a game state and player cards
 	initializeGame(numPlayers, k, seed, &G);
  thisPlayer = whoseTurn(&G);
  // check that current player has +3 cards & noncurrent player doesn't
  memcpy(&testGameState, &G, sizeof(struct gameState));
  cardEffect(smithy, choice1, choice2, choice3, &testGameState, handpos, &bonus);

  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  // expected number of new cards
  drawnCards = 3;
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer] + drawnCards - discarded);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer] - drawnCards + shuffledCards);
  printf("action count = %d, expected = %d\n", testGameState.numActions, G.numActions);

  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer] + drawnCards - discarded, "current player's hand count");
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

  thisPlayer = 2;
  drawnCards = 0;
  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer]);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  printf("action count = %d, expected = %d\n", testGameState.numActions, G.numActions);

  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer], "noncurrent player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer], "noncurrent player's deck count");
  assertTrue(testGameState.numActions == G.numActions, "noncurrent player's number of actions");

  endTurn(&testGameState);

  printf("\n----------------- Testing Smithy with 4 players: ----------------\n");
  numPlayers = 4;
  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);
  thisPlayer = whoseTurn(&G);
  // check that current player has +3 cards & noncurrent player doesn't
  memcpy(&testGameState, &G, sizeof(struct gameState));
  cardEffect(smithy, choice1, choice2, choice3, &testGameState, handpos, &bonus);

  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  // expected number of new cards
  drawnCards = 3;
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer] + drawnCards - discarded);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer] + shuffledCards - drawnCards);
  printf("action count = %d, expected = %d\n", testGameState.numActions, G.numActions);

  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer] + drawnCards - discarded, "current player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer] + shuffledCards - drawnCards, "current player's deck count");
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

  thisPlayer = 2;
  drawnCards = 0;
  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer]);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  printf("action count = %d, expected = %d\n", testGameState.numActions, G.numActions);

  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer], "noncurrent player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer], "noncurrent player's deck count");
  assertTrue(testGameState.numActions == G.numActions, "noncurrent player's number of actions");

  thisPlayer = 3;
  drawnCards = 0;
  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer]);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  printf("action count = %d, expected = %d\n", testGameState.numActions, G.numActions);

  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer], "noncurrent player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer], "noncurrent player's deck count");
  assertTrue(testGameState.numActions == G.numActions, "noncurrent player's number of actions");

  endTurn(&testGameState);

  printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}
