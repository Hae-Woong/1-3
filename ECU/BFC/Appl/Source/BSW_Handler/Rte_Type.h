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
 *             File:  Rte_Type.h
 *           Config:  LightControl.dpa
 *        SW-C Type:  BSW_Handler
 *
 *        Generator:  MICROSAR RTE Generator Version 4.37.00
 *                    RTE Core Version 4.37.00
 *          License:  PAI11871
 *
 *      Description:  Header file containing user defined AUTOSAR types and RTE structures (Contract Phase)
 *********************************************************************************************************************/

/* PRQA S 0777, 0779 EOF */ /* MD_MSR_Rule5.1, MD_MSR_Rule5.2 */

/* double include prevention */
#ifndef RTE_TYPE_H
# define RTE_TYPE_H

# include "Rte.h"

/* PRQA S 1039 EOF */ /* MD_Rte_1039 */

/**********************************************************************************************************************
 * Data type definitions
 *********************************************************************************************************************/

# define Rte_TypeDef_ComM_ModeType
typedef uint8 ComM_ModeType;


# ifndef RTE_SUPPRESS_UNUSED_DATATYPES
/**********************************************************************************************************************
 * Unused Data type definitions
 *********************************************************************************************************************/

#  define Rte_TypeDef_Boolean
typedef boolean Boolean;

#  define Rte_TypeDef_ComM_InhibitionStatusType
typedef uint8 ComM_InhibitionStatusType;

#  define Rte_TypeDef_ComM_UserHandleType
typedef uint16 ComM_UserHandleType;

#  define Rte_TypeDef_NvM_RequestResultType
typedef uint8 NvM_RequestResultType;

#  define Rte_TypeDef_NvM_ServiceIdType
typedef uint8 NvM_ServiceIdType;

#  define Rte_TypeDef_UInt16
typedef uint16 UInt16;

#  define Rte_TypeDef_UInt32
typedef uint32 UInt32;

#  define Rte_TypeDef_UInt8
typedef uint8 UInt8;

#  define Rte_TypeDef_dtRef_VOID
typedef void * dtRef_VOID;

#  define Rte_TypeDef_dtRef_const_VOID
typedef const void * dtRef_const_VOID;

#  define Rte_TypeDef_DataArrayType_uint8_6
typedef uint8 DataArrayType_uint8_6[6];

#  define Rte_TypeDef_Dcm_Data13ByteType
typedef uint8 Dcm_Data13ByteType[13];

#  define Rte_TypeDef_Dcm_Data15ByteType
typedef uint8 Dcm_Data15ByteType[15];

#  define Rte_TypeDef_Dcm_Data17ByteType
typedef uint8 Dcm_Data17ByteType[17];

#  define Rte_TypeDef_Dcm_Data2ByteType
typedef uint8 Dcm_Data2ByteType[2];

#  define Rte_TypeDef_Dcm_Data4ByteType
typedef uint8 Dcm_Data4ByteType[4];

#  define Rte_TypeDef_Dcm_Data6ByteType
typedef uint8 Dcm_Data6ByteType[6];

#  define Rte_TypeDef_Dcm_RequestDataArrayType
typedef uint8 Dcm_RequestDataArrayType[48];

#  define Rte_TypeDef_Dem_MaxDataValueType
typedef uint8 Dem_MaxDataValueType[6];

#  define Rte_TypeDef_DataPrimitiveType_uint16
typedef uint16 DataPrimitiveType_uint16;

#  define Rte_TypeDef_Dcm_DataElement_Boot_Software_Boot_Software_Identification_PrimitiveType
typedef uint32 Dcm_DataElement_Boot_Software_Boot_Software_Identification_PrimitiveType;

#  define Rte_TypeDef_Dcm_DataElement_Boot_Software_NumberOfModules_PrimitiveType
typedef uint8 Dcm_DataElement_Boot_Software_NumberOfModules_PrimitiveType;

#  define Rte_TypeDef_Dcm_DataElement_DID_0x0017_DID_Sint32_Array_ArrayType
typedef sint32 Dcm_DataElement_DID_0x0017_DID_Sint32_Array_ArrayType;

#  define Rte_TypeDef_Dcm_DataElement_DID_0x0018_DID_Uint32_Array_ArrayType
typedef uint32 Dcm_DataElement_DID_0x0018_DID_Uint32_Array_ArrayType;

