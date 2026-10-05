#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// Pin Definitions
#define LED 2

// Motor Driver Pins
#define ENA 14
#define ENB 32
#define IN1 27
#define IN2 26
#define IN3 25
#define IN4 33
#define HUMIDITY 15
#define INFRARED 13

// I2C Pins (Default ESP32)
#define OLED_SDA 21
#define OLED_SCL 22

// Analog Input (ADC1 pin required when Wi-Fi/I2C active)
#define MQ_ANALOG 34 
#define MQ2_ANALOG 35

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

int MQ_Val, MQ2_Val, Humid_Val, Infra_Val = 0;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void updateOLED(int val, int val2) {
  display.clearDisplay();
  
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  
  display.setCursor(0, 10);
  display.print("Value:");

  display.setCursor(0, 35);
  display.print(val);
  display.print(" , ");
  display.print(val2);

  display.display();
}

void setup() {
  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(MQ_ANALOG, INPUT);
  pinMode(MQ2_ANALOG, INPUT);
  pinMode(HUMIDITY, INPUT);
  pinMode(INFRARED, INPUT);

  // Initialize Wire with Dedicated I2C Pins (21 & 22)
  Wire.begin(OLED_SDA, OLED_SCL);

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Stop execution
  }
  Serial.println(F("SSD1306 allocation success"));

  updateOLED(0, 0);
}

void loop() {
  // Read MQ Sensor
  MQ_Val = analogRead(MQ_ANALOG);
  MQ2_Val = analogRead(MQ2_ANALOG);
  Humid_Val = analogRead(HUMIDITY);
  Infra_Val = analogRead(INFRARED);

  Serial.println(MQ_Val);
  Serial.println(MQ2_Val);
  Serial.print("HUMIDITY : ");
  Serial.println(Humid_Val);
  Serial.println(Infra_Val);
  

  // Update Display with Live Sensor Value
  updateOLED(MQ_Val, MQ2_Val);

  // Blink LED
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
}