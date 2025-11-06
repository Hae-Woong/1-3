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
/** \file  File:  BrsHw.c
 *      Project:  Vector Basic Runtime System
 *       Module:  BrsHw for platform Infineon Aurix/AurixPlus
 *     Template:  This file is reviewed according to Brs_Template@Implementation[1.03.06]
 *
 *  \brief Description:  This is the hardware specific code file for Vector Basic Runtime System (BRS).
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
 //test3
/**********************************************************************************************************************
 *  EXAMPLE CODE ONLY
 *  -------------------------------------------------------------------------------------------------------------------
 *  This Example Code is only intended for illustrating an example of a possible BSW integration and BSW configuration.
 *  The Example Code has not passed any quality control measures and may be incomplete. The Example Code is neither
 *  intended nor qualified for use in series production. The Example Code as well as any of its modifications and/or
 *  implementations must be tested with diligent care and must comply with all quality requirements which are necessary
 *  according to the state of the art before their use.
 *********************************************************************************************************************/
#define _BRSHW_C_
#define BRSHW_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "BrsHw.h"

#if !defined (BRS_ENABLE_FBL_SUPPORT)
# include "Os.h"
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
#if (BRSHW_VERSION != 0x0303u)
# error "Header and source file are inconsistent!"
#endif
#if (BRSHW_BUGFIX_VERSION != 0x04u)
# error "Different versions of bugfix in Header and Source used!"
#endif

/**********************************************************************************************************************
 *  CONFIGURATION CHECK
 *********************************************************************************************************************/
#if defined (BRS_COMP_TASKING)    

#else
# error "Unknown compiler specified!"
#endif

/**********************************************************************************************************************
 *  DEFINITION + MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL VARIABLES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONST VARIABLES
 *********************************************************************************************************************/
/*
 * Description: These constants are used to propagate the Versions over
 *              module boundaries.The version numbers are BCD coded. E.g. a sub
 *              version of 23 is coded with 0x23, a bug fix version of 9 is
 *              coded 0x09.
 */
uint8 const kBrsHwMainVersion   = (uint8)(BRSHW_VERSION >> 8);
uint8 const kBrsHwSubVersion    = (uint8)(BRSHW_VERSION & 0xFF);
uint8 const kBrsHwBugfixVersion = (uint8)(BRSHW_BUGFIX_VERSION);

# if defined (BRS_WATCHDOG_GROUP_A)
#define WDTCON_ADDRESS   {BRS_SFR_WDTCPU0CON0_ADDRESS, BRS_SFR_WDTCPU0CON1_ADDRESS}, \
                         {BRS_SFR_WDTCPU1CON0_ADDRESS, BRS_SFR_WDTCPU1CON1_ADDRESS}, \
                         {BRS_SFR_WDTCPU2CON0_ADDRESS, BRS_SFR_WDTCPU2CON1_ADDRESS}, \
                         {BRS_SFR_WDTSCON0_ADDRESS, BRS_SFR_WDTSCON1_ADDRESS}

# elif defined (BRS_WATCHDOG_GROUP_B)
#define WDTCON_ADDRESS   {BRS_SFR_WDTCPU0CON0_ADDRESS, BRS_SFR_WDTCPU0CON1_ADDRESS}, \
                         {BRS_SFR_WDTCPU1CON0_ADDRESS, BRS_SFR_WDTCPU1CON1_ADDRESS}, \
                         {BRS_SFR_WDTCPU2CON0_ADDRESS, BRS_SFR_WDTCPU2CON1_ADDRESS}, \
                         {BRS_SFR_WDTCPU3CON0_ADDRESS, BRS_SFR_WDTCPU3CON1_ADDRESS}, \
                         {BRS_SFR_WDTCPU4CON0_ADDRESS, BRS_SFR_WDTCPU4CON1_ADDRESS}, \
                         {0, 0}, /* core ID 5 is not a valid core ID */ \
                         {BRS_SFR_WDTCPU5CON0_ADDRESS, BRS_SFR_WDTCPU5CON1_ADDRESS}, \
                         {BRS_SFR_WDTSCON0_ADDRESS, BRS_SFR_WDTSCON1_ADDRESS}
#endif

#if defined (BRS_ENABLE_FBL_SUPPORT)
 #define BRS_START_SEC_RAM_CONST
 #include "Brs_MemMap.h"
#endif

# if defined (BRS_COMP_TASKING)
#pragma protect
# endif

# if defined (BRS_WATCHDOG_GROUP_A)
const Brs_WdtRegTypes kBrsWdtCon0Addresses_RAM[4] = {
  WDTCON_ADDRESS
};

# elif defined (BRS_WATCHDOG_GROUP_B)
const Brs_WdtRegTypes kBrsWdtCon0Addresses_RAM[8] = {
  WDTCON_ADDRESS
};
# endif /*BRS_WATCHDOG_GROUP_x*/

#if defined (BRS_ENABLE_FBL_SUPPORT)
 #define BRS_STOP_SEC_RAM_CONST
 #include "Brs_MemMap.h"
#endif

# if defined (BRS_COMP_TASKING)
#pragma endprotect
# endif

# if defined (BRS_WATCHDOG_GROUP_A)
const Brs_WdtRegTypes kBrsWdtCon0Addresses_ROM[4] = {
  WDTCON_ADDRESS
};

# elif defined (BRS_WATCHDOG_GROUP_B)
const Brs_WdtRegTypes kBrsWdtCon0Addresses_ROM[8] = {
  WDTCON_ADDRESS
};
# endif /*BRS_WATCHDOG_GROUP_x*/

#if defined (BRS_FIRST_EXECUTION_INSTANCE)
/* This code is only needed for the first instance/executable in the system */
# if defined (BRS_COMP_TASKING)
#pragma protect
# endif
/* Boot Mode Headers - use boot from internal flash    */
/* At least 1 of these headers has to be present       */
/* TODO: Check if this configuration suits your setup. */

/*+++++++++++++++++++++++++++++++++++++Attention!++++++++++++++++++++++++++++++++++++++++++++++++++++++
++ If you have to adjust the bmiField you have to change the bmi header value and CRC calculation.    +
++ Otherwise you could be locked out of your device! Read the manual for more information.            +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
# if defined (BRS_COMP_TASKING)
#pragma section farrom "BMHD3"
# endif
# if defined (BRS_DERIVATIVE_GROUP_TC2xx)
volatile const uint32 bmiField0[0x08] =
{
  0x80000020ul, 0xB3590070ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0xA36F68D6ul, 0x5C909729ul
};

# elif defined (BRS_DERIVATIVE_GROUP_TC3xx)
volatile const uint32 bmiField0[128] =
{
  0xB359000Eul, 0x80000000ul, 0xD97FAA13ul, 0x268055ECul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x00000000ul, 0x00000000ul, 0x00000000ul, 0x00000000ul,
  0x43211234ul, 0x00000000ul, 0x00000000ul, 0x00000000ul  /* UCB CONFIRMATION - 32-bit CODE = UNLOCKED */
};
# endif /*BRS_DERIVATIVE_GROUP_x*/
# if defined (BRS_COMP_TASKING)
#pragma section farrom restore
# endif
#endif /*BRS_FIRST_EXECUTION_INSTANCE*/

/**********************************************************************************************************************
 *  LOCAL VARIABLES AND LOCAL HW REGISTERS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  CONTROLLER CONFIGURATION REGISTERS
 *********************************************************************************************************************/
#if defined (BRS_PLL_GROUP_A)
/*******************************************************************************
  PLL  GROUP  CONFIG
*******************************************************************************/
#define BRS_PLLCLC        BRSHW_IOS(uint32, 0xF0000040) /* original name: PLL_CLC */
#define BRS_VCO_BYPASS    0x00000020
#define BRS_OSC_DISC      0x01000000
#define BRS_PLL_LOCK      0x00000001
#define BRS_PLL_LOCK_RES  0x00000002
#define BRS_CLOCK_MASK    0x007FFFC4

/*******************************************************************************
  SYSTEM  CONTROL  UNIT  SCU
*******************************************************************************/
#define BRS_SCU_BASE  0xF0036000

#define BRS_SCU_OSCCON       BRSHW_IOS(uint32, BRS_SCU_BASE + 0x10)  /* OSCCON  OSC Control Register; Safety Endinit Protected */
#define BRS_SCU_PLLCON0      BRSHW_IOS(uint32, BRS_SCU_BASE + 0x18)  /* PLLCON0 PLL Configuration 0 Register; Safety Endinit Protected */
#define BRS_SCU_PLLCON1      BRSHW_IOS(uint32, BRS_SCU_BASE + 0x1C)  /* PLLCON1 PLL Configuration 1 Register; Safety Endinit Protected */
#define BRS_SCU_PLLCON2      BRSHW_IOS(uint32, BRS_SCU_BASE + 0x20)  /* PLLCON2 PLL Configuration 2 Register; Safety Endinit Protected */
#define BRS_SCU_PLLSTAT      BRSHW_IOS(uint32, BRS_SCU_BASE + 0x14)  /* PLLSTAT PLL Status Register */

#define BRS_SCU_CCUCON0      BRSHW_IOS(uint32, BRS_SCU_BASE + 0x30)  /* CCUCON0 CCU Control Register 0; Safety Endinit Protected */
#define BRS_SCU_CCUCON1      BRSHW_IOS(uint32, BRS_SCU_BASE + 0x34)  /* CCUCON1 CCU Control Register 1; Safety Endinit Protected */
#define BRS_SCU_CCUCON5      BRSHW_IOS(uint32, BRS_SCU_BASE + 0x4C)  /* CCUCON5 CCU Control Register 5; Safety Endinit Protected */
#define BRS_SCU_CCUCON6      BRSHW_IOS(uint32, BRS_SCU_BASE + 0x80)  /* CCUCON6 CCU Control Register 6; Safety Endinit Protected */
#define BRS_SCU_CCUCON7      BRSHW_IOS(uint32, BRS_SCU_BASE + 0x84)  /* CCUCON7 CCU Control Register 7; Safety Endinit Protected */
#define BRS_SCU_CCUCON8      BRSHW_IOS(uint32, BRS_SCU_BASE + 0x88)  /* CCUCON8 CCU Control Register 8; Safety Endinit Protected */

#define BRS_SCU_PLLERAYCON0  BRSHW_IOS(uint32, BRS_SCU_BASE + 0x28)  /* PLL_ERAY Configuration 0 Register; Safety Endinit Protected */
#define BRS_SCU_PLLERAYCON1  BRSHW_IOS(uint32, BRS_SCU_BASE + 0x2C)  /* PLL_ERAY Configuration 1 Register; Safety Endinit Protected */
#define BRS_SCU_PLLERAYSTAT  BRSHW_IOS(uint32, BRS_SCU_BASE + 0x24)  /* PLL_ERAY Status Register */

#define BRS_RSTSTAT          BRSHW_IOS(uint32, BRS_SCU_BASE + 0x50)  /* Reset Status Register */
#define BRS_RSTCON           BRSHW_IOS(uint32, BRS_SCU_BASE + 0x58)  /* Reset Configuration Register */
#define BRS_SWRSTCON         BRSHW_IOS(uint32, BRS_SCU_BASE + 0x60)  /* Software Reset Configuration Register; Safety Endinit Protected */
#define BRS_SCU_TRAPCLR      BRSHW_IOS(uint32, BRS_SCU_BASE + 0x12C) /* Trap Clear Register */
#define BRS_SCU_TRAPDIS      BRSHW_IOS(uint32, BRS_SCU_BASE + 0x130) /* Trap Disable Register; Endinit Protected */

/*******************************************************************************
  GENERAL PURPOSE TIMER CLOCK CONTROL REGISTER
*******************************************************************************/
#define BRS_GPT120_BASE  0xF0002E00
#define BRS_GPT120_CLC       BRSHW_IOS(uint32, BRS_GPT120_BASE)

#elif defined (BRS_PLL_GROUP_B)
/*******************************************************************************
  SYSTEM  CONTROL  UNIT  SCU
*******************************************************************************/
#define BRS_SCU_BASE  0xF0036000

#define BRS_SCU_OSCCON       BRSHW_IOS(uint32, BRS_SCU_BASE + 0x10)  /* OSCCON  OSC Control Register */
#define BRS_SCU_SYSPLLCON0   BRSHW_IOS(uint32, BRS_SCU_BASE + 0x18)  /* SYSPLLCON0 System PLL Configuration 0 Register */
#define BRS_SCU_SYSPLLCON1   BRSHW_IOS(uint32, BRS_SCU_BASE + 0x1C)  /* SYSPLLCON1 System PLL Configuration 1 Register */
#define BRS_SCU_SYSPLLCON2   BRSHW_IOS(uint32, BRS_SCU_BASE + 0x20)  /* SYSPLLCON2 System PLL Configuration 2 Register */
#define BRS_SCU_SYSPLLSTAT   BRSHW_IOS(uint32, BRS_SCU_BASE + 0x14)  /* SYSPLLSTAT System PLL Status Register */

#define BRS_SCU_CCUCON0      BRSHW_IOS(uint32, BRS_SCU_BASE + 0x30)  /* CCUCON0 CCU Control Register  0 */
#define BRS_SCU_CCUCON1      BRSHW_IOS(uint32, BRS_SCU_BASE + 0x34)  /* CCUCON1 CCU Control Register  1 */

