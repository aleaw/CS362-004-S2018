#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

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

int checkStewardCard(int handPosition, int choice1, int choice2, int choice3, struct gameState *post, int p) {

  struct gameState pre;
  memcpy(&pre, post, sizeof(struct gameState));

  int r = playCard(handPosition, choice1, choice2, choice3, post);
  pre.numActions--;
  pre.playedCardCount++;

  int newCards, newCoins, trashedCards, discarded = 0;

  printf("----- Testing STEWARD -----\n");
  // choice1: +2 cards
  discarded = 1;
  if(choice1 == 1) {
    // chech stats when deck count or discard is >= 2
    if(pre.deckCount[p] >= 2 || pre.discardCount[p] >= 2) {
      newCards = 2;
      printf("hand count = %d, expected = %d\n", post->handCount[p], pre.handCount[p] + newCards - discarded);
      printf("deck count = %d, expected = %d\n", post->deckCount[p], pre.deckCount[p] - newCards);

      assertTrue(post->handCount[p] == pre.handCount[p] + newCards - discarded, "Hand count");
      assertTrue(post->deckCount[p] == pre.deckCount[p] - newCards, "Deck count");

    }
    // chech stats when deck count + discard count = 1
    else if(pre.deckCount[p] == 1 && pre.discardCount[p] == 0){
      newCards = 1;
      printf("hand count = %d, expected = %d\n", post->handCount[p], pre.handCount[p] + newCards - discarded);
      printf("deck count = %d, expected = %d\n", post->deckCount[p], pre.deckCount[p] - newCards);

      assertTrue(post->handCount[p] == pre.handCount[p] + newCards - discarded, "Hand count -- only one card in deck & discard");
      assertTrue(post->deckCount[p] == pre.deckCount[p] - newCards, "Deck count -- only one card in deck & discard");

    } else if(pre.deckCount[p] == 0 && pre.discardCount[p] >= 2){
      newCards = 2;
      printf("hand count = %d, expected = %d\n", post->handCount[p], pre.handCount[p] + newCards - discarded);
      printf("deck count = %d, expected = %d\n", post->deckCount[p], pre.deckCount[p] - newCards);

      assertTrue(post->handCount[p] == pre.handCount[p] + newCards - discarded, "Hand count -- deck is empty but discard is not");
      assertTrue(post->deckCount[p] == pre.deckCount[p] - newCards, "Deck count -- deck is empty but discard is not");
    }
  }
  else if(choice2 == 2) {
    newCoins = 2;
    pre.coins += newCoins;
    printf("coin count = %d, expected = %d\n", post->coins, pre.coins);
    assertTrue(post->coins == pre.coins, "Coin count");

  }

else {
  trashedCards = 2;
  printf("hand count = %d, expected = %d\n", post->handCount[p], pre.handCount[p] - (trashedCards + discarded));
  printf("deck count = %d, expected = %d\n", post->deckCount[p], pre.deckCount[p]);

  assertTrue(post->handCount[p] == pre.handCount[p] - (trashedCards + discarded), "Hand count");
  assertTrue(post->deckCount[p] == pre.deckCount[p] , "Deck count");
}
  assertTrue(r == 0, "Play playSteward() returned 0");

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
int currentPlayer, handPos, i, n, randomNum, choice1, choice2, choice3;
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
  choice1 = 0; choice2 = 0; choice3 = 0;
  // randomize choice selection
  randomNum = 1 + rand() % 2;
  if(randomNum == 1) {
    choice1 = 1;
    choice2 = 0;
    choice3 = 0;
  } else if (randomNum == 2) {
    choice2 = 2;
    choice1 = 0;
    choice3 = 0;
  } else {
    choice3 = 3;
    choice1 = 0;
    choice2 = 0;
  }

  currentPlayer = rand() % (G.numPlayers + 1);
  G.phase = 0;
  G.numActions = rand() % 200;
  G.coins = rand() % 200;
  G.numBuys = rand() % 200;
  G.whoseTurn = currentPlayer;
  G.deckCount[currentPlayer] = rand() % MAX_DECK;
  G.discardCount[currentPlayer] = floor(Random() * MAX_DECK);
  G.handCount[currentPlayer] = floor(Random() * MAX_HAND);
  G.playedCardCount = floor(Random() * MAX_HAND);

  //Setting up hand of player...
  for(int j = 0; j < G.handCount[currentPlayer]; j++) {
    randomNum = rand() % 9;
    G.hand[currentPlayer][j] = k[randomNum];
  //  printf("Player's hand at %d is %d\n", j, G.hand[currentPlayer][j]);
  }
  randomNum = 1 + rand() % 2000;

  // printf("Setting handPos 0f steward...\n");
  handPos = floor(Random() * G.handCount[currentPlayer]);
  G.hand[currentPlayer][handPos] = steward;

  printf("initializeGame...\n");
  initializeGame(G.numPlayers+1, k, randomNum, &G);
  checkStewardCard(handPos, choice1, choice2, choice3, &G, currentPlayer);

  // run through a simple simulation of a dominion game
  // code was taken from playDom.c
  int money = 0;
  int stewardPos = handPos;
  int adventurerPos = -1;
  int i=0;

  int numSmithies = 0;
  int numAdventurers = 0;

  while (!isGameOver(&G)) {
    money = 0;
    stewardPos = -1;
    adventurerPos = -1;
    for (i = 0; i < numHandCards(&G); i++) {
      if (handCard(i, &G) == copper)
    money++;
      else if (handCard(i, &G) == silver)
    money += 2;
      else if (handCard(i, &G) == gold)
    money += 3;
      else if (handCard(i, &G) == steward)
    stewardPos = i;
    else if (handCard(i, &G) == adventurer)
  adventurerPos = i;
  }

    if (whoseTurn(&G) == 0) {
      if (stewardPos != -1) {
        checkStewardCard(handPos, choice1, choice2, choice3, &G, currentPlayer);
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
        // printf("0: bought province\n");
        buyCard(province, &G);
      }
      else if (money >= 6) {
        // printf("0: bought gold\n");
        buyCard(gold, &G);
      }
      else if (money >= 5) {
        // printf("0: bought duchy\n");
        buyCard(duchy, &G);
      }
      else if ((money >= 4) && (numSmithies < 2)) {
        // printf("0: bought smithy\n");
        buyCard(smithy, &G);
        numSmithies++;
      }
      else if (money >= 3) {
        // printf("0: bought silver\n");
        buyCard(silver, &G);
      }
      // else if(money >= 2) {
      //   printf("0: bought estate\n");
      //   buyCard(estate, &G);
      // }

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
        // printf("1: bought province\n");
        buyCard(province, &G);
      }
      else if ((money >= 6) && (numAdventurers < 2)) {
        // printf("1: bought adventurer\n");
        buyCard(adventurer, &G);
        numAdventurers++;
      }else if (money >= 6){
        // printf("1: bought gold\n");
      buyCard(gold, &G);
        }
      else if (money >= 3){
        // printf("1: bought silver\n");
      buyCard(silver, &G);
      }
      printf("1: endTurn\n");

      endTurn(&G);
    }
   // end of While

  // printf ("Finished game.\n");
  printf ("Player 0: %d\nPlayer 1: %d\n", scoreFor(0, &G), scoreFor(1, &G));
  int playerArray[G.numPlayers];
  for(i=0; i< G.numPlayers; i++) {
    playerArray[i] = i;
    scoreFor(i, &G);
  }
  getWinners(playerArray, &G);
  }
}
