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
     int m;
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

  printf("\n----------------- Test 1: no treasure in deck and hand: %s ----------------\n", TESTCARD);

  G.handCount[thisPlayer] = 5;
  G.hand[thisPlayer][0] = adventurer;
  G.hand[thisPlayer][1] = duchy;
  G.hand[thisPlayer][2] = duchy;
  G.hand[thisPlayer][3] = duchy;
  G.hand[thisPlayer][4] = duchy;

  G.deckCount[thisPlayer] = 5;
  G.deck[thisPlayer][0] = estate;
  G.deck[thisPlayer][1] = estate;
  G.deck[thisPlayer][2] = estate;
  G.deck[thisPlayer][3] = estate;
  G.deck[thisPlayer][4] = estate;
  G.coins = 0;
  G.discardCount[thisPlayer] = 0;

  memcpy(&testGameState, &G, sizeof(struct gameState));

  printf("starting cards: ");
  for (m=0; m<testGameState.handCount[thisPlayer]; m++) {
    printf("(%d)", testGameState.hand[thisPlayer][m]);
  }
  printf("; ");

  playCard(handpos, choice1, choice2, choice3, &testGameState);

  printf("ending cards: ");
  for (m=0; m<testGameState.handCount[thisPlayer]; m++) {
    printf("(%d)", testGameState.hand[thisPlayer][m]);
    if(m == 0 || m >= 5) {
      assertTrue(testGameState.hand[thisPlayer][m] == copper || testGameState.hand[thisPlayer][m] == silver || testGameState.hand[thisPlayer][m] == gold, "drawn cards are treasure cards")
    }

  }
  printf("; ");

  drawnTreasure = 0;
  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  // expected number of new cards
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer] + drawnTreasure);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer] - (drawnTreasure + G.discardCount[thisPlayer]));


  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer] + drawnTreasure, "current player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] ==  G.deckCount[thisPlayer] - (drawnTreasure + G.discardCount[thisPlayer]), "current player's deck count");


  thisPlayer = 1;
  drawnCards = 0;
  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer]);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer]);

  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer], "noncurrent player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer], "noncurrent player's deck count");


  printf("\n----------------- Test 2: 1 treasure in deck  hand: %s ----------------\n", TESTCARD);

  G.handCount[thisPlayer] = 5;
  G.hand[thisPlayer][0] = adventurer;
  G.hand[thisPlayer][1] = duchy;
  G.hand[thisPlayer][2] = duchy;
  G.hand[thisPlayer][3] = duchy;
  G.hand[thisPlayer][4] = duchy;

  G.deckCount[thisPlayer] = 5;
  G.deck[thisPlayer][0] = estate;
  G.deck[thisPlayer][1] = estate;
  G.deck[thisPlayer][2] = estate;
  G.deck[thisPlayer][3] = copper;
  G.deck[thisPlayer][4] = estate;
  G.coins = 1;
  G.discardCount[thisPlayer] = 0;

  memcpy(&testGameState, &G, sizeof(struct gameState));

  printf("starting cards: ");
  for (m=0; m<testGameState.handCount[thisPlayer]; m++) {
    printf("(%d)", testGameState.hand[thisPlayer][m]);
  }
  printf("; ");

  playCard(handpos, choice1, choice2, choice3, &testGameState);

  printf("ending cards: ");
  for (m=0; m<testGameState.handCount[thisPlayer]; m++) {
    printf("(%d)", testGameState.hand[thisPlayer][m]);
    if(m == 0 || m >= 5) {
      assertTrue(testGameState.hand[thisPlayer][m] == copper || testGameState.hand[thisPlayer][m] == silver || testGameState.hand[thisPlayer][m] == gold, "drawn cards are treasure cards")
    }
  }
  printf("; ");

  drawnTreasure = 1;
  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  // expected number of new cards
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer] + drawnTreasure);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer] - (drawnTreasure + G.discardCount[thisPlayer]));


  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer] + drawnTreasure, "current player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] ==  G.deckCount[thisPlayer] - (drawnTreasure + G.discardCount[thisPlayer]), "current player's deck count");


  thisPlayer = 1;
  drawnCards = 0;
  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer]);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer]);

  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer], "noncurrent player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer], "noncurrent player's deck count");

  printf("\n----------------- Test 2: 2 treasures in deck  hand: %s ----------------\n", TESTCARD);

  G.handCount[thisPlayer] = 5;
  G.hand[thisPlayer][0] = adventurer;
  G.hand[thisPlayer][1] = duchy;
  G.hand[thisPlayer][2] = duchy;
  G.hand[thisPlayer][3] = duchy;
  G.hand[thisPlayer][4] = duchy;

  G.deckCount[thisPlayer] = 5;
  G.deck[thisPlayer][0] = estate;
  G.deck[thisPlayer][1] = copper;
  G.deck[thisPlayer][2] = estate;
  G.deck[thisPlayer][3] = copper;
  G.deck[thisPlayer][4] = estate;
  G.coins = 2;
  G.discardCount[thisPlayer] = 0;

  memcpy(&testGameState, &G, sizeof(struct gameState));

  printf("starting cards: ");
  for (m=0; m<testGameState.handCount[thisPlayer]; m++) {
    printf("(%d)", testGameState.hand[thisPlayer][m]);
  }
  printf("; ");

  playCard(handpos, choice1, choice2, choice3, &testGameState);

  printf("ending cards: ");
  for (m=0; m<testGameState.handCount[thisPlayer]; m++) {
    printf("(%d)", testGameState.hand[thisPlayer][m]);
    if(m == 0 || m >= 5) {
      assertTrue(testGameState.hand[thisPlayer][m] == copper || testGameState.hand[thisPlayer][m] == silver || testGameState.hand[thisPlayer][m] == gold, "drawn cards are treasure cards")
    }
  }
  printf("; ");

  drawnTreasure = 2;
  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  // expected number of new cards
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer] + drawnTreasure);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer] - (drawnTreasure + G.discardCount[thisPlayer]));

  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer] + drawnTreasure, "current player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] ==  G.deckCount[thisPlayer] - (drawnTreasure + G.discardCount[thisPlayer]), "current player's deck count");

  thisPlayer = 1;
  drawnCards = 0;
  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer]);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer]);

  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer], "noncurrent player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer], "noncurrent player's deck count");

  printf("\n----------------- Test 2: 2 silvers in deck  hand: %s ----------------\n", TESTCARD);

  G.handCount[thisPlayer] = 5;
  G.hand[thisPlayer][0] = adventurer;
  G.hand[thisPlayer][1] = duchy;
  G.hand[thisPlayer][2] = duchy;
  G.hand[thisPlayer][3] = duchy;
  G.hand[thisPlayer][4] = duchy;

  G.deckCount[thisPlayer] = 5;
  G.deck[thisPlayer][0] = estate;
  G.deck[thisPlayer][1] = silver;
  G.deck[thisPlayer][2] = estate;
  G.deck[thisPlayer][3] = silver;
  G.deck[thisPlayer][4] = estate;
  G.coins = 4;
  G.discardCount[thisPlayer] = 0;

  memcpy(&testGameState, &G, sizeof(struct gameState));

  printf("starting cards: ");
  for (m=0; m<testGameState.handCount[thisPlayer]; m++) {
    printf("(%d)", testGameState.hand[thisPlayer][m]);
  }
  printf("; ");

  playCard(handpos, choice1, choice2, choice3, &testGameState);

  printf("ending cards: ");
  for (m=0; m<testGameState.handCount[thisPlayer]; m++) {
    printf("(%d)", testGameState.hand[thisPlayer][m]);
    if(m == 0 || m >= 5) {
      assertTrue(testGameState.hand[thisPlayer][m] == copper || testGameState.hand[thisPlayer][m] == silver || testGameState.hand[thisPlayer][m] == gold, "drawn cards are treasure cards")
    }
  }
  printf("; ");

  drawnTreasure = 2;
  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  // expected number of new cards
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer] + drawnTreasure);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer] - (drawnTreasure + G.discardCount[thisPlayer]));

  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer] + drawnTreasure, "current player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] ==  G.deckCount[thisPlayer] - (drawnTreasure + G.discardCount[thisPlayer]), "current player's deck count");


  thisPlayer = 1;
  drawnCards = 0;
  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer]);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer]);

  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer], "noncurrent player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer], "noncurrent player's deck count");


  printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}
