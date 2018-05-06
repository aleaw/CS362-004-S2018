#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
    char charArray[] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']'};
    int randomNum = rand() % 9;
    // printf("***inputChar() randomNum: %d\n", randomNum);
    return charArray[randomNum];
}

char *inputString()
{
    // TODO: rewrite this function
    // printf("**In inputString()... \n");
    char charArray[] = {'r', 'e', 's', 't', 'e', '\0'};
    char stringArray[6] = {'\0'};
    int randomNum;

    for(int i=0; i < 6; i++) {
      randomNum = rand() % 6;
      while(charArray[randomNum] == '.') {
        randomNum = rand() % 6;
      }
      stringArray[i] = charArray[randomNum];
      charArray[randomNum] = '.';
      // printf("%c", stringArray[i]);
    }
     // printf("****\n");

    char* randString = (char*)malloc(sizeof(stringArray));
    free(randString);
    randString = (char*)malloc(sizeof(stringArray));
    memset(randString, sizeof(randString), '\0');
    // free(randString);
    // printf("Attemp string copy...\n");
    strcpy(randString, stringArray);
    return randString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
