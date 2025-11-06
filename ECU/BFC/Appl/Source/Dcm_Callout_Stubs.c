
/**********************************************************************************************************************
  COPYRIGHT
-----------------------------------------------------------------------------------------------------------------------
  \par      copyright
  \verbatim
  Copyright (c) 2022 by Vector Informatik GmbH.                                                  All rights reserved.

                This software is copyright protected and proprietary to Vector Informatik GmbH.
                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
                All other rights remain with Vector Informatik GmbH.
  \endverbatim
-----------------------------------------------------------------------------------------------------------------------
  FILE DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
  \file  File:  Dcm_Callout_Stubs.c
      Project:  Vector Basic Runtime System for MICROSAR4
       Module:  BrsMain

  \brief Description:  File for implementation of DCM callouts.
                       This file is a template only - please implement the callouts according to your needs.

  \attention Please note:
    The demo and example programs only show special aspects of the software. With regard to the fact
    that these programs are meant for demonstration purposes only, Vector Informatik liability shall be
    expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
**********************************************************************************************************************/

/**********************************************************************************************************************
  REVISION HISTORY
 ----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Description
 ----------------------------------------------------------------------------------------------------------------------
  01.00.00  2015-07-14  visbwa  Initial creation for usage with StartApplication
  01.00.01  2016-06-22  visbwa  Added sample code information block
  01.00.02  2016-08-29  visbwa  Added Dcm_DiagnosticService_0x38()
  01.00.03  2017-08-31  visbwa  Added callouts for Dcm_DiagnosticService 0x00, 0xB2, 0xB6 and 0xB7
  01.00.04  2017-12-06  visbwa  Reworked sample/example code disclaimer
  01.00.05  2019-02-01  visbwa  Added support for DCM ASR Version 4.2.2
  01.00.06  2019-03-11  vismaa  Changed DYNAMIC PART for Dcm_DiagnosticServiceXX
  01.00.07  2022-02-16  visbpz  Added callouts for additional services.
  01.00.08  2022-12-13  visrgm  Changed the return value of Dcm_GetProgConditions() according to TAR-11407
**********************************************************************************************************************/

/**********************************************************************************************************************
*  EXAMPLE CODE ONLY
*  -------------------------------------------------------------------------------------------------------------------
*  This Example Code is only intended for illustrating an example of a possible BSW integration and BSW configuration.
*  The Example Code has not passed any quality control measures and may be incomplete. The Example Code is neither
*  intended nor qualified for use in series production. The Example Code as well as any of its modifications and/or
*  implementations must be tested with diligent care and must comply with all quality requirements which are necessary
*  according to the state of the art before their use.
*********************************************************************************************************************/

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "Dcm.h"
#include "Dcm_Cfg.h"

/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/
#define DCM_START_SEC_CALLOUT_CODE
#include "MemMap.h"


#  define kFblBmFblStartMagicByte0        0x50u /* 'P' */
#  define kFblBmFblStartMagicByte1        0x72u /* 'r' */
#  define kFblBmFblStartMagicByte2        0x6Fu /* 'o' */
#  define kFblBmFblStartMagicByte3        0x67u /* 'g' */
#  define kFblBmFblStartMagicByte4        0x53u /* 'S' */
#  define kFblBmFblStartMagicByte5        0x69u /* 'i' */
#  define kFblBmFblStartMagicByte6        0x67u /* 'g' */
#  define kFblBmFblStartMagicByte7        0x6Eu /* 'n' */

#  define BM_NO_OF_MAGIC_BYTES            0x08u

#define FBLBM_MAIN_MAGICFLAG_START_SEC_VAR_NOINIT
#include "MemMap.h"
uint8                    FblBmMagicFlag[BM_NO_OF_MAGIC_BYTES];
#define FBLBM_MAIN_MAGICFLAG_STOP_SEC_VAR_NOINIT
#include "MemMap.h"

/**********************************************************************************************************************
  PART 1 - STATIC PART
   These Callouts are announced within Dcm_Core.h.
   The existence is configuration specific
**********************************************************************************************************************/
FUNC(void, DCM_CALLOUT_CODE) Dcm_Confirmation(Dcm_IdContextType idContext
                                             ,PduIdType dcmRxPduId
                                             ,Dcm_ConfirmationStatusType status)
{
}

#if (DCM_DIAG_JUMPTOFBL_ENABLED   == STD_ON) || \
    (DCM_DIAG_JUMPFROMFBL_ENABLED == STD_ON)
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_SetProgConditions(Dcm_ProgConditionsPtrType progConditions)
{
  /* Write magic flag for boot manager */
  if(progConditions->ReprogrammingRequest == TRUE)
  {
    FblBmMagicFlag[0] = kFblBmFblStartMagicByte0;
    FblBmMagicFlag[1] = kFblBmFblStartMagicByte1;
    FblBmMagicFlag[2] = kFblBmFblStartMagicByte2;
    FblBmMagicFlag[3] = kFblBmFblStartMagicByte3;
    FblBmMagicFlag[4] = kFblBmFblStartMagicByte4;
    FblBmMagicFlag[5] = kFblBmFblStartMagicByte5;
    FblBmMagicFlag[6] = kFblBmFblStartMagicByte6;
    FblBmMagicFlag[7] = kFblBmFblStartMagicByte7;
  }
  return DCM_E_OK;
}
#endif

#if (DCM_DIAG_JUMPFROMFBL_ENABLED == STD_ON)
FUNC(Dcm_EcuStartModeType, DCM_CALLOUT_CODE) Dcm_GetProgConditions(Dcm_ProgConditionsPtrType progConditions)
{
    return DCM_COLD_START;
}
#endif

