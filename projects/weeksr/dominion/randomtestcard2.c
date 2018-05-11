#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include<stdlib.h>
#include<time.h>


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

// int checkSmithyCard(int p, struct gameState *post, int handPosition) {
int checkSmithyCard(int handPosition, int choice1, int choice2, int choice3, struct gameState *post, int p) {

  struct gameState pre;
  memcpy(&pre, post, sizeof(struct gameState));

  printf("Call playCard\n");
  // int r = playSmithy(p, post, handPosition);
  int r = playCard(handPosition, choice1, choice2, choice3, post);
  pre.numActions--;
  pre.playedCardCount++;


  if(pre.deckCount[p] == 1 && pre.discardCount[p] == 0) {
    pre.handCount[p] += 1;
    pre.deckCount[p]--;
  } else if (pre.deckCount[p] == 2 && pre.discardCount[p] == 0) {
    pre.handCount[p] +=2;
    pre.deckCount[p] -=2;
  } else if(pre.deckCount[p] == 3 && pre.discardCount[p] == 0) {
    pre.handCount[p] +=3;
    pre.deckCount[p] -=3;
  }

  assertTrue(r == 0, "Play playSmithy() returned 0");
  assertTrue(memcmp(&pre, post, sizeof(struct gameState)) == 0, "(memcmp(&pre, post, sizeof(struct gameState)) == 0)");

  return r;
}

int isIn(int cardArray[10], int index) {
  int isFound = 0;
  for(int i = 0; i < index; i++) {
    if(cardArray[i] == cardArray[index]) {
        isFound = 1;
        return isFound;
      }
  }
  return isFound;
}

int main() {

srand(time(NULL));
  // int playSmithy(int currentPlayer, struct gameState *state, int handPos) {
int currentPlayer, handPos, i, n, randomNum;

struct gameState G;

SelectStream(2);
PutSeed(3);

for (n = 0; n < 2000; n++) {
  G = *newGame();

  int k[10] = {0};
  int* kingdomCardsPointer = malloc(10 * sizeof(int));


  // initialize kingdomCards
  for(i=0; i<10; i++) {
    randomNum = adventurer + rand() % treasure_map;
    while( isIn(k, i) ) {
       randomNum = adventurer + rand() % treasure_map;
    }
    k[i] = randomNum;
  }

  kingdomCardsPointer = kingdomCards(k[0], k[1], k[2], k[3], k[4], k[5], k[6], k[7], k[8], k[9]);

  G.numPlayers = rand() % 4;
  printf("number of players: %d\n", G.numPlayers);
  currentPlayer = rand() % (G.numPlayers + 1);
  printf("Current Player: %d\n", currentPlayer );
  G.phase = 0;
  G.numActions = 1;
  G.whoseTurn = currentPlayer;
  G.deckCount[currentPlayer] = rand() % MAX_DECK;
  G.discardCount[currentPlayer] = floor(Random() * MAX_DECK);
  G.handCount[currentPlayer] = floor(Random() * MAX_HAND);
  G.playedCardCount = floor(Random() * MAX_HAND);
  printf("Hand count of player: %d\n", G.handCount[currentPlayer]);

  printf("Setting up hand of player...\n");
  for(int j = 0; j < G.handCount[currentPlayer]; j++) {
    randomNum = rand() % 9;
    G.hand[currentPlayer][j] = k[randomNum];
  //  printf("Player's hand at %d is %d\n", j, G.hand[currentPlayer][j]);
  }
  randomNum = 1 + rand() % 2000;

  printf("Setting handPos 0f smithy...\n");
  handPos = floor(Random() * G.handCount[currentPlayer]);
  G.hand[currentPlayer][handPos] = smithy;
  printf("handPos: %d\n", handPos);

  printf("DeckCount: %d\n", G.deckCount[currentPlayer]);

  printf("initializeGame...\n");
  initializeGame(G.numPlayers+1, k, randomNum, &G);
  // checkSmithyCard(currentPlayer, &G, handPos);
  printf("Call checkSmithyCard()..\n");
  printf("phase: %d\n", G.phase);
  checkSmithyCard(handPos, 0, 0, 0, &G, currentPlayer);

  int money = 0;
  int smithyPos = handPos;
  int adventurerPos = -1;
  int i=0;

  int numSmithies = 0;
  int numAdventurers = 0;

  while (!isGameOver(&G)) {
    money = 0;
    smithyPos = -1;
    adventurerPos = -1;
    for (i = 0; i < numHandCards(&G); i++) {
      if (handCard(i, &G) == copper)
    money++;
      else if (handCard(i, &G) == silver)
    money += 2;
      else if (handCard(i, &G) == gold)
    money += 3;
      else if (handCard(i, &G) == smithy)
    smithyPos = i;
      else if (handCard(i, &G) == adventurer)
    adventurerPos = i;
    }

    if (whoseTurn(&G) == 0) {
      if (smithyPos != -1) {
        printf("0: smithy played from position %d\n", smithyPos);
        checkSmithyCard(handPos, 0, 0, 0, &G, currentPlayer);
        //playCard(smithyPos, -1, -1, -1, &G);
        printf("smithy played.\n");
        money = 0;
        i=0;
        while(i<numHandCards(&G)){
          if (handCard(i, &G) == copper){
            playCard(i, -1, -1, -1, &G);
            money++;
          }
          else if (handCard(i, &G) == silver){
            playCard(i, -1, -1, -1, &G);
            money += 2;
          }
          else if (handCard(i, &G) == gold){
            playCard(i, -1, -1, -1, &G);
            money += 3;
          }
          i++;
        }
      }

      if (money >= 8) {
        printf("0: bought province\n");
        buyCard(province, &G);
      }
      else if (money >= 6) {
        printf("0: bought gold\n");
        buyCard(gold, &G);
      }
      else if ((money >= 4) && (numSmithies < 2)) {
        printf("0: bought smithy\n");
        buyCard(smithy, &G);
        numSmithies++;
      }
      else if (money >= 3) {
        printf("0: bought silver\n");
        buyCard(silver, &G);
      }

      printf("0: end turn\n");
      endTurn(&G);
    }
    else {
        playCard(adventurer, -1, -1, -1, &G);
        money = 0;
        i=0;
        while(i<numHandCards(&G)){
          if (handCard(i, &G) == copper){
            playCard(i, -1, -1, -1, &G);
            money++;
          }
          else if (handCard(i, &G) == silver){
            playCard(i, -1, -1, -1, &G);
            money += 2;
          }
          else if (handCard(i, &G) == gold){
            playCard(i, -1, -1, -1, &G);
            money += 3;
          }
          i++;
        }
      }

      if (money >= 8) {
        printf("1: bought province\n");
        buyCard(province, &G);
      }
      else if ((money >= 6) && (numAdventurers < 2)) {
        printf("1: bought adventurer\n");
        buyCard(adventurer, &G);
        numAdventurers++;
      }else if (money >= 6){
        printf("1: bought gold\n");
      buyCard(gold, &G);
        }
      else if (money >= 3){
        printf("1: bought silver\n");
      buyCard(silver, &G);
      }
      printf("1: endTurn\n");

      endTurn(&G);
    }
   // end of While

  printf ("Finished game.\n");
  printf ("Player 0: %d\nPlayer 1: %d\n", scoreFor(0, &G), scoreFor(1, &G));
  int playerArray[G.numPlayers];
  for(i=0; i< G.numPlayers; i++) {
    playerArray[i] = i;
  }
  getWinners(playerArray, &G);
 }
}
