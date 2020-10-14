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
 *  Definicion de la zonas de moviento
 *  
 *  
 */

#define MAX_P_XY         1.2                        //Valor maximo positivo del eje x e y
#define MAX_N_XY        -1.2                        //Valor maximo negativo del eje x e y


#define Z1_MAX_Z         0                         //Valor maximo del eje Z de la zona 1
#define Z1_MIN_Z         -0.5                      //Valor minimo del eje Z de la zona 1 

#define Z2_MAX_Z         -1.5                     //Valor maximo del eje Z de la zona 2
#define Z2_MIN_Z         -2                       //Valor minimo del eje Z de la zona 2



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
