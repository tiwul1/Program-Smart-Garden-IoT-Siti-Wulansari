
float readSoilMoisture(){ // sensor 1 Soil
  int soil = analogRead(pinSOIL);
  float soilMoisture = map(soil, 4095, 0, 0, 100);
  return soilMoisture;
}

void initDistanceSensor(){ // sensor 2 Distan
  pinMode(ECHOPIN, INPUT_PULLUP);
  pinMode(TRIGPIN, OUTPUT);
  digitalWrite(ECHOPIN, HIGH);
}

float readDistance(){ // sensor 2 Distan
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(15);
  digitalWrite(TRIGPIN, LOW);
  float distance1 = pulseIn(ECHOPIN, HIGH, 26000);
  float ret_distance = distance1/58;
  return ret_distance;
}

void splashScreenOled(){ // output 3 OLED LCD SSD1306
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){ // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(500);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(25, 20);
  display.println("EDSPERT"); // Display static text
  display.setCursor(20,40);
  display.println("BOOTCAMP");
  display.display();
  delay(5000);
  display.clearDisplay();
}

void displayMeassuring(float a, float b, float c, float d, float e){
  display.setTextSize(1.2);
  display.setTextColor(WHITE);
  display.setCursor(15, 5);
  display.println("Nilai Parameter"); // Display static text

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 18);
  display.print("Temp   : ");
  display.print(a);
  display.print(" ");
  display.print((char)247);
  display.println("C");

  display.setCursor(10, 27);
  display.print("Hum    : ");
  display.print(b);
  display.println(" %");

  display.setCursor(10, 36);
  display.print("Inten  : ");
  display.print(c);
  display.println(" Lx");

  display.setCursor(10, 45);
  display.print("Soil   : ");
  display.print(d);
  display.println(" %");

  display.setCursor(10, 54);
  display.print("Distan : ");
  display.print(e);
  display.println(" cm");

  display.display();
}