#define BRS_SCU_CCUCON2      BRSHW_IOS(uint32, BRS_SCU_BASE + 0x40)  /* CCUCON2 CCU Control Register  2 */
#define BRS_SCU_CCUCON5      BRSHW_IOS(uint32, BRS_SCU_BASE + 0x4C)  /* CCUCON5 CCU Control Register  5 */
#define BRS_SCU_CCUCON6      BRSHW_IOS(uint32, BRS_SCU_BASE + 0x80)  /* CCUCON6 CCU Control Register  6 */
#define BRS_SCU_CCUCON7      BRSHW_IOS(uint32, BRS_SCU_BASE + 0x84)  /* CCUCON7 CCU Control Register  7 */
#define BRS_SCU_CCUCON8      BRSHW_IOS(uint32, BRS_SCU_BASE + 0x88)  /* CCUCON8 CCU Control Register  8 */
#define BRS_SCU_CCUCON9      BRSHW_IOS(uint32, BRS_SCU_BASE + 0x8C)  /* CCUCON8 CCU Control Register  9 */
#define BRS_SCU_CCUCON10     BRSHW_IOS(uint32, BRS_SCU_BASE + 0x90)  /* CCUCON8 CCU Control Register 10 */
#define BRS_SCU_CCUCON11     BRSHW_IOS(uint32, BRS_SCU_BASE + 0x94)  /* CCUCON8 CCU Control Register 11 */

#define BRS_SCU_PERPLLCON0   BRSHW_IOS(uint32, BRS_SCU_BASE + 0x28)  /* PERPLLCON0 Peripheral PLL Configuration 0 Register */
#define BRS_SCU_PERPLLCON1   BRSHW_IOS(uint32, BRS_SCU_BASE + 0x2C)  /* PERPLLCON1 Peripheral PLL Configuration 1 Register */
#define BRS_SCU_PERPLLSTAT   BRSHW_IOS(uint32, BRS_SCU_BASE + 0x24)  /* PERPLLSTAT Peripheral PLL Status Register */

#define BRS_RSTSTAT          BRSHW_IOS(uint32, BRS_SCU_BASE + 0x50)  /* Reset Status Register */
#define BRS_RSTCON           BRSHW_IOS(uint32, BRS_SCU_BASE + 0x58)  /* Reset Configuration Register */
#define BRS_SWRSTCON         BRSHW_IOS(uint32, BRS_SCU_BASE + 0x60)  /*Software Reset Configuration Register */

#define BRS_SCU_TRAPCLR      BRSHW_IOS(uint32, BRS_SCU_BASE + 0x12C) /* Trap Clear Register */
#define BRS_SCU_TRAPDIS0     BRSHW_IOS(uint32, BRS_SCU_BASE + 0x130) /* Trap Disable Register 0 */
#define BRS_SCU_TRAPDIS1     BRSHW_IOS(uint32, BRS_SCU_BASE + 0x120) /* Trap Disable Register 1 */

/*******************************************************************************
  GENERAL PURPOSE TIMER CLOCK CONTROL REGISTER
*******************************************************************************/
#define BRS_GPT120_BASE  0xF0001800
#define BRS_GPT120_CLC       BRSHW_IOS(uint32, BRS_GPT120_BASE)

#endif /*BRS_PLL_GROUP_X*/

#if defined (BRS_ENABLE_PORT)
/*******************************************************************************
  PORT  GROUP  CONFIG
*******************************************************************************/
#define PORT_BASE_ADDRESS  0xF003A000

# if defined (BRS_PORT_GROUP_A) || defined (BRS_PORT_GROUP_B)
#define BRS_OFFSET_IOCR0  0x10 /* Port n Input/Output Control Register 0 */
#define BRS_OFFSET_POUT   0x00 /* Port n Output Register */
#define BRS_OFFSET_PIN    0x24 /* Port n Input Register */
#define BRS_OFFSET_PDR0   0x40 /* Port n Pad Driver Mode 0 Register */
#define BRS_OFFSET_PCSR   0x64 /* Port n Pin Controller Select Register */
# endif /*BRS_PORT_GROUP_x*/

# if defined (BRS_PORT_GROUP_A)
#define BRS_PORT_IOCR(g,n) BRSHW_IOS(uint32, PORT_BASE_ADDRESS + 0x1000 * (g / 10) + 0x100 * (g % 10) + BRS_OFFSET_IOCR0 + 4 * ((uint32)n / 4)) /* Port Input/Output Control Register (group, number) */
#define BRS_PORT_POUT(g)   BRSHW_IOS(uint32, PORT_BASE_ADDRESS + 0x1000 * (g / 10) + 0x100 * (g % 10) + BRS_OFFSET_POUT)                        /* Port Output Register (group) */
#define BRS_PORT_PIN(g)    BRSHW_IOS(uint32, PORT_BASE_ADDRESS + 0x1000 * (g / 10) + 0x100 * (g % 10) + BRS_OFFSET_PIN)                         /* Port Input Register (group) */
#define BRS_PORT_PDR(g,n)  BRSHW_IOS(uint32, PORT_BASE_ADDRESS + 0x1000 * (g / 10) + 0x100 * (g % 10) + BRS_OFFSET_PDR0 + 4 * ((uint32)n / 8))  /* Port Pad Driver Mode Register (group, number) */
#define BRS_PORT_PCSR(g)   BRSHW_IOS(uint32, PORT_BASE_ADDRESS + 0x1000 * (g / 10) + 0x100 * (g % 10) + BRS_OFFSET_PCSR)                        /* Port g Pin Controller Select Register */

# elif defined (BRS_PORT_GROUP_B)
#define BRS_PORT_IOCR(g,n) BRSHW_IOS(uint32, PORT_BASE_ADDRESS + g * 0x100 + BRS_OFFSET_IOCR0 + 4 * ((uint32)n / 4)) /* Port Input/Output Control Register (group, number) */
#define BRS_PORT_POUT(g)   BRSHW_IOS(uint32, PORT_BASE_ADDRESS + g * 0x100 + BRS_OFFSET_POUT)                        /* Port Output Register (group) */
#define BRS_PORT_PIN(g)    BRSHW_IOS(uint32, PORT_BASE_ADDRESS + g * 0x100 + BRS_OFFSET_PIN)                         /* Port Input Register (group) */
#define BRS_PORT_PDR(g,n)  BRSHW_IOS(uint32, PORT_BASE_ADDRESS + g * 0x100 + BRS_OFFSET_PDR0 + 4 * ((uint32)n / 8))  /* Port Pad Driver Mode Register (group, number) */
#define BRS_PORT_PCSR(g)   BRSHW_IOS(uint32, PORT_BASE_ADDRESS + g * 0x100 + BRS_OFFSET_PCSR)                        /* Port g Pin Controller Select Register */

# endif /*BRS_PORT_GROUP_x*/
#endif /*BRS_ENABLE_PORT*/

/*******************************************************************************
  INTERRUPT  GROUP  CONFIG
*******************************************************************************/
# if defined(BRS_DERIVATIVE_GROUP_TC2xx) || defined (BRS_DERIVATIVE_GROUP_TC3xx)
#define BRS_INTERRUPT_IR_BASE  0xF0037000                         /* Interrupt base Adresse */
#define BRS_INT_SRC_BASE        (BRS_INTERRUPT_IR_BASE + 0x1000)  /* Interrupt base source adresse */

/* Defining some interrupt masks */
#define BRS_INT_SRC_SRE_MASK    0x00000400
#define BRS_INT_SRC_SETR_MASK   0x04000000

#define BRS_INT_SRC(x)          BRSHW_IOS(uint32, BRS_INT_SRC_BASE + x) /* Interrupt Router SRC Registers */
#endif

/*******************************************************************************
  OLDA Memory (SRI)
*******************************************************************************/
#define BRSHW_SRI_DOM0_SFR_BASE 0xF8700000
#define BRSHW_BRCON BRSHW_IOS(uint32, BRSHW_SRI_DOM0_SFR_BASE + 0x430) /* Bridge Control Register */

#if defined (BRS_ENABLE_FBL_SUPPORT)
/*******************************************************************************
  FLASH  GROUP  CONFIG
*******************************************************************************/
# if defined(BRS_DERIVATIVE_GROUP_TC2xx)
#define BRS_FLASH0_BASE  0xF8001000
#define BRS_FLASH0_MARP           BRSHW_IOS(uint32, BRS_FLASH0_BASE + 0x10A8)  /* PMU Margin Control PFlash register, CPU protected */
#define BRS_FLASH0_MARD           BRSHW_IOS(uint32, BRS_FLASH0_BASE + 0x10AC)  /* PMU Margin Control DFlash register */

# elif defined (BRS_DERIVATIVE_GROUP_TC3xx)
#define BRS_CPUSFR_BASE  0xF8800000u
#define BRS_DMU_BASE     0xF8040000u

#define BRS_CPU0_OFFSET_FLASHCON0  0x00000000u
#define BRS_CPU1_OFFSET_FLASHCON0  0x00020000u
#define BRS_CPU2_OFFSET_FLASHCON0  0x00040000u
#define BRS_CPU3_OFFSET_FLASHCON0  0x00060000u
#define BRS_CPU4_OFFSET_FLASHCON0  0x00080000u
#define BRS_CPU5_OFFSET_FLASHCON0  0x000C0000u

/* CPU Flash Configuration registers */ /** CPU x flash configuration register y, CPU protected */
#define BRS_CPU_FLASHCON(x, y)    BRSHW_IOS(uint32, BRS_CPUSFR_BASE + 0x1100u + BRS_CPU##x##_OFFSET_FLASHCON0 + ((y) * 0x04u))

#define BRS_DMU_ECCC(x)           BRSHW_IOS(uint32, BRS_DMU_BASE + 0x48u + ((x) * 0x200000u))  /**< DF x ECC control register, safety/cpu protected */

#define BRS_FLASHCON1_MASKUECC  0x00010000u  /* MASKUECC bit in FLASHCON1 registers */
#define BRS_DMU_ECCC_TRAPDIS    0xC0000000u  /* TRAPDIS bit in ECCC registers - disable ECC traps */

# endif /*BRS_DERIVATIVE_GROUP_x*/
#endif /*BRS_ENABLE_FBL_SUPPORT*/

/**********************************************************************************************************************
 *  LOCAL VARIABLES
 *********************************************************************************************************************/
#if defined(BRS_DERIVATIVE_GROUP_TC2xx)
  #define nop10() nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();
#endif

/**********************************************************************************************************************
 *  LOCAL CONST VARIABLES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  PROTOTYPES OF GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  PROTOTYPES OF LOCAL FUNCTIONS
 *********************************************************************************************************************/
#if defined (BRS_ENABLE_CAN_SUPPORT)      || \
    defined (BRS_ENABLE_LIN_SUPPORT)      || \
    defined (BRS_ENABLE_FLEXRAY_SUPPORT)  || \
    defined (BRS_ENABLE_ETHERNET_SUPPORT)

# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_START_SEC_RAM_CODE
  #include "Brs_MemMap.h"
# endif
void Appl_UnlockInit(void);
void Appl_UnlockEndinit(void);
void Appl_LockInit(void);
void Appl_LockEndinit(void);
# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_STOP_SEC_RAM_CODE
  #include "Brs_MemMap.h"
# endif
#endif

#if defined (BRS_ENABLE_CAN_SUPPORT)
void ApplCanWaitSetMCR(void);
#endif

#if defined (BRS_ENABLE_FLEXRAY_SUPPORT)
Std_ReturnType BrsHwErayPllInitPowerOn(void);
Std_ReturnType BrsHwErayPllWaitVcoLock(void);
#endif

/**********************************************************************************************************************
 *  FUNCTION DEFINITIONS
 *********************************************************************************************************************/
/*****************************************************************************/
#if defined (BRS_FIRST_EXECUTION_INSTANCE)
#define BRS_START_SEC_STARTUP_CODE
#include "Brs_MemMap.h"
/*****************************************************************************/
/* @brief      This function can be used to initialize controller specific
 *             stuff that should be handled by the first execution instance,
 *             even before the memory initialization took place (e.g.
 *             everything that is necessary to access the memory or to handle
 *             exceptions). This function is called at the beginning of
 *             BrsMainStartup(), immediately after the stackpointer was
 *             initialized in StartupCode
 *             (if BRSHW_EARLYINIT_AVAILABLE is set in BrsHw.h).
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from Brs_PreMainStartup() at power on
 *             initialization
 *****************************************************************************/
void BrsHwEarlyInitPowerOn(void)
{
# if defined (BRS_DERIVATIVE_GROUP_TC3xx)
  /* Early activation of OLDA memory to prevent SW from crashing */
  BRSHW_BRCON = 0x00000201; /* Enable OLDA memory */
# endif /*BRS_DERIVATIVE_GROUP_TC3xx*/

}
#define BRS_STOP_SEC_STARTUP_CODE
#include "Brs_MemMap.h"
#endif /*BRS_FIRST_EXECUTION_INSTANCE*/

#if defined (BRS_ENABLE_WATCHDOG)
/*****************************************************************************/
/* @brief      This function must be used to initialize the Watchdog.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsMainInit() at power on initialization
 *****************************************************************************/
void BrsHwWatchdogInitPowerOn(void)
{
  uint32 memoryType = IN_ROM;
  volatile uint32* WdtCon1 = BrsHw_GetAddrWDTCON1(BRS_READ_COREID(), memoryType);

  /* set Disable Request Control Bit for current core */
  BRS_TRICORE_UNLOCKENDINIT(BRS_READ_COREID(), memoryType);
  *WdtCon1 |= 0x8;
  BRS_TRICORE_LOCKENDINIT(BRS_READ_COREID(), memoryType);

  WdtCon1 = BrsHw_GetAddrWDTCON1(BRS_SAFETY_WATCHDOG_INDEX, memoryType);
  BRS_TRICORE_UNLOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);
  *WdtCon1 |= 0x8;
  BRS_TRICORE_LOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);
}
#endif /*BRS_ENABLE_WATCHDOG*/

#if defined (BRS_ENABLE_PLLCLOCKS)
/*****************************************************************************/
/* @brief      This function must be used to initialize the PLL.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsMainInit() at power on initialization
 *****************************************************************************/
