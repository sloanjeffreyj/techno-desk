#include <iostream>
#include <string>
#include <math.h>
#include <FastLED.h>
#include "customPalettes.h"
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <SerLCD.h>
#include <WiFi.h>
#include <TimeLib.h>

// LED Define
#define LED_TYPE APA102
#define NUM_LEDS 60
#define COLOR_ORDER BGR
#define MASTER_BRIGHTNESS 64
#define UPDATES_PER_SECOND 100
#define DATA_PIN 14
#define CLOCK_PIN 32
#define voltagePin 12

SerLCD lcd;
HTTPClient http;

//Wifi information
const char* ssid = "MVHS-AV 2.4G";
const char* wifiPassword = "MVHS0409";

// API information.
const String endpoint = "http://api.openweathermap.org/data/2.5/weather?q=Phoenix,AZ,pt&APPID=";
const String key = "";
const String unitRequest = "&units=imperial";

// Used to display weather information
int weatherSelectPin = 33;
int weatherVolt = 0;
int weatherSwitchPosition = -1;

// Reads input from LED rotary switch.
int colorSwitchPin = A4;
// Outputs voltage to both rotary switches.
int rotaryVoltInputPin = 21;
// analogRead() from color rotary switch to determine position.
int colorVolt = 0;
// Used to keep blocks of code from rerunning if rotary switch has not changed position.
int colorSwitchPosition = -1;
int intensityValue = 0;

uint8_t min_brightness = 0;
uint8_t brightness;
CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
TBlendType currentBlending;
// Static lights, no motion.
static uint8_t startIndex = 0;

// Used to store date/time.
char sunsetTimeBuff[32];
char sunriseTimeBuff[32];

unsigned long offset_days = 3;  // 3 days
unsigned long t_unix_date1, t_unix_date2;

DynamicJsonDocument doc(5000);

void setup() {
  Serial.begin(115200);
  pinMode(voltagePin, OUTPUT);
  digitalWrite(voltagePin, HIGH);
  pinMode(rotaryVoltInputPin, OUTPUT);
  digitalWrite(rotaryVoltInputPin, HIGH);

  FastLED.addLeds<LED_TYPE, DATA_PIN, CLOCK_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(MASTER_BRIGHTNESS);

  currentBlending = NOBLEND;

  Wire.begin();

  lcd.begin(Wire);
  lcd.setBacklight(255, 255, 255);
  lcd.setContrast(5);
  lcd.clear();
  lcd.print("Sup homies! :)");


  WiFi.begin(ssid, wifiPassword);
  Serial.println("Connecting to wifi...");  // DEBUG
  // DEBUG
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
  }
  
  // DEBUG
  Serial.println("Wifi connected");

  // Call to weather API.
  http.begin(endpoint + key + unitRequest);
  int httpCode = http.GET();

  if (httpCode > 0) {
    String payload = http.getString();

    deserializeJson(doc, payload);

    Serial.print("http code: ");
    Serial.println(httpCode);
    Serial.print("payload: ");
    Serial.println(payload);
    Serial.print("The weather is: ");
    String message = doc["weather"][0]["main"];
    Serial.println(message);
    // Serial.println();
  } else {
    Serial.println("Error");
  }

  int sunsetTime = doc["sys"]["sunset"];
  sunsetTime = sunsetTime - 25200;
  sprintf(sunsetTimeBuff, "%02d:%02d", hourFormat12(sunsetTime), minute(sunsetTime));

  int sunriseTime = doc["sys"]["sunrise"];
  sunriseTime = sunriseTime - 25200;
  sprintf(sunriseTimeBuff, "%02d:%02d", hourFormat12(sunriseTime), minute(sunriseTime));
}

