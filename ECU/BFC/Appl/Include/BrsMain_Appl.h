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
/** \file  File:  BrsMain_Appl.h
 *      Project:  Vector Basic Runtime System
 *       Module:  BrsMain
 *
 *  \brief Description:  Header of additional, Application-specific, implementation
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

#ifndef _BRSMAIN_APPL_H_
#define _BRSMAIN_APPL_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "BrsMain.h"

#if defined (BRS_ENABLE_TESTSUITE_SUPPORT)
  #include "BrsTestsuite.h"
#endif

#if !defined (BRSMAINAPPL_DISABLE_CAN_EXCLUSIVEAREA_HANDLING)
# if defined (BRS_ENABLE_CAN_SUPPORT)
#  if defined (BRS_ENABLE_CAN_CORE_SUPPORT)
  #include "Can_30_Core.h"

#   if defined (VVIRTUALTARGET)
#    if defined (DRVCAN_CANOEEMUCANOEASR_VERSION)
  /* Combination of CanGen3 HW driver with CanGen2 VTT driver detected. Special exclusive area handling should be disabled */
  #define BRSMAINAPPL_DISABLE_CAN_EXCLUSIVEAREA_HANDLING
#    endif
#   else
  #include BRS_DRVCAN_HEADER_FILENAME
#   endif

#  elif defined (BRS_ENABLE_CAN_CLASSIC_SUPPORT)
  /* Just a check to verify, if either CAN_Classic or CAN_Core is active with CAN support enabled */

#  else
  #error "Neither a classic DrvCan nor a Can_30_Core DrvCan was detected, but DrvCan support is enabled. There seems to be something seems wrong here!"
#  endif /*BRS_ENABLE_CAN_X_SUPPORT*/
# endif /*BRS_ENABLE_CAN_SUPPORT*/
#endif /*BRSMAINAPPL_DISABLE_CAN_EXCLUSIVEAREA_HANDLING*/

/**********************************************************************************************************************
 *  CONFIGURATION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL TYPE DEFINITIONS
 *********************************************************************************************************************/
#if !defined (BRSMAINAPPL_DISABLE_CAN_EXCLUSIVEAREA_HANDLING) && defined (BRS_ENABLE_CAN_SUPPORT) && defined (BRS_ENABLE_CAN_CORE_SUPPORT)
# if defined (CAN_30_CORE_COREVERSION)
#  if (CAN_30_CORE_COREVERSION >= 0x0203u)
  #define BRSMAIN_CAN_30_CORE_SPECIFIC_MEMMAP /* include "Can_30_Core_MemMap.h" instead of "MemMap.h" */
#  endif
# elif defined (CAN_30_CORE_SW_MAJOR_VERSION)
  #define CAN_30_CORE_SPECIFIC_MEMMAP /* include "Can_30_Core_MemMap.h" instead of "MemMap.h" */
# else
  #error "Detection of Can_30_Core driver version was not possible. Please configure here manually the valid MemMap header of the module."
# endif
#endif

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL VARIABLES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
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
void BrsMain_Appl_Init(void);

#if defined (BRS_ENABLE_HYPERVISOR_SUPPORT)
/*****************************************************************************/
/* @brief      This is a temporary API for the Hypervisor Demo
 * @pre        -
 * @param[in]  coreID is the physical core ID of the actual running core
 * @param[out] -
 * @return     -
 * @context    Function is called from main
 *****************************************************************************/
void BrsMain_Appl_HypervisorApi(uint32);
#endif

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
BRS_DRVCAN_EXCLUSIVE_AREA_INFIX(Enter,EXCLUSIVE_AREA_0);
BRS_DRVCAN_EXCLUSIVE_AREA_INFIX(Exit,EXCLUSIVE_AREA_0);
BRS_DRVCAN_EXCLUSIVE_AREA_INFIX(Enter,EXCLUSIVE_AREA_6);
BRS_DRVCAN_EXCLUSIVE_AREA_INFIX(Exit,EXCLUSIVE_AREA_6);
#define CAN_STOP_SEC_CODE
/* to support CAN driver name infix, vBRS generator provides a wrapper
   for usage of the driver specific MemMap.h define in vBrsCfg.h */
#include "vBrsCfg.h"

#   if !defined (BRS_ENABLE_FBL_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
void SchM_Enter_CanIf_CANIF_EXCLUSIVE_AREA_0(void);
void SchM_Exit_CanIf_CANIF_EXCLUSIVE_AREA_0(void);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANSM_START_SEC_CODE
#include "MemMap.h"
void SchM_Enter_CanSM_CANSM_EXCLUSIVE_AREA_4(void);
void SchM_Exit_CanSM_CANSM_EXCLUSIVE_AREA_4(void);
void SchM_Enter_CanSM_CANSM_EXCLUSIVE_AREA_1(void);
void SchM_Exit_CanSM_CANSM_EXCLUSIVE_AREA_1(void);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

#define COMM_START_SEC_CODE
#include "MemMap.h"
void SchM_Enter_ComM_COMM_EXCLUSIVE_AREA_1(void);
void SchM_Exit_ComM_COMM_EXCLUSIVE_AREA_1(void);
#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#   endif /*!BRS_ENABLE_FBL_SUPPORT*/
#  endif /*BRS_ENABLE_CAN_CLASSIC_SUPPORT*/

#  if defined (BRS_ENABLE_CAN_CORE_SUPPORT)
/***********************************************************************************************************************
 * A new (Gen3) DrvCan is part of the configuration. New implementation is needed
 **********************************************************************************************************************/
