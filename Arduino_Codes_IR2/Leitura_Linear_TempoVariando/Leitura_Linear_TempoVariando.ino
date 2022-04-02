
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

int timereset=50;     // RESET carga do fotodiodo
int timeexpo=10;      // tempo de exposição
int timeexpomax = 300;//tempo de exposição máximo
float outg = A0;      // sinal na saída do pixel
float s1;             // durante o reset  
float s2;             // Após a exposição
float vph;            // sinal detensão fotogerada
float vph_ac;         // tensão fotogerada acumulada
float vph_media;      // média final
int count;
int cmax=200;        //número de repetições da leitura  
int n;
int m;


// Tensões no Circuito

void set(){
    Serial.println();
    Serial.println("*************************************");
    Serial.println("LEITURA DA MATRIZ EM MODO LINEAR");
    Serial.print("VDD = ");
    v_dd = analogRead(VDD);
    Serial.println(5*v_dd/1024 );
    e_rdr = analogRead(ERDR);    
    Serial.print("ERDR = ");
    Serial.println(5*e_rdr/1024 );
    e_rst = analogRead(ERST);
    Serial.print("ERST = ");
    Serial.println(5*e_rst/1024 );
    Serial.print("tempo de exposição = ");
    Serial.print(timeexpo);
    Serial.println(" microsegundos");
    Serial.println("*************************************");
    delay(1000);
}

//função ler média
void lerpixel(){
count = 1;
vph_ac = 0;
n=1;
while (count <= cmax) {
//reset
digitalWrite(8,0);
digitalWrite(9,0);
digitalWrite(10,0);
delayMicroseconds(timereset);
s1 = analogRead(outg); 
//exposição
digitalWrite(8,1); //RST
delayMicroseconds(timeexpo);
s2 = analogRead(outg);
vph = (s1-s2)*5/1024;
if(vph < 0.05)
{
n=n;
}
else
{
vph_ac = vph_ac + vph;
n=n+1;
}
count++;
}
vph_media=vph_ac/n;
Serial.print(vph_media,3);
Serial.print (" ");
}

//função ler valor máximo
void lermax(){
count = 0;
vph_ac = 0;
while (count <= cmax) {
digitalWrite(8,0);
digitalWrite(9,0);
digitalWrite(10,0);
delayMicroseconds(timereset);
s1 = analogRead(outg); 
digitalWrite(8,1); //RST
delayMicroseconds(timeexpo);
s2 = analogRead(outg);
vph = (s1-s2)*5/1024;
if(vph > vph_ac)
{
vph_ac=vph;
}
count++;
}
Serial.print(vph_ac,3);
Serial.print (" ");
}

void coluna1(){ 
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

void coluna2(){ 
digitalWrite(7,1);
digitalWrite(6,1);
digitalWrite(5,1);
lermax();
digitalWrite(7,1);
digitalWrite(6,1);
digitalWrite(5,0);
lermax();
digitalWrite(7,1);
digitalWrite(6,0);
digitalWrite(5,1);
lermax();
digitalWrite(7,1);
digitalWrite(6,0);
digitalWrite(5,0);
lermax();
digitalWrite(7,0);
digitalWrite(6,1);
digitalWrite(5,1);
lermax();
digitalWrite(7,0);
digitalWrite(6,1);
digitalWrite(5,0);
lermax();
digitalWrite(7,0);
digitalWrite(6,0);
digitalWrite(5,1);
lermax();
digitalWrite(7,0);
digitalWrite(6,0);
digitalWrite(5,0);
lermax();
}

void linha1() {
// ------ linha 0
digitalWrite(4,1);
digitalWrite(3,1);
digitalWrite(2,1);
coluna1();
Serial.println();
// ------ linha 1
digitalWrite(4,1);
digitalWrite(3,1);
digitalWrite(2,0);
coluna1();
Serial.println();
// ------ linha 2
digitalWrite(4,1);
digitalWrite(3,0);
digitalWrite(2,1);
coluna1();
Serial.println();
// ------ linha 3
digitalWrite(4,1);
digitalWrite(3,0);
digitalWrite(2,0);
coluna1();
Serial.println();
// ------ linha 4
digitalWrite(4,0);
digitalWrite(3,1);
digitalWrite(2,1);
coluna1();
Serial.println();
// ------ linha 5
digitalWrite(4,0);
digitalWrite(3,1);
digitalWrite(2,0);
coluna1();
Serial.println();
// ------ linha 6
digitalWrite(4,0);
digitalWrite(3,0);
digitalWrite(2,1);
coluna1();
Serial.println();
// ------ linha 7
digitalWrite(4,0);
digitalWrite(3,0);
digitalWrite(2,0);
coluna1();
Serial.println();
}


void linha2() {
// ------ linha 0
digitalWrite(4,1);
digitalWrite(3,1);
digitalWrite(2,1);
coluna2();
Serial.println();
// ------ linha 1
digitalWrite(4,1);
digitalWrite(3,1);
digitalWrite(2,0);
coluna2();
Serial.println();
// ------ linha 2
digitalWrite(4,1);
digitalWrite(3,0);
digitalWrite(2,1);
coluna2();
Serial.println();
// ------ linha 3
digitalWrite(4,1);
digitalWrite(3,0);
digitalWrite(2,0);
coluna2();
Serial.println();
// ------ linha 4
digitalWrite(4,0);
digitalWrite(3,1);
digitalWrite(2,1);
coluna2();
Serial.println();
// ------ linha 5
digitalWrite(4,0);
digitalWrite(3,1);
digitalWrite(2,0);
coluna2();
Serial.println();
// ------ linha 6
digitalWrite(4,0);
digitalWrite(3,0);
digitalWrite(2,1);
coluna2();
Serial.println();
// ------ linha 7
digitalWrite(4,0);
digitalWrite(3,0);
digitalWrite(2,0);
coluna2();
Serial.println();
}

void loop() {
while(timeexpo <= timeexpomax) {
set();

    Serial.println();
    Serial.println("LEITURA MÉDIA DE CADA PIXEL");
    Serial.println();
    linha1();
    Serial.println();
    delay(1000);
    
timeexpo = timeexpo+10;
}
}

