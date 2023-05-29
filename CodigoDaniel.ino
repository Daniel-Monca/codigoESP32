//Paso 1
#include <WiFi.h>
#include <ESP32Servo.h> 

#include <FirebaseESP32.h>

const char* ssid = "IDSS";
const char* password = "password";

const char* firebaseHost = "https://xxxxxxxxxxxxxxxxxxxxxxxxxxx.firebaseio.com/";
const char* firebaseAuth = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

Servo myservo; 
int pos = 0;

FirebaseData firebaseData;

void setup() {
  myservo.attach(13);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando a Wi-Fi...");
  }
  Serial.println("Conectado a Wi-Fi.");
  
  Firebase.begin(firebaseHost, firebaseAuth);
}

void loop() {
  if (Firebase.get(firebaseData, "/ESP32")) {
    if (firebaseData.dataType() == "string") {
      String value = firebaseData.stringData();
      Serial.print("Valor obtenido: ");
      Serial.println(value);
      if(value == "1"){
        for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(15);                       // waits 15ms for the servo to reach the position
        }
        delay(61000);

        for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(15);                       // waits 15ms for the servo to reach the position
        }
      }
      
    }
  }
 
  delay(1000);
}
