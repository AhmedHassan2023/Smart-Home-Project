/*
 * main.c
 *
 *  Created on: ???/???/????
 *      Author: NAN
 */
#include "STD_TYPES.h"

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "SPI_interface.h"
#include "GIE_interface.h"

#include "SERVO_interface.h"
#include "SSD_interface.h"
#include "BUZZER_interface.h"

#include <util\delay.h>



void main(void)
{
	PORT_voidInit();
	SPI_voidInit();
	SERVO_voidInit();
	BUZZER_voidInit();

	GIE_voidEnable();

	u8 Local_u8DataReceive;
	SSD_t SSD1={DIO_u8PORTA,DIO_u8PORTC,DIO_u8PIN7,SSD_u8ComCathode};






	while(1)
	{


		SPI_u8TransceiveSynch(&Local_u8DataReceive,5);
		_delay_ms(10);

		/*Wrong Pass diplay on SSD Number of Trails left*/
		if(Local_u8DataReceive == 3)
		{
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_LOW);
			SSD_voidSetNumber(&SSD1,2);
		}
		else if(Local_u8DataReceive == 2)
		{
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_LOW);
			SSD_voidSetNumber(&SSD1,1);
		}
		else if(Local_u8DataReceive == 1)
		{
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_LOW);
			SSD_voidSetNumber(&SSD1,0);
		}
		else
		{
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH);
		}


		SPI_u8TransceiveSynch(&Local_u8DataReceive,5);
		_delay_ms(10);


		/*Open Door by Setting Servo 180 degree*/
		if(Local_u8DataReceive == 5)
		{
			SERVO_voidSetAngle(180);
		}


		SPI_u8TransceiveSynch(&Local_u8DataReceive,6);
		_delay_ms(10);

		/*Fan Control*/
		if(Local_u8DataReceive == 9)
		{
			/*Motor ON*/
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8PIN_HIGH);
		}

		//			SPI_u8TransceiveSynch(&Local_u8DataReceive,5);
		//			_delay_ms(10);

		else if(Local_u8DataReceive == 8)
		{
			/*Motor OFF*/
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8PIN_LOW);
		}

		SPI_u8TransceiveSynch(&Local_u8DataReceive,3);
		_delay_ms(10);
		/*Music Control*/
		if(Local_u8DataReceive == 10)
		{
			BUZZER_voidSetSoundValue(10);
			_delay_ms(200);
			BUZZER_voidSetSoundValue(20);
			_delay_ms(200);
			BUZZER_voidSetSoundValue(30);
			_delay_ms(200);
			BUZZER_voidSetSoundValue(40);
			_delay_ms(200);
			BUZZER_voidSetSoundValue(45);
			_delay_ms(200);
			BUZZER_voidSetSoundValue(25);
			_delay_ms(200);
			BUZZER_voidSetSoundValue(35);
			_delay_ms(200);
			BUZZER_voidSetSoundValue(50);
			_delay_ms(200);
			BUZZER_voidSetSoundValue(60);
			_delay_ms(200);
			BUZZER_voidSetSoundValue(80);
			_delay_ms(200);
		}
		else if(Local_u8DataReceive == 11)
		{
			BUZZER_voidSetSoundValue(0);
		}

	}

}




