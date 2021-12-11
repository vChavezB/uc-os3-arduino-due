#include <uCOS-III_Due.h>

#define SIMPLETASK_STACK_SIZE 256



class SimpleTask
{
  public:
    OS_ERR Create(OS_PRIO priority);
  private:
    CPU_STK  stack[SIMPLETASK_STACK_SIZE];
    OS_TCB  tcb;
    int task_no;
    static void  Task(void * args);
    static int totalTasks;
    bool created=false;
};
