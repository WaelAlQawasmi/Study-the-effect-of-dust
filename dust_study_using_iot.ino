/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  You can use this sketch as a debug tool that prints all incoming values
  sent by a widget connected to a Virtual Pin 1 in the Blynk App.

  App project setup:
    Slider widget (0...100) on V1
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
int dustPin = A0; // dust sensor - Wemos A0 pin
int ledPin = D2;    
 
float voltsMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "msQxoNj1taFZsVgXakJUGXQI6Bw3EYGG";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Umniah_82AE48";
char pass[] = "jo554422";

int dust (int dust )
{
  digitalWrite(ledPin,LOW); // power on the LED
  delayMicroseconds(280);
 
  voltsMeasured = analogRead(dustPin); // read the dust value
 
  delayMicroseconds(40);
  digitalWrite(ledPin,HIGH); // turn the LED off
  delayMicroseconds(9680);
 
  //measure your 5v and change below
  calcVoltage = voltsMeasured * (3.3 / 1024.0);
  dustDensity = 0.17 * calcVoltage - 0.094;
  dust= dustDensity*100;

  delay(10);
 if(dust<0)
 dust=0;
  return (dust);
}
float reed (float v )
{ if (v<2)
  return (0);
  if (v>2)
  return (v);
}


// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin 1

void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
 int A=0;
  int y=dust(A);
  float z =Serial.parseFloat();
  float w =reed(z);
 if (w==0)
 goto u;
  
  Blynk.virtualWrite(V3,w);
  u: if(z==0)
  goto o;
  if(z<2)
  Blynk.virtualWrite(V2,z);
  o:Blynk.virtualWrite(V1,dust(A));
  delay(200);

}
BLYNK_WRITE(V4)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  
 digitalWrite(D3,pinValue);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
 pinMode(ledPin,OUTPUT);
  pinMode(D3,OUTPUT);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
}