#  define Rte_TypeDef_Dcm_DataElement_DID_0x0019_DID_Sint16_Array_ArrayType
typedef sint16 Dcm_DataElement_DID_0x0019_DID_Sint16_Array_ArrayType;

#  define Rte_TypeDef_Dcm_DataElement_DID_0x001A_DID_Uint16_Array_ArrayType
typedef uint16 Dcm_DataElement_DID_0x001A_DID_Uint16_Array_ArrayType;

#  define Rte_TypeDef_Dcm_DataElement_DID_0x001B_DID_Sint8_Array_ArrayType
typedef sint8 Dcm_DataElement_DID_0x001B_DID_Sint8_Array_ArrayType;

#  define Rte_TypeDef_Dcm_DataElement_DID_0xF410_DID_Data_PrimitiveType
typedef uint16 Dcm_DataElement_DID_0xF410_DID_Data_PrimitiveType;

#  define Rte_TypeDef_Dcm_DataElement_DID_0xF412_DID_Data_PrimitiveType
typedef uint16 Dcm_DataElement_DID_0xF412_DID_Data_PrimitiveType;

#  define Rte_TypeDef_Dcm_DataElement_DID_0xF413_DID_Data_PrimitiveType
typedef uint16 Dcm_DataElement_DID_0xF413_DID_Data_PrimitiveType;

#  define Rte_TypeDef_Dcm_DataElement_DataDiagnosticIdentifier_DID_DataDiagnosticIdentifier_PrimitiveType
typedef uint16 Dcm_DataElement_DataDiagnosticIdentifier_DID_DataDiagnosticIdentifier_PrimitiveType;

#  define Rte_TypeDef_Dcm_DataElement_DevelopmentData_CanDriverVersion_PrimitiveType
typedef uint16 Dcm_DataElement_DevelopmentData_CanDriverVersion_PrimitiveType;

#  define Rte_TypeDef_Dcm_DataElement_DevelopmentData_DiagnosticModuleVersion_PrimitiveType
typedef uint16 Dcm_DataElement_DevelopmentData_DiagnosticModuleVersion_PrimitiveType;

#  define Rte_TypeDef_Dcm_DataElement_DevelopmentData_NmVersion_PrimitiveType
typedef uint16 Dcm_DataElement_DevelopmentData_NmVersion_PrimitiveType;

#  define Rte_TypeDef_Dcm_DataElement_DevelopmentData_OperatingSystemVersion_PrimitiveType
typedef uint16 Dcm_DataElement_DevelopmentData_OperatingSystemVersion_PrimitiveType;

#  define Rte_TypeDef_Dcm_DataElement_DevelopmentData_TransportLayerVersion_PrimitiveType
typedef uint16 Dcm_DataElement_DevelopmentData_TransportLayerVersion_PrimitiveType;

#  define Rte_TypeDef_Dcm_DataElement_Example_ReadWriteData_GlobalTime_PrimitiveType
typedef uint32 Dcm_DataElement_Example_ReadWriteData_GlobalTime_PrimitiveType;

#  define Rte_TypeDef_Dcm_DataElement_Example_WriteOnlyDID_DID_DataObject_PrimitiveType
typedef uint8 Dcm_DataElement_Example_WriteOnlyDID_DID_DataObject_PrimitiveType;

#  define Rte_TypeDef_Dcm_DataElement_SampleIoControl_DID_Data_PrimitiveType
typedef uint32 Dcm_DataElement_SampleIoControl_DID_Data_PrimitiveType;

#  define Rte_TypeDef_Dcm_DataElement_SerialNumber_SerialNumber_PrimitiveType
typedef uint32 Dcm_DataElement_SerialNumber_SerialNumber_PrimitiveType;

#  define Rte_TypeDef_Dcm_NegativeResponseCodeType
typedef uint8 Dcm_NegativeResponseCodeType;

#  define Rte_TypeDef_Dcm_RequestDataOut_SampleRoutineControl_Out_ResultPrimitiveType
typedef uint16 Dcm_RequestDataOut_SampleRoutineControl_Out_ResultPrimitiveType;

#  define Rte_TypeDef_Dcm_RequestDataOut_SampleRoutineControl_Out_ResultType
typedef Dcm_RequestDataOut_SampleRoutineControl_Out_ResultPrimitiveType Dcm_RequestDataOut_SampleRoutineControl_Out_ResultType;