void BrsHwPllInitPowerOn(void)
{
  uint32 memoryType = IN_ROM;
  /* Configuration checks */
#if (BRS_TIMEBASE_CLOCK > BRS_CPU_MAX_FREQUENCY)
  #error "The selected derivative does not support frequencies above BRS_CPU_MAX_FREQUENCY (please find the defined value inside the Cfg5 BRS PreConfig for your Derivative)."
#endif

#if defined (BRS_PLL_GROUP_A)
  uint32 pllfreq;
  /*CPU DIVIDER VALUES*/
  uint32 cpu0div, cpu1div, cpu2div;
  /*PERIPHERAL DIVIDER VALUES*/
  uint32 stmdivider, spbdivider, candivider, linfdivider, linsdivider, baud1divider, baud2divider, sridivider, gtmdivider, ethdivider, eraydivider;

  /* fvco has to be in the range 400...800MHZ */
  /* fpll = fosc*(N_DIVIDER/(P_DIVIDER*K2_DIVIDER)) */

  /*Divider values for fpll and fpllERAY*/
  #define P_DIVIDER 0x1  /*P_DIVIDER = 2*/
  #define K2_DIVIDER 0x3 /*K2_DIVIDER = 4*/

  /*fpll = 200MHZ fix*/
# if (BRS_OSC_CLK == 40)
  #define N_DIVIDER 0x27 /*N_DIVIDER = 40*/
# elif (BRS_OSC_CLK == 20)
  #define N_DIVIDER 0x4F /*N_DIVIDER = 80*/
# elif (BRS_OSC_CLK == 16)
  #define N_DIVIDER 0x63/*N_DIVIDER = 100*/

# else
  #error "Actual BRS implementation supports oscillator frequencies of 40, 20 and 16 MHz only"
# endif /*BRS_OSC_CLK*/

# if !(BRS_PERIPH_CLOCK==6250000)
   #error "The selected clock frequency of the timer peripheral clock is not yet supported (actually supported: 6.25 MHz)."
# endif /* BRS_PERIPH_CLOCK */

# if defined (BRS_ENABLE_CAN_SUPPORT)
   /*Configuration check */
#  if !(BRS_CAN_CLOCK==25)
   #error "The selected clock frequency of the CAN peripheral clock is not yet supported (actually supported: 25 MHz)."
#  endif
# endif /*BRS_ENABLE_CAN_SUPPORT*/

# if defined (BRS_ENABLE_LIN_SUPPORT)
   /*Configuration check */
#  if !(BRS_LIN_CLOCK==25)
   #error "The selected clock frequency of the LIN peripheral clock is not yet supported (actually supported: 25 MHz)."
#  endif
# endif /*BRS_ENABLE_LIN_SUPPORT*/

# if defined (BRS_ENABLE_FLEXRAY_SUPPORT)
   /*Configuration check */
#  if !(BRS_FLEXRAY_CLOCK==80)
   #error "The selected clock frequency of the FlexRay peripheral clock is not yet supported (actually supported: 80 MHz)."
#  endif
# endif /*BRS_ENABLE_FLEXRAY_SUPPORT*/

# if defined (BRS_ENABLE_ETHERNET_SUPPORT)
   /*Configuration check */
#  if !(BRS_ETH_CLOCK==20)
   #error "The selected clock frequency of the Ethernet peripheral clock is not yet supported (actually supported: 20 MHz)."
#  endif
# endif /*BRS_ENABLE_ETHERNET_SUPPORT*/

  /*check vco range*/
# if( (BRS_OSC_CLK*(N_DIVIDER+0x1))/(P_DIVIDER+0x1) < 400 || (BRS_OSC_CLK*(N_DIVIDER+0x1))/(P_DIVIDER+0x1) > 800)
  #error "fvco must be greater than 400MHZ and less than 800MHZ."
# endif

  /* fixed clock frequency settings
  fPLL:    200 MHz
  fSRI:    200 MHz
  fCAN:     25 MHz
  fLIN:     25 MHz
  fERAY:    80 MHz
  fETH:     20 MHz
  */

# if defined (BRS_DERIVATIVE_TC29x) /* Errata:PLL_TC.005 */
  uint32 errataPllStableDelay = 0;
  BRS_TRICORE_UNLOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);
  BRS_SCU_CCUCON0 &= ~0x30000000; /* switch system clock to back-up clock - should be used as default anyway */
  BRS_SCU_CCUCON0 |=  0x40000000; /* request update */
  BRS_SCU_PLLCON0 &= ~0x00010000; /* set PLL to power saving mode */

  /* Wait 10us:
     - Back-up clock should be 100 MHz: 1us = 1.000 nops -> 10us = 10.000 nops */
  for(errataPllStableDelay = 0; errataPllStableDelay < 1000; errataPllStableDelay++)
    nop10();
  BRS_SCU_PLLCON0 |=  0x00010000; /* set PLL to power saving mode */
  BRS_TRICORE_LOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);
# endif /*BRS_DERIVATIVE_TC29x*/

  pllfreq= BRS_OSC_CLK *(N_DIVIDER+0x1)/((K2_DIVIDER+0x1)*(P_DIVIDER+0x1)); /*pllfreq = 200MHZ*/

# if (BRS_TIMEBASE_CLOCK == 50 || BRS_TIMEBASE_CLOCK == 75 || BRS_TIMEBASE_CLOCK == 100 || BRS_TIMEBASE_CLOCK == 125 || BRS_TIMEBASE_CLOCK == 150 || BRS_TIMEBASE_CLOCK == 175 || BRS_TIMEBASE_CLOCK == 200)
  cpu0div = 64 - ((BRS_TIMEBASE_CLOCK*64)/pllfreq);
  cpu1div = 64 - ((BRS_TIMEBASE_CLOCK*64)/pllfreq);
  cpu2div = 64 - ((BRS_TIMEBASE_CLOCK*64)/pllfreq);
# else
  #error "The selected CPU frequency is not yet supported (please choose 25, 50, 75, 100, 125, 150, 175 or 200MHZ)."
# endif

  /*Set peripheral, system timer and SPB bus clock divider values*/
  stmdivider = pllfreq/100;   /*stmdivider for fstm = 100MHZ;*/
  spbdivider = pllfreq/50;   /*spbdivider for fspb = 50MHZ = fGPT; OS uses GPT: default GPT div = /8 => BRS_PERIPH_CLOCK = 6,25 MHZ */
  candivider = pllfreq/25;   /*candivider for fcan = 25MHZ*/
  linfdivider = pllfreq/25;  /*linfdivider for flinf = 25MHZ*/
  linsdivider = pllfreq/25;  /*linsdivider for flins = 25MHZ*/
  baud1divider = pllfreq/25; /*baud1divider for fbaud1 = 25MHZ*/
  baud2divider = pllfreq/25; /*baud2divider for fbaud2 = 25MHZ*/
  sridivider = 0x1;          /*sridivider for fsri = BRS_TIMEBASE_CLOCK*/
  gtmdivider = pllfreq/25;   /*gtmdivider for fgtm = 25MHZ*/

# if defined (BRS_ENABLE_FLEXRAY_SUPPORT)
  eraydivider = 0x1;         /*eraydivider for feray = 80MHZ*/
# else
  eraydivider = 0x0;         /* no ERAYPLL */
# endif

# if defined (BRS_ENABLE_ETHERNET_SUPPORT)
  ethdivider = 0x1;
# else
  ethdivider = 0x0;
# endif

  /*Configuration of PLL and PLLERAY starts here*/
  BRS_TRICORE_UNLOCKENDINIT(BRS_READ_COREID(), memoryType);
  BRS_GPT120_CLC = 0x0;
  BRS_SCU_TRAPDIS |= 0x3E0; /* Traps can not be generated for PLLs and Clocksystem */
  BRS_TRICORE_LOCKENDINIT(BRS_READ_COREID(), memoryType);

  BRS_TRICORE_UNLOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);
  /*Frist: Select prescaler mode*/
  /*Prescaler mode for pll*/
  BRS_SCU_PLLCON0 = BRS_SCU_PLLCON0
                  | (0x1 << 0)  /*VCOBYP=1    ---> Prescaler mode*/
                  | (0x1 << 4); /*SETFINDIS=1 ---> oscillator clock disconnect to PLL*/

  while((BRS_SCU_CCUCON1 & 0x80000000) == 0x80000000); /* wait until the lock of CCUCON1 is not set */
  BRS_SCU_CCUCON1 = (BRS_SCU_CCUCON1 & 0x0FFFFFFF)
                  | (0x1 << 28); /* pll and pll_ERAY clock source = fosc0 (fxtal1) */

  /* Write CCUCON1 with all values */
  while((BRS_SCU_CCUCON1 & 0x80000000) == 0x80000000); /* wait until the lock of CCUCON1 is not set */
  BRS_SCU_CCUCON1 =  (BRS_SCU_CCUCON1 & 0x30000000)
                  |  (candivider  << 0)   /*fcan = fpll/candivider*/
                  |  (eraydivider << 4)   /*fERAY = fplleray/eraydivider*/
                  |  (stmdivider  << 8)   /*fstm = fpll/stmdivider*/ /*fstm = system timer clock*/
                  |  (gtmdivider  << 12)  /*fgtm = fpll/gtmdivider*/
                  |  (ethdivider  << 16)  /*feth*/
                  |  (linfdivider << 20)  /*fasclinf = fpll/linfdivider*/
                  |  (linsdivider << 24); /*fasclins = fpll/linsdivider*/

  /*Write CCUCON0 with all values*/
  while((BRS_SCU_CCUCON0 & 0x80000000) == 0x80000000); /* wait until the lock of CCUCON0 is not set */
  BRS_SCU_CCUCON0 = (BRS_SCU_CCUCON0 & 0x0FFFFFFF)
                  | (0x1 << 28); /* Choose fpll as clock source, fpll=fsource */

  while((BRS_SCU_CCUCON0 & 0x80000000) == 0x80000000); /* wait until the lock of CCUCON0 is not set */
  BRS_SCU_CCUCON0 = (BRS_SCU_CCUCON0 & 0x30000000)
                  | (baud1divider << 0)   /*fbaud1 = fpll/baud1divider*/ /*Not available for TC22X and TC23X*/
                  | (baud2divider << 4)   /*fbaud2 = fpll/baud2divider*/
                  | (sridivider   << 8)   /*fsri = fpll/sridivider*/
                  | (spbdivider   << 16)  /*fspb = fpll/spbdivider*/ /*fspb = general purpose timer clock*/
                  | (0x2          << 20)  /*ffsi2= fsri/2*/
                  | (0x2          << 24)  /*ffsi =fsri/2*/
                  | (0x1          << 30); /*update CCUCON0, CCUCON1*/

  while((BRS_SCU_CCUCON5 & 0x80000000) == 0x80000000); /* wait until the lock of CCUCON5 is not set */
  BRS_SCU_CCUCON5 = (0x40000040); /* fmax = fsource and update CCUCON5 */

  BRS_SCU_CCUCON6 = cpu0div; /*fcpu0 = fsri*/
  BRS_SCU_CCUCON7 = cpu1div; /*fcpu1 = fsri*/
  BRS_SCU_CCUCON8 = cpu2div; /*fcpu2 = fsri*/

# if (BRS_OSC_CLK == 40)
  BRS_SCU_OSCCON = 0x00000000   /*clear reg.*/
                 | (0x2 << 3)   /*gain control from 4MHZ to 20MHZ*/
                 | (0xF << 16); /*crystalfreq(40MHZ) / 15+1 = 2,5MHZ ---> OSCVAL = 40MHZ/2.5MHZ*/

# elif (BRS_OSC_CLK == 20)
  BRS_SCU_OSCCON = 0x00000000   /*clear reg.*/
                 | (0x2 << 3)   /*gain control from 4MHZ to 20MHZ*/
                 | (0x7 << 16); /*crystalfreq(20MHZ) / 7+1 = 2,5MHZ ---> OSCVAL = 20MHZ/2.5MHZ*/

# elif (BRS_OSC_CLK == 16)
  BRS_SCU_OSCCON = 0x00000000   /*clear reg.*/
                 | (0x2 << 3)   /*gain control from 4MHZ to 20MHZ*/
                 | (0x5 << 16); /*crystalfreq(16MHZ) / 5+1 = 2,67MHZ ---> OSCVAL = 16MHZ/2.5MHZ*/
# endif /*BRS_OSC_CLK*/

  /* Set n and p dividers for pll */
  BRS_SCU_PLLCON0 = (BRS_SCU_PLLCON0 & 0xF0FF01FF)
                  | (N_DIVIDER << 9)    /* Set N-Divider */
                  | (P_DIVIDER  << 24); /* Set P-Divider */

  /* Set k2 divider for pll */
  BRS_SCU_PLLCON1  = (BRS_SCU_PLLCON1 & 0xFFFFFFC0)
                   | K2_DIVIDER; /* K2-Divider */

  while((BRS_SCU_PLLSTAT & 0x00000020) != 0x00000020); /* K2RDY == 1 ? */

  BRS_SCU_PLLCON0 |= 0x00000040; /* In case of a PLL loss-of-lock bit PLLSTAT.FINDIS is cleared */

  while((BRS_SCU_OSCCON & 0x00000102) != 0x00000102); /* check if the OSC frequency is usable */

  /* Second: Select normal mode for pll and for pllERAY */
  BRS_SCU_PLLCON0 |= 0x00000020; /* CLRFINDIS=1 ---> oscillator clock is connected to pll */
  BRS_SCU_PLLCON0 |= 0x00040000; /* RESLD = 1   ---> restart lock detection */
  BRS_TRICORE_LOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);

  /* wait for lock */
  while((BRS_SCU_PLLSTAT & 0x00000004) != 0x00000004); /* VCOLOCK == 1 ?*/

  BRS_TRICORE_UNLOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);
  BRS_SCU_PLLCON0 &= 0xFFFFFFFE; /* VCOBYP=0 ---> select normal mode */

