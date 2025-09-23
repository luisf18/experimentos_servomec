int controle_vel = 200;
int controle_rot = 100;
int controle_line_count = 5;

enum {
  controle_action_front = 0,
  controle_action_dir,
  controle_action_esq
};

uint8_t controle_line_action(){
  
  uint16_t sensor = 0;
  
  for(int i=0;i<SENSOR_COUNT;i++){
    sensor |= (sensor_dig[2]<<i);
  }

  switch (controle_line_count){
    case 1:
      if( sensor_dig[4] ) return controle_action_front;
      else return controle_action_esq;
      break;
    
    case 3:
      sensor = (sensor>>2)&&0b111;
      if( sensor == 0b111 || sensor == 0b010 ) return controle_action_front;
      if( sensor == 0b011 || sensor == 0b001 ) return controle_action_dir;
      if( sensor == 0b110 || sensor == 0b100 ) return controle_action_esq;
      break;
    
    case 5:
    default: 
      sensor = (sensor>>1)&&0b11111;
      if( sensor == 0b11111 || sensor == 0b00100 || sensor == 0b01110 ) return controle_action_front;
      if( sensor == 0b00010 || sensor == 0b00001 || sensor == 0b00011 || sensor == 0b00110 || sensor == 0b00111 || sensor == 0b01111 ) return controle_action_dir;
      if( sensor == 0b01000 || sensor == 0b10000 || sensor == 0b11000 || sensor == 0b01100 || sensor == 0b11100 || sensor == 0b11110 ) return controle_action_esq;
      break;
  }

  return 0xff;
}