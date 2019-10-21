#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
 
#define DIE(msg) \
do { \
  printf("%s\n", msg); \
  exit(EXIT_FAILURE); \
} while(0)
 
void busy_wait()
{
  int x;
  while(1){
      x = 1;
  }    
  return;  
}
 
void batch_wait(pid_t pid)
{
  int batch_ret, unbatch_ret;
  if ((batch_ret = batch(pid)) != 0) {
    printf("batch retornou %d\n", batch_ret);
  }
  busy_wait();
  waitpid(pid, NULL, 0);
}
 
int main()
{
  pid_t child_pid = fork();
  if (child_pid < 0) {
    DIE("fork falhou");
  }
  if (child_pid == 0) {
    pid_t grandchild_pid = fork();
    if (grandchild_pid < 0) {
      DIE("fork do grandchild falhou");
    }
    if (grandchild_pid == 0) {
      pid_t last_pid = fork();
      printf("last_pid = %d\n", last_pid);
      if (last_pid < 0) {
        DIE("fork do last_child falhou");
      }
      if (last_pid == 0) {
        busy_wait();
      } else {
        printf("grandchild para last\n");
        batch_wait(last_pid);
      }
    } else {
      printf("child para grandchild\n");
      batch_wait(grandchild_pid);
    }
  } else {
    printf("parent para child\n");
    batch_wait(child_pid);
  }
  return 0;
}