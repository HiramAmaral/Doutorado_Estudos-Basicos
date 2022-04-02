
 //LEITURA DA MATRIZ COM APLICAÇÃO DA CDS
 
  
  void setup(){

    pinMode(10, OUTPUT);//RW  -> aciona o ROWSEL
    pinMode(9, OUTPUT); //RDR -> aciona o eRDR
    pinMode(8, OUTPUT); //RST -> aciona o eRST
    pinMode(7, OUTPUT); //AC2
    pinMode(6, OUTPUT); //AC1
    pinMode(5, OUTPUT); //AC0
    pinMode(4, OUTPUT); //A2
    pinMode(3, OUTPUT); //A1
    pinMode(2, OUTPUT); //A0
    
    Serial.begin(9600);
        
  }

// variáveis do sistema

float v_dd;
float e_rdr;
float e_rst;
float VDD = A2;
float ERDR = A3;
float ERST = A4;

int timereset=10;  // tempo de carga do fotodiodo (reste)
int timeexpo=100;   // tempo de exposição
float outg = A0;    // sinal na saída do pixel
float s1;           // amostragem após o reset 
float s2;           // amostragem após o tempo de exposição
float vph;          // sinal detensão fotogerada
float vph_ac;       // tensão fotogerada acumulada
float vph_media;    // média final
float n;            //eficiencia quântica
int count;
int cmax=200;      //número de amostras para calcular a média  
char LCHAR;
int leit=0;

// Tensões no Circuito

void set(){

    Serial.println();
    Serial.println("*************************************");
    Serial.println("LEITURA DA MATRIZ EM MODO LINEAR");
    Serial.print("VDD = ");   //imprime VDD
    v_dd = analogRead(VDD);
    Serial.println(5*v_dd/1024 );
    e_rdr = analogRead(ERDR);    
    Serial.print("ERDR = ");   //imprime ERDR
    Serial.println(5*e_rdr/1024 );
    e_rst = analogRead(ERST);
    Serial.print("ERST = ");   //imprime RST
    Serial.println(5*e_rst/1024 );
    Serial.print("tempo de exposição = ");   //imprime tempo de exposição
    Serial.print(timeexpo);
    Serial.println(" microsegundos");   //imprime tempo de exposição
    Serial.println("*************************************");
    delay(1000);
}

//função para leitura do pixel
void lerpixel(){
count = 0;
vph_ac = 0;
while (count <= cmax) {
// reset do pixel
digitalWrite(8,0);
digitalWrite(9,0);
digitalWrite(10,0);
delayMicroseconds(timereset);
s1 = analogRead(outg); 
//exposição do pixel
digitalWrite(8,1); //RST
delayMicroseconds(timeexpo);
s2 = analogRead(outg);
vph = (s1-s2)*5/1024;
Serial.print(vph,3);
Serial.println();
count++;
}
}

void coluna(){
digitalWrite(7,1);
digitalWrite(6,1);
digitalWrite(5,1);
Serial.print(" ======== Pixel ");
Serial.print(LCHAR);
Serial.print(", ");
Serial.println("0");
lerpixel();
digitalWrite(7,1);
digitalWrite(6,1);
digitalWrite(5,0);
Serial.print(" ======== Pixel ");
Serial.print(LCHAR);
Serial.print(", ");
Serial.println("1");
lerpixel();
digitalWrite(7,1);
digitalWrite(6,0);
digitalWrite(5,1);
Serial.print(" ======== Pixel ");
Serial.print(LCHAR);
Serial.print(", ");
Serial.println("2");
lerpixel();
digitalWrite(7,1);
digitalWrite(6,0);
digitalWrite(5,0);
Serial.print(" ======== Pixel ");
Serial.print(LCHAR);
Serial.print(", ");
Serial.println("3");
lerpixel();
digitalWrite(7,0);
digitalWrite(6,1);
digitalWrite(5,1);
Serial.print(" ======== Pixel ");
Serial.print(LCHAR);
Serial.print(", ");
Serial.println("4");
lerpixel();
digitalWrite(7,0);
digitalWrite(6,1);
digitalWrite(5,0);
Serial.print(" ======== Pixel ");
Serial.print(LCHAR);
Serial.print(", ");
Serial.println("5");
lerpixel();
digitalWrite(7,0);
digitalWrite(6,0);
digitalWrite(5,1);
Serial.print(" ======== Pixel ");
Serial.print(LCHAR);
Serial.print(", ");
Serial.println("6");
lerpixel();
digitalWrite(7,0);
digitalWrite(6,0);
digitalWrite(5,0);
Serial.print(" ======== Pixel ");
Serial.print(LCHAR);
Serial.print(", ");
Serial.println("7");
lerpixel();
}

void linha() {
// ----------- linha 0
digitalWrite(4,1);
digitalWrite(3,1);
digitalWrite(2,1);
LCHAR = '0';
coluna();
Serial.println();
// ----------- linha 1
digitalWrite(4,1);
digitalWrite(3,1);
digitalWrite(2,0);
LCHAR = '1';
coluna();
Serial.println();
// ----------- linha 2
digitalWrite(4,1);
digitalWrite(3,0);
digitalWrite(2,1);
LCHAR = '2';
coluna();
Serial.println();
// ----------- linha 3
digitalWrite(4,1);
digitalWrite(3,0);
digitalWrite(2,0);
LCHAR = '3';
coluna();
Serial.println();
// ----------- linha 4
digitalWrite(4,0);
digitalWrite(3,1);
digitalWrite(2,1);
LCHAR = '4';
coluna();
Serial.println();
// ----------- linha 5
digitalWrite(4,0);
digitalWrite(3,1);
digitalWrite(2,0);
LCHAR = '5';
coluna();
Serial.println();
// ----------- linha 6
digitalWrite(4,0);
digitalWrite(3,0);
digitalWrite(2,1);
LCHAR = '6';
coluna();
Serial.println();
// ----------- linha 7
digitalWrite(4,0);
digitalWrite(3,0);
digitalWrite(2,0);
LCHAR = '7';
coluna();
Serial.println();
}



void loop() {

  while (leit <=0) {
    set();
    linha();
    Serial.println();
    leit++;
  }

}


