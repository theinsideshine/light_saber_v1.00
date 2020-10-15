/**
  * File: Simple electronic laser sword
  * An accelerometer sensor reads the movement of the sword,
  * depending on the movements of the sword, it plays sounds and controls a led
  *
  * The sword is turned on and off with a button.

  * It has five states:
  *
  * Sword burning
  * Sword without movement,
  * Sword moving,
  * Sword strike
  * Sword fading
 *        
 *        
 *        
 * 
 *         
 * - Compiler:           Arduino 1.8.13
 * - Supported devices:  Arduino pro or pro mini
 *
 * \author               PT: educacion.ta@gmail.com
 *                       JS: juanschiavoni@gmail.com 
 *                       
* Date:  09-09-2020
 *
 *      The inside shine.
 */

#include "led.h"
#include "timer.h"
#include "button.h"

#include <PCM.h>   //Audio is output from pin 11.
#include "sound.h"
#include "mpu6050.h"


#define ST_INIT                    0       // Initialize the program.
#define ST_WAIT_ON                 1       // Wait for the saber to ignite.
#define ST_ON                      2       // Light the sword.
#define ST_IDLE                    3       // Sword on.
#define ST_KNOCK                   4       // The sword struck.
#define ST_MOVE                    5       // The sword moved.  
#define ST_OFF                     6       // Sword off.



#define N_TILT_SABER                    8       // Times the LED is turned on and off in ST_KNOCK.
#define T_TILT_SABER                    100     // LED togle time in milliseconds in ST_KNOCK.
#define N_MOVE_SOUND2                   2       // Every N times the motion sound 2 is played. Not implemented.

#define T_SOUND_IDLE                    1000    // Idle sound repetition time.
#define T_SOUND_KNOCK                   500     // Knock sound time.
#define T_SOUND_MOVE                    800    // Turn sound time.

CButton Button;
CLed Led;
CMpu6050 Mpu6050;


/*
 *  Initialize the sword peripherals.
 */
 
void setup()
{
    
    Led.init();
    Button.init();
    Mpu6050.init();
    
    Led.tgl() ;         // Reset signal for debugging.
    delay(500); 
    Led.tgl() ;

 }



/*
 * Control loop of the lightsaber.
 */
 
void loop()
{
static CTimer   Timer;
static CTimer   Timer_led;
static CTimer   Timer_idle;
static CTimer   Timer_knock;
static CTimer   Timer_move;

static uint8_t  st_loop = ST_INIT;
static uint8_t  count_tilt = N_TILT_SABER ;
static uint8_t  count_move = N_MOVE_SOUND2;


   
    Button.debounce();

   
    switch( st_loop ) {
        
               
        case ST_INIT:
            
            st_loop = ST_WAIT_ON;
                        
        break;

        case ST_WAIT_ON:
        
        // Pressing the button turns on the saber
        // and flashes the led.
        
        if ( Button.is_pressed() ) {
          
             // In this state, the led blinks
             // a timer is turned on that in ST_LOOP_ON is going to kick T_TILT_SABER times. 
             
            st_loop = ST_ON;
            startPlayback(snd_out_saber, sizeof(snd_out_saber)); // Sound of saber coming out.
            Timer_led.start();
            }
                  
        break;


        case ST_ON:
        
        // Toggle the N_TILT_SABER led times and go to idle state.
        
        if( Timer_led.expired( T_TILT_SABER ) ) {
                  
             Led.tgl() ;
             count_tilt--;
             Timer_led.start();
            }

        // When the TILT counter expires, it goes to IDLE.
         
        if ( !count_tilt )  {

            Led.on();          // Turn on the light of the sword.
            Timer_idle.start();
            startPlayback(snd_idle_saber, sizeof(snd_idle_saber)); // Idle saber sound.
            st_loop = ST_IDLE;           
           }
                   
        break;

        case ST_IDLE:
        
        // Every time the timer expires it repeats the sound.
        
        if( Timer_idle.expired( T_SOUND_IDLE ) ) {
          
           startPlayback(snd_idle_saber, sizeof(snd_idle_saber)); // Idle saber sound.
           Timer_idle.start();
          }

        Mpu6050.get_accel();     // Read the acceleration.
       
        
        
        if ( Mpu6050.is_knock() ) {
            startPlayback(snd_knock_saber, sizeof(snd_knock_saber)); // Sound of saber strike.
            Timer_led.start();
            count_tilt = N_TILT_SABER;
            st_loop = ST_KNOCK;
           
           }else if ( Mpu6050.is_move() ) {
                     startPlayback(snd_move_2_saber, sizeof(snd_move_2_saber)); // Sound of sword moving 2
                     Timer_move.start();
                     st_loop = ST_MOVE;
                    } 

        if ( Button.is_pressed() ) {
             
             st_loop = ST_OFF;
             startPlayback(snd_in_saber, sizeof(snd_in_saber)); // Sound of saber of saber saving.
            }
            
        break;

         case ST_KNOCK:
         
        // Toggle the led N_TILT_SABER times and it goes to the IDLE state. 
        
        if( Timer_led.expired( T_TILT_SABER ) ) {
                  
               Led.tgl() ;
               count_tilt--;
               Timer_led.start();
              }
        
        if ( !count_tilt )  {

           Led.on();           
           Timer_idle.start();
           startPlayback(snd_idle_saber, sizeof(snd_idle_saber)); // Idle saber sound.
           st_loop = ST_IDLE;
          }

        
        break;

        case ST_MOVE:
          if( Timer_move.expired( T_SOUND_MOVE ) ) {
           startPlayback(snd_idle_saber, sizeof(snd_idle_saber)); // Idle saber sound.
           Timer_move.start();
           st_loop = ST_IDLE;
          }
        
         break;

       case ST_OFF:
       
                 count_tilt = N_TILT_SABER;
                 Led.off() ;
                 st_loop = ST_WAIT_ON;
                     
         break;
       
        default:
          st_loop = ST_INIT;
        
    }
}
