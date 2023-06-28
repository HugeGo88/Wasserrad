#include <FastLED.h>
/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/ReadAnalogVoltage
*/
int counter = 0;
bool active = false;
int zeroCounter = 0;

// How many leds in your strip?
#define NUM_LEDS 25

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 10
#define CLOCK_PIN 8

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 12;     // the number of the pushbutton pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

// Define the array of leds
CRGB leds[NUM_LEDS];

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);
} 

// the loop routine runs over and over again forever:
void loop() {
    // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    ;
  } else {
    counter = 0;
  }
  
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  if(voltage < 0.01){
    zeroCounter++;
    active = true;
  }
  if(voltage > 0.01){
    if(zeroCounter > 5){
      counter++;
    }
    zeroCounter = 0;
  }
    // print out the value you read:
    Serial.println(counter);
    for( int i = 0; i < NUM_LEDS; i++){
      leds[i] = CRGB::Black;
    }
    // Turn the LED on, then pause
    leds[(counter/ 5) % NUM_LEDS ] = CRGB::White;
    FastLED.show();
}
