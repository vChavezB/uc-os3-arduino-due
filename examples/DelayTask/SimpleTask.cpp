#include "SimpleTask.hpp"
#include <Arduino.h>

int SimpleTask::totalTasks = 0;

OS_ERR SimpleTask::Create(OS_PRIO priority)
{
  OS_ERR err;
  if (created == false)
  {
    created = false;
    OSTaskCreate((OS_TCB     *) & (this->tcb),
                 (CPU_CHAR   *)"SimpleTask",
                 (OS_TASK_PTR )this->Task,
                 (void       *)this,
                 (OS_PRIO     )priority,
                 (CPU_STK    *) & (this->stack[0]),
                 (CPU_STK_SIZE)SIMPLETASK_STACK_SIZE / 10,
                 (CPU_STK_SIZE)SIMPLETASK_STACK_SIZE,
                 (OS_MSG_QTY  )5,
                 (OS_TICK     )10,
                 (void       *)0,
                 (OS_OPT      )(OS_OPT_TASK_NONE),
                 (OS_ERR     *)&err);
    if (err == OS_ERR_NONE)
    {
      task_no = totalTasks++;
    }
  }
  return err;
}

void  SimpleTask::Task       (void *p_arg)
{
  SimpleTask * pSimpleTask = (SimpleTask * )p_arg;
  OS_ERR      err;
  int count = 0;
  int task_no = pSimpleTask->task_no;
  Serial.print("Task ");
  Serial.print(task_no);
  Serial.println(" started");
  while (1)
  {
    Serial.print("Task ");
    Serial.print(task_no);
    Serial.print(" execution #");
    Serial.println(count++);
    OSTimeDlyHMSM((CPU_INT16U) 0,
                  (CPU_INT16U) 0,
                  (CPU_INT16U) 0,
                  (CPU_INT32U)500,
                  (OS_OPT )OS_OPT_TIME_DLY,
                  (OS_ERR *)&err);
  }
}