void checkWeatherSwitchPosition(int weatherVolt, int lastSwitchPosition) {
  // Select weather information.
  if (weatherVolt >= 0 && weatherVolt < 200 && weatherSwitchPosition != 0) {
    weatherSwitchPosition = 0;
    lcd.clear();
    lcd.print("Welcome");
    lcd.setCursor(0, 1);
    lcd.print("Master Camryn");
    lcd.setFastBacklight(0x000aff);
  }
  if (weatherVolt > 201 && weatherVolt < 600 && weatherSwitchPosition != 1) {
    weatherSwitchPosition = 1;
    lcd.clear();
    lcd.print("Mesa,AZ");
    lcd.setCursor(0, 1);
    const char* weatherStringTwo = doc["weather"][0]["description"];
    lcd.print(weatherStringTwo);
    lcd.setFastBacklight(0xf8ff01);
  }
  if (weatherVolt > 601 && weatherVolt < 1050 && weatherSwitchPosition != 2) {
    weatherSwitchPosition = 2;
    lcd.clear();
    int weatherStringOne = doc["main"]["temp_min"];
    lcd.print("Temp min:");
    lcd.print(weatherStringOne);
    lcd.setCursor(0, 1);
    int weatherStringTwo = doc["main"]["temp_max"];
    lcd.print("Temp max:");
    lcd.print(weatherStringTwo);
    lcd.setFastBacklight(0x2aea2d);
  }
  if (weatherVolt > 1051 && weatherVolt < 1450 && weatherSwitchPosition != 3) {
    weatherSwitchPosition = 3;
    lcd.clear();
    int weatherStringOne = doc["main"]["feels_like"];
    lcd.print("Feels like:");
    lcd.print(weatherStringOne);
    lcd.setCursor(0, 1);
    int weatherStringTwo = doc["main"]["humidity"];
    lcd.print("Humidity:");
    lcd.print(weatherStringOne);
    lcd.setFastBacklight(0xff0106);
  }
  if (weatherVolt > 1510 && weatherVolt < 2010 && weatherSwitchPosition != 4) {
    weatherSwitchPosition = 4;
    lcd.clear();
    lcd.print("Wind Speed:");
    float weatherStringOne = doc["wind"]["speed"];
    lcd.setCursor(0, 1);
    lcd.print(weatherStringOne);
    lcd.print("MPH");
    lcd.setFastBacklight(0xff9001);
  }
  if (weatherVolt > 2150 && weatherVolt < 2250 && weatherSwitchPosition != 5) {
    weatherSwitchPosition = 5;
    lcd.clear();
    lcd.print("Sunrise:");
    lcd.setCursor(0, 1);
    lcd.print(sunriseTimeBuff);
    lcd.print("AM");
    lcd.setFastBacklight(0x01f9ff);
  }
  if (weatherVolt > 2510 && weatherVolt < 2710 && weatherSwitchPosition != 6) {
    weatherSwitchPosition = 6;
    lcd.clear();
    lcd.print("Sunset:");
    lcd.setCursor(0, 1);
    lcd.print(sunsetTimeBuff);
    lcd.print("PM");
    lcd.setFastBacklight(0x9e01ff);
  }
  if (weatherVolt > 2980 && weatherVolt < 3180 && weatherSwitchPosition != 7) {
    weatherSwitchPosition = 7;
    lcd.clear();
    lcd.print("what is up?");
    lcd.setFastBacklight(0xff5b01);
  }
  if (weatherVolt > 3570 && weatherVolt < 3770 && weatherSwitchPosition != 8) {
    weatherSwitchPosition = 8;
    lcd.clear();
    lcd.print("Nothing much you?");
    lcd.setFastBacklight(0xff01f5);
  }
  if (weatherVolt > 4000 && weatherSwitchPosition != 9) {
    weatherSwitchPosition = 9;
    lcd.clear();
    lcd.print("Same. Later loser");
    lcd.setFastBacklight(0x01ff88);
  }
  if (lastSwitchPosition != weatherSwitchPosition) {
    Serial.print("Position ");
    Serial.println(weatherSwitchPosition);
    Serial.print("weatherVolt: ");
    Serial.println(weatherVolt);
  }
}

