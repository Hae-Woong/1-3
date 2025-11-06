/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2024 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/** \file  File:  BrsMain_Appl.c
 *      Project:  Vector Basic Runtime System
 *       Module:  BrsMain
 *
 *  \brief Description:  Additional, Application-specific, implementation
 *
 *  \attention Please note:
 *    The demo and example programs only show special aspects of the software. With regard to the fact
 *    that these programs are meant for demonstration purposes only, Vector Informatik liability shall be
 *    expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to BrsMain.h.
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

#define _BRSMAIN_APPL_C_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "BrsMain_Appl.h"

#if !defined (BRSMAINAPPL_DISABLE_CAN_EXCLUSIVEAREA_HANDLING)
# if defined (BRS_ENABLE_CAN_SUPPORT)
  #include BRS_DRVCAN_HEADER_FILENAME
#  if defined (BRS_DRVCAN1_HEADER_FILENAME)
  #include BRS_DRVCAN1_HEADER_FILENAME
#  endif
# endif
#endif

#if defined (BRS_ENABLE_HYPERVISOR_SUPPORT)
  #include "vHyp.h"
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
#if (BRSMAIN_VERSION != 0x0221u)
  #error "Header and source file are inconsistent!"
#endif
#if (BRSMAIN_BUGFIX_VERSION != 0x02u)
  #error "Different versions of bugfix in Header and Source used!"
#endif

/**********************************************************************************************************************
 *  CONFIGURATION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  DEFINITION + MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL VARIABLES
 *********************************************************************************************************************/
#if !defined (BRSMAINAPPL_DISABLE_CAN_EXCLUSIVEAREA_HANDLING)
# if defined (BRS_ENABLE_CAN_SUPPORT) && (!defined (BRS_ENABLE_FBL_SUPPORT))
#  if defined (BRS_ENABLE_CAN_CLASSIC_SUPPORT)
  #define CAN_START_SEC_VAR_NOINIT_8BIT
  /* to support CAN driver name infix, vBRS generator provides a wrapper
     for usage of the driver specific MemMap.h define in vBrsCfg.h */
  #include "vBrsCfg.h"
  static uint8 BrsAsrApplCanInterruptLockCtr;
  #define CAN_STOP_SEC_VAR_NOINIT_8BIT
  /* to support CAN driver name infix, vBRS generator provides a wrapper
     for usage of the driver specific MemMap.h define in vBrsCfg.h */
  #include "vBrsCfg.h"
#  endif /*BRS_ENABLE_CAN_CLASSIC_SUPPORT*/
# endif /*BRS_ENABLE_CAN_SUPPORT&&!BRS_ENABLE_FBL_SUPPORT*/
#endif /*!BRSMAINAPPL_DISABLE_CAN_EXCLUSIVEAREA_HANDLING*/

/**********************************************************************************************************************
 *  GLOBAL CONST VARIABLES
 *********************************************************************************************************************/
#if defined (BRS_FBL_INSTANCE_FBL)
/***********************************************************************************************************************
 * FBL Instance Presence Pattern
 *   This presence pattern is only required when downloading the FBL with debugger. When using an updater (or an EOL
 *   programmer), this presence pattern is not required as part of the .hex file and should be removed.
 **********************************************************************************************************************/
#define BRS_START_SEC_FBL_PP_CONST
#include "Brs_MemMap.h"
const uint8 FblPresencePatternArray[4] = {0x73u, 0x6Au, 0x29u, 0x3Eu};
#define BRS_STOP_SEC_FBL_PP_CONST
#include "Brs_MemMap.h"
#endif /*BRS_FBL_INSTANCE_FBL*/

/**********************************************************************************************************************
 *  LOCAL VARIABLES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL CONST VARIABLES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  PROTOTYPES OF GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  PROTOTYPES OF LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  FUNCTION DEFINITIONS
 *********************************************************************************************************************/
/*****************************************************************************/
/* @brief      Main initialization routine.
 *             Contains configuration specific initialization of BrsHw parts
 *             and BrsMain specific mechanisms.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from main
 *****************************************************************************/
