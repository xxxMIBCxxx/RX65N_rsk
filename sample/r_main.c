/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer *
* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name	   : r_main.c
* Version      : 1.00
* Description  : This module solves all the world's problems
******************************************************************************/
/*****************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 20.09.2012 1.00     First Release
******************************************************************************/


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include <string.h>
#include "r_adpcm.h"
#include "r_s2_driver.h"
#include "r_s2_sample.h"
#include "platform.h"

/******************************************************************************
Exported global variables (to be accessed by other files)
******************************************************************************/
uint8_t R_StartSelect(void);
mw_version_t s2_version;

/******************************************************************************
* Function Name: main
* Description  : The main loop
* Arguments    : none
* Return Value : none
******************************************************************************/
void main(void)
{
	/* Start user code. Do not edit comment generated here */
	uint8_t mode;
	uint8_t bFlag = 0;

	PORTA.PDR.BIT.B1 = 1;
//	PORTA.PDR.BIT.B2 = 0;
//	PORTA.PCR.BIT.B2 = 1;

	memcpy(&s2_version, &R_s2_version, sizeof(mw_version_t));
	LED0 = LED_OFF;

	while (1U)
	{
		//if (PORTA.PIDR.BIT.B2 == 0)
		if (bFlag == 1)
		{
			/* Decode Function  */
			PORTA.PODR.BIT.B1 = 1;
			R_decode_main();			/* decode main function */
			PORTA.PODR.BIT.B1 = 0;
		}
	}
	/* End user code. Do not edit comment generated here */
}

/*""FUNC COMMENT""*********************************************************************
* Function Name	: R_StartSelect
* Include		: r_s2_driver.h
* Declaration	: uint16_t R_StartSelect( void )
* Description	: Start Select function encode or decode.
* Arguments     : none
* Return value	: uint8_t: function code
				NO_SELECT	: No pushed switch
				SELECT_ENCODE	: encode select
				SELECT_DECODE	: decode select
*""FUNC COMMENT END""*****************************************************************/
uint8_t R_StartSelect(void)
{
	uint8_t ret;
	uint8_t switch_dat;
	static uint8_t switch_dat_old = 0xff;
	static uint8_t match_count = 0;

	ret = NO_SELECT;

	switch_dat = ((uint8_t)SW1);
	if (switch_dat != switch_dat_old)
	{
		switch_dat_old = switch_dat;
		match_count = 0;
	}
	else
	{
		if (match_count < 5)
		{
			if (++match_count == 5)
			{
				if ((switch_dat & 0x01) == 0)		/* encode */
				{
					ret = SELECT_ENCODE;
				}
			}
		}
	}
	return ret;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
