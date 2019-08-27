/*
  RGB LED Demonstration
  rgb-led-demo.ino
  Demonstrates both Common Anode & Common Cathode RGB LEDs
  Uses three potentiometers for input

  DroneBot Workshop 2018
  https://dronebotworkshop.com
*/

// Define RGB LED pins

// Common Cathode RGB LED
int redPinCC = 3;
int greenPinCC = 5;
int bluePinCC = 6;

// Common Anode RGB LED
int redPinCA = 9;
int greenPinCA = 10;
int bluePinCA = 11;

// Define Potentiometer Inputs

int redControl = A0;
int greenControl = A1;
int blueControl = A2;

// Variables for Values

int redVal;
int greenVal;
int blueVal;

void setup()
{
  // Setup LED pins as outputs
  pinMode(redPinCC, OUTPUT);
  pinMode(greenPinCC, OUTPUT);
  pinMode(bluePinCC, OUTPUT);
  pinMode(redPinCA, OUTPUT);
  pinMode(greenPinCA, OUTPUT);
  pinMode(bluePinCA, OUTPUT);

  // Setup Serial Monitor
  Serial.begin(9600);
}

void loop() {

  // Read values from potentiometers
  redVal = analogRead(redControl);
  greenVal = analogRead(greenControl);
  blueVal = analogRead(blueControl);

  // Map values to range of 0-255
  redVal = map(redVal, 0, 1023, 0, 255);
  greenVal = map(greenVal, 0, 1023, 0, 255);
  blueVal = map(blueVal, 0, 1023, 0, 255);

  // Drive Common Cathode LED
  setColorCC(redVal, greenVal, blueVal);

  // Drive Common Anode LED
  setColorCA(redVal, greenVal, blueVal);

  // Write Color values to Serial Monitor
  Serial.print("Red: ");
  Serial.print(redVal);
  Serial.print(" - Green: ");
  Serial.print(greenVal);
  Serial.print(" - Blue: ");
  Serial.println(blueVal);

}

void setColorCC(int redValue, int greenValue, int blueValue) {
  // Set Colors for Common Cathode Display
  analogWrite(redPinCC, redValue);
  analogWrite(greenPinCC, greenValue);
  analogWrite(bluePinCC, blueValue);
}

void setColorCA(int redValue, int greenValue, int blueValue) {
  // Set Colors for Common Anode Display
  analogWrite(redPinCA, (255 - redValue));
  analogWrite(greenPinCA, (255 - greenValue));
  analogWrite(bluePinCA, (255 - blueValue));
}