# if defined (BRS_ENABLE_FLEXRAY_SUPPORT)
  /*Configuration of PLLERAY starts here*/
  BrsHwErayPllInitPowerOn();
# endif

  BRS_TRICORE_LOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);

  /* clear only pending traps related to PLLs and Clocksystem */
  BRS_SCU_TRAPCLR = 0x3E0;
  BRS_TRICORE_UNLOCKENDINIT(BRS_READ_COREID(), memoryType);

  /*enable all Traps again*/
  BRS_SCU_TRAPDIS = BRS_SCU_TRAPDIS & ~0x3E0;
  BRS_TRICORE_LOCKENDINIT(BRS_READ_COREID(), memoryType);
#endif /*BRS_PLL_GROUP_A*/

#if defined (BRS_PLL_GROUP_B)
  uint32 ulIdx;
  /*CPU DIVIDER VALUES*/
  uint32 cpu0div, cpu1div, cpu2div, cpu3div, cpu4div, cpu5div;

# if (BRS_OSC_CLK==20) || (BRS_OSC_CLK==24) || (BRS_OSC_CLK==25) || (BRS_OSC_CLK==40)
# else
  #error "Actual BRS implementation supports oscillator frequency of 20,24,25MHz and 40MHz"
# endif /*BRS_OSC_CLK*/

# if !(BRS_PERIPH_CLOCK==12500000)
   #error "The selected clock frequency of the timer peripheral clock is not yet supported (actually supported: 12.5 MHz)."
# endif /* BRS_PERIPH_CLOCK */

# if (BRS_TIMEBASE_CLOCK == 300)
  cpu0div = 0;  /* no divider, fCPU = fSRI = 300 Mhz */
  cpu1div = 0;  /* no divider, fCPU = fSRI = 300 MHz */
  cpu2div = 0;  /* no divider, fCPU = fSRI = 300 MHz */
  cpu3div = 0;  /* no divider, fCPU = fSRI = 300 MHz */
  cpu4div = 0;  /* no divider, fCPU = fSRI = 300 Mhz */
  cpu5div = 0;  /* no divider, fCPU = fSRI = 300 MHz */
# elif (BRS_TIMEBASE_CLOCK == 150)
  cpu0div = 32; /* fCPU0 = fSRI * (64 - cpu0div) / 64 = fSRI / 2 = 150 MHz */
  cpu1div = 32; /* fCPU0 = fSRI * (64 - cpu0div) / 64 = fSRI / 2 = 150 MHz */
  cpu2div = 32; /* fCPU0 = fSRI * (64 - cpu0div) / 64 = fSRI / 2 = 150 MHz */
  cpu3div = 32; /* fCPU0 = fSRI * (64 - cpu0div) / 64 = fSRI / 2 = 150 MHz */
  cpu4div = 32; /* fCPU0 = fSRI * (64 - cpu0div) / 64 = fSRI / 2 = 150 MHz */
  cpu5div = 32; /* fCPU0 = fSRI * (64 - cpu0div) / 64 = fSRI / 2 = 150 MHz */
# else
  #error "The selected clock frequency of the time base clock is not yet supported (actually supported: 300 and 150 MHz)."
# endif /* BRS_TIMEBASE_CLOCK */

# if defined (BRS_ENABLE_CAN_SUPPORT)
   /*Configuration check */
#  if !((BRS_CAN_CLOCK==80) || (BRS_CAN_CLOCK==54))
   #error "The selected clock frequency of the CAN peripheral clock is not yet supported (actually supported: 80 MHz). At an oscillator frequency of 24 MHz, 54 Mhz is used."
#  endif
# endif /*BRS_ENABLE_CAN_SUPPORT*/

# if defined (BRS_ENABLE_LIN_SUPPORT)
   /*Configuration check */
#  if !((BRS_LIN_CLOCK==80) ||(BRS_LIN_CLOCK==162))
   #error "The selected clock frequency of the LIN peripheral clock is not yet supported (actually supported: 80). At an oscillator frequency of 24 MHz, 162 Mhz is used."
#  endif
# endif /*BRS_ENABLE_LIN_SUPPORT*/

# if defined (BRS_ENABLE_FLEXRAY_SUPPORT)
   /*Configuration check */
#  if !((BRS_FLEXRAY_CLOCK==80) ||(BRS_FLEXRAY_CLOCK==162))
   #error "The selected clock frequency of the FlexRay peripheral clock is not yet supported (actually supported: 80 MHz). At an oscillator frequency of 24 MHz, 162 Mhz is used."
#  endif
# endif /*BRS_ENABLE_FLEXRAY_SUPPORT*/

# if defined (BRS_ENABLE_ETHERNET_SUPPORT)
#  if !((BRS_ETH_CLOCK==300) || (BRS_ETH_CLOCK==150) || (BRS_ETH_CLOCK==100) ||(BRS_ETH_CLOCK==75))
   #error "The selected clock frequency of the Ethernet peripheral clock is not yet supported (actually supported: 300, 150, 100, and 75 MHz). 300 MHz might be not stable."
#  endif
# endif

  /* actual peripheral frequencies for OSC = 20MHz, [25MHz], [24 Mhz] or [40 MHz]
  System PLL DCO: 600 MHz  [600 MHz]  [600 MHz]  [600 MHz]
  fPLL0:          300 MHz  [300 MHz]  [300 Mhz]  [300 MHz]
  fPLL1:          320 MHz  [160 MHz]  [324 MHz]  [320 Mhz]
  fPLL2:          200 MHz  [200 MHz]  [162 MHz]  [160 MHz]
  FSI_clock:      100 MHz  [100 MHz]
  FSI2_clock:     300 MHz  [300 MHz]
  GTM_clock:      200 MHz  [200 MHz]
  STM_clock:      100 MHz  [100 MHz]
  SRI_clock:      300 MHz  [300 MHz]
  SPB_clock:      100 MHz  [100 MHz] (System Peripheral Bus)
  GPT12_clock:    100 MHz  [100 MHz]
  BBB_clock:      150 MHz  [150 MHz]
  REFCLK1:       12.5 MHz  [12.5 MHz]
  HSCT_clock:     320 MHz  [not USED]
  EBU_clock:      160 MHz  [160 MHz]
  QSPI_clock:     200 MHz  [200 MHz]
  ADC_clock:      160 MHz  [160 MHz]
  I2C_clock:     66.6 MHz  [66.6 MHz]
  MCAN_clock:      80 MHz  [80 MHz]
  ERAY_clock:      80 MHz  [80 MHz]
  ASCLINF_clock:  200 MHz  [200 MHz]
  ASCLINS_clock:   80 MHz  [80 MHz]
  MSC_clock:      200 MHz  [200 MHz]
  */

  /*Configuration of PLL starts here*/
  BRS_TRICORE_UNLOCKENDINIT(BRS_READ_COREID(), memoryType);
  BRS_GPT120_CLC = 0x0;
  BRS_SCU_TRAPDIS0 |= 0x0F0F0F0F; /* Traps can not be generated for PLLs and Clocksystem */
  BRS_SCU_TRAPDIS1 |= 0x0F0F;
  BRS_TRICORE_LOCKENDINIT(BRS_READ_COREID(), memoryType);

  BRS_TRICORE_UNLOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);
  /* *** Step 1: setup osc control *** */

# if (BRS_OSC_CLK==20)
  #define OSCVAL 5   /*fOSCREF = 20 MHz = OSCCON.OSCVAL - 1 + 16 MHz -> OSCVAL = 5 */
# elif (BRS_OSC_CLK==24)
  #define OSCVAL 9  /*fOSCREF = 24 MHz = OSCCON.OSCVAL - 1 + 16 MHz -> OSCVAL = 9 */
# elif (BRS_OSC_CLK==25)
  #define OSCVAL 10  /*fOSCREF = 25 MHz = OSCCON.OSCVAL - 1 + 16 MHz -> OSCVAL = 10 */
# elif (BRS_OSC_CLK==40)
  #define OSCVAL 25  /*fOSCREF = 40 MHz = OSCCON.OSCVAL - 1 + 16 MHz -> OSCVAL = 25 */
# endif

  BRS_SCU_CCUCON6  = cpu0div; /*fcpu0 = fsri*/
  BRS_SCU_CCUCON7  = cpu1div; /*fcpu1 = fsri*/
  BRS_SCU_CCUCON8  = cpu2div; /*fcpu2 = fsri*/
  BRS_SCU_CCUCON9  = cpu3div; /*fcpu3 = fsri*/
  BRS_SCU_CCUCON10 = cpu4div; /*fcpu4 = fsri*/
  BRS_SCU_CCUCON11 = cpu5div; /*fcpu5 = fsri*/

  BRS_SCU_OSCCON = 0x00000000      /* mode = 0 -> External Crystal Mode. The oscillator Power-Saving Mode is not entered. */
                 | (0x3 << 3)      /* gain control */
                 | (OSCVAL << 16); /* fOSCREF = OSCCON.OSCVAL - 1 + 16 MHz */

  BRS_SCU_OSCCON |= (0x1 << 2);    /* OSCRES -> reset OSC watchdog with new settings */
  BRS_TRICORE_LOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);

  while((BRS_SCU_OSCCON & 0x00000102) != 0x00000102); /* wait until PLLLV and PLLHV are set */
  
  BRS_TRICORE_UNLOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);

  /* *** Step 2: Initialize the PLLs to target fDCO and fPLLx frequency *** */
  /* set SYSPLLCON0.INSEL = 0x01 -> fOSC is used as clock source */
  BRS_SCU_SYSPLLCON0 &= ~(0x3 << 30);
  BRS_SCU_SYSPLLCON0 |= (0x1 << 30);

# if (BRS_OSC_CLK==20)
  #define PllNdiv 0x1D   /* NDIV = 0x1D = 29 */
# elif (BRS_OSC_CLK==24)
  #define PllNdiv 0x18   /* NDIV = 0x18 = 24 */
# elif (BRS_OSC_CLK==25)
  #define PllNdiv 0x17   /* NDIV = 0x17 = 23 */
# elif (BRS_OSC_CLK==40)
  #define PllNdiv 0xE   /* NDIV = 0xE = 14 */
# endif

  /* fDCO = ((NDIV+1)* fOSC) */
  /* fPll= fDCO /((PDIV+1)*(K2DIV+1)) */

  /* SysPll fDCO = 600MHz, fPLL0 = 100MHz */
  BRS_SCU_SYSPLLCON0 = 0x00000000  /* PDIV = 0, PLLPWD = 0, MODEN = 0 */
                     | (0x1 << 30) /* fOSC used as clock source*/
                     | (0x1 << 16) /* System PLL power saving mode set to normal behavior */
                     | (PllNdiv << 9); /*Ndiv depening on fOSC*/

  /* K2DIV = 5 -> K2 divider = 6 */
  BRS_SCU_SYSPLLCON1 = 0x00000005;

# if (BRS_OSC_CLK==20)
  #define PerPllNdiv 0x1F /* NDIV = 0x1F = 31 */
  #define DIVBY 0         /* DIVBY = 0  */
# elif (BRS_OSC_CLK==24)
  #define PerPllNdiv 0x1A /* NDIV = 0x1A = 26 */
  #define DIVBY 1         /* DIVBY = 1  */
# elif (BRS_OSC_CLK==25)
  #define PerPllNdiv 0x1F /* NDIV = 0x1F = 31 */
  #define DIVBY 1         /* DIVBY = 1  */
# elif (BRS_OSC_CLK==40)
  #define PerPllNdiv 0xF /* NDIV = 0xF = 15 */
  #define DIVBY 1        /* DIVBY = 1  */
# endif

  /*OSC=20 PerPll1 fDCO = 640MHz; fPLL1 = 320MHz; f PLL2 = 200MHz */
  /*OSC=24 PerPll1 fDCO = 648MHz; fPLL1 = 324MHz; f PLL2 = 162MHz */
  /*OSC=25 PerPll1 fDCO = 800MHz; fPLL1 = 160MHz; f PLL2 = 200MHz */
  /*OSC=40 PerPll1 fDCO = 640MHz; fPLL1 = 320MHz; f PLL2 = 160MHz */

  /* fPll1= fDCO /((PDIV+1)*(K2DIV+1)) */
  /* fPll2= fDCO /((PDIV+1)*(K3DIV+1)*1.6) if DIVBY=0  fPll2= fDCO /((PDIV+1)*(K3DIV+1)*2) if DIVBY=1*/

  /* PerPll fDCO = 640MHz; fPLL1 = 320MHz; f PLL2 = 200MHz */
  /* NDIV = 0x1F = 31, PDIV = 0, PLLPWD = 0, MODEN = 0, DIVBY = 0 */
  BRS_SCU_PERPLLCON0 =  0x00000000 /* PDIV = 0, PLLPWD = 0, MODEN = 0 */
                     | (0x1 << 16) /* System PLL power saving mode set to normal behavior */
                     | (PerPllNdiv << 9)
                     | (DIVBY << 0); /* DIVBY depends on fOSC*/

  BRS_TRICORE_LOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);

  for (ulIdx=0; ulIdx < 1000000; ulIdx++) nop(); /* yes this needs so much time!!! */

  BRS_TRICORE_UNLOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);

# if (BRS_OSC_CLK==20)
  #define K3div 0x1     /* K3DIV = 1 -> K3 divider = 2 */
  #define K2div 0x1     /* K2DIV = 1 --> K2 divider 2 */
# elif (BRS_OSC_CLK==24)
  #define K3div 0x1     /* K3DIV = 1 -> K3 divider = 2 */
  #define K2div 0x1     /* K2DIV = 1 --> K2 divider 2 */
# elif (BRS_OSC_CLK==25)
  #define K3div 0x1     /* K3DIV = 1 -> K3 divider = 2 */
  #define K2div 0x4     /* K2DIV = 4 --> K2 divider 5 */
