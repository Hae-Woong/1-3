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
/** \file  File:  BrsHwStartup.c
 *      Project:  Vector Basic Runtime System
 *       Module:  BrsHw for platform Infineon Aurix/AurixPlus
 *     Template:  This file is reviewed according to Brs_Template@Implementation[1.03.05]
 *
 *  \brief Description:  This file contains the assembler part of the BRS StartUpCode.
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

#define _BRSHWSTARTUP_C_
#define BRSHWSTARTUP_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "BrsHw.h"

#if defined (BRS_FIRST_EXECUTION_INSTANCE)
/* This code is only needed for the first instance/executable in the system */

#include "vBrs_Lcfg.h"
#include "vLinkGen_Lcfg.h"

# include "BrsHwStartup_TC2xx_TC3xx.h"

/**********************************************************************************************************************
 *  CONFIGURATION CHECK
 *********************************************************************************************************************/
#if defined (BRS_COMP_TASKING)    

#else
  #error "Unknown compiler specified!"
#endif

#if (VLINKGEN_CFG_MAJOR_VERSION != 2u)
  #error "This StartUpCode is dependent to the vLinkGen version! vLinkGen major version does not fit!"
#else
# if (VLINKGEN_CFG_MINOR_VERSION < 5u)
  #error "This StartUpCode is dependent to the vLinkGen version! Your vLinkGen minor version is too old!"
# endif
#endif

#if defined (BRS_ENABLE_FBL_SUPPORT) && defined (BRS_ENABLE_ETHERNET_SUPPORT)
# define BrsStartupPSW_ResetValue 0x00000BFFUL /* disable calldepthcounter CDC */
#else
# define BrsStartupPSW_ResetValue 0x00000B80UL /* CDC limit = 64 calls */
#endif

#define BrsStartupStackSize 4096ul

typedef uint32 BRS_CSA_Element[16]; /* one CSA element consists of 16 x 32 bit */

extern uint32 _Brs_ExcVect_START;

const uint32 Brs_SizeOfbrsMain_CoreType = sizeof(brsMain_CoreType);

/**********************************************************************************************************************
 *  FUNCTION DEFINITIONS
 *********************************************************************************************************************/
/* =========================================================================== */
/*                                                                             */
/* Description: Entry point for all cores                                      */
/*                                                                             */
/* =========================================================================== */
/* this macro is implemented for each compiler in BrsHw.h */
/* it implements an early stack switch */
BRS_ASSEMBLER_CODESECTION(brsStartup)
BRS_ASSEMBLER_ALIGN(32)
BRS_ASSEMBLER_EXTERNDECLARATION(BrsMain_CoreConfig_Size)
BRS_ASSEMBLER_EXTERNDECLARATION(BrsMain_CoreConfig)
BRS_ASSEMBLER_GLOBALDECLARATION(brsStartupEntry)
BRS_ASSEMBLER_LABEL(brsStartupEntry)
BRS_ASSEMBLER_STARTUP_CODE()


