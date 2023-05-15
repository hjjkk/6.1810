#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

const uint MAX_NUM = 35;
// pipe(p)
// p[0] used for read while p[1] used for write

int solve(int neighbor_fd) {
    // recv from left , send to right
    int prime_num;
    int a[MAX_NUM];
    memset(a, 0, sizeof a);
    read(neighbor_fd, &prime_num, sizeof prime_num);
    if (prime_num == 0) return 0;
    printf("prime %d\n", prime_num);
    int recv = -1;
    int p[2];
    pipe(p);
    int ret;
    while ((ret = read(neighbor_fd, &recv, sizeof recv) != 0) && (recv <= MAX_NUM)) {
        if (recv % prime_num != 0) {
          a[recv] = 1;
        }
    }

    close(neighbor_fd);
   
    for (int i = 2; i <= MAX_NUM; i ++) {
      if (a[i]) {
        write(p[1], &i, sizeof i);
      }
    }
    close(p[1]);
    solve(p[0]);
    return 0;
}

int
main(int argc, char *argv[])
{
  int p[2];
  pipe(p);

  if (fork() == 0) {
    solve(p[0]);
  } else { 
    int i;
    for (i = 2; i <= MAX_NUM + 1; i ++) {
      write(p[1], &i, sizeof i);
    }
    wait(0);
  }
  close(p[1]);
  exit(0);
}
