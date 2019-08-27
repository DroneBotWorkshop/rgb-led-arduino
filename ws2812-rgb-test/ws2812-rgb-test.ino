/*
  WS2812 RGB LED Test
  ws2812-rgb-test.ino
  Uses Adafruit NeoPixel Library
  Functions from Adafruit NeopPixel Strandtest Examples
  DroneBot Workshop 2018
  https://dronebotworkshop.com
*/

// Include Adafruit NeoPixel Library
#include <Adafruit_NeoPixel.h>

// Define Arduino connection pin
#define LED_PIN 4
// Define the number of LEDs - change if necessary
#define LED_COUNT 4

// Create instance of NeoPixel class
// Parameter 1 = number of pixels in leds
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  // Setup Serial Monitor
  Serial.begin(9600);

  // Initialize the LEDs
  leds.begin();
  // Clear them all
  clearLEDs();
  // Show the result of clearing the LEDs
  leds.show();

}

void loop() {

  // Print to Serial Monitor
  Serial.println("Starting RGB LED Demo");

  // Cycle through Color Wipe Examples
  // Set colors to Red
  Serial.println("Color Wipe - RED");
  colorWipe(leds.Color(255, 0, 0), 200);
  delay(1000);
  // Set colors to Green
  Serial.println("Color Wipe - GREEN");
  colorWipe(leds.Color(0, 255, 0), 200);
  delay(1000);
  // Set Colors to Blue
  Serial.println("Color Wipe - BLUE");
  colorWipe(leds.Color(0, 0, 255), 200);
  delay(1000);
  // Set colors to Yellow
  Serial.println("Color Wipe - YELLOW");
  colorWipe(leds.Color(255, 255, 0), 200);
  delay(1000);


  // Theater Chase Examples
  // White
  Serial.println("Theater Chase - WHITE");
  theaterChase(leds.Color(127, 127, 127), 50);
  delay(1000);
  // Red
  Serial.println("Theater Chase - RED");
  theaterChase(leds.Color(127, 0, 0), 50);
  delay(1000);
  // Green
  Serial.println("Theater Chase - GREEN");
  theaterChase(leds.Color(0, 127, 0), 50);
  delay(1000);
  // Blue
  Serial.println("Theater Chase - BLUE");
  theaterChase(leds.Color(0, 0, 127), 50);
  delay(1000);

  // Rainbow Examples
  Serial.println("Rainbow");
  rainbow(20);
  Serial.println("Rainbow Cycle");
  rainbowCycle(20);
  Serial.println("Rainbow Theater Chase");
  theaterChaseRainbow(50);

  //Finished
  Serial.println("Loop Ended, Demo Finished!");
  Serial.println(".................................");

}

// Function to set all LEDs off
void clearLEDs()
{
  // Cycle through all LEDs
  for (int i = 0; i < LED_COUNT; i++)
  {
    // Set color to zero which is off
    leds.setPixelColor(i, 0);
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < leds.numPixels(); i++) {
    leds.setPixelColor(i, c);
    leds.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < leds.numPixels(); i++) {
      leds.setPixelColor(i, Wheel((i + j) & 255));
    }
    leds.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < leds.numPixels(); i++) {
      leds.setPixelColor(i, Wheel(((i * 256 / leds.numPixels()) + j) & 255));
    }
    leds.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < leds.numPixels(); i = i + 3) {
        leds.setPixelColor(i + q, c);  //turn every third pixel on
      }
      leds.show();

      delay(wait);

      for (uint16_t i = 0; i < leds.numPixels(); i = i + 3) {
        leds.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < leds.numPixels(); i = i + 3) {
        leds.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      leds.show();

      delay(wait);

      for (uint16_t i = 0; i < leds.numPixels(); i = i + 3) {
        leds.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return leds.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return leds.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return leds.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
