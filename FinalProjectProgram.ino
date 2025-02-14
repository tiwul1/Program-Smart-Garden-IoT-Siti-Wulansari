#include "header.h"

void setup() {
  Serial.begin(115200);
  splashScreenOled();
  sht20.begin();
  ldr.begin();
  initDistanceSensor();
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(RELAY, LOW); // memastikan pompa mati saat awal program

  clientMQTT.connect_to_AP(ssid, password);
  clientMQTT.init_to_broker(mqttServer, mqttPort);
  clientMQTT.connect_to_broker(myClientID, MQTTUser, MQTTPass);
  clientMQTT.mqtt_subscribe(TopicSub);
}

void loop() {
 clientMQTT.rxMessFrBroker();
 if(callBackTopic == TopicSub){
  fltCallBackPayload = callBackPayload.toFloat();
 }

  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval){
    // Read sensor
    temperature = sht20.readTemperature();
    humidity = sht20.readHumidity();
    intensitas = ldr.readIntensitas();
    soilMoisturePercent = readSoilMoisture();
    distance = readDistance();

    // Convert to JSON
    doc["temp"] = temperature;
    doc["hum"] = humidity;
    doc["inten"] = intensitas;
    doc["soil"] = soilMoisturePercent;
    doc["distan"] = distance;

    // Serializasikan objek JSON ke dalam string JSON
    jsonPayload = ""; // Riset Payload jsonPayload
    serializeJson(doc, jsonPayload);
    clientMQTT.mqtt_publish(Topic, String(jsonPayload));

    displayMeassuring(temperature, humidity, intensitas, soilMoisturePercent, distance);
    display.clearDisplay();
    previousMillis = currentMillis;
  }
  else{
    // Action
    if(distance > 50){
      digitalWrite(BUZZER, HIGH);
    }
    else{
      digitalWrite(BUZZER, LOW);
    }
    // Action based on soil moisture
    if(soilMoisturePercent < 40 || fltCallBackPayload == 1){
      //mengubah nilai relay kebalikannya
      digitalWrite(RELAY, HIGH); 
    }
    else{
      //mengubah nilai relay kebalikannya
      digitalWrite(RELAY, LOW);
    }
  }
}
