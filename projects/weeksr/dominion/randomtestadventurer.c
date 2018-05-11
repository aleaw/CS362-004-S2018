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

int playDom(int handPosition, int kingdom[10], int seed);

int checkAdventurereCard(int handPosition, int choice1, int choice2, int choice3, struct gameState *post, int p) {

  struct gameState pre;
  memcpy(&pre, post, sizeof(struct gameState));

  int r = playCard(handPosition, choice1, choice2, choice3, post);
  pre.numActions--;
  pre.playedCardCount++;

  int newCards, newCoins, trashedCards, discarded, preTreasureCardHandCount, postTreasureCardHandCount = 0;
  preTreasureCardHandCount = 0; int drawnTreasure = 0;

  printf("----- Testing adventurer -----\n");
  // printf("Starting hand:\n");
  for(int i = 0; i < pre.handCount[p]; i++) {
    if(pre.hand[p][i] == copper || pre.hand[p][i] == silver || pre.hand[p][i] == gold){
      preTreasureCardHandCount+=1;
    }
    // printf("(%d)", pre.hand[p][i]);
  }
  // printf("\n");
  // printf("pre treasureCardCount: %d\n", preTreasureCardHandCount);

  // printf("Ending hand:\n");
  for(int i = 0; i < post->handCount[p]; i++) {
    if(post->hand[p][i] == copper || post->hand[p][i] == silver || post->hand[p][i] == gold){
      postTreasureCardHandCount+=1;
    }
    // printf("(%d)", post->hand[p][i]);
  }
  // printf("\n");
  // printf("post treasureCardCount: %d\n", postTreasureCardHandCount);


  int fullDeckCountCopper = fullDeckCount(p, copper, &pre);
  int fullDeckCountSilver = fullDeckCount(p, silver, &pre);
  int fullDeckCountGold = fullDeckCount(p, gold, &pre);

  int treasureCardCountInDeckAndDiscard = fullDeckCountCopper + fullDeckCountSilver + fullDeckCountGold - preTreasureCardHandCount;

  // check that added cards are treasureCards
  for(int i = pre.handCount[p]; i<post->handCount[p]; i++) {
    if(post->hand[p][i] == copper || post->hand[p][i] == silver || post->hand[p][i] == gold) {
      drawnTreasure += 1;
    }
    printf("card added: %d expected: %d or %d or %d\n", post->hand[p][i], copper, silver, gold);
    assertTrue(post->hand[p][i] == copper || post->hand[p][i] == silver || post->hand[p][i] == gold, "Card added was a treasure card");
  }

  // printf("treasureCardCountInDeckAndDiscard: %d\n", treasureCardCountInDeckAndDiscard);
  if(treasureCardCountInDeckAndDiscard > 2) {
  printf("pre treasureCardCount: %d\n", preTreasureCardHandCount);
  printf("post treasureCardCount: %d\n", postTreasureCardHandCount);
  assertTrue(postTreasureCardHandCount - preTreasureCardHandCount == 2, "hand contains 2 more treasure cards");
  } else if(treasureCardCountInDeckAndDiscard == 1) {
  printf("pre treasureCardCount: %d\n", preTreasureCardHandCount);
  printf("post treasureCardCount: %d\n", postTreasureCardHandCount);
  assertTrue(postTreasureCardHandCount - preTreasureCardHandCount == 1, "hand contains 1 more treasure cards");
  } else {
  printf("pre treasureCardCount: %d\n", preTreasureCardHandCount);
  printf("post treasureCardCount: %d\n", postTreasureCardHandCount);
  assertTrue(postTreasureCardHandCount - preTreasureCardHandCount == 0, "hand contains 0 more treasure cards");
  }

  assertTrue(r == 0, "Play playAdventurere() returned 0");
  //assertTrue(memcmp(&pre, post, sizeof(struct gameState)) == 0, "(memcmp(&pre, post, sizeof(struct gameState)) == 0)");

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

// printf("Starting..\n");
srand(time(NULL));
int currentPlayer, handPos, i, n, randomNum, choice1, choice2, choice3;
struct gameState G;

// SelectStream(2);
// PutSeed(3);

for (n = 0; n < 5000; n++) {
  // printf("loop# %d\n", n);
  G = *newGame();

  int k[10] = {0};
  int* kingdomCardsPointer = malloc(10 * sizeof(int));


  // initialize kingdomCards
  for(i=0; i<10; i++) {
    randomNum = adventurer + rand() % treasure_map+1;
    while( isIn(k, i) ) {
       randomNum = adventurer + rand() % treasure_map+1;
    }
    k[i] = randomNum;
  }

  kingdomCardsPointer = kingdomCards(k[0], k[1], k[2], k[3], k[4], k[5], k[6], k[7], k[8], k[9]);

  for(i=0; i<10; i++){
    G.supplyCount[k[i]] = rand() % 200;
  }

  // printf("randomizing gameState...\n");
  G.numPlayers = rand() % 4;
  // printf("randomizing choices...\n");
  choice1 = 0; choice2 = 0; choice3 = 0;
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

    // randomize hand, deck, and discard
    for(int j = 0; j < G.handCount[currentPlayer]; j++) {
      randomNum = rand() % 26;
      G.hand[currentPlayer][j] = randomNum;
    }
    for(int j = 0; j < G.deckCount[currentPlayer]; j++) {
      randomNum = rand() % 26;
      G.deck[currentPlayer][j] = randomNum;
    }
    for(int j = 0; j < G.discardCount[currentPlayer]; j++) {
      randomNum = rand() % 26;
      G.discard[currentPlayer][j] = randomNum;
    }

    // randomize hand, deck, and discard
    if(G.numPlayers > 1){
      //G.handCount[currentPlayer+1] = floor(Random() * MAX_HAND);
      for(int j = 0; j < G.handCount[currentPlayer+1]; j++) {
        randomNum = rand() % 26;
        G.hand[currentPlayer+1][j] = randomNum;
      }
      for(int j = 0; j < G.deckCount[currentPlayer+1]; j++) {
        randomNum = rand() % 26;
        G.deck[currentPlayer+1][j] = randomNum;
      }
      for(int j = 0; j < G.discardCount[currentPlayer+1]; j++) {
        randomNum = rand() % 26;
        G.discard[currentPlayer+1][j] = randomNum;
      }
    }

  i = 10;

  // printf("Setting handPos 0f adventurer...\n");
  handPos = floor(Random() * G.handCount[currentPlayer]);
  G.hand[currentPlayer][handPos] = adventurer;

  // printf("handPos: %d\n", handPos);

  randomNum = 1 + rand() % 2000;
  // printf("initializeGame...\n");
  initializeGame(G.numPlayers+1, k, randomNum, &G);
  // printf("Call checkAdventurereCard()..\n");
  checkAdventurereCard(handPos, choice1, choice2, choice3, &G, currentPlayer);

  //play baron
  if(G.handCount[currentPlayer] > 2){
    int handPosBaron = floor(Random() * G.handCount[currentPlayer]);
    G.hand[currentPlayer][handPosBaron] = baron;
    while(handPosBaron == handPos){
      handPosBaron = floor(Random() * G.handCount[currentPlayer]);
    }
    choice1 = rand() % 100;
    playCard(handPosBaron, choice1, choice2, choice3, &G);
  }

  // play mine
  if(G.handCount[currentPlayer] > 2){
    int handPosMine = floor(Random() * G.handCount[currentPlayer]);
    int moneyPos = floor(Random() * G.handCount[currentPlayer]);
    G.hand[currentPlayer][moneyPos] = 3 + rand() % 7;
    while(handPosMine == moneyPos){
      moneyPos = floor(Random() * G.handCount[currentPlayer]);
    }
    G.hand[currentPlayer][handPosMine] = mine;
    choice1 = moneyPos;
    int choice2 = floor(Random() * G.supplyCount[rand() % 27]);
    playCard(handPosMine, choice1, choice2, choice3, &G);
  }

  // play remodel
  if(G.handCount[currentPlayer] > 2){
    int handPosRemodel = floor(Random() * G.handCount[currentPlayer]);
    G.hand[currentPlayer][handPosRemodel] = remodel;
    int trashPos = floor(Random() * G.handCount[currentPlayer]);
    G.hand[currentPlayer][trashPos] = 3 + rand() % 7;
    while(handPosRemodel == trashPos){
      trashPos = floor(Random() * G.handCount[currentPlayer]);
    }
    choice1 = trashPos;
    int choice2 = floor(Random() * G.supplyCount[rand() % 27]);
    playCard(handPosRemodel, choice1, choice2, choice3, &G);
  }

  // play minion
  if(G.handCount[currentPlayer] > 2){
    int handPosMinion = floor(Random() * G.handCount[currentPlayer]);
    G.hand[currentPlayer][handPosMinion] = minion;
    choice1 = rand() % 2;
    int choice2 = rand() % 2;
    G.handCount[currentPlayer+1] = 6;
    playCard(handPosMinion, choice1, choice2, choice3, &G);
  }

  // play steward
 if(G.handCount[currentPlayer] > 2){
    //choice1 = 0; choice2 = 0; choice3 = 0;
    // randomize choice selection
    randomNum = rand() % 3;
    choice1 = randomNum;
    int handPosSteward = floor(Random() * G.handCount[currentPlayer]);
    G.hand[currentPlayer][handPosSteward] = steward;
    playCard(handPosSteward, choice1, choice2, choice3, &G);
  }

  // play tribute
  if(G.handCount[currentPlayer] > 2){
     int handPosTribute = floor(Random() * G.handCount[currentPlayer]);
     G.hand[currentPlayer][handPosTribute] = tribute;
     playCard(handPosTribute, choice1, choice2, choice3, &G);
   }

   // play ambassador
   if(G.handCount[currentPlayer] > 2){
      int handPosAmbassador = floor(Random() * G.handCount[currentPlayer]);
      G.hand[currentPlayer][handPosAmbassador] = ambassador;
      choice1 = floor(Random() * G.handCount[currentPlayer]);
      choice2 = floor(Random() * G.handCount[currentPlayer]);
      playCard(handPosAmbassador, choice1, choice2, choice3, &G);
    }

    //play treasure_map
    if(G.handCount[currentPlayer] > 2){
       int handPosTreasureMap = floor(Random() * G.handCount[currentPlayer]);
       G.hand[currentPlayer][handPosTreasureMap] = treasure_map;
       handPosTreasureMap = floor(Random() * G.handCount[currentPlayer]);
       G.hand[currentPlayer][handPosTreasureMap] = treasure_map;
       playCard(handPosTreasureMap, choice1, choice2, choice3, &G);
     }

  printf("Playing card...%d\n", handCard(i, &G));
  playCard(G.hand[currentPlayer][i], choice1, choice2, choice3, &G);


  playDom(handPos, k, randomNum);

  int playerArray[G.numPlayers];
  for(i=0; i< G.numPlayers; i++) {
    playerArray[i] = i;
    scoreFor(i, &G);
  }
  getWinners(playerArray, &G);
}

}


