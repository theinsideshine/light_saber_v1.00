/** - File: Class that controls  button
  * - Compiler:           Arduino 1.8.13
  * - Supported devices:  Arduino pro or pro mini

 *
 * \author               
 *                       JS: juanschiavoni@gmail.com 
 *                       
* Date:  09-09-2020
 *
 *      The inside shine.
 */
 
#include "button.h"

CButton::CButton()
{

}

void CButton::init( void )
{
    pinMode( PIN_BUTTON, INPUT_PULLUP );
}

// Reset the click event to avoid false shots.
bool CButton::is_pressed( void )
{
bool ret_val = state;

    state = false;

    return ret_val;
}

  // Returns true when the operator pressed the programming button.
  // Apply an anti-bounce mechanism.
void CButton::debounce( void )
{
    state = (digitalRead( PIN_BUTTON ) == LOW);
    
  // After the button is pressed, it must remain 500 mS released.
    if( state ) {
        if( !Timer.expired( 500 ) ){
          state = false;
        }

        Timer.start();
    }
}