void checkColorSwitchPosition(int colorVolt, int switchPosition) {
  if (colorVolt >= 0 && colorVolt < 200 && switchPosition != 0) {
    colorSwitchPosition = 0;
    currentPalette = White_p;
    currentBlending = NOBLEND;
    startIndex = 0;
    startIndex = startIndex + 1;
    FillLEDsFromPaletteColors(startIndex);
    FastLED.show();
  };
  if (colorVolt > 250 && colorVolt < 500 && switchPosition != 1) {
    colorSwitchPosition = 1;
    currentPalette = Red_p;
    currentBlending = NOBLEND;
    startIndex = 0;
    startIndex = startIndex + 1;
    FillLEDsFromPaletteColors(startIndex);
    FastLED.show();
  };
  if (colorVolt > 500 && colorVolt < 950 && switchPosition != 2) {
    colorSwitchPosition = 2;
    currentPalette = Orange_p;
    currentBlending = NOBLEND;
    startIndex = 0;
    startIndex = startIndex + 1;
    FillLEDsFromPaletteColors(startIndex);
    FastLED.show();
  };
  if (colorVolt > 950 && colorVolt < 1350 && switchPosition != 3) {
    colorSwitchPosition = 3;
    currentPalette = Yellow_p;
    currentBlending = NOBLEND;
    startIndex = 0;
    startIndex = startIndex + 1;
    FillLEDsFromPaletteColors(startIndex);
    FastLED.show();
  };
  if (colorVolt > 1410 && colorVolt < 1810 && switchPosition != 4) {
    colorSwitchPosition = 4;
    currentPalette = Green_p;
    currentBlending = NOBLEND;
    startIndex = 0;
    startIndex = startIndex + 1;
    FillLEDsFromPaletteColors(startIndex);
    FastLED.show();
  };
  if (colorVolt > 1810 && colorVolt < 2250 && switchPosition != 5) {
    colorSwitchPosition = 5;
    currentPalette = Blue_p;
    currentBlending = NOBLEND;
    startIndex = 0;
    startIndex = startIndex + 1;
    FillLEDsFromPaletteColors(startIndex);
    FastLED.show();
  };
  if (colorVolt > 2250 && colorVolt < 2710 && switchPosition != 6) {
    colorSwitchPosition = 6;
    currentPalette = Purple_p;
    currentBlending = NOBLEND;
    startIndex = 0;
    startIndex = startIndex + 1;
    FillLEDsFromPaletteColors(startIndex);
    FastLED.show();
  };
  if (colorVolt > 2780 && colorVolt < 3180) {
    colorSwitchPosition = 7;
    currentPalette = Villains_p;
    currentBlending = NOBLEND;
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1;
    FillLEDsFromPaletteColors(startIndex);
    FastLED.show();
  };
  if (colorVolt > 3180 && colorVolt < 3770) {
    colorSwitchPosition = 8;
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1;
    FillLEDsFromPaletteColors(startIndex);
    FastLED.show();
  };
  if (colorVolt > 4000) {
    colorSwitchPosition = 9;
    currentPalette = CloudyDays_p;
    currentBlending = LINEARBLEND;
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1;
    FillLEDsFromPaletteColors(startIndex);
    FastLED.show();
  };
};

void FillLEDsFromPaletteColors(uint8_t colorIndex) {
  uint8_t brightness = 225;
  for (int i = 0; i < NUM_LEDS; ++i) {
    leds[i] = ColorFromPalette(currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}

int roundNearestEight(int inputNumber) {
  inputNumber++;

  // To prevent flickering at the lowest intensity, if within certain range set to first brightness step.
  if (inputNumber < 300 && inputNumber > 250) {
    inputNumber = 256;
  }
  inputNumber = (inputNumber / 256) * 256;
  return inputNumber;
}

void loop() {
  colorVolt = analogRead(colorSwitchPin);
  checkColorSwitchPosition(colorVolt, colorSwitchPosition);
  //  Serial.println(colorVolt);
  //  Serial.println(colorSwitchPosition);
  //  Serial.println(intensityValue);

  int voltage = analogRead(A3);
  Serial.println(analogRead(A3));
  voltage = roundNearestEight(voltage);
  intensityValue = voltage / 64;

  FastLED.setBrightness(intensityValue);
  FastLED.delay(1000 / UPDATES_PER_SECOND);

  weatherVolt = analogRead(weatherSelectPin);
  checkWeatherSwitchPosition(weatherVolt, weatherSwitchPosition);
  // Serial.println(weatherVolt);
  // Serial.println(weatherSwitchPosition);
}