#   if ((Can_30_Core_IsHardwareCancelByApplOfGeneralFeature(0u) == TRUE) && (Can_30_Core_IsHardwareLoopCheckOfGeneralFeature(0u) == TRUE))

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
void Appl_30_CoreCanTimerStart(uint8, uint8);
void Appl_30_CoreCanTimerEnd(uint8, uint8);
Can_ReturnType Appl_30_CoreCanTimerLoop(uint8, uint8);
#define CAN_30_CORE_STOP_SEC_CODE
#     if defined (BRSMAIN_CAN_30_CORE_SPECIFIC_MEMMAP)
  #include "Can_30_Core_MemMap.h"
#     else
  #include "MemMap.h"
#     endif
#    endif /*!BRS_ENABLE_FBL_SUPPORT*/

#   else
/***********************************************************************************************************************
 * UserDefined ExclusiveArea handling for CAN Driver Core, according to TechnicalReference_Can_30_Core.pdf, Note within chapter 3.2
 **********************************************************************************************************************/
#define CAN_30_CORE_START_SEC_CODE
#    if defined (BRSMAIN_CAN_30_CORE_SPECIFIC_MEMMAP)
  #include "Can_30_Core_MemMap.h"
#    else
  #include "MemMap.h"
#    endif
void SchM_Enter_Can_30_Core_CAN_30_CORE_EXCLUSIVE_AREA_6(void);
void SchM_Exit_Can_30_Core_CAN_30_CORE_EXCLUSIVE_AREA_6(void);
#define CAN_30_CORE_STOP_SEC_CODE
#    if defined (BRSMAIN_CAN_30_CORE_SPECIFIC_MEMMAP)
  #include "Can_30_Core_MemMap.h"
#    else
  #include "MemMap.h"
#    endif

#    if !defined (BRS_ENABLE_CAN_CLASSIC_SUPPORT)
/***********************************************************************************************************************
 * UserDefined ExclusiveArea handling for vCAN Driver, according to TechnicalReference_vCan_30_Mcan.pdf, Note within chapter 3.2
 **********************************************************************************************************************/
#define CAN_START_SEC_CODE
/* to support CAN driver name infix, vBRS generator provides a wrapper
   for usage of the driver specific MemMap.h define in vBrsCfg.h */
#include "vBrsCfg.h"
BRS_DRVCAN_EXCLUSIVE_AREA_INFIX(Enter,EXCLUSIVE_AREA_0);
BRS_DRVCAN_EXCLUSIVE_AREA_INFIX(Exit,EXCLUSIVE_AREA_0);
BRS_DRVCAN_EXCLUSIVE_AREA_INFIX(Enter,EXCLUSIVE_AREA_1);
BRS_DRVCAN_EXCLUSIVE_AREA_INFIX(Exit,EXCLUSIVE_AREA_1);
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
BRS_DRVCAN1_EXCLUSIVE_AREA_INFIX(Enter,EXCLUSIVE_AREA_0);
BRS_DRVCAN1_EXCLUSIVE_AREA_INFIX(Exit,EXCLUSIVE_AREA_0);
BRS_DRVCAN1_EXCLUSIVE_AREA_INFIX(Enter,EXCLUSIVE_AREA_1);
BRS_DRVCAN1_EXCLUSIVE_AREA_INFIX(Exit,EXCLUSIVE_AREA_1);
#define CAN1_STOP_SEC_CODE
/* to support CAN driver name infix, vBRS generator provides a wrapper
   for usage of the driver specific MemMap.h define in vBrsCfg.h */
#include "vBrsCfg.h"
#    endif /*BRS_DRVCAN1_HEADER_FILENAME*/

#    if !defined (BRS_ENABLE_FBL_SUPPORT)
#     if !defined (BRS_ENABLE_CAN_CLASSIC_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
void SchM_Enter_CanIf_CANIF_EXCLUSIVE_AREA_0(void);
void SchM_Exit_CanIf_CANIF_EXCLUSIVE_AREA_0(void);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANSM_START_SEC_CODE
#include "MemMap.h"
void SchM_Enter_CanSM_CANSM_EXCLUSIVE_AREA_4(void);
void SchM_Exit_CanSM_CANSM_EXCLUSIVE_AREA_4(void);
void SchM_Enter_CanSM_CANSM_EXCLUSIVE_AREA_1(void);
void SchM_Exit_CanSM_CANSM_EXCLUSIVE_AREA_1(void);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

#define COMM_START_SEC_CODE
#include "MemMap.h"
void SchM_Enter_ComM_COMM_EXCLUSIVE_AREA_1(void);
void SchM_Exit_ComM_COMM_EXCLUSIVE_AREA_1(void);
#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#     endif /*!BRS_ENABLE_CAN_CLASSIC_SUPPORT*/
#    endif /*!BRS_ENABLE_FBL_SUPPORT*/
#   endif /* Can_30_Core_IsHardwareCancelByApplOfGeneralFeature(0u) && Can_30_Core_IsHardwareLoopCheckOfGeneralFeature(0u) */
#  endif /*BRS_ENABLE_CAN_CORE_SUPPORT*/
# endif /*BRS_ENABLE_CAN_SUPPORT*/
#endif /*!BRSMAINAPPL_DISABLE_CAN_EXCLUSIVEAREA_HANDLING*/
#endif /*_BRSMAIN_APPL_H_*/
