#include "StartupTask.h"
#include "SimpleTask.hpp"
#include <Arduino.h>

StartupConfig_t StartupCfg;
SimpleTask simpleTask1;
SimpleTask simpleTask2;

const unsigned long cpu_clock = 84000000;
const int simple_task_prio = STARTUP_TASK_PRIO + 1;
/*
   Startup Task for initialization of system and OS
*/

void  StartupTask        (void *p_arg)
{
  Serial.println("Startup Task started");
  (void)p_arg;
  OS_ERR err;

  CPU_Init();                                  /* Initialize uC/CPU services.                          */
  OS_CPU_SysTickInitFreq(cpu_clock);            /* Init uC/OS periodic time src (SysTick).              */

  //Mem_Init();                                 /* Initialize Memory Management Module                  */
  CPU_IntEn();
  err = simpleTask1.Create(simple_task_prio);
  OS_ASSERT(err, OS_ERR_NONE);
  
  err = simpleTask2.Create(simple_task_prio + 1);
  OS_ASSERT(err, OS_ERR_NONE);
  
  Serial.println("Additional Tasks Created");
  
  OSTaskDel(&StartupCfg.tcb, &err);
  OS_ASSERT(err, OS_ERR_NONE);
  while (1);
}
