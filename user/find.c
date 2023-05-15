#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"


void
find(char *dir,const char* name) {
    char buf[512];
    struct dirent de;
    struct stat st;
    char *p;
    int fd = open(dir, 0);
    fstat(fd, &st);

    strcpy(buf, dir);
    p = buf+strlen(buf);
    *p++ = '/';

    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      if(strcmp(de.name, "." ) == 0 || strcmp(de.name, "..") == 0)
        continue;

      if (strcmp(de.name, name) == 0) {
        printf("%s/", dir);
        printf("%s\n", name);
      }

      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      stat(buf ,&st);
      if (st.type == T_DIR) {
        find(buf, name);
      }
    }
}

int
main(int argc, char *argv[])
{
  char file_name[512];
  memcpy(file_name, argv[2], strlen(argv[2]));
  find(".", file_name);
  exit(0);
}