#  define Rte_TypeDef_Dcm_RequestDataOut_SampleRoutineControl_StartOnly_Out_ResultPrimitiveType
typedef uint32 Dcm_RequestDataOut_SampleRoutineControl_StartOnly_Out_ResultPrimitiveType;

#  define Rte_TypeDef_Dcm_RequestDataOut_SampleRoutineControl_StartOnly_Out_ResultType
typedef Dcm_RequestDataOut_SampleRoutineControl_StartOnly_Out_ResultPrimitiveType Dcm_RequestDataOut_SampleRoutineControl_StartOnly_Out_ResultType;

#  define Rte_TypeDef_Dcm_StartDataIn_SampleRoutineControl_In_Option0PrimitiveType
typedef uint8 Dcm_StartDataIn_SampleRoutineControl_In_Option0PrimitiveType;

#  define Rte_TypeDef_Dcm_StartDataIn_SampleRoutineControl_In_Option0Type
typedef Dcm_StartDataIn_SampleRoutineControl_In_Option0PrimitiveType Dcm_StartDataIn_SampleRoutineControl_In_Option0Type;

#  define Rte_TypeDef_Dcm_StartDataIn_SampleRoutineControl_StartOnly_In_Option1ArrayType
typedef uint8 Dcm_StartDataIn_SampleRoutineControl_StartOnly_In_Option1ArrayType;

#  define Rte_TypeDef_Dcm_StartDataOut_SampleRoutineControl_Out_InitStatePrimitiveType
typedef uint32 Dcm_StartDataOut_SampleRoutineControl_Out_InitStatePrimitiveType;

#  define Rte_TypeDef_Dcm_StartDataOut_SampleRoutineControl_Out_InitStateType
typedef Dcm_StartDataOut_SampleRoutineControl_Out_InitStatePrimitiveType Dcm_StartDataOut_SampleRoutineControl_Out_InitStateType;

#  define Rte_TypeDef_Dcm_StopDataOut_SampleRoutineControl_Out_StopStatePrimitiveType
typedef uint32 Dcm_StopDataOut_SampleRoutineControl_Out_StopStatePrimitiveType;

#  define Rte_TypeDef_Dcm_StopDataOut_SampleRoutineControl_Out_StopStateType
typedef Dcm_StopDataOut_SampleRoutineControl_Out_StopStatePrimitiveType Dcm_StopDataOut_SampleRoutineControl_Out_StopStateType;

#  define Rte_TypeDef_Dem_BufferLengthType
typedef uint16 Dem_BufferLengthType;

#  define Rte_TypeDef_Dem_DTCGroupType
typedef uint32 Dem_DTCGroupType;

#  define Rte_TypeDef_Dem_DTCStatusMaskType
typedef uint8 Dem_DTCStatusMaskType;

#  define Rte_TypeDef_Dem_EventIdType
typedef uint16 Dem_EventIdType;

#  define Rte_TypeDef_Dem_OperationCycleIdType
typedef uint8 Dem_OperationCycleIdType;

#  define Rte_TypeDef_Dem_RatioIdType
typedef uint16 Dem_RatioIdType;

#  define Rte_TypeDef_EcuM_TimeType
typedef uint32 EcuM_TimeType;

#  define Rte_TypeDef_EcuM_UserType
typedef uint8 EcuM_UserType;

#  define Rte_TypeDef_NvM_BlockIdType
typedef uint16 NvM_BlockIdType;

#  define Rte_TypeDef_TimeInMicrosecondsType
typedef uint32 TimeInMicrosecondsType;

#  define Rte_TypeDef_Dcm_CommunicationModeType
typedef uint8 Dcm_CommunicationModeType;

#  define Rte_TypeDef_Dcm_ConfirmationStatusType
typedef uint8 Dcm_ConfirmationStatusType;

#  define Rte_TypeDef_Dcm_ControlDtcSettingType
typedef uint8 Dcm_ControlDtcSettingType;

#  define Rte_TypeDef_Dcm_DiagnosticSessionControlType
typedef uint8 Dcm_DiagnosticSessionControlType;

#  define Rte_TypeDef_Dcm_EcuResetType
typedef uint8 Dcm_EcuResetType;

#  define Rte_TypeDef_Dcm_OpStatusType
typedef uint8 Dcm_OpStatusType;

#  define Rte_TypeDef_Dcm_ProtocolType
typedef uint8 Dcm_ProtocolType;

#  define Rte_TypeDef_Dcm_RequestKindType
typedef uint8 Dcm_RequestKindType;