# elif (BRS_OSC_CLK==40)
  #define K3div 0x1     /* K3DIV = 1 -> K3 divider = 2 */
  #define K2div 0x1     /* K2DIV = 1 --> K2 divider 2 */
# endif

  BRS_SCU_PERPLLCON1 = 0x00000000
                     | (K3div << 8)  /* K3DIV */
                     | (K2div << 0); /* K2DIV */

  /* *** Step 3: Wait for PLL lock to be set *** */
  /* Restart DCO lock detection */
  BRS_SCU_SYSPLLCON0 |= 0x00040000;

  BRS_TRICORE_LOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);

  /* Wait for PLL lock */
  while((BRS_SCU_SYSPLLSTAT & 0x4) == 0);

  /* *** Step 4: Configure CCUCON0, and CCUCON1 to first target setting *** */
  while((BRS_SCU_CCUCON0 & 0x80000000) != 0); /* Wait for CCUCON0 unlocked */

  BRS_TRICORE_UNLOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);
  BRS_SCU_CCUCON0 = 0x47230113;
  BRS_TRICORE_LOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);

  while((BRS_SCU_CCUCON0 & 0x80000000) != 0); /* Wait until change is executed */
  while((BRS_SCU_CCUCON1 & 0x80000000) != 0); /* Wait for CCUCON1 unlocked */

  BRS_TRICORE_UNLOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);

# if (BRS_OSC_CLK==20)
  BRS_SCU_CCUCON1 = 0x21210012;
# elif (BRS_OSC_CLK==24)
  BRS_SCU_CCUCON1 = 0x21210096; /*divider disabled for fpll1 fpll1= fsource1, fMCAN=fsource1/6= 54MHz*/
# elif (BRS_OSC_CLK==25)
  BRS_SCU_CCUCON1 = 0x21210092;
# elif (BRS_OSC_CLK==40)
  BRS_SCU_CCUCON1 = 0x21210012; /*divider disabled for fpll1 fpll1= fsource1, fMCAN=fsource1/2*/
# endif

  BRS_TRICORE_LOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);

  while((BRS_SCU_CCUCON1 & 0x80000000) != 0); /* Wait until change is executed */
  while((BRS_SCU_CCUCON2 & 0x80000000) != 0); /* Wait for CCUCON2 unlocked */

  BRS_TRICORE_UNLOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);
  BRS_SCU_CCUCON2 = 0x02001201; /*additional set ERAYPERON*/
  BRS_TRICORE_LOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);

  while((BRS_SCU_CCUCON2 & 0x80000000) != 0); /* Wait until change is executed */

  /* *** Step 5: Switch CCU input clock fSOURCE0 to PLL via CCUCON0.CLKSEL *** */
  while((BRS_SCU_CCUCON0 & 0x80000000) != 0); /* Wait for CCUCON0 unlocked */

  BRS_TRICORE_UNLOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);
  BRS_SCU_CCUCON0 = 0x57230113;
  BRS_TRICORE_LOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);

  while((BRS_SCU_CCUCON0 & 0x80000000) != 0); /* Wait until change is executed */

  /* *** Step 6: fPLL has to be increased step by step to target frequency *** */
  /* fPLL0 100 MHz -> 150 MHz -> 200 MHz -> 300 MHz */
  /* K2DIV = 3 -> K2 divider = 4 */
  BRS_TRICORE_UNLOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);
  BRS_SCU_SYSPLLCON1 = 0x00000003;
  while((BRS_SCU_SYSPLLSTAT & 0x4) == 0); /* Wait for System PLL to be stable */
  BRS_TRICORE_LOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);

  BRS_TRICORE_UNLOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);
  BRS_SCU_SYSPLLCON1 = 0x00000002;
  while((BRS_SCU_SYSPLLSTAT & 0x4) == 0); /* Wait for System PLL to be stable */
  BRS_TRICORE_LOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);

  BRS_TRICORE_UNLOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);
  BRS_SCU_SYSPLLCON1 = 0x00000001;
  while((BRS_SCU_SYSPLLSTAT & 0x4) == 0); /* Wait for System PLL to be stable */
  BRS_TRICORE_LOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);

  while((BRS_SCU_CCUCON5 & 0x80000000) != 0); /* Wait for CCUCON5 unlocked - additionally added (GETH)*/

  BRS_TRICORE_UNLOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);

# if defined (BRS_ENABLE_ETHERNET_SUPPORT)
#  if (BRS_ETH_CLOCK==300)
  /* 300 MHz might not be working in some use cases; if you run into problems, use the default 150 MHz */
  BRS_SCU_CCUCON5 = (BRS_SCU_CCUCON5 | 0x01); /* fPLL0 = 300 Mhz -> 300 Mhz / 1 = 300 Mhz (GETH) */
#  elif (BRS_ETH_CLOCK==150)
  BRS_SCU_CCUCON5 = (BRS_SCU_CCUCON5 | 0x02); /* fPLL0 = 300 Mhz -> 300 Mhz / 2 = 150 Mhz (GETH) */
#  elif (BRS_ETH_CLOCK==100)
  BRS_SCU_CCUCON5 = (BRS_SCU_CCUCON5 | 0x03); /* fPLL0 = 300 Mhz -> 300 Mhz / 3 = 100 Mhz (GETH) */
#  elif (BRS_ETH_CLOCK==75)
  BRS_SCU_CCUCON5 = (BRS_SCU_CCUCON5 | 0x04); /* fPLL0 = 300 Mhz -> 300 Mhz / 4 = 75 Mhz (GETH) */
#  endif
# else
  BRS_SCU_CCUCON5 = (BRS_SCU_CCUCON5 | 0x00); /* GETH clock is shut off */
# endif

  BRS_SCU_CCUCON5 = (BRS_SCU_CCUCON5 | 0x01 << 30u);
  BRS_TRICORE_LOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);

  BRS_TRICORE_UNLOCKENDINIT(BRS_READ_COREID(), memoryType);
  /* clear only pending traps related to PLLs and Clocksystem */
  BRS_SCU_TRAPCLR = 0xF;

  /* enable all Traps again - except for ESR1T for all cores*/
  /* The ESR1 Pin on 2nd Gen TC3xx Triboards is pulled to high level via pull-up resistor which triggers an non-maskable Interrupt*/
  BRS_SCU_TRAPDIS0 = 0xF2F2F2F2;
  BRS_SCU_TRAPDIS1 = 0xF2F2;

  BRS_TRICORE_LOCKENDINIT(BRS_READ_COREID(), memoryType);
#endif /*BRS_PLL_GROUP_B */
}

# if defined (BRS_PLL_GROUP_A)
#  if defined (BRS_ENABLE_FLEXRAY_SUPPORT)
/* function to initialize ERAY PLL */
Std_ReturnType BrsHwErayPllInitPowerOn(void)
{
  Std_ReturnType ErrorFlag;
  volatile uint32 PllStableDelay;
  uint8 PllNdiv;
  uint8 PllK2div;
  uint8 PllK3div;
  uint8 PllPdiv;
  uint32 memoryType = IN_ROM;


  /*Store PLL Divider values in local variables*/
# if (BRS_OSC_CLK == 40)
  PllNdiv = 0x7; /* 8 - 1*/
  PllK2div = 0x3; /* 4 - 1*/
  PllK3div = 0x3; /* 4 - 1*/
  PllPdiv =  0x0; /* 1 - 1*/

# elif (BRS_OSC_CLK == 20)
  PllNdiv = 0xF; /* 16 - 1*/
  PllK2div = 0x3; /* 4 - 1*/
  PllK3div = 0x3; /* 4 - 1*/
  PllPdiv =  0x0; /* 1 - 1*/

# elif (BRS_OSC_CLK == 16)
  PllNdiv = 0x13; /* 20 - 1*/
  PllK2div = 0x3; /* 4 - 1*/
  PllK3div = 0x3; /* 4 - 1*/
  PllPdiv =  0x0; /* 1 - 1*/
# endif /*BRS_OSC_CLK*/

  BRS_TRICORE_UNLOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);

  /* Enter Prescalar mode */
  /* Update K and N dividers */
  BRS_SCU_PLLERAYCON1 = (BRS_SCU_PLLERAYCON1 & 0xFF80FFFF); /* Clear K1DIV. K1DIV = 1 */

  BRS_SCU_PLLERAYCON0 = (BRS_SCU_PLLERAYCON0 & 0xFFFFFFEE)
                      | (0x1 << 0)    /* VCOBYP = 1 */
                      | (0x1 << 4);   /* SETFINDIS = 1 */

  BRS_SCU_PLLERAYCON1 = (BRS_SCU_PLLERAYCON1 & 0xFFFFF080)
                      | (PllK2div << 0)   /* K2DIV */
                      | (PllK3div << 8);  /* K3DIV */

  BRS_SCU_PLLERAYCON0 = (BRS_SCU_PLLERAYCON0 & 0xF0FFC1FF)
                      | (PllNdiv << 9)     /* NDIV */
                      | (PllPdiv << 24);   /* PDIV */

  /* Enter normal mode */
  BRS_SCU_PLLERAYCON0 = (BRS_SCU_PLLERAYCON0 & 0xFFFEFF9F)
                      | (0x1 << 5)     /* CLRFINDIS=1 */
                      | (0x1 << 6)     /* OSCDISCDIS=1 */
                      | (0x0 << 16);   /* PLLPWD=0 */

  /* Regarding PLL_ERAY_TC.001, between setting of PLLPWD=0 and PLLPWD=1, it is necessary to wait 10us */
  /* Back-up clock should be 100 MHz: 1us = 1.000 nops -> 10us = 10.000 nops */
  for(PllStableDelay=0U; PllStableDelay < 1000; PllStableDelay++)
    nop10();

  /*
    RESLD = 1     ==> Restart VCO lock detection
    CLRFINDIS = 1 ==> Connect OSC to PLL
    PLLPWD = 1    ==> PLL Power Saving Mode : Normal behaviour
    NDIV = FR_17_ERAY_PLL_NDIV (Pre-compile parameter)
  */

  BRS_SCU_PLLERAYCON0 = (BRS_SCU_PLLERAYCON0 & 0xFFFEFFFF)
                      | (0x1 << 16);   /*PLLPWD = 1*/

  for(PllStableDelay=0U; PllStableDelay < 100; PllStableDelay++)
  {}/*Errata*/

  BRS_SCU_PLLERAYCON0 = (BRS_SCU_PLLERAYCON0 & 0xFFFBFFFF)
              | (0x1 << 18);   /* RESLD = 1 */

  /* Set the ENDINIT bit in the WDT_CON0 register again
  to enable the write-protection and to prevent a time-out */
  BRS_TRICORE_LOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);

  /* Wait for ERAY PLL VCO locking */
  ErrorFlag = BrsHwErayPllWaitVcoLock();

  /*By Pass VCO only if PLL is locked*/
  if(ErrorFlag == E_OK)
  {
    /* Clear the ENDINIT bit in the WDT_CON0 register in order
    to disable the write-protection for registers protected
    via the EndInit feature */
    BRS_TRICORE_UNLOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);

    /*Bypass VCO*/
    /* Distribute the clock */
    BRS_SCU_PLLERAYCON0 = (BRS_SCU_PLLERAYCON0 & 0xFFFFFFBE)
                        | (0x0 << 0)     /*VCOBYP = 0*/
                        | (0x0 << 6);    /*OSCDISCDIS = 0*/

    /* Set the ENDINIT bit in the WDT_CON0 register again
    to enable the write-protection and to prevent a time-out */
    BRS_TRICORE_LOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);
  }
  return(ErrorFlag);
}

Std_ReturnType BrsHwErayPllWaitVcoLock(void)
{
  Std_ReturnType ErrorFlag;
  uint32 TimeOutCount;

  ErrorFlag = E_OK;
  TimeOutCount = ((uint32)0x000001FFU);
  do
  {
    TimeOutCount-- ;
  } while (((BRS_SCU_PLLERAYSTAT & 0x00000004) != 0x00000004) && (TimeOutCount > 0U)) ;

  if (TimeOutCount == 0U)
  {
    ErrorFlag = E_NOT_OK;
  }

  return(ErrorFlag);
}
#  endif /*BRS_ENABLE_FLEXRAY_SUPPORT*/
# endif /*BRS_PLL_GROUP_A*/
#endif /*BRS_ENABLE_PLLCLOCKS*/

#if defined (BRS_ENABLE_PORT)
/*******************************************************************************
 *  Port Pin initialization helper functions for usage of BrsHw_Ports.h
 *******************************************************************************/
/*****************************************************************************/
/* @brief      This function configures a port pin as input pin.
 * @pre        Port pin configurations available within BrsHw_Ports.h and
 *             no DrvPort used for port pin initialization.
 * @param[in]  p - brsHw_Port_PortType, to be initialized.
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsHwPortInitPowerOn() and
 *             provided to external modules (e.g. driver testsuits).
 *****************************************************************************/
void BrsHwInitPortInput(brsHw_Port_PortType p)
{
  BRS_PORT_IOCR(p.portGroup,p.portNumber) &= ~(uint32)( 0x1F << (3 + 8 * ((uint32)p.portNumber % 4)));
  BRS_PORT_IOCR(p.portGroup,p.portNumber) |= (uint32)( 0x10 + p.portAlternative ) << (8 * ((uint32)p.portNumber % 4));
}

/*****************************************************************************/
/* @brief      This function configures a port pin as output pin.
 * @pre        Port pin configurations available within BrsHw_Ports.h and
 *             no DrvPort used for port pin initialization.
 * @param[in]  p - brsHw_Port_PortType, to be initialized.
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsHwPortInitPowerOn() and
 *             provided to external modules (e.g. driver testsuits).
 *****************************************************************************/
