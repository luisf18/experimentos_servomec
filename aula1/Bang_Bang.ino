

#define SENSOR_COUNT (sizeof(sensores)/sizeof(*sensores))

#define S1 A6
#define S2 A5
#define S3 A4
#define S4 A3
#define S5 A2
#define S6 A1
#define S7 A0

int sensor_trig = 70;
int   sensores[] = {S7, S6, S5, S4, S3, S2, S1};
bool  sensor_dig[SENSOR_COUNT];
int  sensor_an[SENSOR_COUNT];
int vel_base = 200;
bool  running = false;
int rot = 100;

void sensor_update() {
    for (size_t i = 0; i<SENSOR_COUNT; i++) {
      sensor_an[i] = analogRead(sensores[i]);
      sensor_dig[i] = (sensor_an[i] < sensor_trig);
    }
}
#include <SoftwareSerial.h>
SoftwareSerial BT(53, 52);

#include "motor.h"
#include "terminal.h"



void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  BT.println("Espere...");
  pinMode(motorEsq1, OUTPUT);
  pinMode(motorEsq2, OUTPUT);
  pinMode(motorDir1, OUTPUT);
  pinMode(motorDir2, OUTPUT);
  stop();
  BT.println("Seguidor Pronto");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (BT.available() > 0){
        String CMD = BT.readString(); // Read the command
        Serial.println("command: " + CMD);
        BT.println("command: " + CMD);
        String resposta = terminal(CMD.c_str());
        Serial.println(resposta);
        BT.println(resposta);
    }

    if(running){
      sensor_update();
      bool left   = sensor_dig[2];
      bool center = sensor_dig[3];
      bool right  = sensor_dig[4];

      if( (left && !right && center) || (!center && left && !right) ){
        mover(vel_base+rot,vel_base-rot);
      }else if( (!left && right && center) || (!center && !left && right)) {
        mover(vel_base-rot,vel_base+rot);
      }else{
        mover(vel_base,vel_base);  
    }
    }
}
  
