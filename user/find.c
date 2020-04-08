#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void
find(char *path, char *filename)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;
  int fnsize, pathsize;
  printf("[DEBUG] On find\n");

  if((fd = open(path, 0)) < 0){
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "find : cannot stat %s\n", path);
    close(fd);
    return;
  }

  printf("[DEBUG] After basic file checking\n");

  switch(st.type){
  case T_FILE:
    pathsize = strlen(path);
    fnsize = strlen(filename);
    if(pathsize >= fnsize){
      printf("[DEBUG] Checking path %s, implied filename: %s \n", path, (char*)(path + (pathsize-fnsize)));
      if(strcmp(filename, (char*)(path + (pathsize-fnsize))) == 0){
        printf("%s\n", path);
      }
    }
    break;

  case T_DIR:
    printf("[DEBUG] Checking dir \"%s\"\n", path);
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("find : path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      if(de.name[0] == '.')
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf("find: cannot stat %s\n", buf);
        continue;
      }
      find(buf, filename);
    }
    break;
  }
  close(fd);
}


int main(int argc, char *argv[]){
  if(argc != 3){
    printf("Usage : find dir filename\n");
    exit();
  }

  find(argv[1], argv[2]);

  exit();
}
