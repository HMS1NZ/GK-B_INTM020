#include <dht11.h>
#define DHT11PIN 4

dht11 DHT11;

bool feny =false;
bool atfolyas=false;
bool vizm=true;
bool ontozve = false;
bool ho = false;
bool para = false;
int segednap = 0;
char customKey = '0';

volatile int  flow_frequency;  // Measures flow meter pulses
unsigned int  l_hour;          // Calculated litres/hour                      
unsigned char flowmeter = 2;  // Flow Meter Pin number
unsigned long currentTime;
unsigned long cloopTime;
float hasznalt;
float hasznalttort;

#define POWERvizm  12
#define Lampa_PIN  13
#define SIGNAL_PINvizm A5

void flow ()                  // Interruot function
{ 
   flow_frequency++;
} 


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(flowmeter, INPUT); 
  attachInterrupt(0, flow, RISING);
                                     
   sei();                              
   currentTime = millis();
   cloopTime = currentTime;

  pinMode(POWERvizm, OUTPUT);   // vizmélység szerzor áramellátása
  pinMode(Lampa_PIN, OUTPUT);   // lampa/motor áramellátása
  digitalWrite(POWERvizm, LOW); // vizm elöször kikapcs
}

void loop() {
  // put your main code here, to run repeatedly:
  ontozve = false;
  
  //feny
  feny =false;
  int fenyero = analogRead(A0);

  /*
  if (fenyero < 10) {
    Serial.println(" - sotet");
  } else if (fenyero < 200) {
    Serial.println(" - arnyek");
  } else if (fenyero < 500) {
    Serial.println(" - feny");
  } else if (fenyero < 800) {
    Serial.println(" - vilagos");
  } else {
    Serial.println(" - nagyon");
  }
  */

  
  if(fenyero>300){
    feny = true;
  }

  //vizm
  vizm = true;
  digitalWrite(POWERvizm, HIGH);  // vizm bekapcs
  delay(10);                      // vár 10 millisecet
  int value = analogRead(SIGNAL_PINvizm); // analog adat (vizm)
  digitalWrite(POWERvizm, LOW);   // vizm kikapcs  

  if(value<200){
    vizm=false;
  }

  //ho+para

  ho=false;
  para=false;
  
  int chk = DHT11.read(DHT11PIN);

  if(ho>0){
    ho=true;
  }

  if(para<95){
    para=true;
  }

if(segednap > 8640){

if(ho){  
if(para){
if(feny){
  if(vizm){
    digitalWrite(Lampa_PIN, HIGH);
    delay(5000);
    currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {     
      cloopTime = currentTime;              // Updates cloopTime
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min. (Results in +/- 3% range)
      l_hour = (flow_frequency * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flow rate in L/hour 
      flow_frequency = 0;                   // Reset Counter
      //Serial.print(l_hour, DEC);            // Print litres/hour
      //Serial.println(" L/hour");
   }
   delay(5000);
    digitalWrite(Lampa_PIN, LOW);
    ontozve = true;
  }
}
}
}
}

if(ontozve){
  segednap = 0;
}

if(segednap > 25920){
    digitalWrite(Lampa_PIN, HIGH);
    delay(5000);
    currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {     
      cloopTime = currentTime;              // Updates cloopTime
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min. (Results in +/- 3% range)
      l_hour = (flow_frequency * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flow rate in L/hour 
      flow_frequency = 0;                   // Reset Counter
      //Serial.print(l_hour, DEC);            // Print litres/hour
      //Serial.println(" L/hour");
   }
   delay(5000);
    digitalWrite(Lampa_PIN, LOW);
    ontozve = true;
}

if(ontozve){
  segednap = 0;
}

  //Serial.print("Fenyero: ");
  Serial.println(fenyero);

  //Serial.print("Vizmeéyseg: ");
  Serial.println(value);

  //Serial.print("Para (%): ");
  Serial.println((float)DHT11.humidity, 2);

  //Serial.print("Ho (C): ");
  Serial.println((float)DHT11.temperature, 2);


  //Serial.print("segednap: ");
  //Serial.println(segednap);

 //Serial.print("felhasznált viz: ");
 hasznalt = l_hour/360;
 hasznalttort=l_hour%360;
 //hasznalt=hasznalthasznalttort;
 //Serial.print(l_hour, DEC);
 //Serial.println(" L vizet haszálnánk oránként");
 //Serial.print(hasznalt);
 //Serial.print(",");
 //Serial.print(hasznalttort);
 //Serial.println(" valódi használat");

 for(int k=0; k<10; k++){
  delay(1000);
 }

 segednap++;
   
}
