const int analogIn = A0; //Connect current sensor with A0 of Arduino
int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
int RawValue= 0;
int ACSoffset = 2500;
double Voltage = 0; //voltage measuring
double Amps = 0;// Current measuring
// the setup function runs once when you press reset or power the board
void setup () {Serial. Begin(9600);
 // initialize digital pin LED_BUILTIN as an output.
pinMode(A0,INPUT);
pinMode(A1,INPUT);
}
// the loop function runs over and over again forever
void loop() {
unsigned int x=0;
float AcsValue=0.0,Samples=0.0,AvgAcs=0.0,AcsValueF=0.0;
 for (int x = 0; x < 150; x++){ //Get 150 samples
 AcsValue = analogRead(A0); //Read current sensor values
 Samples = Samples + AcsValue; //Add samples together
 delay (3); // let ADC settle before next sample 3ms
}
AvgAcs=Samples/150.0;//Taking Average of Samples
Samples=0.0;
 for (int x = 0; x < 150; x++){ //Get 150 samples
float v = analogRead(A1);
 float volt= ((v *5.0/1024.0)*10);//Read current sensor values
 Samples = Samples + volt; //Add samples together
 delay (3); // let ADC settle before next sample 3ms
}
float Avgv=Samples/150.0;//Taking Average of Samples
Avgv=Avgv-1.26;
if(Avgv<2)
Avgv=0;
 //((AvgAcs * (5.0 / 1024.0)) is converitng the read voltage in 0-5 volts
//2.5 is offset(I assumed that arduino is working on 5v so the viout at no current comes
//out to be 2.5 which is out offset. If your arduino is working on different voltage than
//you must change the offset according to the input voltage)
//0.185v(185mV) is rise in output voltage when 1A current flows at input
AcsValueF = (2.5 - (AvgAcs * (5.0 / 1024.0)) )/0.185;
if(AcsValueF<0)
AcsValueF=0;
Serial.print("I=");
Serial.println(AcsValueF);
Serial.print("V=");
Serial.println(Avgv);//Print the read current on Serial monitor
delay(10);
