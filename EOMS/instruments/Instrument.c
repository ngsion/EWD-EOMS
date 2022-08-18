//==============================================================================
//
// Title:		Instrument.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-08-16 at 14:05:04 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <ansi_c.h>
#include "Instrument.h"
#include "stddef.h"
#include "visa.h"
#include <string.h>
#include "../logger/log.h"
//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions
int Open(struct Instrument *pInstr)
{
	if (NULL == pInstr)
	{
		return -1;
	}

	ViStatus status = viOpen(pInstr->resouceMgr, pInstr->address, VI_NULL, VI_NULL, &pInstr->session);

	if (status < VI_SUCCESS)
	{
		log_error("Cannot open a session to the device %s.\n", pInstr->address);
		return -1;
	}
	else
	{
		log_info("instrument %s is open", pInstr->address);
		pInstr->status = Instrument_Status_Open;
	}

	if (Instrument_Type_USB == pInstr->type)
	{
		
	}
	else if (Instrument_Type_ASRL != pInstr->type)
	{
		/*
		 * At this point we now have a session open to the serial instrument.
		 * Now we need to configure the serial port:
		 */
		/* Set the timeout to 5 seconds (10000 milliseconds). */
		status = viSetAttribute(pInstr->session, VI_ATTR_TMO_VALUE, 10000);

		/* Set the baud rate to 38400 (default is 9600). */
		status = viSetAttribute(pInstr->session, VI_ATTR_ASRL_BAUD, 38400);
	
		/* Set the number of data bits contained in each frame (from 5 to 8).
		 * The data bits for  each frame are located in the low-order bits of
		 * every byte stored in memory.
		 */
		status = viSetAttribute(pInstr->session, VI_ATTR_ASRL_DATA_BITS, 8);

		/* Specify parity. Options:
		 * VI_ASRL_PAR_NONE  - No parity bit exists,
		 * VI_ASRL_PAR_ODD   - Odd parity should be used,
		 * VI_ASRL_PAR_EVEN  - Even parity should be used,
		 * VI_ASRL_PAR_MARK  - Parity bit exists and is always 1,
		 * VI_ASRL_PAR_SPACE - Parity bit exists and is always 0.
		 */
		status = viSetAttribute(pInstr->session, VI_ATTR_ASRL_PARITY, VI_ASRL_PAR_NONE);

		/* Specify stop bit. Options:
		 * VI_ASRL_STOP_ONE   - 1 stop bit is used per frame,
		 * VI_ASRL_STOP_ONE_5 - 1.5 stop bits are used per frame,
		 * VI_ASRL_STOP_TWO   - 2 stop bits are used per frame.
		 */
		status = viSetAttribute(pInstr->session, VI_ATTR_ASRL_STOP_BITS, VI_ASRL_STOP_ONE);

		/* Specify that the read operation should terminate when a termination
		 * character is received.
		 */
		status = viSetAttribute(pInstr->session, VI_ATTR_TERMCHAR_EN, VI_TRUE);

		/* Set the termination character to 0xA , \n
		 */
		status = viSetAttribute(pInstr->session, VI_ATTR_TERMCHAR, 0xA);
		
	}
	else
	{

		status = viSetAttribute(pInstr->session, VI_ATTR_TMO_VALUE, 10000);

		status = viSetAttribute(pInstr->session, VI_ATTR_ASRL_BAUD, 9600);

		status = viSetAttribute(pInstr->session, VI_ATTR_ASRL_DATA_BITS, 8);

		status = viSetAttribute(pInstr->session, VI_ATTR_ASRL_PARITY, VI_ASRL_PAR_NONE);

		status = viSetAttribute(pInstr->session, VI_ATTR_ASRL_STOP_BITS, VI_ASRL_STOP_ONE);

		status = viSetAttribute(pInstr->session, VI_ATTR_TERMCHAR_EN, VI_TRUE);

		status = viSetAttribute(pInstr->session, VI_ATTR_TERMCHAR, 0x0D);
	
	}

	return 0;
}

int QueryID(struct Instrument *pInstr)
{
	if (NULL == pInstr)
	{
		return -1;
	}

	unsigned char buffer[INSTRUMENT_ID_LENGTH];
	memset(buffer, 0, INSTRUMENT_ID_LENGTH);
	char stringinput[64];
	ViUInt32 retCount;
	ViUInt32 writeCount;
	ViStatus status;

	/*
	 * At this point we now have a session open to the USB TMC instrument.
	 * We will now use the viWrite function to send the device the string "*IDN?\n",
	 * asking for the device's identification.
	 */
	strcpy(stringinput, "*IDN?\n");
	status = viWrite(pInstr->session, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);
	if (status < VI_SUCCESS)
	{
		log_error("Error writing to the device %s.\n", pInstr->address);

		return -1;
	}

	/*
	 * Now we will attempt to read back a response from the device to
	 * the identification query that was sent.  We will use the viRead
	 * function to acquire the data.  We will try to read back 100 bytes.
	 * This function will stop reading if it finds the termination character
	 * before it reads 100 bytes.
	 * After the data has been read the response is displayed.
	 */
	status = viRead(pInstr->session, buffer, INSTRUMENT_ID_LENGTH, &retCount);
	if (status < VI_SUCCESS)
	{
		log_error("Error reading a response from the device %s.\n", pInstr->address);
	}
	else
	{
		log_info("instrument %s id is: %*s\n", pInstr->address, retCount, buffer);
		memcpy(pInstr->id, buffer, retCount);
	}

	return 0;
}

int Close(struct Instrument *pInstr)
{
	if (NULL == pInstr)
	{
		return -1;
	}

	ViStatus status = viClose(pInstr->session);
	if (VI_SUCCESS == status)
	{
		pInstr->status = Instrument_Status_Connected;
	}
	return 0;
}

Instrument *InstrumentAllocInit()
{
	Instrument *pInstr = (Instrument *)malloc(sizeof(Instrument));
	if (NULL == pInstr)
	{
		log_fatal("Error creating an Instrument.\n");
	}
	else
	{
		pInstr->status = Instrument_Status_Disconnected;
		pInstr->type = Instrument_Type_UNKNOWN;
		pInstr->session = 0;
		pInstr->resouceMgr = 0;
		memset(pInstr->address, 0, INSTRUMENT_ADDRESS_LENGTH);
		memset(pInstr->id, 0, INSTRUMENT_ID_LENGTH);
		pInstr->Open = Open;
		pInstr->QueryID = QueryID;
		pInstr->Close = Close;
	}
	return pInstr;
}

void InstrumentDelloc(Instrument *pInstr)
{
	if (NULL != pInstr)
	{
		free(pInstr);
		pInstr = NULL;
	}
}
