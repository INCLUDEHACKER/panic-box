#include <TinyGPS++.h>
#include <SoftwareSerial.h>
TinyGPSPlus gps;
SoftwareSerial gsmSerial(2, 3); //RX is digital pin 2 (connect to TX of other device)TX is digital pin 3 (connect to RX of other device)
SoftwareSerial gpsSerial(4, 5); //RX is digital pin 4 (connect to TX of other device)TX is digital pin 5 (connect to RX of other device)
int button, SWITCH;
void setup() {
  gsmSerial.begin(9600);
  gpsSerial.begin(9600);
  pinMode(6, INPUT);
  pinMode(7, INPUT);

}
void loop() {
 
button = digitalRead(7);
 if ((button == HIGH) && (SWITCH == LOW)){
   gsmSerial.println("ATD+ +911234567890;"); // enter your mobile no here
    delay(10000);
    gsmSerial.println("ATH");
 }
   
SWITCH = digitalRead(6);
 if ((SWITCH == HIGH) && (button == LOW)){
   while (gpsSerial.available() > 0){ 
      if (gps.encode(gpsSerial.read())) {
        if (gps.location.isValid()) {
          gsmSerial.println("AT+CMGF=1");
          gsmSerial.println("AT+CMGS=\"+911234567890\"");
          gsmSerial.print(gps.location.lat(), 6);
          gsmSerial.print(" ");
          gsmSerial.print(gps.location.lng(), 6);
          gsmSerial.write(26);
          delay(5000);
           }
      if (gps.date.isValid()){
         gsmSerial.println("AT+CMGF=1");
         gsmSerial.println("AT+CMGS=\"+911234567890\"");
        gsmSerial.print(gps.date.day());
        gsmSerial.print("/");
        gsmSerial.print(gps.date.month());
        gsmSerial.print("/");
        gsmSerial.print(gps.date.year());
        
        delay(5000);
      }

 }
}
}
}
   
  

  
