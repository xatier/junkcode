#include <stdio.h>
#include <stdlib.h>

#define PLURK_USERNAME "cciwn2010"
#define PLURK_PASSWORD "wintercamp"

int main (void) {
  char cmd[50];
  char content[] = "Hello world~";
  sprintf(cmd, "plurk --user=%s --pass=%s %s", PLURK_USERNAME, PLURK_PASSWORD, content);
  system(cmd);
  return 0;
}