#  define Rte_TypeDef_Dcm_SecLevelType
typedef uint8 Dcm_SecLevelType;

#  define Rte_TypeDef_Dcm_SesCtrlType
typedef uint8 Dcm_SesCtrlType;

#  define Rte_TypeDef_Dem_DTCFormatType
typedef uint8 Dem_DTCFormatType;

#  define Rte_TypeDef_Dem_DTCKindType
typedef uint8 Dem_DTCKindType;

#  define Rte_TypeDef_Dem_DTCOriginType
typedef uint16 Dem_DTCOriginType;

#  define Rte_TypeDef_Dem_DTCSeverityType
typedef uint8 Dem_DTCSeverityType;

#  define Rte_TypeDef_Dem_DTRControlType
typedef uint8 Dem_DTRControlType;

#  define Rte_TypeDef_Dem_DebounceResetStatusType
typedef uint8 Dem_DebounceResetStatusType;

#  define Rte_TypeDef_Dem_DebouncingStateType
typedef uint8 Dem_DebouncingStateType;

#  define Rte_TypeDef_Dem_EventStatusType
typedef uint8 Dem_EventStatusType;

#  define Rte_TypeDef_Dem_IndicatorStatusType
typedef uint8 Dem_IndicatorStatusType;

#  define Rte_TypeDef_Dem_InitMonitorReasonType
typedef uint8 Dem_InitMonitorReasonType;

#  define Rte_TypeDef_Dem_IumprDenomCondIdType
typedef uint8 Dem_IumprDenomCondIdType;

#  define Rte_TypeDef_Dem_IumprDenomCondStatusType
typedef uint8 Dem_IumprDenomCondStatusType;

#  define Rte_TypeDef_Dem_IumprReadinessGroupType
typedef uint8 Dem_IumprReadinessGroupType;

#  define Rte_TypeDef_Dem_MonitorStatusType
typedef uint8 Dem_MonitorStatusType;

#  define Rte_TypeDef_Dem_OperationCycleStateType
typedef uint8 Dem_OperationCycleStateType;

#  define Rte_TypeDef_Dem_UdsStatusByteType
typedef uint8 Dem_UdsStatusByteType;

#  define Rte_TypeDef_EcuM_BootTargetType
typedef uint8 EcuM_BootTargetType;

#  define Rte_TypeDef_EcuM_ModeType
typedef uint8 EcuM_ModeType;

#  define Rte_TypeDef_EcuM_ShutdownCauseType
typedef uint8 EcuM_ShutdownCauseType;

#  define Rte_TypeDef_EcuM_StateType
typedef uint8 EcuM_StateType;

#  define Rte_TypeDef_Dcm_DataElement_DID_0x0017_DID_Sint32_ArrayType
typedef Dcm_DataElement_DID_0x0017_DID_Sint32_Array_ArrayType Dcm_DataElement_DID_0x0017_DID_Sint32_ArrayType[5];

#  define Rte_TypeDef_Dcm_DataElement_DID_0x0018_DID_Uint32_ArrayType
typedef Dcm_DataElement_DID_0x0018_DID_Uint32_Array_ArrayType Dcm_DataElement_DID_0x0018_DID_Uint32_ArrayType[6];

#  define Rte_TypeDef_Dcm_DataElement_DID_0x0019_DID_Sint16_ArrayType
typedef Dcm_DataElement_DID_0x0019_DID_Sint16_Array_ArrayType Dcm_DataElement_DID_0x0019_DID_Sint16_ArrayType[11];

#  define Rte_TypeDef_Dcm_DataElement_DID_0x001A_DID_Uint16_ArrayType
typedef Dcm_DataElement_DID_0x001A_DID_Uint16_Array_ArrayType Dcm_DataElement_DID_0x001A_DID_Uint16_ArrayType[4];

#  define Rte_TypeDef_Dcm_DataElement_DID_0x001B_DID_Sint8_ArrayType
typedef Dcm_DataElement_DID_0x001B_DID_Sint8_Array_ArrayType Dcm_DataElement_DID_0x001B_DID_Sint8_ArrayType[28];

#  define Rte_TypeDef_Dcm_StartDataIn_SampleRoutineControl_StartOnly_In_Option1Type
typedef Dcm_StartDataIn_SampleRoutineControl_StartOnly_In_Option1ArrayType Dcm_StartDataIn_SampleRoutineControl_StartOnly_In_Option1Type[3];

