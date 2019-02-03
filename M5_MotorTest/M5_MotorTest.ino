#include <M5Stack.h>
#include "M5StackUpdater.h"

#include "M5Motor.h"

String DisplayFileName = "";

boolean fwdFlag = true;

void setup_l293d() {
  pinMode( TB_A1, OUTPUT );
  pinMode( TB_A2, OUTPUT );

  pinMode( TB_B1, OUTPUT );
  pinMode( TB_B2, OUTPUT );

  pinMode( TB_Ap, OUTPUT);
  pinMode( TB_Bp, OUTPUT);
   
  digitalWrite( TB_A1, LOW );
  digitalWrite( TB_A2, LOW );

  digitalWrite( TB_B1, LOW );
  digitalWrite( TB_B2, LOW );

  digitalWrite( TB_Ap, LOW );
  digitalWrite( TB_Bp, LOW );

}

void cmd_forward() {
  Serial.println("all forward");
  
  digitalWrite( TB_A1, HIGH );
  digitalWrite( TB_A2, LOW );
  
  digitalWrite( TB_B1, HIGH );
  digitalWrite( TB_B2, LOW );

  digitalWrite( TB_Ap, HIGH);
  digitalWrite( TB_Bp, HIGH);
}

void cmd_back() {
  Serial.println("all back");
  
  digitalWrite( TB_A1, LOW );
  digitalWrite( TB_A2, HIGH );
  
  digitalWrite( TB_B1, LOW );
  digitalWrite( TB_B2, HIGH );

  digitalWrite( TB_Ap, HIGH);
  digitalWrite( TB_Bp, HIGH);
}

void cmd_stop() {
  Serial.println("all stop");

  digitalWrite( TB_Ap, LOW);
  digitalWrite( TB_Bp, LOW);
}

void cmd_spin_turn() {
  Serial.println("spin turn");
  
  digitalWrite( TB_A1, HIGH );
  digitalWrite( TB_A2, LOW );
  
  digitalWrite( TB_B1, LOW );
  digitalWrite( TB_B2, HIGH );

  digitalWrite( TB_Ap, HIGH);
  digitalWrite( TB_Bp, HIGH);
}

void cmd_turn_left() {
  Serial.println("turn left");
  
  digitalWrite( TB_A1, HIGH );
  digitalWrite( TB_A2, LOW );
  
  digitalWrite( TB_B1, HIGH );
  digitalWrite( TB_B2, LOW );

  digitalWrite( TB_Ap, LOW);
  digitalWrite( TB_Bp, HIGH);
}

void cmd_turn_right() {
  Serial.println("turn right");
  
  digitalWrite( TB_A1, HIGH );
  digitalWrite( TB_A2, LOW );
  
  digitalWrite( TB_B1, HIGH );
  digitalWrite( TB_B2, LOW );

  digitalWrite( TB_Ap, HIGH);
  digitalWrite( TB_Bp, LOW);
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
        if(fwdFlag == true){
          fwdFlag = false;
          cmd_back();
        }else{
          fwdFlag = true;
          cmd_forward();
        }
    } 
    if(M5.BtnC.wasPressed()) {
        Serial.printf("C");
        cmd_turn_right();
    } 
    M5.update();
}
