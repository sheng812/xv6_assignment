#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"
#include "defs.h"

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
    char* ara[] = {"look", 0};
    *ara[1] = *argv[2];
    printf(1, "%d\n", getpid());
    setslice(getpid(), atoi(argv[1]));
    exec("loop", ara);
  } else {
    p_b = fork();
    if (p_b == -1) {
      return -2;
    } else if (p_b == 0) {
      char* arb[] = {"loop", 0};
      safestrcpy(*arb[1])
      *arb[1] = *argv[4];
      printf(1, "%d\n", getpid());
      setslice(getpid(), atoi(argv[3]));
      printf(1, "%s\n", *arb[1]);
      exec("loop", arb);
    } else {
      sleep(atoi(argv[5]));
      int pid_a = wait();
      int pid_b = wait();
      int compticksA;
      int compticksB;
      struct pstat* ps = {0};
      getpinfo(ps);
      printf(1, "end");
      for (int i = 0; i < NPROC; i++) {
        if (ps->pid[i] == pid_a) {
          compticksA = ps->compticks[i];
        } else if (ps->pid[i] == pid_b) {
          compticksB = ps->compticks[i];
        }
      } 
      printf(1, "%d %d\n", compticksA, compticksB);
    }
  }
  exit();
}
