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
/** \file  File:  BrsHwStartup_TC2xx_TC3xx.h
 *      Project:  Vector Basic Runtime System
 *       Module:  BrsHw for platform Infineon Aurix/AurixPlus
 *
 *  \brief Description:  This is the hardware specific header file for Vector Basic Runtime System (BRS).
 *
 *  \attention Please note:
 *    The demo and example programs only show special aspects of the software. With regard to the fact
 *    that these programs are meant for demonstration purposes only, Vector Informatik liability shall be
 *    expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Description
 *  --------  ----------  ------  -------------------------------------------------------------------------------------
 *  01.00.00  2021-06-09  visto   creation
 *  01.00.01  2022-03-10  vismaa  Removed BRS_DISABLE_VIRTUALIZATION(); not needed anymore
 *  01.00.02  2022-12-23  vismaa  Added additional defines memory type
 *********************************************************************************************************************/

#ifndef _BRSHWSTARTUP_TC2XX_TC3XX_H_
#define _BRSHWSTARTUP_TC2XX_TC3XX_H_

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define BRS_CORE_ID_REGISTER  0xFE1C
#define BRS_PCXI_OFFSET       0xFE00
#define BRS_PSW_OFFSET        0xFE04
#define BRS_FCX_OFFSET        0xFE38
#define BRS_LCX_OFFSET        0xFE3C
#define BRS_BTV_OFFSET        0xFE24
#define BRS_BIV_OFFSET        0xFE20
#define BRS_PCON0_OFFSET      0x920C
#define BRS_CPU_VCON0_OFFSET  0xB000

#define BRS_READ_COREID()  BRS_MOVE_FROM_CSFR(BRS_CORE_ID_REGISTER)

#define BRS_TRICORE_UNLOCKENDINIT(CoreId, memoryType) BrsHwUnlockInitInline(CoreId, memoryType)
#define BRS_TRICORE_LOCKENDINIT(CoreId, memoryType)   BrsHwLockInitInline(CoreId, memoryType)

#define IN_ROM           1
#define IN_RAM           2
#define MEMORY_TYPE_RAM  2

#define BRSHW_DERIVATIVE_CORE0_ID  0x0u
#define BRSHW_DERIVATIVE_CORE1_ID  0x1u
#define BRSHW_DERIVATIVE_CORE2_ID  0x2u
#define BRSHW_DERIVATIVE_CORE3_ID  0x3u
#define BRSHW_DERIVATIVE_CORE4_ID  0x4u
#define BRSHW_DERIVATIVE_CORE5_ID  0x6u

#endif /*_BRSHWSTARTUP_TC2XX_TC3XX_H_*/
