/* 
 * File:   i2c_master.c
 * Author: Mohan
 *
 * Created on November 22, 2019, 10:20 AM
 */

/*INCLUDE LIBRARY FILES-------------------------------------------------------*/

#include <avr/io.h>
#include <util/twi.h>
#include "I2C_Master.h"

/*MACROs----------------------------------------------------------------------*/

#ifndef  F_CPU
#define F_CPU 16000000UL
#endif
#define F_SCL 100000UL // SCL frequency
#define Prescaler 1
#define TWBR_val ((((F_CPU / F_SCL) / Prescaler) - 16 ) / 2)

/*PRIVATE FUNCTION DEFINTIONS-------------------------------------------------*/

/*I2C_Init function is used to set data rate for I2C BUS*/
void
I2C_Init(void)
{
  TWBR = 0x00;
  TWBR = (uint8_t)TWBR_val;
}

/*I2C_Stop function will set STOP condition*/
void
I2C_Stop(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

/*I2C_Start function is used for set start condition and send slave address with 
  read or write mode
  For example,
              Write Mode: I2C_Start((slave_address<<1)|I2C_WRITE)
              Read Mode : I2C_Start((slave_address<<1)|I2C_READ)*/
void
I2C_Start(char slave_address)
{
    TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
    while(!(TWCR&(1<<TWINT)));
    TWDR = slave_address;
    TWCR = (1<<TWEN)|(1<<TWINT);
    while(!(TWCR&(1<<TWINT)));
}

/*I2C_WriteByte function sends only one byte of data
  if you are use this function then there is need for separate START function*/   
void
I2C_WriteByte(uint8_t data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while( !(TWCR & (1<<TWINT)) );
}

/*I2C_ReadByte_ACK functions is used to receive one byte of data from slave and 
  send ACK bit to salve */
uint8_t
I2C_ReadByte_ACK(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA); 
	while( !(TWCR & (1<<TWINT)) );
	return TWDR;
}

/*I2C_ReadByte_NACK functions is used to receive one byte of data from slave and 
  send NACK bit to salve */
uint8_t
I2C_ReadByte_NACK(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	while( !(TWCR & (1<<TWINT)) );
	return TWDR;
}

/*I2C_WriteBytes function sends multi bytes of data
  if you are use this function then no need for separate START function*/ 
void
I2C_WriteBytes(uint8_t address, uint8_t* data, uint16_t length)
{
  I2C_Start( address | I2C_WRITE);
  for (uint16_t i = 0; i < length; i++)
	{
		I2C_WriteByte(data[i]);
	}
	I2C_Stop();
}

/*I2C_ReadBytes function receives multi byte of data
 if you are use this function then no need for separate START function*/ 
uint8_t
I2C_ReadBytes(uint8_t address, uint8_t* data, uint16_t length)
{
	I2C_Start(address | I2C_READ);
	for (uint16_t i = 0; i < (length-1); i++)
	{
		data[i] = I2C_ReadByte_ACK();
	}
	data[(length-1)] = I2C_ReadByte_NACK();
	I2C_Stop();
	return 0;
}

void
I2C_WriteReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length)
{
  I2C_Start((devaddr<<1) | I2C_WRITE);
	I2C_WriteByte(regaddr);
	for (uint16_t i = 0; i < length; i++)
	{
		I2C_WriteByte(data[i]);
	}
	I2C_Stop();
}

uint8_t
I2C_ReadReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length)
{
	I2C_Start((devaddr<<1) | I2C_WRITE);
	I2C_WriteByte(regaddr);
	I2C_Start((devaddr<<1) | I2C_READ);
	for (uint16_t i = 0; i < (length-1); i++)
	{
		data[i] = I2C_ReadByte_ACK();
	}
	data[(length-1)] = I2C_ReadByte_NACK();
	I2C_Stop();
	return 0;
}