#  define Rte_TypeDef_Dcm_DataElement_Boot_Software_Boot_Software_IdentificationType
typedef Dcm_DataElement_Boot_Software_Boot_Software_Identification_PrimitiveType Dcm_DataElement_Boot_Software_Boot_Software_IdentificationType;

#  define Rte_TypeDef_Dcm_DataElement_Boot_Software_NumberOfModulesType
typedef Dcm_DataElement_Boot_Software_NumberOfModules_PrimitiveType Dcm_DataElement_Boot_Software_NumberOfModulesType;

#  define Rte_TypeDef_Dcm_DataElement_DID_0xF410_DID_DataType
typedef Dcm_DataElement_DID_0xF410_DID_Data_PrimitiveType Dcm_DataElement_DID_0xF410_DID_DataType;

#  define Rte_TypeDef_Dcm_DataElement_DID_0xF412_DID_DataType
typedef Dcm_DataElement_DID_0xF412_DID_Data_PrimitiveType Dcm_DataElement_DID_0xF412_DID_DataType;

#  define Rte_TypeDef_Dcm_DataElement_DID_0xF413_DID_DataType
typedef Dcm_DataElement_DID_0xF413_DID_Data_PrimitiveType Dcm_DataElement_DID_0xF413_DID_DataType;

#  define Rte_TypeDef_Dcm_DataElement_DataDiagnosticIdentifier_DID_DataDiagnosticIdentifierType
typedef Dcm_DataElement_DataDiagnosticIdentifier_DID_DataDiagnosticIdentifier_PrimitiveType Dcm_DataElement_DataDiagnosticIdentifier_DID_DataDiagnosticIdentifierType;

#  define Rte_TypeDef_Dcm_DataElement_DevelopmentData_CanDriverVersionType
typedef Dcm_DataElement_DevelopmentData_CanDriverVersion_PrimitiveType Dcm_DataElement_DevelopmentData_CanDriverVersionType;

#  define Rte_TypeDef_Dcm_DataElement_DevelopmentData_DiagnosticModuleVersionType
typedef Dcm_DataElement_DevelopmentData_DiagnosticModuleVersion_PrimitiveType Dcm_DataElement_DevelopmentData_DiagnosticModuleVersionType;

#  define Rte_TypeDef_Dcm_DataElement_DevelopmentData_NmVersionType
typedef Dcm_DataElement_DevelopmentData_NmVersion_PrimitiveType Dcm_DataElement_DevelopmentData_NmVersionType;

#  define Rte_TypeDef_Dcm_DataElement_DevelopmentData_OperatingSystemVersionType
typedef Dcm_DataElement_DevelopmentData_OperatingSystemVersion_PrimitiveType Dcm_DataElement_DevelopmentData_OperatingSystemVersionType;

#  define Rte_TypeDef_Dcm_DataElement_DevelopmentData_TransportLayerVersionType
typedef Dcm_DataElement_DevelopmentData_TransportLayerVersion_PrimitiveType Dcm_DataElement_DevelopmentData_TransportLayerVersionType;

#  define Rte_TypeDef_Dcm_DataElement_Example_ReadWriteData_GlobalTimeType
typedef Dcm_DataElement_Example_ReadWriteData_GlobalTime_PrimitiveType Dcm_DataElement_Example_ReadWriteData_GlobalTimeType;

#  define Rte_TypeDef_Dcm_DataElement_Example_WriteOnlyDID_DID_DataObjectType
typedef Dcm_DataElement_Example_WriteOnlyDID_DID_DataObject_PrimitiveType Dcm_DataElement_Example_WriteOnlyDID_DID_DataObjectType;

#  define Rte_TypeDef_Dcm_DataElement_SampleIoControl_DID_DataType
typedef Dcm_DataElement_SampleIoControl_DID_Data_PrimitiveType Dcm_DataElement_SampleIoControl_DID_DataType;

#  define Rte_TypeDef_Dcm_DataElement_SerialNumber_SerialNumberType
typedef Dcm_DataElement_SerialNumber_SerialNumber_PrimitiveType Dcm_DataElement_SerialNumber_SerialNumberType;

# endif

#endif /* RTE_TYPE_H */

/**********************************************************************************************************************
 MISRA 2012 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_1039:  MISRA rule: Rule1.2
     Reason:     Same macro and function names are required to meet AUTOSAR spec.
     Risk:       No functional risk. Macro will be undefined before function definition.
     Prevention: Not required.

*/
