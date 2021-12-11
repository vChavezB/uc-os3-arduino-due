extern void OS_CPU_PendSVHandler();
extern void OS_CPU_SysTickHandler();
/*
Implementation of PendSV hook for
the Arduino DUE SDK located in /cores/Arduino/cortex_handlers.c
*/
void pendSVHook(void){
    OS_CPU_PendSVHandler();	
}

/*
Implementation of System Tick hook for
the Arduino DUE SDK located in /cores/Arduino/cortex_handlers.c
*/
void sysTickHook(void)
{
  
    OS_CPU_SysTickHandler();

}