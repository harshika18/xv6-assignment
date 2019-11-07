#include "types.h"
#include "stat.h"
//#include "proc.h"
#include "user.h"
#include "fs.h"


int main(int argc, char *argv[])
{
    int pid;

    if (argc < 1)
    {
        printf(2, "Usage: info\n");
        exit();
    }
    pid = atoi(argv[1]);    
    struct proc_stat *p = 0;
    printf(1, "Process pid %d\n",pid);
    getpinfo(pid,p);
    exit();
}