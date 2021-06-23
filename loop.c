#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char **argv)
{
  if(argc != 2){
    printf(2, "usage: loop sleepT\n");
    exit();
  }
  sleep(atoi(argv[1]));
  int i = 0, j = 0;
  while (i < 800000000) {
    j += i * j + 1;
    i++;
  }
  exit();
}
