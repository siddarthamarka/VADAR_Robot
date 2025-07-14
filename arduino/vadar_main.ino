#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <Servo.h>

#define TRIG_PIN 9
#define ECHO_PIN 8
#define GSM_TX 10
#define GSM_RX 11
#define GPS_RX 4
#define GPS_TX 3
#define THRESHOLD 20

TinyGPSPlus gps;
SoftwareSerial ss_gps(GPS_RX, GPS_TX);
SoftwareSerial gsm(GSM_TX, GSM_RX);
Servo ultrasonicServo;

long readUltrasonicDistance() {
  digitalWrite(TRIG_PIN, LOW); delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  return pulseIn(ECHO_PIN, HIGH) * 0.034 / 2;
}

void sendSMS(String locationURL) {
  gsm.println("AT+CMGF=1"); delay(1000);
  gsm.println("AT+CMGS=\"+91xxxxxxxxxx\""); delay(1000);
  gsm.print("Accident detected! Location: "); gsm.print(locationURL);
  gsm.write(26);
}

void setup() {
  Serial.begin(9600);
  ss_gps.begin(9600);
  gsm.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  ultrasonicServo.attach(6);
  ultrasonicServo.write(90);
}

void loop() {
  long distance = readUltrasonicDistance();
  if (distance <= THRESHOLD) {
    float lat = 0.0, lon = 0.0;
    unsigned long start = millis();
    while (millis() - start < 3000) {
      while (ss_gps.available()) {
        gps.encode(ss_gps.read());
        if (gps.location.isUpdated()) {
          lat = gps.location.lat();
          lon = gps.location.lng();
        }
      }
    }

    String googleMapsURL = "https://maps.google.com/?q=" + String(lat, 6) + "," + String(lon, 6);
    sendSMS(googleMapsURL);
    delay(20000);  // Wait before next check
  }
}
