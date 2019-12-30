 /************************************************ */
 /*  Educational tutorial for Arduino in robotics  */
 /*  File: srf08.h                                 */
 /*  Author: Jan Beran                             */
 /*  Date: autumn 2019                             */
 /* This file is a part of authors bachelor thesis */
 /*                                                */
 /* This file contains macros and function         */
 /* prototypes for controlling srf-08 ligh         */
 /* and distance sensor.                           */
 /**************************************************/

//TODO prace se svetelnym senzorem
 #ifndef _SRF08_H
 #define _SRF08_H       1

/*
* srf-08 I2C address
*/
#define SRF08_ADDRESS 0x70

/*
* Macros for setting measurement unit 
*/
#define CMD_INCH 0x50
#define CMD_CM 0x51
#define CMD_MS 0x52
 
 /*
 * Macros for accessing registers
 */ 
#define REG_CMD 0x00
#define REG_LIGH 0x01


/*
* Function sets measurement by writing into REG_CMD the desired unit.
* After setting measurement, there should be at least 65 ms waiting time
* to execute the measurement. 
*/
void set_measurement(byte unit);


/*
* Function gets distance from srf-08 register.
* Return value:  distance in desired unit set by set_measurement() function 
* or TODO -1 if value is not available
*/
int get_distance();


/*
* Function gets the light intensity from SRF-08 register.
* Return value: light_intensity as a number form 0 to 255.
* Note: set_measurement() must be called before this function is called! 
*/
byte get_light_intensity();

#endif