#if (DCM_DCM_AR_VERSION >= DCM_DCM_AR_VERSION_422)
# if (DCM_SVC_23_SUPPORT_ENABLED == STD_ON)
//FUNC(Dcm_ReturnReadMemoryType, DCM_CALLOUT_CODE) Dcm_ReadMemory(Dcm_OpStatusType OpStatus
//                                                               ,uint8  MemoryIdentifier
//                                                               ,uint32 MemoryAddress
//                                                               ,uint32 MemorySize
//                                                               ,Dcm_MsgType MemoryData
//                                                               ,Dcm_NegativeResponseCodePtrType ErrorCode)
//{
//  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
//  return DCM_E_NOT_OK;
//}
# endif

# if (DCM_SVC_3D_SUPPORT_ENABLED == STD_ON)
//FUNC(Dcm_ReturnWriteMemoryType, DCM_CALLOUT_CODE) Dcm_WriteMemory(Dcm_OpStatusType OpStatus
//                                                                 ,uint8  MemoryIdentifier
//                                                                 ,uint32 MemoryAddress
//                                                                 ,uint32 MemorySize
//                                                                 ,Dcm_MsgType MemoryData
//                                                                 ,Dcm_NegativeResponseCodePtrType ErrorCode)
//{
//  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
//  return DCM_E_NOT_OK;
//}
# endif

#else
# if (DCM_SVC_23_SUPPORT_ENABLED == STD_ON)
//FUNC(Dcm_ReturnReadMemoryType, DCM_CALLOUT_CODE) Dcm_ReadMemory(Dcm_OpStatusType OpStatus
//                                                               ,uint8  MemoryIdentifier
//                                                               ,uint32 MemoryAddress
//                                                               ,uint32 MemorySize
//                                                               ,Dcm_MsgType MemoryData)
//{
//  return DCM_E_NOT_OK;
//}
# endif

# if (DCM_SVC_3D_SUPPORT_ENABLED == STD_ON)
//FUNC(Dcm_ReturnWriteMemoryType, DCM_CALLOUT_CODE) Dcm_WriteMemory(Dcm_OpStatusType OpStatus
//                                                                 ,uint8  MemoryIdentifier
//                                                                 ,uint32 MemoryAddress
//                                                                 ,uint32 MemorySize
//                                                                 ,Dcm_MsgType MemoryData)
//{
//  return DCM_E_NOT_OK;
//}
# endif
#endif /*DCM_DCM_AR_VERSION_422*/

// FUNC(Dcm_ReturnWriteMemoryType, DCMADDON_APPL_CODE) DcmAddOn_WriteMemory(                                                                             /* PRQA S 1753 */ /* MD_DcmAddOn_1753 */
 // Dcm_OpStatusType OpStatus,
 // uint8  MemoryIdentifier,
 // uint32 MemoryAddress,
 // uint32 MemorySize,
 // Dcm_MsgType MemoryData,
 // Dcm_NegativeResponseCodePtrType ErrorCode
 // )
// {
  // return DCM_E_NOT_OK;
// }

// FUNC(Dcm_ReturnReadMemoryType, DCMADDON_APPL_CODE) DcmAddOn_ReadMemory(                                                                               /* PRQA S 1753 */ /* MD_DcmAddOn_1753 */
 // Dcm_OpStatusType OpStatus,
 // uint8  MemoryIdentifier,
 // uint32 MemoryAddress,
 // uint32 MemorySize,
 // Dcm_MsgType MemoryData,
 // Dcm_NegativeResponseCodePtrType ErrorCode
 // )
// {
  // return DCM_E_NOT_OK;
// }

/**********************************************************************************************************************
  PART 2 - DYNAMIC PART
   These Callouts are announced within Dcm_Lcfg.h.
   The existence is configuration specific
**********************************************************************************************************************/
#if (DCM_DCM_AR_VERSION >= DCM_DCM_AR_VERSION_422)
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x00(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode)
{
  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return E_NOT_OK;
}
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x34(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode)
{
  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return E_NOT_OK;
}
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x35(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode)
{
  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return E_NOT_OK;
}
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x36(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode)
{
  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return E_NOT_OK;
}
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x37(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode)
{
  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return E_NOT_OK;
}
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0xB2(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode)
{
  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return E_NOT_OK;
}
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0xB6(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode)
{
  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return E_NOT_OK;
}
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0xB7(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode)
{
  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return E_NOT_OK;
}

#else
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x00(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x34(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x35(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x36(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x37(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x38(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0xB2(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0xB6(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0xB7(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
#endif /*DCM_DCM_AR_VERSION_422*/

# if (DCM_FBLMGR_SUPPORT_ENABLED == STD_ON)

FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ProcessRequestDownload(
  Dcm_OpStatusType OpStatus,
  uint8  DataFormatIdentifier,
  uint8  MemoryIdentifier,
  uint32 MemoryAddress,
  uint32 MemorySize,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) BlockLength,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  return E_NOT_OK;
}

FUNC(Dcm_ReturnWriteMemoryType, DCM_CALLOUT_CODE) Dcm_ProcessTransferDataWrite(
  Dcm_OpStatusType OpStatus,
  uint8  MemoryIdentifier,
  uint32 MemoryAddress,
  uint32 MemorySize,
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) MemoryData,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  return E_NOT_OK;
}

FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ProcessRequestTransferExit(
  Dcm_OpStatusType OpStatus,
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) transferRequestParameterRecord,
  uint32 transferRequestParameterRecordSize,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) transferResponseParameterRecord,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) transferResponseParameterRecordSize,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  return E_NOT_OK;
}
# endif /* (DCM_FBLMGR_SUPPORT_ENABLED == STD_ON) */

/**********************************************************************************************************************
  END of User implementation area
**********************************************************************************************************************/
#define DCM_STOP_SEC_CALLOUT_CODE
#include "MemMap.h"
