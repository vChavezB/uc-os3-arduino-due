#ifndef STARTUP_TASK_H
#define STARTUP_TASK_H

#include <uCOS-III_Due.h>
#include <cstddef>
#define STARTUP_TASK_STK_SIZE 256
#define STARTUP_TASK_PRIO 2

typedef  void (*os_task)(void * args);
extern void  StartupTask        (void *p_arg);
struct StartupConfig_t
{
  CPU_STK stack[STARTUP_TASK_STK_SIZE];
  OS_TCB  tcb;
  const size_t stack_size = STARTUP_TASK_STK_SIZE;
  const int prio = STARTUP_TASK_PRIO;
  os_task task=StartupTask;
};

extern StartupConfig_t StartupCfg;




#endif
