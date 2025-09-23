#include "sensor.h"
#include "motor.h"
#include "controle.h"
#include <SoftwareSerial.h>

// Variaveis globais
SoftwareSerial BT(53, 52);
bool  running = false;

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
      switch (controle_line_action()){
        case controle_action_front: mover(controle_vel,controle_vel); break;
        case controle_action_dir: mover(controle_vel+controle_rot,controle_vel-controle_rot); break;
        case controle_action_esq: mover(controle_vel-controle_rot,controle_vel+controle_rot); break;
      }
    }
}
  
