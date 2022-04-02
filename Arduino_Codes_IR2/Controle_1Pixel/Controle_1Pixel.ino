
 //CONTROLE DE UM PIXEL EM MODO LINEAR PARA TESTE DO CHIP
 
  
  void setup(){


    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(2, OUTPUT);  
    Serial.begin(9600);
        
  }

// variáveis do sistema

int timereset=100; //tempo de carga do fotodiodo ou tempo de reset
int timeexpo=500;  //tempo de exposição a luz no pixel em modo linear

void loop() {

digitalWrite(2,1); //A0
digitalWrite(3,1); //A1
digitalWrite(4,1); //A5
digitalWrite(5,1); //AC0
digitalWrite(6,1); //AC1
digitalWrite(7,1); //AC2

digitalWrite(8,0);
digitalWrite(9,0);
digitalWrite(10,0);
delayMicroseconds(timereset);

digitalWrite(8,1);
delayMicroseconds(timeexpo);

}
