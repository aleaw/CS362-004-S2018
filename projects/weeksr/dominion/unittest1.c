#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
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
    int i;
    int zeroCost[] = {curse, copper};
    int twoCost[] = {estate, embargo};
    int threeCost[] = {silver, village, great_hall, steward, ambassador};
    int fourCost[] = {feast, gardens, remodel, smithy, baron, cutpurse, salvager, sea_hag, treasure_map};
    int fiveCost[] = {duchy, council_room, mine, minion, tribute, outpost};
    int sixCost[] = {gold, adventurer};

    printf ("TESTING getCost() for zero cost cards:\n");

    for(i=0; i < 2; i++) {
      printf("cost %d, expected cost %d\n", getCost(zeroCost[i]), 0);
      assertTrue(getCost(zeroCost[i]) == 0, "zeroCost");
    }

    printf ("TESTING getCost() for two cost cards:\n");

    for(i=0; i < 2; i++) {
      printf("cost %d, expected cost %d\n", getCost(twoCost[i]), 2);
      assertTrue(getCost(twoCost[i]) == 2, "twoCost");
    }

    printf ("TESTING getCost() for three cost cards:\n");

    for(i=0; i < 5; i++) {
      printf("cost %d, expected cost %d\n", getCost(threeCost[i]), 3);
      assertTrue(getCost(threeCost[i]) == 3, "threeCost");
    }

    printf ("TESTING getCost() for four cost cards:\n");

    for(i=0; i < 9; i++) {
      printf("cost %d, expected cost %d\n", getCost(fourCost[i]), 4);
      assertTrue(getCost(fourCost[i]) == 4, "fourCost");
    }

    printf ("TESTING getCost() for five cost cards:\n");

    for(i=0; i < 6; i++) {
      printf("cost %d, expected cost %d\n", getCost(fiveCost[i]), 5);
      assertTrue(getCost(fiveCost[i]) == 5, "fiveCost");
    }

    printf ("TESTING getCost() for six cost cards:\n");

    for(i=0; i < 2; i++) {
      printf("cost %d, expected cost %d\n", getCost(sixCost[i]), 6);
      assertTrue(getCost(sixCost[i]) == 6, "sixCost");
    }

    printf ("TESTING getCost() for eight cost card:\n");
    printf("cost %d, expected cost %d\n", getCost(province), 8);
    assertTrue(getCost(province) == 8, "eightCost");


    printf("All tests passed!\n");

    return 0;
}
