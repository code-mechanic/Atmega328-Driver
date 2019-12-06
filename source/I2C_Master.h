/* 
 * File:   i2c_master.h
 * Author: Mohan
 *
 * Created on November 22, 2019, 10:16 AM
 */

/*HEADER GUARD----------------------------------------------------------------*/

#ifndef I2C_MASTER_H
#define	I2C_MASTER_H

/*INCLUDE LIBRARY FILES-------------------------------------------------------*/

#include"stdint.h"

/*MACROs----------------------------------------------------------------------*/

#ifdef	__cplusplus
extern "C" {
#endif
    
#define I2C_READ 0x01
#define I2C_WRITE 0x00
 
/*PUBLIC FUNCTION PROTYPING---------------------------------------------------*/
    
void I2C_Init(void);
void I2C_Stop(void);
void I2C_Start(char slave_address);
void I2C_WriteByte(uint8_t data);
uint8_t I2C_ReadByte_ACK(void);
uint8_t I2C_ReadByte_NACK(void);
void I2C_WriteBytes(uint8_t address, uint8_t* data, uint16_t length);
uint8_t I2C_ReadBytes(uint8_t address, uint8_t* data, uint16_t length);
void  I2C_WriteReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);
uint8_t I2C_ReadReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_MASTER_H */

