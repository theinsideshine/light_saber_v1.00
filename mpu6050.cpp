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
 
#include "mpu6050.h"

CMpu6050::CMpu6050()
{

}

void CMpu6050::init( void )
{

    //La I2C del arduino mino esta en A4 SDA y A5 SCL

    Wire.begin();                      //Inicializa la I2C
    Wire.beginTransmission(0b1101000); //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
    Wire.write(0x6B);                  //Accessing the register 6B - Power Management (Sec. 4.28)
    Wire.write(0b00000000); //Setting SLEEP register to 0. (Required; see Note on p. 9)
    Wire.endTransmission();  
    Wire.beginTransmission(0b1101000); //I2C address of the MPU
    Wire.write(0x1B); //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4) 
    Wire.write(0x00000000); //Setting the gyro to full scale +/- 250deg./s 
    Wire.endTransmission(); 
    Wire.beginTransmission(0b1101000); //I2C address of the MPU
    Wire.write(0x1C); //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5) 
    Wire.write(0b00000000); //Setting the accel to +/- 2g
    Wire.endTransmission(); 
}

/*
 *Lee el registro de la aceleracion y lo convierte a los valores fisicos. 
 * 
 */
void CMpu6050::get_accel(void) {
  
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x3B); //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Accel Registers (3B - 40)
  while(Wire.available() < 6);
  Accel.accelX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  Accel.accelY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  Accel.accelZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ

  Accel.gForceX = Accel.accelX / 16384.0;
  Accel.gForceY = Accel.accelY / 16384.0;
  Accel.gForceZ = Accel.accelZ / 16384.0;
 
  }


/*
 * Devuelve True si la aceleracion paso los limites del golpe
 * 
 */

bool CMpu6050::is_knock( void )
{
bool state = false; 

 if  ( 
          /*
        ( Accel.gForceX > 1.5 )  || ( Accel.gForceY > 1.5 )  || ( Accel.gForceZ > 0.5) ||
           
        ( Accel.gForceX < -1.5 ) || ( Accel.gForceY < -1.5 ) || ( Accel.gForceZ < -2.5 )*/

        ( Accel.gForceX > 1.2 )  || ( Accel.gForceY > 1.2 ) /* ||  ( Accel.gForceZ > 0) */ ||
           
        ( Accel.gForceX < -1.2 ) || ( Accel.gForceY < -1.2 ) /* || ( Accel.gForceZ < -2 ) */
         

        
     ){
         state = true ;
      }
  
  return state;

}


/*
 * Detecta el movimiento de la espada       
 */

bool CMpu6050::is_move ( void ) {
  
bool state = false; 
/*
  if   ( 
         ( ( Accel.gForceX > 0.5 )  && ( Accel.gForceX < 1) || ( Accel.gForceX > -1  )  && ( Accel.gForceX < -0.5 )  ) || 
  
         ( ( Accel.gForceZ > -0.5 )  && ( Accel.gForceZ < 0 )                                                         )  ||
  
         ( ( Accel.gForceY > 0.5 )  && ( Accel.gForceY < 1) || ( Accel.gForceY > -1  )  && ( Accel.gForceY < -0.5 )  )
       ){
            state = true ;
        }
  */
/*
  if   (  ( ( Accel.gForceY > 0.5 )  && ( Accel.gForceY < 1 ) ) || ( ( Accel.gForceY > -1  )  && ( Accel.gForceY < -0.5 )  )
       ){
            state = true ;
        }
*/
        if   (  ( ( Accel.gForceZ > -0.5 )  && ( Accel.gForceZ < 0 ) ) || ( ( Accel.gForceZ > -2 )  && ( Accel.gForceZ < -1.5)  )
       ){
            state = true ;
        }
  return  (  state );

}
