#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

const uint MAX_NUM = 35;
// pipe(p)
// p[0] used for read while p[1] used for write

void solve(int neighbor_fd) {
    int prime, recv;
    read(neighbor_fd, &prime, sizeof prime);
    if (prime == 0) 
      return ;
    printf("prime %d\n", prime);

    int p[2];
    pipe(p);
    while ((read(neighbor_fd, &recv, sizeof recv) != 0) && (recv <= MAX_NUM)) {
        if (recv % prime != 0) {
           write(p[1], &recv, sizeof recv);
        }
    }
    close(neighbor_fd);
    close(p[1]);

    // next solve
    solve(p[0]);
    return ;
}

int
main(int argc, char *argv[])
{
  int p[2];
  pipe(p);
  if (fork() == 0) {
    solve(p[0]);
  } else { 
    for (int i = 2; i <= MAX_NUM + 1; i ++) { // 多发一个判断停止
      write(p[1], &i, sizeof i);
    }
    close(p[1]);
    wait(0);
  }
  exit(0);
}