void BrsMain_Appl_Init(void)
{
#if !defined (BRSMAINAPPL_DISABLE_CAN_EXCLUSIVEAREA_HANDLING)
# if defined (BRS_ENABLE_CAN_SUPPORT) && (!defined (BRS_ENABLE_FBL_SUPPORT))
#  if defined (BRS_ENABLE_CAN_CLASSIC_SUPPORT)
  /* UserDefined ExclusiveArea handling for CAN channels, according to AN-ISC-8-1149_ErrorHook_E_OS_DISABLED_INT.pdf */
  BrsAsrApplCanInterruptLockCtr = 0u;
#  endif
# endif
#endif
}

#if defined (BRS_ENABLE_HYPERVISOR_SUPPORT)
/*****************************************************************************/
/* @brief      This is a temporary API for the Hypervisor Demo
 * @pre        -
 * @param[in]  coreID is the physical core ID of the actual running core
 * @param[out] -
 * @return     -
 * @context    Function is called from main
 *****************************************************************************/
void BrsMain_Appl_HypervisorApi(uint32 coreID)
{
  if (coreID == BRSHW_INIT_CORE_ID)
  {
    vHyp_Start();
  }
  else
  {
    while(1);
  }
}
#endif /*BRS_ENABLE_HYPERVISOR_SUPPORT*/

#if !defined (BRSMAINAPPL_DISABLE_CAN_EXCLUSIVEAREA_HANDLING)
# if defined (BRS_ENABLE_CAN_SUPPORT)
#  if defined (BRS_ENABLE_CAN_CLASSIC_SUPPORT)
/***********************************************************************************************************************
 * A classic (non-Gen3) DrvCan is part of the configuration. "Oldschool" implementation is needed
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * UserDefined ExclusiveArea handling for CAN channels, according to AN-ISC-8-1149_ErrorHook_E_OS_DISABLED_INT.pdf
 **********************************************************************************************************************/
/* Macro is generated in vBrsCfg.h, to support drivers with infix.
   Sample w/o infix: void SchM_Enter_Can_CAN_EXCLUSIVE_AREA_0(void)
                     Can_DisableControllerInterrupts(0u);
   Sample w/ infix:  void SchM_Enter_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_0(void)
                     Can_30_Mcan_DisableControllerInterrupts(0u);*/

#define CAN_START_SEC_CODE
/* to support CAN driver name infix, vBRS generator provides a wrapper
   for usage of the driver specific MemMap.h define in vBrsCfg.h */
#include "vBrsCfg.h"
BRS_DRVCAN_EXCLUSIVE_AREA_INFIX(Enter,EXCLUSIVE_AREA_0)
{
#if !defined (BRS_ENABLE_FBL_SUPPORT)
  if (++BrsAsrApplCanInterruptLockCtr == 1u)
  {
    BRS_DRVCAN_ControllerInterrupts_INFIX(Disable)(0u);
  }
#endif
}

BRS_DRVCAN_EXCLUSIVE_AREA_INFIX(Exit,EXCLUSIVE_AREA_0)
{
#if !defined (BRS_ENABLE_FBL_SUPPORT)
  if (--BrsAsrApplCanInterruptLockCtr == 0u)
  {
    BRS_DRVCAN_ControllerInterrupts_INFIX(Enable)(0u);
  }
#endif
}

BRS_DRVCAN_EXCLUSIVE_AREA_INFIX(Enter,EXCLUSIVE_AREA_6)
{
#if !defined (BRS_ENABLE_FBL_SUPPORT)
  if (++BrsAsrApplCanInterruptLockCtr == 1u)
  {
    BRS_DRVCAN_ControllerInterrupts_INFIX(Disable)(0u);
  }
#endif
}

BRS_DRVCAN_EXCLUSIVE_AREA_INFIX(Exit,EXCLUSIVE_AREA_6)
{
#if !defined (BRS_ENABLE_FBL_SUPPORT)
  if (--BrsAsrApplCanInterruptLockCtr == 0u)
  {
    BRS_DRVCAN_ControllerInterrupts_INFIX(Enable)(0u);
  }
#endif
}
#define CAN_STOP_SEC_CODE
/* to support CAN driver name infix, vBRS generator provides a wrapper
   for usage of the driver specific MemMap.h define in vBrsCfg.h */
#include "vBrsCfg.h"

#   if !defined (BRS_ENABLE_FBL_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
void SchM_Enter_CanIf_CANIF_EXCLUSIVE_AREA_0(void)
{
  if (++BrsAsrApplCanInterruptLockCtr == 1u)
  {
    BRS_DRVCAN_ControllerInterrupts_INFIX(Disable)(0u);
  }
}

