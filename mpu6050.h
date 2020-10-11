/**
 * File:   Clase que controla el boton aceletrometro MPU6050
 *         de la espada laser
 * - Compiler:           Arduino 1.8.13
 * - Supported devices:  mini
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

//La I2C del arduino mino esta en A4 SDA y A5 SCL

/*
 *  X es la medida longitudinal del ROLL
 *  
 *  Z es la medida longitudinal del YAW 
 */


/*
 * Estrutura de datos de aceleracion  
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
      ACCEL Accel;                  // Estrutura de datos de aceleracion    
      
};

#endif // MPU6050_H
