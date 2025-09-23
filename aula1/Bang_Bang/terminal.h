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

    // ----------------------------------------
    //  Comandos
    // ----------------------------------------
    if (key == "help"){
        BT.println("### MENU ###");
        //BT.println("'kp, ki ou kd' para mostrar valores atuais do PID");
        //BT.println("'kp, ki ou kd' seguido de um valor x altera valores.");
        BT.println("'start' para acionar os motores.");
        BT.println("'stop' para parar os motores.");
        BT.println("'contagem' Contagem de sensores usados no controle.");
        BT.println("'line' Exibe a leitura dos sensores de linha.");
        BT.println("'vel' Exibe a velocidade linear do controlador.");
        BT.println("'giro' Exibe a velocidade de rotacao do controlador");
    }

    // ----------------------------------------
    //  Variaveis
    // ----------------------------------------
    // [Variavel] velocidade linear
    else if (key == "vel") {
        if (hasValue) controle_vel = x;
        resposta = "Vel: " + String(controle_vel) + "  (Max: 255 pwm)" + "\n";
    }
    else if (key == "giro") {
        if (hasValue) controle_rot = x;
        resposta = "Vel: " + String(controle_vel) + "\n";
    }
    // [Variavel] variavel de conversão de analogico para digital
    else if (key == "trig"){
      if (hasValue) {
        sensor_trig = x; }
        resposta = "Threshold: " + String(sensor_trig);
    }
    // line.count
    else if (key == "contagem") {
        if (hasValue){
            controle_line_count = x;
            if( controle_line_count != 1 && controle_line_count != 3 && controle_line_count != 5 ){
                controle_line_count = 5;
            }
        }
        resposta = "Contagem de sensores no controle: " + String(controle_line_count) + "\n";
    }
    
    // ----------------------------------------
    //  Start / stop
    // ----------------------------------------
    // Inicia o loop de controle
    else if (key == "start") {
        resposta = "Loop de controle iniciado\n";
        resposta += ("Contagem: " + String(controle_line_count) + " sensores\n");
        resposta += ("vel: " + String(controle_vel) + "\n");
        resposta += ("giro: " + String(controle_rot) + "\n");
        start();
    }
    // Encerra o loop de controle
    else if (key == "stop") {
        stop(); 
        resposta = "Parado!";
    }
    
    // ----------------------------------------
    //  Teste de hardware
    // ----------------------------------------
    // Lê o estado dos sensores
    else if (key == "line") {
        sensor_update(); 
        resposta += str_array("", sensor_dig, SENSOR_COUNT) + "\n";
        resposta += str_array("", sensor_an, SENSOR_COUNT) + "\n";
    }
    // Movimenta o robo
    else if (key == "move") {
      int speed = 255;
      if (hasValue) { speed = x; }
      mover(speed, speed);
      delay(1000);
      stop();
    }
    
    // Comando invalido
    else {
        resposta = "Unknown command: " + key + "\n"; 
    }
    
    Serial.println("Response: " + resposta); 
    return resposta;
}

