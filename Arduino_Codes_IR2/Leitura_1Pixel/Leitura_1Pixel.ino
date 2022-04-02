
 //LEITURA DA MATRIZ COM APLICAÇÃO DA CDS
 
  
  void setup(){

    pinMode(10, OUTPUT);//RW -> ROWSEL
    pinMode(9, OUTPUT); //RDR-> eRDR
    pinMode(8, OUTPUT); //RST-> eRST
    pinMode(7, OUTPUT); //AC2
    pinMode(6, OUTPUT); //AC1
    pinMode(5, OUTPUT); //AC0
    pinMode(4, OUTPUT); //A2
    pinMode(3, OUTPUT); //A1
    pinMode(2, OUTPUT); //A0 
    Serial.begin(9600);
        
  }

float v_dd;
float e_rdr;
float e_rst;
float VDD = A2;
float ERDR = A3;
float ERST = A4;

int timereset=10;  // tempo reset
int timeexpo=600;// tempo de exposição
float outg = A0;  // sinal na saída do pixel
float s1;         // leitura no reset
float s2;         // leitura após exposição
float vph;        // tensão fotogerada (CDS)
float vph_ac;     // vph acumulado (média)
float vph_media;  // média final
int count;
int cmax=100;    //número de execuções  
int n;            //dividendo da média
int m=0;
float m1;
float m2;

void set(){

    Serial.println();
    Serial.println("*******************************");
    Serial.print("tempo de exposição = ");
    Serial.print(timeexpo);
    Serial.println(" microsegundos");
}

//função para leitura do pixel

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

/*void lermax(){
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

void lermin(){
count = 0;
vph_ac = vph;
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
if(vph <= vph_ac)
{
vph_ac=vph;
}
count++;
}
Serial.print(vph_ac,3);
Serial.print (" ");
}
*/
void pixel() {
digitalWrite(4,0);
digitalWrite(3,0);
digitalWrite(2,1);
digitalWrite(7,0);
digitalWrite(6,0);
digitalWrite(5,1);
Serial.println();
//Serial.print("Máximo - ");
//lermax();
Serial.println();
Serial.print("Médio - ");
lerpixel();
//Serial.println();
//Serial.print("Mínimo - ");
//lermin();
}

//Média de VRDR
void mediaRDR(){
m2=0;
count = 0;
vph_ac = 0;
while (count <= cmax) {
digitalWrite(8,0);
digitalWrite(9,0);
digitalWrite(10,0);
delayMicroseconds(timereset);
s1 = analogRead(outg); 
digitalWrite(8,1);
delayMicroseconds(timeexpo);
s2 = analogRead(outg);

e_rdr = analogRead(ERDR);
m1=5*e_rdr/1024;
m2=m2+m1;
count++;
}
Serial.print("VRDR = ");
Serial.print(m2/cmax);
Serial.println();
}

void loop() {
while (m<30){
set();
pixel();
Serial.println();
delay(15000);
m++; 
}
}



