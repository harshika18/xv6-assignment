#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

void ff(int f)
{
  if(f<1)
  return;
  ff(f-1);
  ff(f-2);
  return;
}

int main()
{
	sleep(10);
  int pid = fork();
  if(pid == 0)
  {
  	sleep (10);
    int ppid = fork();
    if(ppid == 0)
    {    
      ff(33);
      printf(1,"P1\n");
     //#endif
    }
    else
    {
      ff(39);
      printf(1,"P2\n");
      wait();
      //#endif          
          
    }
  }
  else
  {
    ff(36);
    printf(1,"P3\n");
    wait();
   // #endif  
  }
  exit();
}
