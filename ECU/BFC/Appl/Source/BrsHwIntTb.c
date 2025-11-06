/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/** \file  File:  BrsHwIntTb.c
 *      Project:  Vector Basic Runtime System
 *       Module:  BrsHw for platform Infineon Aurix/AurixPlus
 *     Template:  This file is reviewed according to Brs_Template@Implementation[1.03.05]
 *
 *  \brief Description:  This file consists of the core exception table for Startup and a 2nd one to be copied into RAM
 *                       for FBL projects.
 *
 *  \attention Please note:
 *    The demo and example programs only show special aspects of the software. With regard to the fact
 *    that these programs are meant for demonstration purposes only, Vector Informatik liability shall be
 *    expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to BrsHw.h.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EXAMPLE CODE ONLY
 *  -------------------------------------------------------------------------------------------------------------------
 *  This Example Code is only intended for illustrating an example of a possible BSW integration and BSW configuration.
 *  The Example Code has not passed any quality control measures and may be incomplete. The Example Code is neither
 *  intended nor qualified for use in series production. The Example Code as well as any of its modifications and/or
 *  implementations must be tested with diligent care and must comply with all quality requirements which are necessary
 *  according to the state of the art before their use.
 *********************************************************************************************************************/

#define BRSHWINTTB_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "BrsHw.h"

/**********************************************************************************************************************
 *  CONFIGURATION CHECK
 *********************************************************************************************************************/
#if defined (BRS_COMP_TASKING)

#else
  #error "Unknown compiler specified!"
#endif

#if defined (BRS_FIRST_EXECUTION_INSTANCE)
/* This code is only needed for the first instance/executable in the system */

/********************************************************************************************
 *                                                                                          *
 *                 Startup Core Exception Handler                                           *
 *                                                                                          *
 ********************************************************************************************/
void BrsHw_CoreExceptionHandler(uint32 CLASS_TIN)
{
  /* the parameter CLASS_TIN holds the trap class in the upper 16 bit and the TIN in the lower 16 bit */
  BrsMainExceptionHandler(kBrsInterruptHandlerNotInstalled, BRSERROR_MODULE_BRSHW, (uint16)0);
}

/**********************************************************************************************************************
 *  Compiler abstraction
 *********************************************************************************************************************/


#if defined (BRS_COMP_TASKING)
# define Brs_ExceptionTableBegin() \
  __asm ("  .SDECL  \".text.brsExcVect\",code,PROTECT");\
  __asm ("  .SECT   \".text.brsExcVect\""); \
  __asm ("  .ALIGN 256"); \

# define Brs_ExceptionTableEnd()

# define Brs_ExceptionHandler(core, class) \
  __asm ("  .ALIGN 32"); \
  __asm ("  .GLOBAL brsTrap_" #class "_Core" #core); \
  __asm ("brsTrap_" #class "_Core" #core ": svlcx");            /* save lower context */ \
  __asm ("  movh d4, #" #class);                                /* prepare parameters for C-Function; D4 = Exception class */ \
  __asm ("  or d4, d15");                                       /* prepare parameters for C-Function; D4 |= TIN (D15) */ \
  __asm ("  movh.a a14, #@his(BrsHw_CoreExceptionHandler)");    /* load address of BrsHw_CoreExceptionHandler */ \
  __asm ("  lea a14,[a14]@los(BrsHw_CoreExceptionHandler)");    /* load address of BrsHw_CoreExceptionHandler */ \
  __asm ("  ji a14 ");                                          /* jump to the handler */
#endif


/********************************************************************************************
 *                                                                                          *
 *                 Startup Core Exception Table                                             *
 *                                                                                          *
 ********************************************************************************************/
Brs_ExceptionTableBegin()
Brs_ExceptionHandler(0, 0)
Brs_ExceptionHandler(0, 1)
Brs_ExceptionHandler(0, 2)
Brs_ExceptionHandler(0, 3)
Brs_ExceptionHandler(0, 4)
Brs_ExceptionHandler(0, 5)
Brs_ExceptionHandler(0, 6)
Brs_ExceptionHandler(0, 7)
Brs_ExceptionTableEnd()
#endif /*BRS_FIRST_EXECUTION_INSTANCE*/

#if defined (BRS_ENABLE_FBL_SUPPORT) && defined (BRS_FBL_EXCEPTIONTABLE_IN_RAM)
/********************************************************************************************
 *                                                                                          *
 *                 Core Exception Handler in RAM                                            *
 *                                                                                          *
 ********************************************************************************************/
#define BRS_START_SEC_RAM_CODE
#include "Brs_MemMap.h"
void BrsHw_CoreExceptionHandler_Ram(uint32 CLASS_TIN)
{
#if defined (BRSHW_BRSHW_COREEXCEPTIONHANDLER_RAM_CALLOUT)
  BrsTestsuite_BrsHw_CoreExceptionHandler_Ram();
#endif

  volatile uint8 BrsMain_Continue;
  BrsMain_Continue = 0;

  while (BrsMain_Continue == 0)
  {
    /* Set BrsMain_Continue to 1 to continue here.
     *  If the debugger is not able to show the stack properly, this mechanism can be used to find the
     *  source of the exception. */
  }
}
#define BRS_STOP_SEC_RAM_CODE
#include "Brs_MemMap.h"

/**********************************************************************************************************************
  Compiler abstraction
**********************************************************************************************************************/


#if defined (BRS_COMP_TASKING)
#define Brs_ExceptionTableRamBegin() \
  __asm ("  .SDECL  \".text.brsExcVectRam\",code,PROTECT");\
  __asm ("  .SECT   \".text.brsExcVectRam\""); \
  __asm ("  .ALIGN 256"); \

#define Brs_ExceptionTableRamEnd()

#define Brs_ExceptionHandlerRam(core, class) \
  __asm ("  .ALIGN 32"); \
  __asm ("  .GLOBAL brsTrap_Ram_" #class "_Core" #core); \
  __asm ("brsTrap_Ram_" #class "_Core" #core ": svlcx");          /* save lower context */ \
  __asm ("  movh d4, #" #class);                                  /* prepare parameters for C-Function; D4 = Exception class */ \
  __asm ("  or d4, d15");                                         /* prepare parameters for C-Function; D4 |= TIN (D15) */ \
  __asm ("  movh.a a14, #@his(BrsHw_CoreExceptionHandler_Ram)");  /* load address of BrsHw_CoreExceptionHandler_Ram */ \
  __asm ("  lea a14,[a14]@los(BrsHw_CoreExceptionHandler_Ram)");  /* load address of BrsHw_CoreExceptionHandler_Ram */ \
  __asm ("  ji a14 ");                                            /* jump to the handler */
#endif


/********************************************************************************************
 *                                                                                          *
 *                 Core Exception Table in RAM                                              *
 *                                                                                          *
 ********************************************************************************************/
Brs_ExceptionTableRamBegin()
Brs_ExceptionHandlerRam(0, 0)
Brs_ExceptionHandlerRam(0, 1)
Brs_ExceptionHandlerRam(0, 2)
Brs_ExceptionHandlerRam(0, 3)
Brs_ExceptionHandlerRam(0, 4)
Brs_ExceptionHandlerRam(0, 5)
Brs_ExceptionHandlerRam(0, 6)
Brs_ExceptionHandlerRam(0, 7)
Brs_ExceptionTableRamEnd()
#endif /*BRS_ENABLE_FBL_SUPPORT&&BRS_FBL_EXCEPTIONTABLE_IN_RAM*/
