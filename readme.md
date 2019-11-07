xv6 is a re-implementation of Dennis Ritchie's and Ken Thompson's Unix
Version 6 (v6).  xv6 loosely follows the structure and style of v6,
but is implemented for a modern x86-based multiprocessor using ANSI C.

ACKNOWLEDGMENTS

xv6 is inspired by John Lions's Commentary on UNIX 6th Edition (Peer
to Peer Communications; ISBN: 1-57398-013-7; 1st edition (June 14,
2000)). See also https://pdos.csail.mit.edu/6.828/, which
provides pointers to on-line resources for v6.

xv6 borrows code from the following sources:
    JOS (asm.h, elf.h, mmu.h, bootasm.S, ide.c, console.c, and others)
    Plan 9 (entryother.S, mp.h, mp.c, lapic.c)
    FreeBSD (ioapic.c)
    NetBSD (console.c)

The following people have made contributions: Russ Cox (context switching,
locking), Cliff Frey (MP), Xiao Yu (MP), Nickolai Zeldovich, and Austin
Clements.

We are also grateful for the bug reports and patches contributed by Silas
Boyd-Wickizer, Anton Burtsev, Cody Cutler, Mike CAT, Tej Chajed, eyalz800,
Nelson Elhage, Saar Ettinger, Alice Ferrazzi, Nathaniel Filardo, Peter
Froehlich, Yakir Goaron,Shivam Handa, Bryan Henry, Jim Huang, Alexander
Kapshuk, Anders Kaseorg, kehao95, Wolfgang Keller, Eddie Kohler, Austin
Liew, Imbar Marinescu, Yandong Mao, Matan Shabtay, Hitoshi Mitake, Carmi
Merimovich, Mark Morrissey, mtasm, Joel Nider, Greg Price, Ayan Shafqat,
Eldar Sehayek, Yongming Shen, Cam Tenny, tyfkda, Rafael Ubal, Warren
Toomey, Stephen Tu, Pablo Ventura, Xi Wang, Keiichi Watanabe, Nicolas
Wolovick, wxdao, Grant Wu, Jindong Zhang, Icenowy Zheng, and Zou Chang Wei.

The code in the files that constitute xv6 is
Copyright 2006-2018 Frans Kaashoek, Robert Morris, and Russ Cox.

ERROR REPORTS

We switched our focus to xv6 on RISC-V; see the mit-pdos/xv6-riscv.git
repository on github.com.

BUILDING AND RUNNING XV6

To build xv6 on an x86 ELF machine (like Linux or FreeBSD), run
"make". On non-x86 or non-ELF machines (like OS X, even on x86), you
will need to install a cross-compiler gcc suite capable of producing
x86 ELF binaries (see https://pdos.csail.mit.edu/6.828/).
Then run "make TOOLPREFIX=i386-jos-elf-". Now install the QEMU PC
simulator and run "make qemu".


##waitx System Call
The files which were modified are in the modified files directory. 
Replace the original files in the xv6 source with these files, make and then run in qemu 
This question was about implementing the waitx system call. This was done mainly by changing the proc structure and trap call.
Four new variables stime (start time), etime (end time), rtime (run time) and iotime (I/O time) have been added.
The variable stime is updated when the command is first scheduled on the CPU. 
End time is called when the program exits. 
The runtime is calculated by appropriately calculating the stime, etime and the iotime(the time when the process is sleeping and I/O is going on) 
Ticks have been used to calculate the time.
#Testing:
#“time ‘command’”

##Original Xv6 Scheduler

The original Xv6 Scheduler has round robin scheduler.

On testing the original scheduler with three instances of the “pbs” program, it was observed that the process which was started earlier finished earlier and there is no way to set priority or make a runnable program running unless a program exits.

#Testing:
#“make clean qemu”
#“roundtest”

##Priority based Xv6 Scheduler

A priority-based scheduler selects the process with the highest priority for execution.Set the default priority of a process as 60. To change the default priority add a new system call ​ set_priority​ which can change the priority of a process.
				int set_priority(int)
The system-call returns the old-priority value of the process. In case the priority of the process increases (the value is lower than before), then rescheduling should be done.

#Testing:
#“make qemu SCHEDULER=PBS”
#“pbs n 0.01 & ; pbs n 0.01 & ...”
#“set_priority pid final_pid”

##First Come First Serve Xv6 Scheduler

Implement a non preemptive ​ policy that selects the process with the lowest creation
time. The process runs until it no longer needs CPU time

#Testing:
#“make qemu SCHEDULER=FCFS”
#“fcfs”
#output: p3 p2 p1


##Getpinfo Sys Call

You'll need to create a new system call for this part: ​ int getpinfo(struct proc_stat*)​ . This routine returns some basic information about each process: its process ID, total run time, how many times it has been chosen to run, which queue it is currently on 0, 1, 2, 3 or 4 (check Task 2 part c) and ticks received in each queue.

#Testing:
#“pinfo”