void BRS_FORCE_ACTIVE brsStartupEntry_C(void)
{
  /* CurrentCoreConfig is still stored in d6 from Assembler Startup code. BRS_GET_CURRENT_CONFIG must be called at the
     beginning of brsStartupEntry_C to guarantee consistency. */
  uint32 CurrentCoreConfig;
  BRS_GET_CURRENT_CONFIG(&CurrentCoreConfig);
#if (defined (VLINKGEN_CFG_NUM_ZERO_INIT_EARLY_BLOCKS) && (VLINKGEN_CFG_NUM_ZERO_INIT_EARLY_BLOCKS>1uL)) \
 || (defined (VLINKGEN_CFG_NUM_ZERO_INIT_EARLY_GROUPS) && (VLINKGEN_CFG_NUM_ZERO_INIT_EARLY_GROUPS>1uL))
  uint32 CurrentCoreId = BRS_READ_COREID();
#endif 
  uint32 AuxVariable = 0;
  BRS_MOVE_TO_CSFR(BRS_PCON0_OFFSET, 0x0UL); /* setting the PCON0 to zero disables the cache bypass (thus program caching is enabled) */

/* =========================================================================== */
/*                                                                             */
/* Description: Initialize memory blocks and groups with zero                  */
/*                                                                             */
/* =========================================================================== */
#if defined (VLINKGEN_CFG_NUM_ZERO_INIT_EARLY_BLOCKS)
# if (VLINKGEN_CFG_NUM_ZERO_INIT_EARLY_BLOCKS>1uL)
  /* Loop over all entries of vLinkGen_ZeroInit_Early_Blocks and zero the configured memory blocks. */
  volatile uint32 *memPtr;
  uint32 u32End;
  uint8 blockNum;
  for(blockNum = 0; blockNum < vLinkGen_ZeroInit_Early_BlocksSet.Num; blockNum++)
  {
    if(vLinkGen_ZeroInit_Early_BlocksSet.Areas[blockNum].Core == CurrentCoreId &&
      (vLinkGen_ZeroInit_Early_BlocksSet.Areas[blockNum].End - vLinkGen_ZeroInit_Early_BlocksSet.Areas[blockNum].Start) > 0)
    {
      memPtr = (volatile uint32 *)vLinkGen_ZeroInit_Early_BlocksSet.Areas[blockNum].Start;
      u32End = vLinkGen_ZeroInit_Early_BlocksSet.Areas[blockNum].End;
      while((uint32)memPtr < u32End)
      {
        *memPtr = 0x0;
        memPtr++;
      }
    }
  }
# endif /*VLINKGEN_CFG_NUM_ZERO_INIT_EARLY_BLOCKS>1uL*/

#else
  #error "Mandatory define VLINKGEN_CFG_NUM_ZERO_INIT_EARLY_BLOCKS missing within vLinkGen configuration!"
#endif /*VLINKGEN_CFG_NUM_ZERO_INIT_EARLY_BLOCKS*/

#if defined (VLINKGEN_CFG_NUM_ZERO_INIT_EARLY_GROUPS)
# if (VLINKGEN_CFG_NUM_ZERO_INIT_EARLY_GROUPS>1uL)
  /* Loop over all entries of vLinkGen_ZeroInit_Early_Groups and zero the configured memory areas. */
  volatile uint32 *memPtr2;
  uint32 u32End2;
  uint8 areaNum;
  for(areaNum = 0; areaNum < vLinkGen_ZeroInit_Early_GroupsSet.Num; areaNum++)
  {
    if(vLinkGen_ZeroInit_Early_GroupsSet.Areas[areaNum].Core == CurrentCoreId &&
      (vLinkGen_ZeroInit_Early_GroupsSet.Areas[areaNum].End - vLinkGen_ZeroInit_Early_GroupsSet.Areas[areaNum].Start) > 0)
    {
      memPtr2 = (volatile uint32 *)vLinkGen_ZeroInit_Early_GroupsSet.Areas[areaNum].Start;
      u32End2 = vLinkGen_ZeroInit_Early_GroupsSet.Areas[areaNum].End;
      while((uint32)memPtr2 < u32End2)
      {
        *memPtr2 = 0x0;
        memPtr2++;
      }
    }
  }
# endif /*VLINKGEN_CFG_NUM_ZERO_INIT_EARLY_GROUPS>1uL*/

#else
  #error "Mandatory define VLINKGEN_CFG_NUM_ZERO_INIT_EARLY_GROUPS missing within vLinkGen configuration!"
#endif /*VLINKGEN_CFG_NUM_ZERO_INIT_EARLY_GROUPS*/

/* =========================================================================== */
/* Set the PSW to its reset value in case of a warm start */
/* =========================================================================== */
  BRS_MOVE_TO_CSFR(BRS_PSW_OFFSET, BrsStartupPSW_ResetValue);

/* =========================================================================== */
/* Set the PCXS and PCXO to its reset value in case of a warm start */
/* =========================================================================== */
  AuxVariable = BRS_MOVE_FROM_CSFR(BRS_PCXI_OFFSET);
  AuxVariable &= 0xfff00000UL;
  BRS_MOVE_TO_CSFR(BRS_PCXI_OFFSET, AuxVariable);

/* =========================================================================== */
/* initialize the CSAs (inlined function) */
/* aftwerwards function calls are possible */
/* =========================================================================== */
  BRS_CSA_Element* CSA;
  uint32 NumberOfCSA;
  uint32 pcxi_val = 0;    /* the last PCXI has to point to 0 */
  uint32 CSAReserve = 20; /* the LCX will be initalized to point to 20 CSAs before the very last CSA */
  uint32 seg_nr, seg_idx; /* auxiliary variables to assemble the PCXI value */

  BRS_CSA_Element* CSAAddress = (BRS_CSA_Element*)((uint32)BrsMain_CoreConfig[CurrentCoreConfig].StartupStackEndLabel - (uint32)BrsMain_CoreConfig[CurrentCoreConfig].StartupStackSize);
  uint32 CSA_Numbers = ((uint32)BrsMain_CoreConfig[CurrentCoreConfig].StartupStackEndLabel - BrsStartupStackSize - (uint32)CSAAddress) / 64;

  if (CSA_Numbers<512)
  {
    /* The configured stack size is smaller than the recommended one!
     * Beginning with vBaseEnv 2.17, the startup stack setup was harmonized and the stack sizes are configured automatically via the vBRS generator
     * (vBRS/vBRSGeneral/vBRSEnableCoreSpecificVLinkGenConfig).
     * The recommended default for the Aurix platforms is 36864 Byte, listed in vBaseEnv/vBaseEnvGeneral/vBaseEnvStartupStackSettings/vBaseEnvStackSize.
     * This means, BrsStartupStackSize Byte for the startup stack and 512 CSA list entries (64 Byte each). There is no separated section for the CSAs anymory,
     * they are placed in STACK_Cx, together with the startup stack. Be aware, that the CSAs are shared across all execution instances
     * (vBRS/vBRSGeneral/vBRSExecutionInstance). All instances inherit it from the first execution instance (vBRS/vBRSGeneral/vBRSFirstInstance).
     * Uncomment this loop, if you intentionally reduced the size of STACK_Cx and ensure it is suitable for your project.
     * Otherwise, please increase the size of STACK_Cx to at least 36864 (vLinkGenVarSectionGroup/vLinkGenVarSectionGroupSize).
     */
    while (1);
  }

  if(CSAAddress != 0)
  {
    CSA = CSAAddress;
    for (NumberOfCSA=0; NumberOfCSA < CSA_Numbers; NumberOfCSA++) /* loop over all CSA elements */
    {
      *CSA[0] = pcxi_val; /* *CSA is equal to CSA[0] is equal to CSA.PCXI (it holds the PCXI value and has to point to the next PCXI) */

      /* now translate the current CSA address to a valid PCXI value which is used within the AURIX registers */
      seg_nr  = (((unsigned int)CSA >> 28) & 0xf) << 16;
      seg_idx = (((unsigned int)CSA >> 6) & 0xffff);
      pcxi_val = seg_nr | seg_idx;
      if (NumberOfCSA == CSAReserve) /* reserve CSAs for exception handling */
      {
        BRS_MOVE_TO_CSFR(BRS_LCX_OFFSET, pcxi_val);
      }
      CSA++; /* point to the next CSA */
    }
    BRS_MOVE_TO_CSFR(BRS_FCX_OFFSET, pcxi_val);
  }

  /* Program the brs default vector table base addresses to handle exceptions during startup */
  BrsHw_ExceptionTable_Init((Brs_AddressOfConstType)&_Brs_ExcVect_START, BRS_DEFINE_ADDRESS_UNUSED);

/* =========================================================================== */
/*                                                                             */
/* Description: Jump to Brs_PreMainStartup() (BrsMainStartup.c)                */
/*                                                                             */
/* =========================================================================== */
  Brs_PreMainStartup();

/* =========================================================================== */
/*                                                                             */
/* Description: Jump to BrsMainExceptionStartup() in case of an unexpected     */
/*              return from PreMain/main                                       */
/*                                                                             */
/* =========================================================================== */
  BrsMainExceptionStartup();
}

#endif /*BRS_FIRST_EXECUTION_INSTANCE*/
