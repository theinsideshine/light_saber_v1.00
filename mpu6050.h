/**
  * File: Class that controls the MPU6050 acceletrometer
 *       of the sword
 *       
 * - Compiler:           Arduino 1.8.13
 * - Supported devices:  Arduino pro or pro mini
 *
 * \author               PT: educacion.ta@gmail.com
 *                        
 *                       
* Date:  21-09-2020
 *
 *      The inside shine.
 */
 
#ifndef MPU6050_H
#define MPU6050_H

#include "Arduino.h"
#include <Wire.h>

 //The I2C of the arduino mino is in A4 SDA and A5 SCL

/*
 *  Definition of movement zones
 *  
 *  
 */

#define MAX_P_XY         1.2                        // Maximum positive value of the x and y axis
#define MAX_N_XY        -1.2                        // Maximum negative value of the x and y axis


#define Z1_MAX_Z         0                         // Maximum value of the Z axis of zone 1
#define Z1_MIN_Z         -0.5                      // Minimum value of the Z axis of zone 1

#define Z2_MAX_Z         -1.5                     // Maximum value of the Z axis of zone 2
#define Z2_MIN_Z         -2                       // Minimum value of the Z axis of zone 2

/* 
 * Acceleration data structure * 
 * 
  */
  
typedef struct tag_ACCEL{
  long  accelX;
  long  accelY;
  long  accelZ;
  float gForceX; 
  float gForceY; 
  float gForceZ;
} ACCEL;

class CMpu6050
{
  public:
    CMpu6050();
    void init ( void );
    void get_accel ( void );
    bool is_knock ( void );
    bool is_move ( void );
    
    
  private:
      ACCEL Accel;                  // Acceleration data structure   
      
};

#endif // MPU6050_H