void BrsHwInitPortOutput(brsHw_Port_PortType p)
{
  BRS_PORT_IOCR(p.portGroup,p.portNumber) &= ~(uint32)( 0x1F << (3 + 8 * ((uint32)p.portNumber % 4)));
  BRS_PORT_IOCR(p.portGroup,p.portNumber) |= (uint32)( 0x10 + p.portAlternative ) << (3 + 8 * ((uint32)p.portNumber % 4));
}

/*****************************************************************************/
/* @brief      This function configures a port pin as input and output pin.
 * @pre        Port pin configurations available within BrsHw_Ports.h and
 *             no DrvPort used for port pin initialization.
 * @param[in]  p - brsHw_Port_PortType, to be initialized.
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsHwPortInitPowerOn() and
 *             provided to external modules (e.g. driver testsuits).
 *****************************************************************************/
void BrsHwInitPortInputOutput(brsHw_Port_PortType p)
{
  /* no classical input buffer setting on this platform. Output with alternative function should be suitable */
  BrsHwInitPortOutput(p);
}

/*****************************************************************************/
/* @brief      This function configures the port pin configuration registers
 *             (set DriverStrength and pad level at automotive level)
 * @pre        Port pin configurations available within BrsHw_Ports.h and
 *             no DrvPort used for port pin initialization.
 * @param[in]  p - brsHw_Port_PortType, to be initialized,
               n - brsHw_Port_ConfType, for port pin configuration
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsHwPortInitPowerOn() and
 *             BrsHwEvaBoardInitPowerOn() locally.
 *****************************************************************************/
void BrsHwInitPortConfig(brsHw_Port_PortType p, brsHw_Port_ConfType n)
{
  uint32 memoryType = IN_ROM;
  BRS_TRICORE_UNLOCKENDINIT(BRS_READ_COREID(), memoryType);
  BRS_PORT_PDR(p.portGroup,p.portNumber)  &= ~(uint32)( 0x0F << (4 * ((uint32)p.portNumber % 8)) );
  switch (n.PortDriverSetting)
  {
    case PORT_STRONG_DRIVER_SHARP_EDGE:
      BRS_PORT_PDR(p.portGroup,p.portNumber)  |= (0x1 | PORT_STRONG_DRIVER_SHARP_EDGE) << (4 * ((uint32)p.portNumber % 8));
      break;
    case PORT_STRONG_DRIVER_MEDIUM_EDGE:
      BRS_PORT_PDR(p.portGroup,p.portNumber)  |= (0x1 | PORT_STRONG_DRIVER_MEDIUM_EDGE) << (4 * ((uint32)p.portNumber % 8));
      break;
    case PORT_MEDIUM_DRIVER:
      BRS_PORT_PDR(p.portGroup,p.portNumber)  |= (0x1 | PORT_MEDIUM_DRIVER) << (4 * ((uint32)p.portNumber % 8));
      break;
    case PORT_RGMII_DRIVER:
      BRS_PORT_PDR(p.portGroup,p.portNumber)  |= (0x1 | PORT_RGMII_DRIVER) << (4 * ((uint32)p.portNumber % 8));
      break;
  }
  BRS_TRICORE_LOCKENDINIT(BRS_READ_COREID(), memoryType);
}

# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_START_SEC_RAM_CODE
  #include "Brs_MemMap.h"
# endif
/*****************************************************************************/
/* @brief      This function sets the output level of a port pin.
 * @pre        Port pin configurations available within BrsHw_Ports.h,
 *             no DrvPort used for port pin initialization and
 *             transferred port pin has to be initialized as output pin with
 *             GPIO functionality.
 * @param[in]  p     - brsHw_Port_PortType, to be set,
 *             Level - level, port pin has to be set to
 *                     (BRSHW_PORT_LOGIC_LOW or BRSHW_PORT_LOGIC_HIGH).
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsHwPortInitPowerOn() and
 *             provided to external modules (e.g. BrsMainTogglePin()).
 *****************************************************************************/
void BrsHwPort_SetLevel(brsHw_Port_PortType p, uint8 Level)
{
  if (Level == BRSHW_PORT_LOGIC_LOW)
  {
    BRS_PORT_POUT(p.portGroup) &= ~(0x1 << p.portNumber);
  }
  else
  {
    BRS_PORT_POUT(p.portGroup) |=  (0x1 << p.portNumber);
  }
}

/*****************************************************************************/
/* @brief      This function reads the input level of a port pin.
 * @pre        Port pin configurations available within BrsHw_Ports.h,
 *             no DrvPort used for port pin initialization and
 *             transferred port pin has to be initialized as input pin with
 *             GPIO functionality.
 * @param[in]  p - brsHw_Port_PortType, to be read.
 * @param[out] -
 * @return     Level, read from port pin
 *             (BRSHW_PORT_LOGIC_LOW or BRSHW_PORT_LOGIC_HIGH).
 * @context    Function is provided to external modules.
 *****************************************************************************/
uint8 BrsHwPort_GetLevel(brsHw_Port_PortType p)
{
  uint32 temp;

  temp = BRS_PORT_PIN(p.portGroup);
  temp &= (1 << p.portNumber);

  if(temp !=0x0000)
  {
    return BRSHW_PORT_LOGIC_HIGH;
  }
  else
  {
    return BRSHW_PORT_LOGIC_LOW;
  }
}
# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_STOP_SEC_RAM_CODE
  #include "Brs_MemMap.h"
# endif

/*****************************************************************************/
/* @brief      This function must be used to initialize the used ports.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsMainInit() at power on initialization
 *****************************************************************************/
void BrsHwPortInitPowerOn(void)
{
#if defined (BRS_ENABLE_SUPPORT_LEDS)
  BrsHwInitPortOutput(BRSHW_PORT_LED);

  /* Set LED on EVB demo board to show the system is alive */
  BrsMainTogglePin(BRSMAIN_TOGGLEPIN_LED);
#endif

#if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
  BrsHwInitPortOutput(BRSHW_PORT_TOGGLE_WD);
#endif

#if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  BrsHwInitPortOutput(BRSHW_PORT_TOGGLE_CUSTOM);
#endif

/*******************************************************************************
 *  CAN driver
 *******************************************************************************/
#if defined (BRS_ENABLE_CAN_SUPPORT)
# if defined (BRS_ENABLE_CAN_CHANNEL_0)
  BrsHwInitPortOutput(BRSHW_PORT_CAN0_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN0_RX);
  BrsHwInitPortConfig(BRSHW_PORT_CAN0_TX, BRSHW_PORT_CONF_CAN);
  BrsHwInitPortConfig(BRSHW_PORT_CAN0_RX, BRSHW_PORT_CONF_CAN);
#  if defined(_BRSHW_PORT_CAN0_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN0_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN0_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
#  if defined (_BRSHW_PORT_CAN0_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN0_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN0_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_CAN_CHANNEL_0*/

# if defined (BRS_ENABLE_CAN_CHANNEL_1)
  BrsHwInitPortOutput(BRSHW_PORT_CAN1_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN1_RX);
  BrsHwInitPortConfig(BRSHW_PORT_CAN1_TX, BRSHW_PORT_CONF_CAN);
  BrsHwInitPortConfig(BRSHW_PORT_CAN1_RX, BRSHW_PORT_CONF_CAN);
#  if defined(_BRSHW_PORT_CAN1_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN1_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN1_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
#  if defined (_BRSHW_PORT_CAN1_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN1_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN1_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_CAN_CHANNEL_1*/

# if defined (BRS_ENABLE_CAN_CHANNEL_2)
  BrsHwInitPortOutput(BRSHW_PORT_CAN2_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN2_RX);
  BrsHwInitPortConfig(BRSHW_PORT_CAN2_TX, BRSHW_PORT_CONF_CAN);
  BrsHwInitPortConfig(BRSHW_PORT_CAN2_RX, BRSHW_PORT_CONF_CAN);
#  if defined(_BRSHW_PORT_CAN2_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN2_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN2_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
#  if defined (_BRSHW_PORT_CAN2_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN2_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN2_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_CAN_CHANNEL_2*/

# if defined (BRS_ENABLE_CAN_CHANNEL_3)
  BrsHwInitPortOutput(BRSHW_PORT_CAN3_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN3_RX);
  BrsHwInitPortConfig(BRSHW_PORT_CAN3_TX, BRSHW_PORT_CONF_CAN);
  BrsHwInitPortConfig(BRSHW_PORT_CAN3_RX, BRSHW_PORT_CONF_CAN);
#  if defined(_BRSHW_PORT_CAN3_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN3_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN3_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
#  if defined (_BRSHW_PORT_CAN3_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN3_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN3_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_CAN_CHANNEL_3*/

# if defined (BRS_ENABLE_CAN_CHANNEL_4)
  BrsHwInitPortOutput(BRSHW_PORT_CAN4_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN4_RX);
  BrsHwInitPortConfig(BRSHW_PORT_CAN4_TX, BRSHW_PORT_CONF_CAN);
  BrsHwInitPortConfig(BRSHW_PORT_CAN4_RX, BRSHW_PORT_CONF_CAN);
#  if defined(_BRSHW_PORT_CAN4_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN4_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN4_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
#  if defined (_BRSHW_PORT_CAN4_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN4_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN4_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_CAN_CHANNEL_4*/

# if defined (BRS_ENABLE_CAN_CHANNEL_5)
  BrsHwInitPortOutput(BRSHW_PORT_CAN5_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN5_RX);
  BrsHwInitPortConfig(BRSHW_PORT_CAN5_TX, BRSHW_PORT_CONF_CAN);
  BrsHwInitPortConfig(BRSHW_PORT_CAN5_RX, BRSHW_PORT_CONF_CAN);
#  if defined(_BRSHW_PORT_CAN5_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN5_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN5_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
#  if defined (_BRSHW_PORT_CAN5_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN5_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN5_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_CAN_CHANNEL_5*/

# if defined (BRS_ENABLE_CAN_CHANNEL_6)
  BrsHwInitPortOutput(BRSHW_PORT_CAN6_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN6_RX);
  BrsHwInitPortConfig(BRSHW_PORT_CAN6_TX, BRSHW_PORT_CONF_CAN);
  BrsHwInitPortConfig(BRSHW_PORT_CAN6_RX, BRSHW_PORT_CONF_CAN);
#  if defined(_BRSHW_PORT_CAN6_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN6_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN6_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
#  if defined (_BRSHW_PORT_CAN6_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN6_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN6_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_CAN_CHANNEL_6*/

# if defined (BRS_ENABLE_CAN_CHANNEL_7) || defined (BRS_ENABLE_CAN_CHANNEL_8)  || \
     defined (BRS_ENABLE_CAN_CHANNEL_9) || defined (BRS_ENABLE_CAN_CHANNEL_10) || \
     defined (BRS_ENABLE_CAN_CHANNEL_11)
  #error "Port config for your CAN channel not yet implemented"
# endif
#endif /*BRS_ENABLE_CAN_SUPPORT*/

/*******************************************************************************
 *  LIN driver
 *******************************************************************************/
#if defined (BRS_ENABLE_LIN_SUPPORT)
# if defined (BRS_ENABLE_LIN_CHANNEL_0)
  BrsHwInitPortOutput(BRSHW_PORT_LIN0_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN0_RX);
#  if defined(_BRSHW_PORT_LIN0_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_LIN0_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_LIN0_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_LIN_CHANNEL_0*/

# if defined (BRS_ENABLE_LIN_CHANNEL_1)
  BrsHwInitPortOutput(BRSHW_PORT_LIN1_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN1_RX);
#  if defined(_BRSHW_PORT_LIN1_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_LIN1_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_LIN1_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_LIN_CHANNEL_1*/

# if defined (BRS_ENABLE_LIN_CHANNEL_2)
  BrsHwInitPortOutput(BRSHW_PORT_LIN2_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN2_RX);
#  if defined (_BRSHW_PORT_LIN2_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_LIN2_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_LIN2_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_LIN_CHANNEL_2*/

# if defined (BRS_ENABLE_LIN_CHANNEL_3)
  BrsHwInitPortOutput(BRSHW_PORT_LIN3_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN3_RX);
#  if defined(_BRSHW_PORT_LIN3_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_LIN3_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_LIN3_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_LIN_CHANNEL_3*/

# if defined (BRS_ENABLE_LIN_CHANNEL_4) || defined (BRS_ENABLE_LIN_CHANNEL_5) || \
     defined (BRS_ENABLE_LIN_CHANNEL_6) || defined (BRS_ENABLE_LIN_CHANNEL_7) || \
     defined (BRS_ENABLE_LIN_CHANNEL_8) || defined (BRS_ENABLE_LIN_CHANNEL_9) || \
     defined (BRS_ENABLE_LIN_CHANNEL_10) || defined (BRS_ENABLE_LIN_CHANNEL_11)
  #error "Port config for your LIN channel not yet implemented"
# endif
#endif /*BRS_ENABLE_LIN_SUPPORT*/

/*******************************************************************************
 *  FLEXRAY driver
 *******************************************************************************/
#if defined (BRS_ENABLE_FLEXRAY_SUPPORT)
# if defined (BRS_ENABLE_FLEXRAY_CHANNEL_0_A)
  BrsHwInitPortOutput(BRSHW_PORT_FR0A_TX);
  BrsHwInitPortInput(BRSHW_PORT_FR0A_RX);
  BrsHwInitPortOutput(BRSHW_PORT_FR0A_TXEN);
  BrsHwInitPortInput(BRSHW_PORT_FR0A_ERRNA);
#  if defined (_BRSHW_PORT_FR0A_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_FR0A_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_FR0A_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
#  if defined (_BRSHW_PORT_FR0A_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_FR0A_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_FR0A_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_FLEXRAY_CHANNEL_0_A*/

# if defined (BRS_ENABLE_FLEXRAY_CHANNEL_0_B)
  BrsHwInitPortOutput(BRSHW_PORT_FR0B_TX);
  BrsHwInitPortInput(BRSHW_PORT_FR0B_RX);
  BrsHwInitPortOutput(BRSHW_PORT_FR0B_TXEN);
  BrsHwInitPortInput(BRSHW_PORT_FR0B_ERRNB);
#  if defined (_BRSHW_PORT_FR0B_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_FR0B_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_FR0B_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
#  if defined (_BRSHW_PORT_FR0B_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_FR0B_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_FR0B_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_FLEXRAY_CHANNEL_0_B*/

#  if defined (BRS_ENABLE_FLEXRAY_CHANNEL_1_A)
  BrsHwInitPortOutput(BRSHW_PORT_FR1A_TX);
  BrsHwInitPortInput(BRSHW_PORT_FR1A_RX);
  BrsHwInitPortOutput(BRSHW_PORT_FR1A_TXEN);
  BrsHwInitPortInput(BRSHW_PORT_FR1A_ERRNA);
#   if defined(_BRSHW_PORT_FR1A_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_FR1A_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_FR1A_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#   endif
#   if defined (_BRSHW_PORT_FR1A_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_FR1A_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_FR1A_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#   endif
#  endif /*BRS_ENABLE_FLEXRAY_CHANNEL_1_A*/

#  if defined (BRS_ENABLE_FLEXRAY_CHANNEL_1_B)
  BrsHwInitPortOutput(BRSHW_PORT_FR1B_TX);
  BrsHwInitPortInput(BRSHW_PORT_FR1B_RX);
  BrsHwInitPortOutput(BRSHW_PORT_FR1B_TXEN);
  BrsHwInitPortInput(BRSHW_PORT_FR1B_ERRNB);
#   if defined(_BRSHW_PORT_FR1B_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_FR1B_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_FR1B_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#   endif
#   if defined (_BRSHW_PORT_FR1B_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_FR1B_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_FR1B_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#   endif
#  endif /*BRS_ENABLE_FLEXRAY_CHANNEL_1_B*/
#endif /*BRS_ENABLE_FLEXRAY_SUPPORT*/

/*******************************************************************************
 *  ETHERNET driver
 *******************************************************************************/
#if defined (BRS_ENABLE_ETHERNET_SUPPORT)
# if defined (BRSHW_PORT_ETH0_TYPE_RGMII)
  /* Reduced gigabit media-independent interface */
#  if defined (_BRSHW_PORT_ETH0_GREFCLK)
  BrsHwInitPortInput(BRSHW_PORT_ETH0_GREFCLK); /* RGMII_GREFCLK */
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_GREFCLK, BRSHW_PORT_CONF_ETHERNET);
#  endif
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXCLK);  /* RGMII_TXCLK */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD0);   /* RGMII_TXD0 */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD1);   /* RGMII_TXD1 */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD2);   /* RGMII_TXD2 */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD3);   /* RGMII_TXD3 */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TX_CTL); /* RGMII_CTL (This pin is also used for TXEN or TXER, because the TX_CTL signal carries TXEN on rising edge, and (TXEN xor TXER) on the falling edge) */

  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXCLK);   /* RGMII_RXCLK */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD0);    /* RGMII_RXD0 */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD1);    /* RGMII_RXD1 */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD2);    /* RGMII_RXD2 */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD3);    /* RGMII_RXD3 */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_RX_CTL); /* RGMII_CTL (This pin is also used for RXDV or RXER, because the RX_CTL signal carries RXDV on the rising edge, and (RXDV xor RXER) on the falling edge) */

  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXCLK, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXD0, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXD1, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXD2, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXD3, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TX_CTL, BRSHW_PORT_CONF_ETHERNET);

  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXCLK, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXD0, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXD1, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXD2, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXD3, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RX_CTL, BRSHW_PORT_CONF_ETHERNET);
