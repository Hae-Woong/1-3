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



#define MEMMAP_REMAPPING_ONLY
# include "_MemMap_MSR4_MBP.h"
# include "_MemMap_MSR4_MCP.h"
#undef MEMMAP_REMAPPING_ONLY
# include "MemMap_MSR4_MPP_VTT.h"
