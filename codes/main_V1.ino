/*
 * Auth: TIMOTHY FRANCESCHI
 * Year: 2020
 * 
 * Resources:
 * 
 * EXT SRAM datasheet:    http://ww1.microchip.com/downloads/en/DeviceDoc/22100F.pdf
 * 
 * EXT SRAM discussion:   https://forum.arduino.cc/index.php?topic=675103.0
 * 
 * PORT MANIPULATION:     https://www.arduino.cc/en/Reference/PortManipulation
 *                        https://forum.arduino.cc/index.php?topic=93737.0
 *                        
 * ATMEGA644 datashhet:   http://ww1.microchip.com/downloads/en/DeviceDoc/doc2593.pdf
 * 
 * A* Algorithm steps:    http://csis.pace.edu/~benjamin/teaching/cs627/webfiles/Astar.pdf
 */
 
//#include <U8glib.h>
//#include <VL53L0X.h>
#include <Wire.h>
//#include "SdFat.h"
//SdFat SD;
//#include <Ultrasonic.h>
#include <sram.h>


//#define SD_CS_PIN SS PROGMEM;
//File myFile;

////////VARIABILI GENERALI/////////
int posX; //Posizione attuale su asse X
int posY; //Posizione attuale su asse Y

///////NAVIGATION////////

const byte maxX PROGMEM  = 100;
const byte maxY  PROGMEM  = 100;
const byte empty PROGMEM = 0;
const byte full  PROGMEM  = 1;

byte adiacenti[4][2];
byte openID;
byte closedID;

////////////////

bool const seriale PROGMEM = false;

void setup() {
  // put your setup code here, to run once:
  if(seriale==true) {Serial.begin(9600);}
  
  if(seriale==true) {Serial.print(F("ACTION: Setup"));}
  
  pinModes();
  if(seriale==true) {Serial.print(F("."));}
  
  shiftReset();
  if(seriale==true) {Serial.print(F("."));}
  
  if(seriale==true) {Serial.println(F("\nACTION: Setup completed"));} 

  
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