# endif /*BRSHW_PORT_ETH0_TYPE_RGMII*/

# if defined (BRSHW_PORT_ETH0_TYPE_RMII)
  /* Reduced media-independent interface */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_REFCLK); /* RMII_REFCLK (This pin could also be set as Output, please check the user manual of the used transceiver)*/

  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD0);  /* RMII_TXD0 */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD1);  /* RMII_TXD1 */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXEN);  /* RMII_TXEN */

  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD0);  /* RMII_RXD0 */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD1);  /* RMII_RXD1 */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_CRSDV); /* RMII_CRSDV */
#  if defined (_BRSHW_PORT_ETH0_RXER)
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXER);  /* RMII_RXER (Optional) */
#  endif

  BrsHwInitPortConfig(BRSHW_PORT_ETH0_REFCLK, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXD0, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXD1, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXEN, BRSHW_PORT_CONF_ETHERNET);

  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXD0, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXD1, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_CRSDV, BRSHW_PORT_CONF_ETHERNET);
#  if defined (_BRSHW_PORT_ETH0_RXER)
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXER, BRSHW_PORT_CONF_ETHERNET);
#  endif
# endif /*BRSHW_PORT_ETH0_TYPE_RMII*/

# if defined (BRSHW_PORT_ETH0_TYPE_MII)
  /* Standard Media-independent interface */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXCLK); /* MII_TXCLK */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD0);  /* MII_TXD0 */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD1);  /* MII_TXD1 */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD2);  /* MII_TXD2 */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD3);  /* MII_TXD3 */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXEN);  /* MII_TXEN */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXER);  /* MII_TXER */

  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXCLK); /* MII_RXCLK */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD0);  /* MII_RXD0 */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD1);  /* MII_RXD1 */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD2);  /* MII_RXD2 */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD3);  /* MII_RXD3 */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXDV);  /* MII_RXDV */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXER);  /* MII_RXER */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_COL);   /* MII_COL */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_CRS);   /* MII_CRS */

  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXCLK, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXD0, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXD1, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXD2, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXD3, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXEN, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXER, BRSHW_PORT_CONF_ETHERNET);

  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXCLK, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXD0, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXD1, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXD2, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXD3, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXDV, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXER, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_COL, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_CRS, BRSHW_PORT_CONF_ETHERNET);
# endif /*BRSHW_PORT_ETH0_TYPE_MII*/

#  if defined (BRSHW_PORT_ETH0_TYPE_GMII) || defined (BRSHW_PORT_ETH0_TYPE_SGMII)
  /* Gigabit media-independent interface | Serial gigabit media-independent interface */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_TXCLK);   /* GMII_TXCLK (For 10 or 100 Mbit/s operation, the TXCLK is supplied by the PHY to the MAC) */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_GTXCLK); /* GMII_GTXCLK (For gigabit operation, the GTXCLK is supplied by the MAC to the PHY)*/
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD0);   /* GMII_TXD0 */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD1);   /* GMII_TXD1 */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD2);   /* GMII_TXD2 */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD3);   /* GMII_TXD3 */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD4);   /* GMII_TXD4 */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD5);   /* GMII_TXD5 */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD6);   /* GMII_TXD6 */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD7);   /* GMII_TXD7 */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXEN);   /* GMII_TXEN */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXER);   /* GMII_TXER */

  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXCLK); /* GMII_RXCLK */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD0);  /* GMII_RXD0 */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD1);  /* GMII_RXD1 */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD2);  /* GMII_RXD2 */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD3);  /* GMII_RXD3 */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD4);  /* GMII_RXD4 */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD5);  /* GMII_RXD5 */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD6);  /* GMII_RXD6 */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD7);  /* GMII_RXD7 */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXDV);  /* GMII_RXDV */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXER);  /* GMII_RXER */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_COL);   /* GMII_COL */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_CRS);   /* GMII_CRS */

  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXCLK, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_GTXCLK, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXD0, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXD1, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXD2, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXD3, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXD4, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXD5, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXD6, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXD7, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXEN, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_TXER, BRSHW_PORT_CONF_ETHERNET);

  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXCLK, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXD0, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXD1, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXD2, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXD3, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXD4, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXD5, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXD6, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXD7, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXDV, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_RXER, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_COL, BRSHW_PORT_CONF_ETHERNET);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0_CRS, BRSHW_PORT_CONF_ETHERNET);
# endif /*BRSHW_PORT_ETH0_TYPE_GMII||BRSHW_PORT_ETH0_TYPE_SGMII*/

  /* Management signals, used by every interface type */
  BrsHwInitPortInputOutput(BRSHW_PORT_ETH0_MDIO); /* MDIO */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_MDC);       /* MDC */

# if defined (_BRSHW_PORT_ETH0_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_ETH0_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
# endif

# if defined (BRS_PORT_GROUP_B) /* corresponds to TC3xx */
#  if defined (BRSHW_PORT_ETH0_TYPE_MII) || defined (BRSHW_PORT_ETH0_TYPE_RMII) || defined (BRSHW_PORT_ETH0_TYPE_RGMII)
  uint32 memoryType = IN_ROM;
  BRS_TRICORE_UNLOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);
  while((BRS_PORT_PCSR(BRSHW_PORT_ETH0_TXD0.portGroup) & 0x80000000) != 0);
#   if defined (BRSHW_PORT_ETH0_TYPE_MII)
  BRS_PORT_PCSR(BRSHW_PORT_ETH0_TXD0.portGroup) = (0x01 << BRSHW_PORT_ETH0_TXEN.portNumber) |
                                                  (0x01 << BRSHW_PORT_ETH0_TXD0.portNumber) |
                                                  (0x01 << BRSHW_PORT_ETH0_TXD1.portNumber) |
                                                  (0x01 << BRSHW_PORT_ETH0_TXD2.portNumber) |
                                                  (0x01 << BRSHW_PORT_ETH0_TXD3.portNumber) |
                                                  (0x01 << BRSHW_PORT_ETH0_TXCLK.portNumber);
#   endif /*BRSHW_PORT_ETH0_TYPE_MII*/
#   if defined (BRSHW_PORT_ETH0_TYPE_RMII)
  BRS_PORT_PCSR(BRSHW_PORT_ETH0_TXD0.portGroup) = (0x01 << BRSHW_PORT_ETH0_TXEN.portNumber) |
                                                  (0x01 << BRSHW_PORT_ETH0_TXD0.portNumber) |
                                                  (0x01 << BRSHW_PORT_ETH0_TXD1.portNumber);
#   endif /*BRSHW_PORT_ETH0_TYPE_MII*/
#   if defined (BRSHW_PORT_ETH0_TYPE_RGMII)
  BRS_PORT_PCSR(BRSHW_PORT_ETH0_TXD0.portGroup) = (0x01 << BRSHW_PORT_ETH0_TX_CTL.portNumber) |
                                                  (0x01 << BRSHW_PORT_ETH0_TXD0.portNumber) |
                                                  (0x01 << BRSHW_PORT_ETH0_TXD1.portNumber) |
                                                  (0x01 << BRSHW_PORT_ETH0_TXD2.portNumber) |
                                                  (0x01 << BRSHW_PORT_ETH0_TXD3.portNumber) |
                                                  (0x01 << BRSHW_PORT_ETH0_TXCLK.portNumber);
#   endif /*BRSHW_PORT_ETH0_TYPE_RGMII*/
  BRS_TRICORE_LOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);
#  endif /*BRSHW_PORT_ETH0_TYPE_MII||BRSHW_PORT_ETH0_TYPE_RMII||BRSHW_PORT_ETH0_TYPE_RGMII*/
# endif /*BRS_PORT_GROUP_B*/
#endif /*BRS_ENABLE_ETHERNET_SUPPORT*/

/*******************************************************************************
 *  I2C driver
 *******************************************************************************/
#if defined (BRS_ENABLE_I2C_SUPPORT)
  #error "Pin configuration for I2C not supported yet."
#endif /*BRS_ENABLE_I2C_SUPPORT*/

/*******************************************************************************
 *  HYPERBUS driver
 ********************************************************************************/
#if defined (BRS_ENABLE_HYPERBUS_SUPPORT)
  #error "Pin configuration for Hyperbus not supported yet."
#endif /*BRS_ENABLE_HYPERBUS_SUPPORT*/

/*******************************************************************************
 *  SPI driver
 *******************************************************************************/
#if defined (BRS_ENABLE_SPI_SUPPORT)
  #error "Pin configuration for SPI not supported yet."
#endif /*BRS_ENABLE_SPI_SUPPORT*/
}
#endif /*BRS_ENABLE_PORT*/

/*****************************************************************************/
/* @brief      Disable the global system interrupt.
 * @pre        Must be the first function call in main@BrsMain
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from main@BrsMain at power on initialization
 *****************************************************************************/
void BrsHwDisableInterruptAtPowerOn(void)
{
#if defined (BRS_COMP_TASKING)
  __disable();
#endif /*BRS_COMP_x*/
}

/*****************************************************************************/
/* @brief      Program the vector table base addresses
 * @pre        -
 * @param[in]  ExcVecLabel - address of the core exception table
 *             IntVecLabel - address of the interrupt vector table
 *             Use BRS_DEFINE_ADDRESS_UNUSED for unused values
 * @param[out] -
 * @return     -
 * @context    Function is called from main@BrsMain at power on initialization
 *****************************************************************************/
void BrsHw_ExceptionTable_Init(Brs_AddressOfConstType ExcVecLabel, Brs_AddressOfConstType IntVecLabel)
{
  uint32 CurrentCoreId = BRS_READ_COREID();
  uint32 memoryType = IN_ROM;
/* =========================================================================== */
/* initialize BIV and BTV / endinit protected */
/* =========================================================================== */
  if (ExcVecLabel!=BRS_DEFINE_ADDRESS_UNUSED)
    if((((uint32)ExcVecLabel) % 0x100) != 0)
    {
      /* the trap vector table must be aligned on a 256 byte boundary */
      for(;;);
    }

  if (IntVecLabel!=BRS_DEFINE_ADDRESS_UNUSED)
    if((((uint32)IntVecLabel) % 0x2000) != 0)
    {
      /* the interrupt vector table must be aligned on a 8192 byte boundary */
      for(;;);
    }

  BRS_TRICORE_UNLOCKENDINIT(CurrentCoreId, memoryType);
  if (ExcVecLabel!=BRS_DEFINE_ADDRESS_UNUSED)
  {
    BRS_MOVE_TO_CSFR(BRS_BTV_OFFSET, (uint32)ExcVecLabel);
  }

  if (IntVecLabel!=BRS_DEFINE_ADDRESS_UNUSED)
  {
    BRS_MOVE_TO_CSFR(BRS_BIV_OFFSET, (uint32)IntVecLabel);
  }

  BRS_MOVE_TO_CSFR(BRS_PCON0_OFFSET, 0x0UL); /* setting the PCON0 to zero disables the cache bypass (thus program caching is enabled) */
  BRS_TRICORE_LOCKENDINIT(CurrentCoreId, memoryType);
}

