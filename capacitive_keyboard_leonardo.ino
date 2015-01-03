#include <CapacitiveSensor.h>

/*
 * Based on the
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Extended by Tyler Smith to send keyboard presses when the capacitive sensors are touched.
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */

/*
 * Note: if you enabled debugging with the serial monitor, responsiveness of the keyboard and mouse suffers. This is 
 * particularly noticeable when you try to hold down a single key and have it repeat, whether or not the ctrl key is 
 * held!
*/

// #define DEBUG
#define THRESH 300
boolean CTRL_ON = false ;
byte LED = 12;
CapacitiveSensor   cs_7_2 = CapacitiveSensor(7,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_7_10 = CapacitiveSensor(7,10);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
// CapacitiveSensor   cs_4_8 = CapacitiveSensor(4,8);        // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil

void setup()                    
{
//   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);
   pinMode(LED, OUTPUT) ;
   Keyboard.begin();
}

void loop()                    
{
    long total1 =  cs_7_2.capacitiveSensor(30);
    long total2 =  cs_7_10.capacitiveSensor(30);
  
#ifdef DEBUG 
    long start = millis();
    // long total3 =  cs_4_8.capacitiveSensor(30);

      Serial.print(millis() - start);        // check on performance in milliseconds
      Serial.print("\t");                    // tab character for debug windown spacing

      Serial.print(total1);                  // print sensor output 1
      Serial.print("\t");
      Serial.print(total2);                  // print sensor output 2
      // Serial.print("\t");
      // Serial.println(total3);                // print sensor output 3
      Serial.print("\n") ;
#endif

// NOTE: only send a keyboard message if the state of CTRL_ON changes!
  if(! CTRL_ON && (total1 > THRESH || total2 > THRESH)){
//    if((total1 > THRESH)){
    digitalWrite(LED, HIGH) ;
    Keyboard.press(KEY_LEFT_CTRL);
    CTRL_ON = true;
//    Serial.println("light") ;
  } else if (CTRL_ON && total1 <= THRESH && total2 <= THRESH) {
    digitalWrite(LED, LOW) ;
    Keyboard.release(KEY_LEFT_CTRL);
    CTRL_ON = false ;
  }

//    delay(10);                             // arbitrary delay to limit data to serial port 
    
}
