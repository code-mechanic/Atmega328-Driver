/*
 * File:   i2c_main.c
 * Author: Mohan
 *
 * Created on November 22, 2019, 10:24 AM
 */

#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>
#include "I2C_Master.h"
int main()
{
  I2C_Init();
  while(1)
  {
    I2C_WriteBytes(0x20,"ABCD",4);
    _delay_ms(500);
  }
  return 0;
}
