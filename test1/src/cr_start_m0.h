//*****************************************************************************
//
// cr_start_m0.h
//
// Provides function for CM4 'master' CPU in an NXP LPC43xx MCU to release
// CM0 'slave' CPUs from reset and begin executing.
//
// Version : 130731
//
//*****************************************************************************
//
// Copyright(C) NXP Semiconductors, 2013, 2020
// All rights reserved.
//
// NXP Confidential. This software is owned or controlled by NXP and may only be
// used strictly in accordance with the applicable license terms.
//
// By expressly accepting such terms or by downloading, installing, activating
// and/or otherwise using the software, you are agreeing that you have read, and
// that you agree to comply with and are bound by, such license terms.
// 
// If you do not agree to be bound by the applicable license terms, then you may not
// retain, install, activate or otherwise use the software.
//*****************************************************************************

#ifndef CR_START_M0_H_
#define CR_START_M0_H_

#define SLAVE_M0APP 0
#define SLAVE_M0SUB 1

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

extern uint8_t __core_m0app_START__;
extern uint8_t __core_m0sub_START__;

/*******************************************************************
 * Function to start required CM0 slave cpu executing
 *******************************************************************/
void cr_start_m0(uint32_t slavenum, uint8_t *CM0image_start);

#ifdef __cplusplus
}
#endif

#endif /* CR_START_M0_H_ */
