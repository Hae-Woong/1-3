/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *             File:  Rte_BSW_Handler_Type.h
 *           Config:  LightControl.dpa
 *        SW-C Type:  BSW_Handler
 *
 *        Generator:  MICROSAR RTE Generator Version 4.37.00
 *                    RTE Core Version 4.37.00
 *          License:  PAI11871
 *
 *      Description:  Application types header file for SW-C <BSW_Handler> (Contract Phase)
 *********************************************************************************************************************/

/* double include prevention */
#ifndef RTE_BSW_HANDLER_TYPE_H
# define RTE_BSW_HANDLER_TYPE_H

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

# include "Rte_Type.h"

# ifndef RTE_CORE

/**********************************************************************************************************************
 * Range, Invalidation, Enumeration and Bit Field Definitions
 *********************************************************************************************************************/

#  ifndef COMM_NO_COMMUNICATION
#   define COMM_NO_COMMUNICATION (0U)
#  endif

#  ifndef COMM_SILENT_COMMUNICATION
#   define COMM_SILENT_COMMUNICATION (1U)
#  endif

#  ifndef COMM_FULL_COMMUNICATION
#   define COMM_FULL_COMMUNICATION (2U)
#  endif
# endif /* RTE_CORE */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* RTE_BSW_HANDLER_TYPE_H */
