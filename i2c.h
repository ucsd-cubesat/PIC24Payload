/* 
 * File:   i2c.h
 * Author: Triton³
 *
 * Created on April 30, 2019, 6:04 PM
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Configures I2C with the proper bitrate
 */
void i2c_init();

/*
 * Closes the I2C session.
 */
void i2c_close();

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

