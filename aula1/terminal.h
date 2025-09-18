template<typename T>
String str_array(const char *nome, T* arr, size_t sz){
    String str = String(nome) + " = [ ";
    for (size_t i=0; i<sz-1; i++) str += (String(arr[i]) + " ");
    str += String(arr[sz-1]) + " ]";
    return str;
}

template<typename T>
void print_array(String prefix, T* arr, size_t sz){
    Serial.print(prefix);
    Serial.print("[");
    for (size_t i=0; i<sz-1; i++){
        Serial.print(arr[i]);
    }
    Serial.print(arr[sz-1]);
    Serial.print("]\n");
}

String terminal(const char *const cmd) {
    //Tratamento dos dados
    String input = String(cmd);
    input.trim(); 
    input.replace(',', '.'); 

    Serial.println("Raw command: " + input);

    int spaceIndex = input.indexOf(' ');
    String key;
    double x = 0;
    bool hasValue = (spaceIndex != -1); 
    if (hasValue) {
        key = input.substring(0, spaceIndex); 
        String valueStr = input.substring(spaceIndex + 1); 
        x = valueStr.toDouble(); 
    } else {
        key = input;
    }

    String resposta = "";

    
    //Comandos
    if (key == "vel") {
      if (hasValue) {
        vel_base = x; }
        resposta = "Vel: " + String(vel_base) + "  (Max: 255 pwm)" + "\n";
    } else if (key == "start") {
        start();
        resposta = "System started\n";
    } else if (key == "stop") {
        stop(); 
        resposta = "PARADO!";
    } else if (key == "line.read") {
        sensor_update(); 
        resposta += str_array("", sensor_dig, SENSOR_COUNT) + "\n";
        resposta += str_array("", sensor_an, SENSOR_COUNT) + "\n";
    } else if (key == "help"){
        BT.println("### MENU ###");
        BT.println("'kp, ki ou kd' para mostrar valores atuais do PID");
        BT.println("'kp, ki ou kd' seguido de um valor x altera valores.");
        BT.println("'start' para acionar os motores.");
        BT.println("'stop' para parar os motores.");
        BT.println("'line.read' indica quais sensores estão ativos naquele momento.");
        BT.println("'vel' ativa ou desativa a função de mostrar velocidade.");
        BT.println("'vel' seguido de um valor x entre 0 e 255 altera o valor");
    } else if (key == "trig"){
      if (hasValue) {
        sensor_trig = x; }
        resposta = "Threshold: " + String(sensor_trig);
    } else if (key == "move") {
      int speed = 255;
      if (hasValue) { speed = x; }
      mover(speed, speed);
      delay(1000);
      stop();
    } else {
        resposta = "Unknown command: " + key + "\n"; 
    }
    
    Serial.println("Response: " + resposta); 
    return resposta;
}

