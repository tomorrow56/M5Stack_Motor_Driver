#include <M5Stack.h>
#include "M5StackUpdater.h"

#include "M5Motor.h"

String DisplayFileName = "";

//ESP32 SPEED Control sample

//LEDC channel of 16 channels (started from zero)
#define LEDC_CHANNEL_0 0
#define LEDC_CHANNEL_1 1

//use 8 bit precission for LEDC timer
#define LEDC_TIMER_BIT 8

//use 10 kHz as a LEDC base frequency
#define LEDC_BASE_FREQ 20000

int min = 0;
int max = 255;

int duration = 255; // duration time msec
int interval = duration / (max - min);

void setup_l293d() {
  pinMode( TB_A1, OUTPUT );
  pinMode( TB_A2, OUTPUT );

  pinMode( TB_B1, OUTPUT );
  pinMode( TB_B2, OUTPUT );

  // Set Enable pin to LEDC
  ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_BIT);
  ledcSetup(LEDC_CHANNEL_1, LEDC_BASE_FREQ, LEDC_TIMER_BIT);

  ledcAttachPin(TB_Ap, LEDC_CHANNEL_0);  // Motor A
  ledcAttachPin(TB_Bp, LEDC_CHANNEL_1);  // Motor B
   
  digitalWrite( TB_A1, LOW );
  digitalWrite( TB_A2, LOW );

  digitalWrite( TB_B1, LOW );
  digitalWrite( TB_B2, LOW );

  ledcWrite(0, min);
  ledcWrite(1, min);
}

void cmd_forward() {
  Serial.println("all forward");
  
  digitalWrite( TB_A1, HIGH );
  digitalWrite( TB_A2, LOW );
  
  digitalWrite( TB_B1, HIGH );
  digitalWrite( TB_B2, LOW );

  for(int n = min; n <= max; n++){
    ledcWrite(0, n);
    ledcWrite(1, n);
    delay(interval);
  }
}

void cmd_back() {
  Serial.println("all back");
  
  digitalWrite( TB_A1, LOW );
  digitalWrite( TB_A2, HIGH );
  
  digitalWrite( TB_B1, LOW );
  digitalWrite( TB_B2, HIGH );

  for(int n = min; n <= max; n++){
    ledcWrite(0, n);
    ledcWrite(1, n);
    delay(interval);
  }
}

void cmd_stop() {
  Serial.println("all stop");

  ledcWrite(0, 0);
  ledcWrite(1, 0);
}

void cmd_spin_turn() {
  Serial.println("spin turn");
  
  digitalWrite( TB_A1, HIGH );
  digitalWrite( TB_A2, LOW );
  
  digitalWrite( TB_B1, LOW );
  digitalWrite( TB_B2, HIGH );

  for(int n = min; n <= max; n++){
    ledcWrite(0, n);
    ledcWrite(1, n);
    delay(interval);
  }
}

void cmd_turn_left() {
  Serial.println("turn left");
  
  digitalWrite( TB_A1, HIGH );
  digitalWrite( TB_A2, LOW );
  
  digitalWrite( TB_B1, HIGH );
  digitalWrite( TB_B2, LOW );

  ledcWrite(0, 0);

  for(int n = min; n <= max; n++){
    ledcWrite(1, n);
    delay(interval);
  }
}

void cmd_turn_right() {
  Serial.println("turn right");
  
  digitalWrite( TB_A1, HIGH );
  digitalWrite( TB_A2, LOW );
  
  digitalWrite( TB_B1, HIGH );
  digitalWrite( TB_B2, LOW );

  for(int n = min; n <= max; n++){
    ledcWrite(0, n);
    delay(interval);
  }
  ledcWrite(1, 0);
}

void setup() { 
    M5.begin();

    if(digitalRead(BUTTON_A_PIN) == 0) {
      Serial.println("Will Load menu binary");
      updateFromFS(SD);
      ESP.restart();
    }

//    Serial.begin(115200);

    setup_l293d();
    cmd_stop();

    DisplayFileName = "/jpg/M5Logo.jpg";
    M5.Lcd.drawJpgFile(SD, DisplayFileName.c_str(), 0, 0, 320, 240);

    Serial.println( "Setup done");
}

void loop() {
    if(M5.BtnA.wasPressed()) {
        Serial.printf("A");
        cmd_turn_left();
    }
    if(M5.BtnB.wasPressed()) {
        Serial.printf("B");
        cmd_back();
    } 
    if(M5.BtnC.wasPressed()) {
        Serial.printf("C");
        cmd_turn_right();
    } 
    M5.update();
}
