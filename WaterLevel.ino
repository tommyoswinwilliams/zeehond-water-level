#include <TimeLib.h>

// Readings buffer
const int numReadings = 10;
int readings[numReadings];  // the readings from the analog input
int buffer = 5;              // the running total buffer
int notificationTime = now() - 21600; // last notification time

void setup() {
  Serial.begin(9600);
  pinMode(5,INPUT);
  Serial.print("Setup Complete");
}

void loop() {
  digitalRead(5) == 0 ? buffer -- : buffer ++;
  Serial.print("Liquid_level= ");
  Serial.println(digitalRead(5),DEC);

  if (buffer > 10) {
    buffer = 10;
  }
  if (buffer < 0) {
    buffer = 0;
  }

  Serial.println(buffer,DEC);
  
  if(buffer == 0) {
    Serial.print((now() - notificationTime));
    if ((now() - notificationTime) > 21600) { 
      Serial.print("Webhook Called");
      webhook();
      notificationTime = now(); // Store the current time in notificationTime
      Serial.print((notificationTime));
    }
  }

  if ((now() - notificationTime) > 21600) { 
    Serial.print((now() - notificationTime));
    Serial.print("Webhook Water Check Called");
    webhookWaterCheck();
    notificationTime = now(); // Store the current time in notificationTime
    Serial.print((notificationTime));
  }
  
  delay(300000);
  // delay(5000);
}