void SchM_Exit_CanIf_CANIF_EXCLUSIVE_AREA_0(void)
{
  if (--BrsAsrApplCanInterruptLockCtr == 0u)
  {
    BRS_DRVCAN_ControllerInterrupts_INFIX(Enable)(0u);
  }
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANSM_START_SEC_CODE
#include "MemMap.h"
void SchM_Enter_CanSM_CANSM_EXCLUSIVE_AREA_4(void)
{
  if (++BrsAsrApplCanInterruptLockCtr == 1u)
  {
    BRS_DRVCAN_ControllerInterrupts_INFIX(Disable)(0u);
  }
}

void SchM_Exit_CanSM_CANSM_EXCLUSIVE_AREA_4(void)
{
  if (--BrsAsrApplCanInterruptLockCtr == 0u)
  {
    BRS_DRVCAN_ControllerInterrupts_INFIX(Enable)(0u);
  }
}

void SchM_Enter_CanSM_CANSM_EXCLUSIVE_AREA_1(void)
{
  /* Protects against task interruptions -> no locking needed, because all main functions are on same task */
}

void SchM_Exit_CanSM_CANSM_EXCLUSIVE_AREA_1(void)
{
  /* Protects against task interruptions -> no locking needed, because all main functions are on same task */
}
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

#define COMM_START_SEC_CODE
#include "MemMap.h"
void SchM_Enter_ComM_COMM_EXCLUSIVE_AREA_1(void)
{
  /* Protects against task interruptions -> no locking needed, because all main functions are on same task */
}

void SchM_Exit_ComM_COMM_EXCLUSIVE_AREA_1(void)
{
  /* Protects against task interruptions -> no locking needed, because all main functions are on same task */
}
#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#   endif /*!BRS_ENABLE_FBL_SUPPORT*/
#  endif /*BRS_ENABLE_CAN_CLASSIC_SUPPORT*/

#  if defined (BRS_ENABLE_CAN_CORE_SUPPORT)
/***********************************************************************************************************************
 * A new (Gen3) DrvCan is part of the configuration. New implementation is needed
 **********************************************************************************************************************/
#   if (Can_30_Core_IsHardwareCancelByApplOfGeneralFeature(0u) == TRUE) && (Can_30_Core_IsHardwareLoopCheckOfGeneralFeature(0u) == TRUE)
  /* If these do not exist, maybe Can_30_Core/Can/CanGeneral/CanConstantDataToDefine is deactivated. If so, please choose the suitable implementation manually */

#    if !defined (BRS_ENABLE_FBL_SUPPORT)
  /* Within a FBL project, depending APIs are already available within Fbl_cw.c */
/***********************************************************************************************************************
 * Hardware Loop Check / Timeout Monitoring for CAN Driver, according to TechnicalReference_Can_30_Core.pdf, chapter 2.8.2
 **********************************************************************************************************************/
#define CAN_30_CORE_START_SEC_CODE
#     if defined (BRSMAIN_CAN_30_CORE_SPECIFIC_MEMMAP)
  #include "Can_30_Core_MemMap.h"
#     else
  #include "MemMap.h"
#     endif
static uint32 BrsAsrApplCanTimerCount;
void Appl_30_CoreCanTimerStart(uint8 Controller, uint8 source)
{
  BrsAsrApplCanTimerCount = 0u;
}

void Appl_30_CoreCanTimerEnd(uint8 Controller, uint8 source)
{
  /* nothing to be done here; BrsAsrApplCanTimerCount will be set to 0 by next call of Appl_30_CoreCanTimerStart() */
}

Can_ReturnType Appl_30_CoreCanTimerLoop(uint8 Controller, uint8 source)
{
  BrsAsrApplCanTimerCount++;

  if (BrsAsrApplCanTimerCount>10000u)
  {
    /* timeout detected! Something seems to block the DrvCan */
    return CAN_NOT_OK;
  } else
    return CAN_OK;
}
#define CAN_30_CORE_STOP_SEC_CODE
#     if defined (BRSMAIN_CAN_30_CORE_SPECIFIC_MEMMAP)
  #include "Can_30_Core_MemMap.h"
#     else
  #include "MemMap.h"
#     endif
#    endif /*!BRS_ENABLE_FBL_SUPPORT*/

#   else
  //#error "Can_30_Core/Can/CanGeneral/CanHardwareCancelByAppl and/or Can_30_Core/Can/CanGeneral/CanHardwareLoopCheck are deactivated! If you really want to use customer specific exclusive area handling, implement them controller and project specific. The following APIs are only a generic sample and need to be adapted."

/***********************************************************************************************************************
 * UserDefined ExclusiveArea handling for CAN Driver Core, according to TechnicalReference_Can_30_Core.pdf, Note within chapter 3.2
 **********************************************************************************************************************/
/* BE AWARE, THIS IS ONLY A SAMPLE IMPLEMENTATION!
   To get a suitable implementation for your project, take account to the technical reference of Can_30_Core
   and implement them according to your specific project settings.
   The suitable implementation is highly configuration specific, e.g. amount of channels, postbuild, ... */

#define CAN_30_CORE_START_SEC_CODE
#    if defined (BRSMAIN_CAN_30_CORE_SPECIFIC_MEMMAP)
  #include "Can_30_Core_MemMap.h"
#    else
  #include "MemMap.h"
#    endif
void SchM_Enter_Can_30_Core_CAN_30_CORE_EXCLUSIVE_AREA_6(void)
{
#if !defined (BRS_ENABLE_FBL_SUPPORT)
  /* sample for singlechannel configuration:
  Can_30_Core_DisableControllerInterrupts(0u); */

  /* sample for multichannel configuration (be aware, this will have an effect on the runtime!):
  uint8 ch;
  for (ch = 0; ch < Can_30_Core_GetSizeOfControllerConfig(); ch++) {
    Can_30_Core_DisableControllerInterrupts(ch); */
#endif
}

void SchM_Exit_Can_30_Core_CAN_30_CORE_EXCLUSIVE_AREA_6(void)
{
#if !defined (BRS_ENABLE_FBL_SUPPORT)
  /* sample for singlechannel configuration:
  Can_30_Core_EnableControllerInterrupts(0u); */

  /* sample for multichannel configuration (be aware, this will have an effect on the runtime!):
  uint8 ch;
  for (ch = 0; ch < Can_30_Core_GetSizeOfControllerConfig(); ch++) {
    Can_30_Core_EnableControllerInterrupts(ch); */
#endif
}
#define CAN_30_CORE_STOP_SEC_CODE
#    if defined (BRSMAIN_CAN_30_CORE_SPECIFIC_MEMMAP)
  #include "Can_30_Core_MemMap.h"
#    else
  #include "MemMap.h"
#    endif

#    if !defined (BRS_ENABLE_CAN_CLASSIC_SUPPORT)
  /* If vCan and classic CAN is mixed within one config, the "old" DrvCan is expected to be the 1st one. So, the exclusive areas are already implemented earlier in this file */
/***********************************************************************************************************************
 * UserDefined ExclusiveArea handling for vCAN Driver, according to TechnicalReference_vCan_30_Mcan.pdf, Note within chapter 3.2
 **********************************************************************************************************************/
/* BE AWARE, THIS IS ONLY A SAMPLE IMPLEMENTATION!
   To get a suitable implementation for your project, take account to the technical reference of your specific DrvCan
   and implement them according to your specific project settings.
   The suitable implementation is highly configuration specific, e.g. amount of channels, postbuild, ... */

#define CAN_START_SEC_CODE
/* to support CAN driver name infix, vBRS generator provides a wrapper
   for usage of the driver specific MemMap.h define in vBrsCfg.h */
#include "vBrsCfg.h"
BRS_DRVCAN_EXCLUSIVE_AREA_INFIX(Enter,EXCLUSIVE_AREA_0)
{
#if !defined (BRS_ENABLE_FBL_SUPPORT)
  /* sample for singlechannel configuration:
  Can_30_Core_DisableControllerInterrupts(0u); */

  /* sample for multichannel configuration (be aware, this will have an effect on the runtime!):
  uint8 ch;
  for (ch = 0; ch < Can_30_Core_GetSizeOfControllerConfig(); ch++) {
    Can_30_Core_DisableControllerInterrupts(ch); */
#endif
}

BRS_DRVCAN_EXCLUSIVE_AREA_INFIX(Exit,EXCLUSIVE_AREA_0)
{
#if !defined (BRS_ENABLE_FBL_SUPPORT)
  /* sample for singlechannel configuration:
  Can_30_Core_RestoreControllerInterrupts(0u); */

  /* sample for multichannel configuration (be aware, this will have an effect on the runtime!):
  uint8 ch;
  for (ch = 0; ch < Can_30_Core_GetSizeOfControllerConfig(); ch++) {
    Can_30_Core_RestoreControllerInterrupts(ch); */
#endif
}

BRS_DRVCAN_EXCLUSIVE_AREA_INFIX(Enter,EXCLUSIVE_AREA_1)
{
#if !defined (BRS_ENABLE_FBL_SUPPORT)
  /* sample for singlechannel configuration:
  Can_30_Core_DisableControllerInterrupts(0u); */

  /* sample for multichannel configuration (be aware, this will have an effect on the runtime!):
  uint8 ch;
  for (ch = 0; ch < Can_30_Core_GetSizeOfControllerConfig(); ch++) {
    Can_30_Core_DisableControllerInterrupts(ch); */
#endif
}

BRS_DRVCAN_EXCLUSIVE_AREA_INFIX(Exit,EXCLUSIVE_AREA_1)
{
#if !defined (BRS_ENABLE_FBL_SUPPORT)
  /* sample for singlechannel configuration:
  Can_30_Core_RestoreControllerInterrupts(0u); */

  /* sample for multichannel configuration (be aware, this will have an effect on the runtime!):
  uint8 ch;
  for (ch = 0; ch < Can_30_Core_GetSizeOfControllerConfig(); ch++) {
    Can_30_Core_RestoreControllerInterrupts(ch); */
#endif
}
#define CAN_STOP_SEC_CODE
/* to support CAN driver name infix, vBRS generator provides a wrapper
   for usage of the driver specific MemMap.h define in vBrsCfg.h */
#include "vBrsCfg.h"
#    endif /*!BRS_ENABLE_CAN_CLASSIC_SUPPORT*/

#    if defined (BRS_DRVCAN1_HEADER_FILENAME)
  /* 2nd DrvCan instance detected */
#define CAN1_START_SEC_CODE
/* to support CAN driver name infix, vBRS generator provides a wrapper
   for usage of the driver specific MemMap.h define in vBrsCfg.h */
#include "vBrsCfg.h"
BRS_DRVCAN1_EXCLUSIVE_AREA_INFIX(Enter,EXCLUSIVE_AREA_0)
{
#if !defined (BRS_ENABLE_FBL_SUPPORT)
  /* sample for singlechannel configuration:
  Can_30_Core_DisableControllerInterrupts(0u); */

  /* sample for multichannel configuration (be aware, this will have an effect on the runtime!):
  uint8 ch;
  for (ch = 0; ch < Can_30_Core_GetSizeOfControllerConfig(); ch++) {
    Can_30_Core_DisableControllerInterrupts(ch); */
#endif
}

BRS_DRVCAN1_EXCLUSIVE_AREA_INFIX(Exit,EXCLUSIVE_AREA_0)
{
#if !defined (BRS_ENABLE_FBL_SUPPORT)
  /* sample for singlechannel configuration:
  Can_30_Core_RestoreControllerInterrupts(0u); */

  /* sample for multichannel configuration (be aware, this will have an effect on the runtime!):
  uint8 ch;
  for (ch = 0; ch < Can_30_Core_GetSizeOfControllerConfig(); ch++) {
    Can_30_Core_RestoreControllerInterrupts(ch); */
#endif
}

BRS_DRVCAN1_EXCLUSIVE_AREA_INFIX(Enter,EXCLUSIVE_AREA_1)
{
#if !defined (BRS_ENABLE_FBL_SUPPORT)
  /* sample for singlechannel configuration:
  Can_30_Core_DisableControllerInterrupts(0u); */

  /* sample for multichannel configuration (be aware, this will have an effect on the runtime!):
  uint8 ch;
  for (ch = 0; ch < Can_30_Core_GetSizeOfControllerConfig(); ch++) {
    Can_30_Core_DisableControllerInterrupts(ch); */
#endif
}

BRS_DRVCAN1_EXCLUSIVE_AREA_INFIX(Exit,EXCLUSIVE_AREA_1)
{
#if !defined (BRS_ENABLE_FBL_SUPPORT)
  /* sample for singlechannel configuration:
  Can_30_Core_RestoreControllerInterrupts(0u); */

  /* sample for multichannel configuration (be aware, this will have an effect on the runtime!):
  uint8 ch;
  for (ch = 0; ch < Can_30_Core_GetSizeOfControllerConfig(); ch++) {
    Can_30_Core_RestoreControllerInterrupts(ch); */
#endif
}
#define CAN1_STOP_SEC_CODE
/* to support CAN driver name infix, vBRS generator provides a wrapper
   for usage of the driver specific MemMap.h define in vBrsCfg.h */
#include "vBrsCfg.h"
#    endif /*BRS_DRVCAN1_HEADER_FILENAME*/

#    if !defined (BRS_ENABLE_FBL_SUPPORT)
#     if !defined (BRS_ENABLE_CAN_CLASSIC_SUPPORT)
  /* If vCan and classic CAN is mixed within one config, these exclusive areas are already implemented earlier in this file */
#define CANIF_START_SEC_CODE
#include "MemMap.h"
void SchM_Enter_CanIf_CANIF_EXCLUSIVE_AREA_0(void)
{
  /* sample for singlechannel configuration:
  Can_30_Core_DisableControllerInterrupts(0u); */

  /* sample for multichannel configuration (be aware, this will have an effect on the runtime!):
  uint8 ch;
  for (ch = 0; ch < Can_30_Core_GetSizeOfControllerConfig(); ch++) {
    Can_30_Core_DisableControllerInterrupts(ch); */
}

void SchM_Exit_CanIf_CANIF_EXCLUSIVE_AREA_0(void)
{
  /* sample for singlechannel configuration:
  Can_30_Core_RestoreControllerInterrupts(0u); */

  /* sample for multichannel configuration (be aware, this will have an effect on the runtime!):
  uint8 ch;
  for (ch = 0; ch < Can_30_Core_GetSizeOfControllerConfig(); ch++) {
    Can_30_Core_RestoreControllerInterrupts(ch); */
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANSM_START_SEC_CODE
#include "MemMap.h"
void SchM_Enter_CanSM_CANSM_EXCLUSIVE_AREA_4(void)
{
  /* sample for singlechannel configuration:
  Can_30_Core_DisableControllerInterrupts(0u); */

  /* sample for multichannel configuration (be aware, this will have an effect on the runtime!):
  uint8 ch;
  for (ch = 0; ch < Can_30_Core_GetSizeOfControllerConfig(); ch++) {
    Can_30_Core_DisableControllerInterrupts(ch); */
}

void SchM_Exit_CanSM_CANSM_EXCLUSIVE_AREA_4(void)
{
  /* sample for singlechannel configuration:
  Can_30_Core_RestoreControllerInterrupts(0u); */

  /* sample for multichannel configuration (be aware, this will have an effect on the runtime!):
  uint8 ch;
  for (ch = 0; ch < Can_30_Core_GetSizeOfControllerConfig(); ch++) {
    Can_30_Core_RestoreControllerInterrupts(ch); */
}

void SchM_Enter_CanSM_CANSM_EXCLUSIVE_AREA_1(void)
{
  /* Protects against task interruptions -> no locking needed, because all main functions are on same task */
}

void SchM_Exit_CanSM_CANSM_EXCLUSIVE_AREA_1(void)
{
  /* Protects against task interruptions -> no locking needed, because all main functions are on same task */
}
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

#define COMM_START_SEC_CODE
#include "MemMap.h"
void SchM_Enter_ComM_COMM_EXCLUSIVE_AREA_1(void)
{
  /* Protects against task interruptions -> no locking needed, because all main functions are on same task */
}

void SchM_Exit_ComM_COMM_EXCLUSIVE_AREA_1(void)
{
  /* Protects against task interruptions -> no locking needed, because all main functions are on same task */
}
#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#     endif /*!BRS_ENABLE_CAN_CLASSIC_SUPPORT*/
#    endif /*!BRS_ENABLE_FBL_SUPPORT*/
#   endif /* Can_30_Core_IsHardwareCancelByApplOfGeneralFeature(0u) && Can_30_Core_IsHardwareLoopCheckOfGeneralFeature(0u) */
#  endif /*BRS_ENABLE_CAN_CORE_SUPPORT*/
# endif /*BRS_ENABLE_CAN_SUPPORT*/
#endif /*!BRSMAINAPPL_DISABLE_CAN_EXCLUSIVEAREA_HANDLING*/
