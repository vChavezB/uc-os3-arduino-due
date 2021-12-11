#include <uc-os3-arduino.h>

#include "StartupTask.h"

void setup() {
  OS_ERR  err;
  Serial.begin(115200);
  CPU_IntDis();                                               /* Disable all interrupts.                              */
  OSInit(&err);                                               /* Init uC/OS-III.        */
  OS_ASSERT(err, OS_ERR_NONE);
  
  OSTaskCreate((OS_TCB     *)&StartupCfg.tcb,                 /* Create the startup task                              */
               (CPU_CHAR   *)"Startup Task",
               (OS_TASK_PTR )StartupCfg.task,
               (void       *)0,
               (OS_PRIO     )StartupCfg.prio,
               (CPU_STK    *)&StartupCfg.stack[0],
               (CPU_STK_SIZE)StartupCfg.stack_size / 10,
               (CPU_STK_SIZE)StartupCfg.stack_size,
               (OS_MSG_QTY  )0,
               (OS_TICK     )0,
               (void       *)0,
               (OS_OPT      )(OS_OPT_TASK_NONE),
               (OS_ERR     *)&err);
  OS_ASSERT(err, OS_ERR_NONE);
 
  OSStart(&err);                                              /* Start multitasking (i.e. give control to uC/OS-III). */
  OS_ASSERT(err, OS_ERR_NONE);
  while (1U) ; /* Code shoul never enter here */
}

void loop() {
  /* do nothing */
}
