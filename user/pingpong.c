#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p[2];
  pipe(p);
  int recv;
  int pid;
  if (fork() == 0) { // child
    pid = getpid();
    write(p[0], &pid, 1);
    read(p[1], &recv, 1);
    printf("%d: received ping\n", pid);
    close(p[0]);
  } else {
    write(p[1], &pid, 1);
    read(p[1], &recv, 1);
    printf("%d: received pong\n", pid);
    close(p[1]);
  }

  exit(0);
}
