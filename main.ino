#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Encoder.h>
#define NUM_LEDS 24
#define PIN_LED A5
#define PIN_BUTTON 10
#define PIN_CLK 11
#define PIN_DT 12

Adafruit_NeoPixel strip(NUM_LEDS, PIN_LED, NEO_GRB + NEO_KHZ800);
Encoder encoder(PIN_CLK, PIN_DT);

void setup() {

 //  pinMode(PIN_DEVICE1_GND, OUTPUT); // Устанавливаем пин GND устройства 1 как выход
  //pinMode(PIN_DEVICE2_GND, OUTPUT);
  strip.setBrightness(10);   
  strip.begin();
  strip.show(); 

  pinMode(13, OUTPUT); // выход для питания энкодера
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_CLK, INPUT);
  pinMode(PIN_DT, INPUT);

  Serial.begin(9600);
}

bool ledState = false;
int counter = 0;
int brightnessLevel = 50;

void loop() {

  bool buttonState = digitalRead(10);
  Serial.println(buttonState);
  int encoderDelta = encoder.read();
  Serial.println(encoderDelta);
  brightnessLevel = map(encoderDelta, 0, 30, 0, 255);

    if(brightnessLevel < 10){
    brightnessLevel =10;
    }
  if (brightnessLevel > 255){
    brightnessLevel = 255;
  }

  if (encoderDelta >45){
     encoder.write(0);
  } else if(encoderDelta < -20){
    encoder.write(30);
  }
  Serial.println(counter);
  
  //strip.show(); // Применяем изменения
  if (counter == 1){
    strip.setBrightness(brightnessLevel);
    turnOnLEDs();
    strip.show();
  } else if( counter ==2){
    strip.setBrightness(brightnessLevel);
    redMode();
    strip.show();
  }

     if (buttonState) {
    counter++;

    if (counter == 1) {
      turnOnLEDs();
      strip.show();
      //encoderDelta = previousEncoderState;
      Serial.println("On");

    } else if (counter == 2 ) {
      redMode();
      strip.show();
      Serial.println("state 2");
      //strip.setBrightness(10);
    }
      else {
      counter = 0;
      Serial.println("off");
      turnOffLEDs();
      strip.show();
    }
    delay(500);
  }
}

void turnOnLEDs() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, 240, 142, 10); // simple mode colours
  }
}

void redMode() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, 255, 20, 10); // red mode colours
  }
  
}

void turnOffLEDs() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, 0, 0, 0); // turn off LED strip
  }
}




