/* Rain-Snow
By: Alice
Date: Avril 2015
Light up a random Led in Blue or White and fade out.
*/

// include FastLED library.
#include "FastLED.h"
 
// Fixed definitions
#define DATA_PIN 6                                        
#define CLOCK_PIN 11                                            
#define COLOR_ORDER RGB                                      
#define LED_TYPE NEOPIXEL                                      
#define NUM_LEDS  30                                          

// Initialize changeable global variables.
// Overall brightness definition (0-255).
uint8_t max_bright = 255;                                 
// Initialize our LED array.
CRGB leds[NUM_LEDS];                                  


// The following variables can be changed.
// The higher the number, lowers the chance for a pixel to light up.
int     ranamount =  50;                                      
// Standard delay value in milliseconds.
uint8_t thisdelay =  50;                                      
// Fade rate
uint8_t   fadeval = 224;
// number that helps to switch between Blue and White
int n = 0;


void setup() {
  // Power-up safety delay or something like that.
  delay(1000);                                                
  Serial.begin(57600);

  // Use this for WS2801 Leds
  //  LEDS.addLeds<LED_TYPE, DATA_PIN, CLOCK_PIN, COLOR_ORDER>(leds, NUM_LEDS);

  // Use this for NEOPIXEL
  LEDS.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS);  
  
  // FastLED power management set at 5V, 500mA
  set_max_power_in_volts_and_milliamps(5, 500);
  
  // Set brightness of Leds 
  FastLED.setBrightness(max_bright);
  
} // end setup()


void loop() {
  // Simple call to the routine.
  twinkle();
  
  // Power managed display is better than FastLED.show()  
  show_at_max_brightness_for_power();
  
  // Power managed delay.  
  delay_at_max_brightness_for_power(thisdelay*2.5);
  
} // end loop()


void twinkle() {
  // Make sure we're at least utilizing ALL the LED's.
  if (ranamount >NUM_LEDS) ranamount = NUM_LEDS;
  
  // Set random value  
  int idex = random16(0, ranamount);
  
  // Light up a random Led in Blue or White (Blue if Pair, White if not)
  if (idex < NUM_LEDS && n % 2 == 0) {                                    
      leds[idex] = CRGB::Blue;
      n++;
  } else {
      leds[idex] = CRGB::White;
      n++;
  }
    
  // Go through the array and reduce each RGB value by a percentage.
  for (int i = 0; i <NUM_LEDS; i++) leds[i].nscale8(fadeval); 
  
} // end twinkle()
