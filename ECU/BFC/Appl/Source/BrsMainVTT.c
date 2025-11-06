#include "EcuM.h"
#include "Os.h"

TASK(Default_Init_Task)
{
  EcuM_StartupTwo();
  
  (void)TerminateTask();
}

TASK(Default_Init_Task_Trusted)
{

  Os_InitialEnableInterruptSources(FALSE);

  (void)TerminateTask();
}

int main(void)
{
  Os_InitMemory();
  Os_Init();
  EcuM_Init(); /* never returns */

  return 0;
}
