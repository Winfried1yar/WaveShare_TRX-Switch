// ============================================================================
/*TRX-Schalter zur Auswahl des aktiven TRX
DL1YAR  20251113
PiPico_TRX_Switch_20251205
PiPico_TRX_Switch_20251208
 Tast1+Tast4 = alles aus   20251212
 
Aufruf Terminal
winfried@winfried-laptop:~$ echo Trx2 > /dev/ttyACM0
------Script fuer die Bildschirmoberfläche ----------------
#!/bin/bash
#kleines Script, um mit einem Waveshare-Zero TRX umzuschalten
stty -F /dev/TRX 9600 -parodd -cstopb -icrnl -ixon -opost -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke
echo Trx2 > /dev/TRX
------------------------------------------------------------
Trx1 bis Trx4 sind selsterklärend
Trx0 schaltet alle Trx von der Antenne ab

für Windows kann dieses Script helfen
wenn z.B. Commport5 benutzt wird

dieses Skript in C: mit dem Namen "COM5-Trx1.ps1"
##################################################
$port = New-Object System.IO.Ports.SerialPort COM5, 9600, None, 8, one
$port.Open()
$port.Write("Trx1")
$port.Close()

###################################################

Verknüpfung auf dem Desktop erstellen nit folgenden Eigenschaften:

C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe -ExecutionPolicy Bypass -File C:\COM5-Trx1.ps1
*/
//  https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
//  programmer: none
// 
// ============================================================================

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


//------Pinbelegung Waveshare One---------------

int LED_   = 16   ;// OnboardLED
int Trx1    =  1   ;// TRX1  GP_0
int Trx2    =  2   ;// TRX2  GP_1
int Trx3    =  3   ;// TRX3  GP_2
int Trx4    =  4   ;// TRX1  GP_3
int Led_1   =  14  ;// Led   GP_5
int Led_2   =  15  ;// Led   GP_5
int Led_3   =  26  ;// Led   GP_5
int Led_4   =  27  ;// Led   GP_5
int Tast1   =  8   ;// Taster
int Tast2   =  7   ;// Taster
int Tast3   =  6   ;// Taster
int Tast4   =  5   ;// Taster


int Rel_an = HIGH;
int Rel_ab = LOW;
int t= 0; //Zählvariable
//------------------------------

#define NUMPIXELS 1  // Zielboard
int pixelFormat = NEO_GRB + NEO_KHZ800;
Adafruit_NeoPixel pixels(NUMPIXELS, LED_, NEO_GRB + NEO_KHZ800);// Zielboard

//---------------------------------
void LED_aus(){
   pixels.setPixelColor(0, pixels.Color(0, 0, 0));  pixels.show();
}     
void LED_ein(){
  pixels.setPixelColor(0, pixels.Color(0, 20, 0)); pixels.show(); 
}  
void alles_aus(){
  digitalWrite(Trx1,Rel_ab);
  digitalWrite(Trx2,Rel_ab);
  digitalWrite(Trx3,Rel_ab);
  digitalWrite(Trx4,Rel_ab);

  digitalWrite(Led_1,LOW);
  digitalWrite(Led_2,LOW);
  digitalWrite(Led_3,LOW);
  digitalWrite(Led_4,LOW);
}
//###################################
//-------Hauptschleifen----------
//###################################
void setup() {
  pinMode(LED_,  OUTPUT);
  pinMode(Trx1,  OUTPUT);
  pinMode(Trx2,  OUTPUT);
  pinMode(Trx3,  OUTPUT);
  pinMode(Trx4,  OUTPUT);
  pinMode(Led_1,  OUTPUT);
  pinMode(Led_2,  OUTPUT);
  pinMode(Led_3,  OUTPUT);
  pinMode(Led_4,  OUTPUT);

  pinMode(Tast1, INPUT);
  pinMode(Tast2, INPUT);
  pinMode(Tast3, INPUT);
  pinMode(Tast4, INPUT);


  digitalWrite(16, 1);//LED
  alles_aus();
   Serial.begin(9600);
  Serial.setTimeout(5100);
    pixels.begin();
     alles_aus();
    
}
//###################################

void loop() {
  // Warten auf String...
  if (Serial.available()) {
    String ser= Serial.readStringUntil('\n');
    if (ser =="Trx1") {
      LED_ein();
        alles_aus();
        digitalWrite(Trx1,Rel_an); // nur EIN
        digitalWrite(Led_1,HIGH); // nur EIN
       
        delay(250);
         Serial.println("TRX1");
      };
    if (ser =="Trx2") {
     LED_ein();
        alles_aus();
        digitalWrite(Trx2,Rel_an);
        digitalWrite(Led_2,HIGH); // nur EIN
        delay(250);
         Serial.println("TRX2");
      }; 
     if (ser =="Trx3") {
     LED_ein();
        alles_aus();
        digitalWrite(Trx3,Rel_an);
        digitalWrite(Led_3,HIGH); // nur EIN
        delay(250);
         Serial.println("TRX3");
      }; 
      if (ser =="Trx4") {
     LED_ein();
        alles_aus();
        digitalWrite(Trx4,Rel_an);
        digitalWrite(Led_4,HIGH); // nur EIN
        delay(250);
         Serial.println("TRX4");
      };  
     if (ser =="Trx0") {  //alles AUS
        LED_ein();
        alles_aus();
        delay(250);
         Serial.println("noTRX");
      };  
      LED_aus();//serielle Eingabe
  }
  //LED_aus();//serielle Eingabe
  //Tastenabfrage ----------------------
      if (digitalRead(Tast1) == LOW) {
        alles_aus();
          do{
          digitalWrite(Trx1,Rel_an); // nur EIN
          digitalWrite(Led_1,HIGH); // nur EIN
          delay(500);
          if (digitalRead(Tast4) == LOW) {
            alles_aus();
            do{
              delay(500);
            }while((digitalRead(Tast4) == LOW));
          };
        }while((digitalRead(Tast1) == LOW));
        };
    
      if (digitalRead(Tast2) == LOW) {
        alles_aus();
          do{
          digitalWrite(Trx2,Rel_an); // nur EIN
          digitalWrite(Led_2,HIGH); // nur EIN
          delay(500);
        }while(digitalRead(Tast2) == LOW);
      }
      if (digitalRead(Tast3) == LOW) {
        alles_aus();
         do{
          digitalWrite(Trx3,Rel_an); // nur EIN
          digitalWrite(Led_3,HIGH); // nur EIN
          delay(500);
        }while(digitalRead(Tast3) == LOW);
      }
      if (digitalRead(Tast4) == LOW) {
        alles_aus();
        do{
          digitalWrite(Trx4,Rel_an); // nur EIN
          digitalWrite(Led_4,HIGH); // nur EIN
          delay(500);
        }while((digitalRead(Tast4) == LOW));
      }
     
    

}