/*****************************************************************************/
/* @brief      Restart ECU (issue a software reset or jump to startup code)
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from e.g. ECU state handling
 *****************************************************************************/
void BrsHwSoftwareResetECU(void)
{
  uint32 ui32tmp;
  uint32 memoryType = IN_ROM;
  BrsMain_SoftwareResetECU_Hook();

#if !defined (BRS_ENABLE_FBL_SUPPORT) /* FBL is always running in polling mode with interrupts disabled */
  DisableAllInterrupts();
#endif

#if defined (BRS_PLL_GROUP_A) || defined (BRS_PLL_GROUP_B)
  /* set SW Reset Request Trigger Reset Configuration to Systen Reset */
  BRS_TRICORE_UNLOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);
  ui32tmp = BRS_RSTCON;
  ui32tmp &= 0xFFFFFCFF;
  ui32tmp |= 0x00000100;
  BRS_RSTCON = ui32tmp;
#endif
  BRS_TRICORE_LOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);

  /* trigger a software reset */
#if defined (BRS_RESET_GROUP_A)
  BRS_TRICORE_UNLOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);
  BRS_SWRSTCON |= 0x00000002;
  BRS_TRICORE_LOCKENDINIT(BRS_SAFETY_WATCHDOG_INDEX, memoryType);

#elif defined (BRS_RESET_GROUP_B)
  BRS_TRICORE_UNLOCKENDINIT(BRS_READ_COREID(), memoryType);
  BRS_SWRSTCON |= 0x00000002;
  BRS_TRICORE_LOCKENDINIT(BRS_READ_COREID(), memoryType);
#endif

  while (1)
  {
    /* Wait until reset/watchdog reset occurs */
  }
}

#if defined (BRS_FIRST_EXECUTION_INSTANCE)
/* This code is only needed for the first instance/executable in the system */
#define BRS_START_SEC_STARTUP_CODE
#include "Brs_MemMap.h"
/*****************************************************************************/
/* @brief      Get reset reason
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     Reset reason
 * @context    Function is called from BrsMainStartup to determine if reset
 *             was triggered through software call (BrsHwSoftwareResetECU()).
 *             The result is stored by BrsMainStartup in the global variable
 *             brsMain_ResetReason. It should only be called once, during
 *             startup. The old API name BrsHwGetResetReason() is remapped
 *             to BrsMainGetResetReason.
 *****************************************************************************/
brsMain_ResetReasonType BrsHwGetResetReasonStartup(void)
{
  if((BRS_RSTSTAT & 0x10) == 0x10)
  {
    return BRSMAIN_RESET_SW;
  }
  else
  {
    return BRSMAIN_RESET_OTHER;
  }
}
#define BRS_STOP_SEC_STARTUP_CODE
#include "Brs_MemMap.h"
#endif /*BRS_FIRST_EXECUTION_INSTANCE*/

/*****************************************************************************/
/* @brief      This API is used for the BRS time measurement support to get a
 *             default time value for all measurements with this platform to
 *             be able to compare time measurements on different dates based
 *             on this time result.
 * @pre        Should be called with interrupts global disabled
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from e.g. component testsuits for calibration
 *****************************************************************************/
void BrsHwTime100NOP(void)
{
  nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();
  nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();
  nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();
  nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();
  nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();

  nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();
  nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();
  nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();
  nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();
  nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();
}

#if defined (BRS_ENABLE_SAFECTXSUPPORT)
/*****************************************************************************/
/* @brief      This API is used to enable hardware access in untrusted mode
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function must be called after all depending peripheral modules
 *             are supplied by proper clocks AND before the OS is started.
 *****************************************************************************/
void BrsHw_EnableHwAccess(void)
{
  /* Nothing to do for Aurix/AurixPlus yet */
}
#endif /*BRS_ENABLE_SAFECTXSUPPORT*/

/* check if necessary vismaa*/
//#if defined (BRS_ENABLE_FBL_SUPPORT)
// #define BRS_START_SEC_ROM_CODE
// #include "Brs_MemMap.h"
//#endif
/*****************************************************************************/
/* @brief      This API is used to read the core ID of the actual running core
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     Core ID of the actual running core
 * @context    Function is e.g. called from main@BrsMain, to only call HW-init
 *             code once, on the boot core.
 *             In MultiCore setups, additional BRSHW_INIT_CORE_ID must be
 *             declared inside BrsHw.h, to configure the proper core ID value
 *             of that boot core.
 *****************************************************************************/
uint32 BrsHw_GetCore(void)
{
  return BRS_MOVE_FROM_CSFR(BRS_CORE_ID_REGISTER);
}
/* check if necessary vismaa*/
//#if defined (BRS_ENABLE_FBL_SUPPORT)
// #define BRS_STOP_SEC_ROM_CODE
// #include "Brs_MemMap.h"
//#endif

/*****************************************************************************/
/* @brief      This API is used to enable an interrupt source in the core
 *             interrupt controller.
 * @pre        -
 * @param[in]  Source to be enabled.
 * @param[in]  Priority level to be set.
 * @param[out] -
 * @return     -
 * @context    Function is called from HlpTest and other test environments.
 *****************************************************************************/
void BrsHw_EnableInterrupt(uint32 Source, uint8 Priority)
{
  /* #10 Enable the given interrupt source in its SRC register. */
  BRS_INT_SRC(Source) |= BRS_INT_SRC_SRE_MASK;
  BRS_INT_SRC(Source) |= Priority;
}

/*****************************************************************************/
/* @brief      This API is used to disable an interrupt source in the core
 *             interrupt controller.
 * @pre        -
 * @param[in]  Source to be disabled.
 * @param[out] -
 * @return     -
 * @context    Function is called from HlpTest and other test environments.
 *****************************************************************************/
void BrsHw_DisableInterrupt(uint32 Source)
{
  /* #10 Disable the given interrupt source in its SRC register. */
  BRS_INT_SRC(Source) &= ~BRS_INT_SRC_SRE_MASK;
}

/*****************************************************************************/
/* @brief      This API is used to trigger the given software interrupt source.
 * @pre        -
 * @param[in]  Source to be triggered.
 *             Some derivatives only support few software triggerable sources,
 *             check for their validity.
 * @param[out] -
 * @return     -
 * @context    Function is called from HlpTest and other test environments.
 *****************************************************************************/
void BrsHw_TriggerSoftwareInterrupt(uint32 Source)
{
  BRS_INT_SRC(Source) |= BRS_INT_SRC_SETR_MASK;
}

#if defined (BRS_ENABLE_FBL_SUPPORT)
/*****************************************************************************/
/* @brief      This API is used to disable the flash ECC error reporting,
 *             if this is necessary on the platform to grant access to it.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from FBL boot code, before flash is accessed.
 *****************************************************************************/
void BrsHwDisableEccErrorReporting(void)
{
  uint32 memoryType = IN_ROM;
#if defined (BRS_DERIVATIVE_GROUP_TC2xx)
  /* Disable Flash 0 traps. TODO: Check if this is needed by your configuration. */
  /* FLASH0_MARD */
  BRS_FLASH0_MARD = 0x00008000ul;
  /* FLASH0_MARP */
  BRS_TRICORE_UNLOCKENDINIT(BRS_READ_COREID(), memoryType);
  BRS_FLASH0_MARP = 0x00008000ul;
  BRS_TRICORE_LOCKENDINIT(BRS_READ_COREID(), memoryType);

#elif defined (BRS_DERIVATIVE_GROUP_TC3xx)
  /* Disable uncorrectable bit error traps */
  BRS_TRICORE_UNLOCKENDINIT(BRS_READ_COREID(), memoryType);

  /* Mask PFLASH uncorrectable ECC bit error */
  BRS_CPU_FLASHCON(0, 1u) = BRS_FLASHCON1_MASKUECC;       /* CPU0_FLASHCON1 MASKUECC=1 (ECC error disabled) */
#if (BRS_CPU_CORE_AMOUNT > 1)
  BRS_CPU_FLASHCON(1, 1u) = BRS_FLASHCON1_MASKUECC;       /* CPU1_FLASHCON1 MASKUECC=1 (ECC error disabled) */
#endif
#if (BRS_CPU_CORE_AMOUNT > 2)
  BRS_CPU_FLASHCON(2, 1u) = BRS_FLASHCON1_MASKUECC;       /* CPU2_FLASHCON1 MASKUECC=1 (ECC error disabled) */
#endif
#if (BRS_CPU_CORE_AMOUNT > 3)
  BRS_CPU_FLASHCON(3, 1u) = BRS_FLASHCON1_MASKUECC;       /* CPU3_FLASHCON1 MASKUECC=1 (ECC error disabled) */
#endif
#if (BRS_CPU_CORE_AMOUNT > 5)
  BRS_CPU_FLASHCON(4, 1u) = BRS_FLASHCON1_MASKUECC;       /* CPU4_FLASHCON1 MASKUECC=1 (ECC error disabled) */
  BRS_CPU_FLASHCON(5, 1u) = BRS_FLASHCON1_MASKUECC;       /* CPU5_FLASHCON1 MASKUECC=1 (ECC error disabled) */
#endif

  /* For DF0 and DF1 (when DF1 is configured as not HSM_exclusive), the uncorrectable ECC error trap is disabled. */
  BRS_DMU_ECCC(0) = BRS_DMU_ECCC_TRAPDIS; /* DMU_HF_ECCC TRAPDIS = ECC error trap is disabled */
  /* If DF1 is configured as HSM_exclusive then the uncorrectable ECC error trap is disabled. */
  /* BRS_DMU_ECCC(1) = BRS_DMU_ECCC_TRAPDIS; */ /* DMU_SF_ECCC TRAPDIS = ECC error trap is disabled */

  BRS_TRICORE_LOCKENDINIT(BRS_READ_COREID(), memoryType);

# else
  #error Function to Disable Ecc Error Reporting is currently only supported for TC2xx and TC3xx derivative groups.
#endif /*BRS_DERIVATIVE_GROUP_x*/
}
#endif /*BRS_ENABLE_FBL_SUPPORT*/

/* DrvCan/DrvLin/DrvFr/DrvEth application callback functions for access protection of critical registers */
/* As different driver versions use different callback names, they are duplicated. */
#if defined (BRS_ENABLE_CAN_SUPPORT)      || \
    defined (BRS_ENABLE_LIN_SUPPORT)      || \
    defined (BRS_ENABLE_FLEXRAY_SUPPORT)  || \
    defined (BRS_ENABLE_ETHERNET_SUPPORT)

# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_START_SEC_RAM_CODE
  #include "Brs_MemMap.h"
# endif
void Appl_UnlockInit(void)
{
  BRS_TRICORE_UNLOCKENDINIT(BRS_READ_COREID(), IN_RAM);
}

void Appl_UnlockEndinit(void)
{
  BRS_TRICORE_UNLOCKENDINIT(BRS_READ_COREID(), IN_RAM);
}

void Appl_LockInit(void)
{
  BRS_TRICORE_LOCKENDINIT(BRS_READ_COREID(), IN_RAM);
}

void Appl_LockEndinit(void)
{
  BRS_TRICORE_LOCKENDINIT(BRS_READ_COREID(), IN_RAM);
}
# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_STOP_SEC_RAM_CODE
  #include "Brs_MemMap.h"
# endif
#endif /*BRS_ENABLE_CAN_SUPPORT || BRS_ENABLE_LIN_SUPPORT || BRS_ENABLE_FLEXRAY_SUPPORT || BRS_ENABLE_ETHERNET_SUPPORT*/

/* DrvCan Application function for wait mechanism */
#if defined (BRS_ENABLE_CAN_SUPPORT)
void ApplCanWaitSetMCR(void)
{
  uint32 i;
  for (i=0; i<10000; i++)
  {
    nop();
  }
}
#endif /*BRS_ENABLE_CAN_SUPPORT*/

#if defined (BRS_ENABLE_FLEXRAY_SUPPORT)
/*****************************************************************************/
/* @brief      Callback from communication stack. Init E-RAY RAM to avoid ECC errors
 * @pre
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called Fr_InitMemory(). It is just an empty function
 *             because the RAM init is already done during startup.
 *****************************************************************************/
void Appl_TricoreAurixInit(void)
{
   /* Callback from communication stack. Init E-RAY RAM to avoid ECC errors
      -> Already done in startup! */
}
#endif /*BRS_ENABLE_FLEXRAY_SUPPORT*/

#if defined (BRS_ENABLE_OS_MULTICORESUPPORT)
/*****************************************************************************/
/* @brief      This API is used as sync barrier. It is used to unlock cores
 *             that are locked in the Startup code. The implementation is only
 *             needed on platforms, where all cores are started automatically
 *             after a power-on reset. All additional cores are looped, until
 *             the boot core reaches this function.
 * @pre        -
 * @param[in]  uint32 coreId
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsMainStartup on the boot core.
 *****************************************************************************/
void BrsHw_UnlockCores(uint32 coreId)
{
  /* The mechanism is not used/needed on this platform */
}
#endif /*BRS_ENABLE_OS_MULTICORESUPPORT*/
