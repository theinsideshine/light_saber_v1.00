/**
 * File: Class that controls the MPU6050 acceletrometer
 *       of the sword 

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
 
#include "mpu6050.h"

CMpu6050::CMpu6050()
{

}

void CMpu6050::init( void )
{

    //The I2C of the arduino mino is in A4 SDA and A5 SCL

    Wire.begin();                      //Inicializa la I2C.
    Wire.beginTransmission(0b1101000); //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
    Wire.write(0x6B);                  //Accessing the register 6B - Power Management (Sec. 4.28)
    Wire.write(0b00000000);            //Setting SLEEP register to 0. (Required; see Note on p. 9)
    Wire.endTransmission();  
    Wire.beginTransmission(0b1101000); //I2C address of the MPU
    Wire.write(0x1B);                  //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4) 
    Wire.write(0x00000000);            //Setting the gyro to full scale +/- 250deg./s 
    Wire.endTransmission(); 
    Wire.beginTransmission(0b1101000); //I2C address of the MPU
    Wire.write(0x1C);                 //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5) 
    Wire.write(0b00000000);          //Setting the accel to +/- 2g
    Wire.endTransmission(); 
    
}

/*
 * Read the acceleration log and convert it to physical values.
 * 
 */
void CMpu6050::get_accel(void) {
  
  Wire.beginTransmission(0b1101000);          //I2C address of the MPU
  Wire.write(0x3B);                           //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6);             //Request Accel Registers (3B - 40)
  while(Wire.available() < 6);
  Accel.accelX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  Accel.accelY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  Accel.accelZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ

  Accel.gForceX = Accel.accelX / 16384.0;
  Accel.gForceY = Accel.accelY / 16384.0;
  Accel.gForceZ = Accel.accelZ / 16384.0;
 }


/*
 * Returns True if the acceleration passed the stroke limits.
  * As a first approximation, 2 acceleration zones were defined to validate the movement, one on the Y axis and the other on the X axis.
 */

bool CMpu6050::is_knock( void )
{
bool state = false; 

 if  (         
        ( Accel.gForceX > MAX_P_XY )  || ( Accel.gForceY > MAX_P_XY )  ||
           
        ( Accel.gForceX < MAX_N_XY ) || ( Accel.gForceY < MAX_N_XY ) 
        
     ){
         state = true ;
      }
  
  return state;

}

/*
  * Detects the movement of the sword
  * so that it is not confused with the movement zones, the z axis is used to detect the crash
  * Two acceleration zones were defined for the z axis
  */

bool CMpu6050::is_move ( void ) {
  
bool state = false; 

       if   (  ( ( Accel.gForceZ > Z1_MIN_Z )  && ( Accel.gForceZ < Z1_MAX_Z ) ) || ( ( Accel.gForceZ > Z2_MIN_Z )  && ( Accel.gForceZ < Z2_MAX_Z )  )
       ){
            state = true ;
        }
  return  (  state );

}
