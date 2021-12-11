#include <os.h>
#include <lib_mem.h>

#define ASSERT(result,expected_value) \
  do { \
    if ((result) != (expected_value)) { \
      Serial.print("Error: ");\
      Serial.println(result,HEX);\
      while(1);\
    } \
  } while (0)

  
#define STARTUP_TASK_STK_SIZE 256
#define TASK_PRIO 5
static  CPU_STK  StartupTaskStk[STARTUP_TASK_STK_SIZE];
static  OS_TCB  StartupTaskTCB;
static  CPU_STK  AppTaskStck[STARTUP_TASK_STK_SIZE];
static  OS_TCB  AppTaskTCB;

static  void  AppTask        (void *p_arg)
{
  OS_ERR      err;

  while (1)
  {
    digitalWrite(4, 1);
    OSTimeDlyHMSM((CPU_INT16U) 0,
                  (CPU_INT16U) 0,
                  (CPU_INT16U) 0,
                  (CPU_INT32U)100,
                  (OS_OPT )OS_OPT_TIME_HMSM_STRICT,
                  (OS_ERR *)&err);

    digitalWrite(4, 0);
    OSTimeDlyHMSM((CPU_INT16U) 0,
                  (CPU_INT16U) 0,
                  (CPU_INT16U) 0,
                  (CPU_INT32U)100,
                  (OS_OPT )OS_OPT_TIME_HMSM_STRICT,
                  (OS_ERR *)&err);

    // OSTaskResume(&StartupTaskTCB, &err);
    //OSTaskSuspend(&AppTaskTCB, &err);
    //OSTimeDly(1, OS_OPT_TIME_DLY, &err);
  }
}
void startApp()
{
  OS_ERR      err;

  OSTaskCreate((OS_TCB     *)&AppTaskTCB,
               (CPU_CHAR   *)"App Task",
               (OS_TASK_PTR )AppTask,
               (void       *)0,
               (OS_PRIO     )TASK_PRIO + 1,
               (CPU_STK    *)&AppTaskStck[0],
               (CPU_STK_SIZE)STARTUP_TASK_STK_SIZE / 2,
               (CPU_STK_SIZE)STARTUP_TASK_STK_SIZE,
               (OS_MSG_QTY  )5,
               (OS_TICK     )10,
               (void       *)0,
               (OS_OPT      )(OS_OPT_TASK_NONE),
               (OS_ERR     *)&err);
}

static  void  StartupTask        (void *p_arg)
{

  (void)p_arg;
  OS_ERR      err;

  CPU_Init();                                                 /* Initialize uC/CPU services.                          */

  //OS_CPU_SysTickInitFreq(84000000);                                   /* Init uC/OS periodic time src (SysTick).              */
  //TODO: not recognizeed by arduino ide
  //Mem_Init();                                                 /* Initialize Memory Management Module                  */
  CPU_IntEn();
  /*

  */
  // ASSERT(err, OS_ERR_NONE);
  startApp();

  while (1)
  {
    Serial.println("hello");
    OSTimeDlyHMSM((CPU_INT16U) 0,
                  (CPU_INT16U) 0,
                  (CPU_INT16U) 0,
                  (CPU_INT32U)300,
                  (OS_OPT )OS_OPT_TIME_HMSM_STRICT,
                  (OS_ERR *)&err);

   

  }
}




void setup() {
  OS_ERR  err;
  Serial.begin(115200);
  pinMode(4, OUTPUT);
  digitalWrite(4, 0);
  delay(100);
  CPU_IntDis();                                               /* Disable all interrupts.                              */
  OSInit(&err);                                               /* Init uC/OS-III.        */
  ASSERT(err, OS_ERR_NONE);
  OSTaskCreate((OS_TCB     *)&StartupTaskTCB,                 /* Create the startup task                              */
               (CPU_CHAR   *)"Startup Task",
               (OS_TASK_PTR )StartupTask,
               (void       *)0,
               (OS_PRIO     )TASK_PRIO,
               (CPU_STK    *)&StartupTaskStk[0],
               (CPU_STK_SIZE)STARTUP_TASK_STK_SIZE / 2,
               (CPU_STK_SIZE)STARTUP_TASK_STK_SIZE,
               (OS_MSG_QTY  )5,
               (OS_TICK     )10,
               (void       *)0,
               (OS_OPT      )(OS_OPT_TASK_NONE),
               (OS_ERR     *)&err);
  ASSERT(err, OS_ERR_NONE);

  OSStart(&err);                                              /* Start multitasking (i.e. give control to uC/OS-III). */
  ASSERT(err, OS_ERR_NONE);
  while (1U) ;
}

void loop() {
  /* do nothing */
}