int playDom(int handPosition, int kingdom[10], int seed) {
    struct gameState G;
    int n;
    int i=0;

    printf ("Starting game.\n");

    seed = 100 + rand() % 2000;
    initializeGame(2, kingdom, seed, &G);

    int money = 0;
    int smithyPos = -1;
    int adventurerPos = -1;

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
        else {
          smithyPos = i;
          adventurerPos = i;
        }
      }

      if (whoseTurn(&G) == 0) {
        if (smithyPos != -1) {
          printf("0: smithy played from position %d\n", smithyPos);
          playCard(smithyPos, -1, -1, -1, &G);
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
        if (adventurerPos != -1) {
          printf("1: adventurer played from position %d\n", adventurerPos);
          checkAdventurereCard(handPosition, -1, -1, -1, &G, 1);
          money = 0;
          i=0;
          while(i<numHandCards(&G)){
            if(handCard(i, &G) == steward){
              printf("1: steward played from position %d\n", i);
              playCard(i, 1, 0, 0, &G);
            }
            else if(handCard(i, &G) == outpost){
                printf("1: outpost played from position %d\n", i);
                playCard(i, 0, 0, 0, &G);
            }
            else if(handCard(i, &G) == council_room){
                printf("1: council_room played from position %d\n", i);
                playCard(i, 0, 0, 0, &G);
            }
            else if(handCard(i, &G) == baron){
                printf("1: baron played from position %d\n", i);
                playCard(i, rand()%1, 0, 0, &G);
            }
            else if(handCard(i, &G) == mine){
                printf("1: mine played from position %d\n", i);
                playCard(i, rand()%9, 0, 0, &G);
            }
            else if (handCard(i, &G) == copper){
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

  } // end of While

    printf ("Finished game.\n");
    printf ("Player 0: %d\nPlayer 1: %d\n", scoreFor(0, &G), scoreFor(1, &G));
    int playerArray[G.numPlayers];
    for(i=0; i< G.numPlayers; i++) {
      playerArray[i] = i;
      scoreFor(i, &G);
    }
    getWinners(playerArray, &G);


    return 0;
  }
