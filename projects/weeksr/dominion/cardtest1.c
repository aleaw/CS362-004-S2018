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

#define TESTCARD "Village"

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
     int newCards = 0;
     int discarded = 1;
     int m, villageCard;
     int shuffledCards = 0;
     int newActions = 0;
     int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
     int seed = 1000;
     int numPlayers = 2;
     int thisPlayer = 0;
 	   struct gameState G, testGameState;
 	   int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
 			sea_hag, tribute, smithy, council_room};



  printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

  printf("\n----------------- Testing Card: %s with 2 players ----------------\n", TESTCARD);

  numPlayers = 2;
  seed = 1003;
  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  // set hand and deck of player 0
  G.handCount[thisPlayer] = 5;
  G.hand[thisPlayer][0] = village;
  G.hand[thisPlayer][1] = copper;
  G.hand[thisPlayer][2] = copper;
  G.hand[thisPlayer][3] = copper;
  G.hand[thisPlayer][4] = copper;

  G.deck[thisPlayer][0] = estate;
  G.deck[thisPlayer][1] = estate;
  G.deck[thisPlayer][2] = estate;
  G.deck[thisPlayer][3] = estate;
  G.deck[thisPlayer][4] = estate;

  // set hand and deck of player 1
  G.hand[thisPlayer+1][0] = village;
  G.hand[thisPlayer+1][1] = copper;
  G.hand[thisPlayer+1][2] = copper;
  G.hand[thisPlayer+1][3] = copper;
  G.hand[thisPlayer+1][4] = copper;

  G.deck[thisPlayer+1][0] = estate;
  G.deck[thisPlayer+1][1] = estate;
  G.deck[thisPlayer+1][2] = estate;
  G.deck[thisPlayer+1][3] = estate;
  G.deck[thisPlayer+1][4] = estate;

  villageCard = G.hand[thisPlayer][0];
  printf("villageCard # %d\n", villageCard);
  memcpy(&testGameState, &G, sizeof(struct gameState));
  printf("villageCard # in testGameState: %d\n", testGameState.hand[thisPlayer][0]);

  printf("starting cards: ");
  for (m=0; m<testGameState.handCount[thisPlayer]; m++) {
    printf("(%d)", testGameState.hand[thisPlayer][m]);
  }
  printf("; ");

  playCard(handpos, choice1, choice2, choice3, &testGameState);

  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  // expected number of new cards
  newCards = 1;
  // expected number of new actions
  newActions = 2;
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
  printf("action count = %d, expected = %d\n", testGameState.numActions, G.numActions);
  printf("# cards in discard pile = %d, expected = %d\n", testGameState.discardCount[thisPlayer], discarded);
  printf("drawn card = %d, expected = %d\n", testGameState.hand[thisPlayer][0], 1); // expected drawn card is estate


  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, "current player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards, "current player's deck count");
  assertTrue(testGameState.numActions == G.numActions + newActions, "current player's number of actions");
  assertTrue(testGameState.discardCount[thisPlayer] == 1, "village is in discard pile");
  assertTrue(testGameState.hand[thisPlayer][0] == 1, "estate was added to hand");

  printf("ending cards: ");
  for (m=0; m<testGameState.handCount[thisPlayer]; m++) {
    printf("(%d)", testGameState.hand[thisPlayer][m]);
  }
  printf("; ");


  thisPlayer = 1;
  newCards = 0;
  newActions = 0;
  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer]);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  printf("action count = %d, expected = %d\n", testGameState.numActions, G.numActions);

  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer], "noncurrent player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer], "noncurrent player's deck count");
  assertTrue(testGameState.numActions == G.numActions + newActions, "noncurrent player's number of actions");


  endTurn(&testGameState);
  endTurn(&G);


  printf("\n----------------- Testing Card: %s with 2 players and empty deck)----------------\n", TESTCARD);

  numPlayers = 2;
  seed = 1001;

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);
  thisPlayer = 0;
  // set hand and deck of player 0
  G.handCount[thisPlayer] = 5;
  G.hand[thisPlayer][0] = village;
  G.hand[thisPlayer][1] = copper;
  G.hand[thisPlayer][2] = copper;
  G.hand[thisPlayer][3] = copper;
  G.hand[thisPlayer][4] = copper;

  G.discard[thisPlayer][0] = estate;
  G.discard[thisPlayer][1] = estate;
  G.discard[thisPlayer][2] = estate;
  G.discard[thisPlayer][3] = estate;
  G.discard[thisPlayer][4] = estate;
  G.discardCount[thisPlayer] = 5;
  G.deckCount[thisPlayer] = 0;

  // set hand and deck of player 1
  G.hand[thisPlayer+1][0] = village;
  G.hand[thisPlayer+1][1] = copper;
  G.hand[thisPlayer+1][2] = copper;
  G.hand[thisPlayer+1][3] = copper;
  G.hand[thisPlayer+1][4] = copper;

  G.deck[thisPlayer+1][0] = estate;
  G.deck[thisPlayer+1][1] = estate;
  G.deck[thisPlayer+1][2] = estate;
  G.deck[thisPlayer+1][3] = estate;
  G.deck[thisPlayer+1][4] = estate;

  villageCard = G.hand[thisPlayer][0];
  printf("villageCard # %d\n", villageCard);
  memcpy(&testGameState, &G, sizeof(struct gameState));
  printf("villageCard # in testGameState: %d\n", testGameState.hand[thisPlayer][0]);

  printf("starting cards: ");
  for (m=0; m<testGameState.handCount[thisPlayer]; m++) {
    printf("(%d)", testGameState.hand[thisPlayer][m]);
  }
  printf("; ");

  playCard(handpos, choice1, choice2, choice3, &testGameState);

  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  // expected number of new cards
  newCards = 1;
  // expected number of new actions
  newActions = 2;
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer] + G.discardCount[thisPlayer] - newCards);
  printf("action count = %d, expected = %d\n", testGameState.numActions, G.numActions);
  printf("# of cards in  discard pile= %d, expected = %d\n", testGameState.discardCount[thisPlayer], 1);
  printf("drawn card = %d, expected = %d\n", testGameState.hand[thisPlayer][0], 1); // expected drawn card is estate


  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, "current player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer] + G.discardCount[thisPlayer] - newCards, "current player's deck count");
  assertTrue(testGameState.numActions == G.numActions + newActions, "current player's number of actions");
  assertTrue(testGameState.discardCount[thisPlayer] == 1, "# of cards in discard pile");
  assertTrue(testGameState.hand[thisPlayer][0] == 1, "estate was added to hand");


  printf("ending cards: ");
  for (m=0; m<testGameState.handCount[thisPlayer]; m++) {
    printf("(%d)", testGameState.hand[thisPlayer][m]);
  }
  printf("; ");

  thisPlayer = 1;
  newCards = 0;
  newActions = 0;
  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer]);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  printf("action count = %d, expected = %d\n", testGameState.numActions, G.numActions);

  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer], "noncurrent player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer], "noncurrent player's deck count");
  assertTrue(testGameState.numActions == G.numActions + newActions, "noncurrent player's number of actions");

  endTurn(&testGameState);
  endTurn(&G);


  printf("\n----------------- Testing Card: %s with 2 players ----------------\n", TESTCARD);

  numPlayers = 2;
  thisPlayer = 0;
  memset(&G, 23, sizeof(struct gameState));   // clear the game state
  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  // set hand and deck of player 0
  G.handCount[thisPlayer] = 5;
  G.hand[thisPlayer][0] = village;
  G.hand[thisPlayer][1] = copper;
  G.hand[thisPlayer][2] = copper;
  G.hand[thisPlayer][3] = copper;
  G.hand[thisPlayer][4] = copper;

  G.deck[thisPlayer][0] = estate;
  G.deck[thisPlayer][1] = estate;
  G.deck[thisPlayer][2] = estate;
  G.deck[thisPlayer][3] = estate;
  G.deck[thisPlayer][4] = estate;

  // set hand and deck of player 1
  G.hand[thisPlayer+1][0] = copper;
  G.hand[thisPlayer+1][1] = copper;
  G.hand[thisPlayer+1][2] = copper;
  G.hand[thisPlayer+1][3] = village;
  G.hand[thisPlayer+1][4] = copper;

  G.deck[thisPlayer+1][0] = estate;
  G.deck[thisPlayer+1][1] = estate;
  G.deck[thisPlayer+1][2] = estate;
  G.deck[thisPlayer+1][3] = estate;
  G.deck[thisPlayer+1][4] = estate;

  villageCard = G.hand[thisPlayer][0];
  printf("villageCard # %d\n", villageCard);
  memcpy(&testGameState, &G, sizeof(struct gameState));
  printf("villageCard # in testGameState: %d\n", testGameState.hand[thisPlayer][0]);

  printf("starting cards: ");
  for (m=0; m<testGameState.handCount[thisPlayer]; m++) {
    printf("(%d)", testGameState.hand[thisPlayer][m]);
  }
  printf("; ");

  playCard(handpos, choice1, choice2, choice3, &testGameState);

  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  // expected number of new cards
  newCards = 1;
  // expected number of new actions
  newActions = 2;
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
  printf("action count = %d, expected = %d\n", testGameState.numActions, G.numActions);
  printf("# cards in discard pile = %d, expected = %d\n", testGameState.discardCount[thisPlayer], discarded);
  printf("drawn card = %d, expected = %d\n", testGameState.hand[thisPlayer][0], 1); // expected drawn card is estate


  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, "current player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards, "current player's deck count");
  assertTrue(testGameState.numActions == G.numActions + newActions, "current player's number of actions");
  assertTrue(testGameState.discardCount[thisPlayer] == 1, "village is in discard pile");
  assertTrue(testGameState.hand[thisPlayer][0] == 1, "estate was added to hand");

  printf("ending cards: ");
  for (m=0; m<testGameState.handCount[thisPlayer]; m++) {
    printf("(%d)", testGameState.hand[thisPlayer][m]);
  }
  printf("; ");


  thisPlayer = 1;
  newCards = 0;
  newActions = 0;
  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer]);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  printf("action count = %d, expected = %d\n", testGameState.numActions, G.numActions);

  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer], "noncurrent player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer], "noncurrent player's deck count");
  assertTrue(testGameState.numActions == G.numActions + newActions, "noncurrent player's number of actions");


  endTurn(&testGameState);
  endTurn(&G);

  printf("\n----------------- Testing Card: %s with 3 players ----------------\n", TESTCARD);

  numPlayers = 3;
  thisPlayer = 0;
  memset(&G, 23, sizeof(struct gameState));   // clear the game state
  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  // set hand and deck of player 0
  G.handCount[thisPlayer] = 5;
  G.hand[thisPlayer][0] = village;
  G.hand[thisPlayer][1] = copper;
  G.hand[thisPlayer][2] = copper;
  G.hand[thisPlayer][3] = copper;
  G.hand[thisPlayer][4] = copper;

  G.deck[thisPlayer][0] = estate;
  G.deck[thisPlayer][1] = estate;
  G.deck[thisPlayer][2] = estate;
  G.deck[thisPlayer][3] = estate;
  G.deck[thisPlayer][4] = estate;

  // set hand and deck of player 1
  G.handCount[thisPlayer+1] = 5;
  G.hand[thisPlayer+1][0] = village;
  G.hand[thisPlayer+1][1] = copper;
  G.hand[thisPlayer+1][2] = copper;
  G.hand[thisPlayer+1][3] = copper;
  G.hand[thisPlayer+1][4] = copper;


  G.deck[thisPlayer+1][0] = estate;
  G.deck[thisPlayer+1][1] = estate;
  G.deck[thisPlayer+1][2] = estate;
  G.deck[thisPlayer+1][3] = estate;
  G.deck[thisPlayer+1][4] = estate;

  villageCard = G.hand[thisPlayer][0];

  memcpy(&testGameState, &G, sizeof(struct gameState));
  printf("villageCard # in testGameState: %d\n", testGameState.hand[thisPlayer][0]);

  printf("starting cards: ");
  for (m=0; m<testGameState.handCount[thisPlayer]; m++) {
    printf("(%d)", testGameState.hand[thisPlayer][m]);
  }
  printf("; ");
  playCard(handpos, choice1, choice2, choice3, &testGameState);

  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  // expected number of new cards
  newCards = 1;
  // expected number of new actions
  newActions = 2;
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
  printf("action count = %d, expected = %d\n", testGameState.numActions, G.numActions);
  printf("# cards in discard pile = %d, expected = %d\n", testGameState.discardCount[thisPlayer], discarded);
  printf("drawn card = %d, expected = %d\n", testGameState.hand[thisPlayer][0], 1); // expected drawn card is estate


  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, "current player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards, "current player's deck count");
  assertTrue(testGameState.numActions == G.numActions + newActions, "current player's number of actions");
  assertTrue(testGameState.discardCount[thisPlayer] == 1, "village is in discard pile");
  assertTrue(testGameState.hand[thisPlayer][0] == 1, "estate was added to hand");

  printf("ending cards: ");
  for (m=0; m<testGameState.handCount[thisPlayer]; m++) {
    printf("(%d)", testGameState.hand[thisPlayer][m]);
  }
  printf("; ");


  thisPlayer = 1;
  newCards = 0;
  newActions = 0;
  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer]);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  printf("action count = %d, expected = %d\n", testGameState.numActions, G.numActions);

  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer], "noncurrent player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer], "noncurrent player's deck count");
  assertTrue(testGameState.numActions == G.numActions + newActions, "noncurrent player's number of actions");

  thisPlayer = 2;
  newCards = 0;
  newActions = 0;
  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer]);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  printf("action count = %d, expected = %d\n", testGameState.numActions, G.numActions);

  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer], "noncurrent player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer], "noncurrent player's deck count");
  assertTrue(testGameState.numActions == G.numActions + newActions, "noncurrent player's number of actions");


  endTurn(&testGameState);
  endTurn(&G);

  printf("\n----------------- Testing Card: %s with 4 players ----------------\n", TESTCARD);

  numPlayers = 4;
  thisPlayer = 0;
  memset(&G, 23, sizeof(struct gameState));   // clear the game state
  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  // set hand and deck of player 0
  G.handCount[thisPlayer] = 5;
  G.hand[thisPlayer][0] = village;
  G.hand[thisPlayer][1] = copper;
  G.hand[thisPlayer][2] = copper;
  G.hand[thisPlayer][3] = copper;
  G.hand[thisPlayer][4] = copper;

  G.deck[thisPlayer][0] = estate;
  G.deck[thisPlayer][1] = estate;
  G.deck[thisPlayer][2] = estate;
  G.deck[thisPlayer][3] = estate;
  G.deck[thisPlayer][4] = estate;

  // set hand and deck of player 1
  G.handCount[thisPlayer+1] = 5;
  G.hand[thisPlayer+1][0] = village;
  G.hand[thisPlayer+1][1] = copper;
  G.hand[thisPlayer+1][2] = copper;
  G.hand[thisPlayer+1][3] = copper;
  G.hand[thisPlayer+1][4] = copper;


  G.deck[thisPlayer+1][0] = estate;
  G.deck[thisPlayer+1][1] = estate;
  G.deck[thisPlayer+1][2] = estate;
  G.deck[thisPlayer+1][3] = estate;
  G.deck[thisPlayer+1][4] = estate;

  villageCard = G.hand[thisPlayer][0];

  memcpy(&testGameState, &G, sizeof(struct gameState));
  printf("villageCard # in testGameState: %d\n", testGameState.hand[thisPlayer][0]);

  printf("starting cards: ");
  for (m=0; m<testGameState.handCount[thisPlayer]; m++) {
    printf("(%d)", testGameState.hand[thisPlayer][m]);
  }
  printf("; ");
  playCard(handpos, choice1, choice2, choice3, &testGameState);

  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  // expected number of new cards
  newCards = 1;
  // expected number of new actions
  newActions = 2;
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
  printf("action count = %d, expected = %d\n", testGameState.numActions, G.numActions);
  printf("# cards in discard pile = %d, expected = %d\n", testGameState.discardCount[thisPlayer], discarded);
  printf("drawn card = %d, expected = %d\n", testGameState.hand[thisPlayer][0], 1); // expected drawn card is estate


  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, "current player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards, "current player's deck count");
  assertTrue(testGameState.numActions == G.numActions + newActions, "current player's number of actions");
  assertTrue(testGameState.discardCount[thisPlayer] == 1, "village is in discard pile");
  assertTrue(testGameState.hand[thisPlayer][0] == 1, "estate was added to hand");

  printf("ending cards: ");
  for (m=0; m<testGameState.handCount[thisPlayer]; m++) {
    printf("(%d)", testGameState.hand[thisPlayer][m]);
  }
  printf("; ");


  thisPlayer = 1;
  newCards = 0;
  newActions = 0;
  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer]);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  printf("action count = %d, expected = %d\n", testGameState.numActions, G.numActions);

  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer], "noncurrent player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer], "noncurrent player's deck count");
  assertTrue(testGameState.numActions == G.numActions + newActions, "noncurrent player's number of actions");

  thisPlayer = 2;
  newCards = 0;
  newActions = 0;
  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer]);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  printf("action count = %d, expected = %d\n", testGameState.numActions, G.numActions);

  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer], "noncurrent player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer], "noncurrent player's deck count");
  assertTrue(testGameState.numActions == G.numActions + newActions, "noncurrent player's number of actions");

  thisPlayer = 3;
  newCards = 0;
  newActions = 0;
  printf("\n*** Testing stats of player %d ***\n", thisPlayer);
  printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer]);
  printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  printf("action count = %d, expected = %d\n", testGameState.numActions, G.numActions);

  assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer], "noncurrent player's hand count");
  assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer], "noncurrent player's deck count");
  assertTrue(testGameState.numActions == G.numActions + newActions, "noncurrent player's number of actions");


  endTurn(&testGameState);
  endTurn(&G);

  printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}
