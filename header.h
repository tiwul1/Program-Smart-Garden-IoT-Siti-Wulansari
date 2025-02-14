#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Edspert_sht20.h>
#include <EdspertPubSub.h>
#include <LDR.h>
#include <ArduinoJson.h>

//====== JSON Declaration ======//
StaticJsonDocument<200> doc;
String jsonString, jsonPayload;

//====== Connection Declaration ======//
// Wifi Setting
char* ssid = "NAMA_WIFI";
char* password = "PASSWORD_WIFI";

// Broker Setting
String MQTTUser = "";
String MQTTPass = "";

// MQTT Setting
char *mqttServer = "127.0.0.1";
int mqttPort = 1883;
String myClientID = "Device1";
String Topic_1 = "edspert/data/temp";
String Topic_2 = "edspert/data/hum";
String Topic_3 = "edspert/data/inten";
String Topic_4 = "edspert/data/soil";
String Topic_5 = "edspert/data/distance";

String Topic = "edspert/data/sensor/wulan";
extern String callBackPayload; // Variabel untuk menerima Payload dari callback
extern String callBackTopic; // Variabel untuk menerima Topic dari callback
EdspertPubSub clientMQTT;

//===== OLED LCD Declaration ======//
#define SCREEN_WIDTH 128 // OLED displays width, in pixles
#define SCREEN_HEIGHT 64 // OLED display hegight, in pixels

// Decdlaration for SSD1306 display connected to I2C (SDA< SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//====== SHT Declaration ======//
HardwareSerial serial(2);
Edspert_sht20 sht20(&serial, 9600, 16, 17);

//====== LDR Declaration ======//
#define pinLDR 35
LDR ldr(pinLDR);

//====== Soil Moisture Declaration ======//
#define pinSOIL 34

//====== Distance Sensor ======//
#define ECHOPIN 13
#define TRIGPIN 12

float temperature, humidity, intensitas, soilMoisturePercent, distance;

//======  Relay Declaration  ======//
#define RELAY 4

//======  Buzzer Declaration  ======//
#define BUZZER 27

String TopicSub = "edspert/data/pump/wulan";
unsigned long previousMillis = 0; // Waktu sejak terakhir kali melakukan sesuatu
const long interval = 5000;  // Interval yg diinginkan dalam milidetik (3 detik)
float fltCallBackPayload = 0;
