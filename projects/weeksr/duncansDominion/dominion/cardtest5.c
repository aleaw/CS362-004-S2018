

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>


#define TESTCARD "remodel"

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
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;
    int extraActions = 1;
    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testGameState;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

/*
+1 Action
Choice 1: +2 coins;
Choice 2: discard your hand,
+4 Cards, and each other player with at least 5 cards in hand discards their hand and draws 4 cards.
*/

	// ----------- TEST 1:  --------------
	//printf("TEST 1: choice1 = 1 = +2 coins\n");

	// copy the game state to a test case
	memcpy(&testGameState, &G, sizeof(struct gameState));
	choice1 = 1;
	//cardEffect(minion, choice1, choice2, choice3, &testGameState, handpos, &bonus);

			G.hand[thisPlayer][0] = steward;
			G.hand[thisPlayer][1] = copper;
			G.hand[thisPlayer][2] = duchy;
			G.hand[thisPlayer][3] = estate;
			G.hand[thisPlayer][4] = feast;

			// copy the game state to a test case
			memcpy(&testGameState, &G, sizeof(struct gameState));

			printf("starting cards: ");
			for (m=0; m<testGameState.handCount[thisPlayer]; m++) {
				printf("(%d)", testGameState.hand[thisPlayer][m]);
			}
			printf("; ");

			choice1 = 1;
      choice2 = supply # of embargo or estate;
			remove1 = testGameState.hand[thisPlayer][i];
			cardEffect(remodel, choice1, choice2, choice3, &testGameState, handpos, &bonus);

			printf("removed: (%d); ", remove1);
			printf("ending cards: ");

			// tests that the removed cards are no longer in the player's hand
			for (m=0; m<testGameState.handCount[thisPlayer]; m++) {
				printf("(%d)", testGameState.hand[thisPlayer][m]);
				assert(testGameState.hand[thisPlayer][m] != remove1);
				assert(testGameState.hand[thisPlayer][m] != remove2);
			}
			printf(", expected: ");
			for (m=1; m<G.handCount[thisPlayer]; m++) {
				if (G.hand[thisPlayer][m] != G.hand[thisPlayer][i] && G.hand[thisPlayer][m] != G.hand[thisPlayer][j]) {
					printf("(%d)", G.hand[thisPlayer][m]);
				}
			}
			printf("\n");

			// tests for the appropriate number of remaining cards
			newCards = 1;
			xtraCoins = 0;
			discarded = 3;
			if (i==1) {
				printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
				printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
			}
			assert(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
			assert(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
		}

	}



	printf("hand count = %d, expected = %d\n", testGameState.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testGameState.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testGameState.coins, G.coins + xtraCoins);
  printf("actions = %d, expected = %d\n", testGameState.numActions, G.numActions + extraActions);

	assertTrue(testGameState.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, "current player's hand count");
	assertTrue(testGameState.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards, "current player's deck count");
	assertTrue(testGameState.coins == G.coins + xtraCoins, "current player's coin count");
  assertTrue(testGameState.numActions == G.numActions + extraActions, "current player's action count");


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}
