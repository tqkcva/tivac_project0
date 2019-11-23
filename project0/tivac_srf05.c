/*
 * tivac_srf05.c
 *
 *  Created on: Nov 23, 2019
 *      Author: tqkieu
 */

#include "tivac_srf05.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_nvic.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"

static unsigned long first_tick;
static unsigned long last_tick;
static unsigned long distance;

int srf05_init(void)
{
	//
	// Enable interrupts to the processor.
	//
	ROM_IntMasterEnable();

	//
	// Enable the interrupts.
	//
	ROM_IntEnable(INT_GPIOA);

	//
	// Set the interrupt priorities so they are all equal.
	//
	ROM_IntPrioritySet(INT_GPIOA, 0x00);
	ROM_IntPrioritySet(INT_GPIOB, 0x00);
	ROM_IntPrioritySet(INT_GPIOC, 0x00);

	//
	// Enable and wait for the port to be ready for access
	//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	do {}
	while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));

	// Configure GPIOA7 as interrupt source
	GPIODirModeSet(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_DIR_MODE_IN);
	GPIOIntTypeSet(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_BOTH_EDGES);
	GPIOIntClear(GPIO_PORTA_BASE, GPIO_INT_PIN_7);
	GPIOIntEnable(GPIO_PORTA_BASE, GPIO_INT_PIN_7);

	// Use flashed vetors or dynamic (SRAM) vetors?
}

int srf05_deinit(void)
{
	GPIOIntClear(GPIO_PORTA_BASE, GPIO_INT_PIN_7);
	GPIOIntDisable(GPIO_PORTA_BASE, GPIO_INT_PIN_7);
	GPIODirModeSet(GPIO_PORTA_BASE, GPIO_PIN_7, 0);
	GPIOIntTypeSet(GPIO_PORTA_BASE, GPIO_PIN_7, 0);

	//
	// Disable the interrupts.
	//
	ROM_IntDisable(INT_GPIOA);

	//
	// Disable interrupts to the processor.
	//
	ROM_IntMasterDisable();
}

//*****************************************************************************
//
// This is the handler for INT_GPIOA.  It simply saves the interrupt sequence
// number. This function should be registered in startup file
//
//*****************************************************************************
void
IntGPIOa(void)
{
	uint32_t int_status = 0;
	int_status = GPIOIntStatus(GPIO_PORTA_BASE, true);
	if (int_status | GPIO_INT_PIN_7) {
		// this interrupt source is correct for SRF05 sensor
		// Dertimine Raising/Failing edge

	}
}

int srf05_get_distance(void)
{

}
