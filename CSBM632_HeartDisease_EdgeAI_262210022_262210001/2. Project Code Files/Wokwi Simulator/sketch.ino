#include "model.h" 
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

String apiKey = "846Q12CTJ2MMIXZZ";

// Initialize the Logistic Regression machine learning model object
Eloquent::ML::Port::LogisticRegression classifier;

void setup() {

  Serial.begin(115200);

  Serial.println("ESP32 Edge ML Initialization Complete.");

  // Connect to WiFi
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting Heart Disease Prediction...");
  Serial.println();
}


void loop() {
  // Array of 13 features in the exact order your model was trained on
  float patient_vitals[13] = {
    62.0,            // age
    1.0,             // sex
    1.0,             // cp
    (float)random(110, 160), // trestbps (Simulated dynamic Blood Pressure)
    230.0,           // chol
    0.0,             // fbs
    1.0,             // restecg
    (float)random(100, 175), // thalach (Simulated dynamic Heart Rate)
    0.0,             // exang
    1.4,             // oldpeak
    1.0,             // slope
    0.0,             // ca
    2.0              // thal
  };

  // Call predict() on the Logistic Regression classifier object
  int prediction = classifier.predict(patient_vitals);

  // Print results to the Wokwi Serial Monitor
  Serial.print("Sensors -> BP: ");
  Serial.print(patient_vitals[3]);
  Serial.print(" | HR: ");
  Serial.print(patient_vitals[7]);
  Serial.print(" ---> Diagnosis: ");

  if (prediction == 1) {
    Serial.println("ALERT (1): Defective Heart Risk");
  } else {
    Serial.println("NORMAL (0): Healthy Heart");
  }
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    String serverPath =
        "http://api.thingspeak.com/update?api_key=" +
        apiKey +
        "&field1=" + String(patient_vitals[3]) +
        "&field2=" + String(patient_vitals[7]) +
        "&field3=" + String(prediction);

    http.begin(serverPath);

    int httpResponseCode = http.GET();

    Serial.print("ThingSpeak Response Code: ");
    Serial.println(httpResponseCode);

    http.end();
}

  // Wait 5 seconds before the next reading
  delay(5000);
}