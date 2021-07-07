#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"
// #include "defs.h"
int
main(int argc, char **argv)
{
  if(argc != 6){
    printf(2, "usage: schedtest sliceA sleepA sliceB sleepB sleepParent\n");
    exit();
  }
  int p_a;
  int p_b;
  p_a = fork();
  if (p_a == -1) {
    return -1;
  } else if (p_a == 0) {
    char* ara[] = {"loop", "       "};
    strcpy(ara[1], argv[2]);
    // *ara[1] = *argv[2];
    // printf(1, "%d\n", getpid());
    setslice(getpid(), atoi(argv[1]));
    // printf(1, "%s\n", argv[2]);
    // printf(1, "%s\n", ara[1]);
    exec("loop", ara);
  } else {
    p_b = fork();
    if (p_b == -1) {
      return -2;
    } else if (p_b == 0) {
      char* arb[] = {"loop", "       "};
      // sleep(5);
      strcpy(arb[1], argv[4]);
      // *arb[1] = *argv[4];
      // printf(1, "%d\n", getpid());
      setslice(getpid(), atoi(argv[3]));
      // printf(1, "%s\n", *arb[1]);
      exec("loop", arb);
    } else {
      sleep(atoi(argv[5]));
      wait();
      wait();
      int compticksA = 0;
      int compticksB = 0;
      struct pstat *ps = malloc(sizeof(*ps));
      memset(ps, 0, sizeof(*ps));
      getpinfo(ps);
      
      // ps->compticks[4] = 5;
      for (int i = 0; i < NPROC; i++) {
        if (ps->timeslice[i] == atoi(argv[1]) && ps->inuse[i] == 0 && ps->timeslice[i+1] == atoi(argv[3])) {
          compticksA = ps->compticks[i];
          compticksB = ps->compticks[i+1];
        }
      } 
      // printf(1, "%d %d\n", pid_a, pid_b);
      printf(1, "%d %d\n", compticksA, compticksB);
      free(ps);
    }
  }
  exit();
}
