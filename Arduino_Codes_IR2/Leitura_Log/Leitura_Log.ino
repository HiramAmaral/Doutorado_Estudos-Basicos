
 //LEITURA DA MATRIZ EM MODO LOGARÍTIMICO
 
  
  void setup(){

    DDRB = B00000111;
    PORTB = B0000000;
        
    pinMode(7, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(2, OUTPUT);
    digitalWrite(7,1);
    digitalWrite(6,1);
    digitalWrite(5,1);
    digitalWrite(4,1);
    digitalWrite(3,1);
    digitalWrite(2,1);
    PORTB = B0000111;
    delay(1000);
    
    Serial.begin(9600);
        
  }

// =================================================================

float s; // amostragem 
float outg = A0;
float vph;
float v_dd;
float e_rdr;
float e_rst;
float VDD = A2;
float ERDR = A3;
float ERST = A4;

void set(){

    Serial.println();
    Serial.println("=============================================================");
    Serial.println("LEITURA DA MATRIZ DE PIXEL DO CHIP IR2 EM MODO LOGARÍTIMO");
    Serial.print("VDD = ");   //imprime VDD
    v_dd = analogRead(VDD);
    Serial.println(5*v_dd/1024 );
    e_rdr = analogRead(ERDR);    
    Serial.print("ERDR = ");   //imprime ERDR
    Serial.println(5*e_rdr/1024 );
    e_rst = analogRead(ERST);
    Serial.print("ERST = ");   //imprime RST
    Serial.println(5*e_rst/1024 );
    Serial.println("=============================================================");
    delay(1000);
}

void lerpixel(){

// PIXEL EM MODO LOG
digitalWrite(8,0);
digitalWrite(9,0);
digitalWrite(10,0);

s = analogRead(outg);
Serial.print (s*5/1024,2);
Serial.print (" | ");
}

void coluna(){
  
digitalWrite(7,1);
digitalWrite(6,1);
digitalWrite(5,1);
lerpixel();

digitalWrite(7,1);
digitalWrite(6,1);
digitalWrite(5,0);
lerpixel();

digitalWrite(7,1);
digitalWrite(6,0);
digitalWrite(5,1);
lerpixel();

digitalWrite(7,1);
digitalWrite(6,0);
digitalWrite(5,0);
lerpixel();

digitalWrite(7,0);
digitalWrite(6,1);
digitalWrite(5,1);
lerpixel();

digitalWrite(7,0);
digitalWrite(6,1);
digitalWrite(5,0);
lerpixel();

digitalWrite(7,0);
digitalWrite(6,0);
digitalWrite(5,1);
lerpixel();

digitalWrite(7,0);
digitalWrite(6,0);
digitalWrite(5,0);
lerpixel();

}

void loop() {
// --------- linha 0
set();
digitalWrite(4,1);
digitalWrite(3,1);
digitalWrite(2,1);
coluna();
Serial.println();
// --------- linha 1
digitalWrite(4,1);
digitalWrite(3,1);
digitalWrite(2,0);
coluna();
Serial.println();
// --------- linha 2
digitalWrite(4,1);
digitalWrite(3,0);
digitalWrite(2,1);
coluna();
Serial.println();
// --------- linha 3
digitalWrite(4,1);
digitalWrite(3,0);
digitalWrite(2,0);
coluna();
Serial.println();
// --------- linha 4
digitalWrite(4,0);
digitalWrite(3,1);
digitalWrite(2,1);
coluna();
Serial.println();
// --------- linha 5
digitalWrite(4,0);
digitalWrite(3,1);
digitalWrite(2,0);
coluna();
Serial.println();
// --------- linha 6
digitalWrite(4,0);
digitalWrite(3,0);
digitalWrite(2,1);
coluna();
Serial.println();
// --------- linha 7
digitalWrite(4,0);
digitalWrite(3,0);
digitalWrite(2,0);
coluna();
Serial.println();
}

