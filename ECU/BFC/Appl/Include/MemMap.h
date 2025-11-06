/**********************************************************************************************************************
*  COPYRIGHT
*  -------------------------------------------------------------------------------------------------------------------
*  \verbatim
*  Copyright (c) 2021- 2022 by Vector Informatik GmbH.                                           All rights reserved.
*
*                 This software is copyright protected and proprietary to Vector Informatik GmbH.
*                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
*                 All other rights remain with Vector Informatik GmbH.
*  \endverbatim
*  -------------------------------------------------------------------------------------------------------------------
*  FILE DESCRIPTION
*  -------------------------------------------------------------------------------------------------------------------
*         File:  MemMap.h
*
*  Description:  This MemMap.h provides all the memory section definitions from the template MemMap file of each package 
*
*********************************************************************************************************************/

#include "_Compiler_Cfg_MSR4_MPP_Aurix_2G_TC3xx_Tasking.h"

#if defined( FBLBM_MAIN_MAGICFLAG_START_SEC_VAR_NOINIT )
# pragma section nearbss "MagicFlagSection"
# pragma section farbss "MagicFlagSection"
# undef FBLBM_MAIN_MAGICFLAG_START_SEC_VAR_NOINIT
# undef FBL_MEMMAP_ERROR
#endif

#define MEMMAP_REMAPPING_ONLY
# include "_MemMap_MSR4_MBP.h"
# include "_MemMap_MSR4_MCP.h"
#undef MEMMAP_REMAPPING_ONLY
//# include "_MemMap_MSR4_MPP_VTT.h"
