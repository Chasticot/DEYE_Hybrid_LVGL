#include "lv_conf.h"
#include <Arduino_GFX_Library.h>
#include <lvgl.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <ETH.h>
#include <ModbusIP_ESP8266.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include <RemoteDebug.h>
#include <ArduinoOTA.h>
#include <Preferences.h>
#include <ESPmDNS.h>
#include "time.h"

// Configuration Ethernet
#define ETH_ADDR 1
#define ETH_POWER_PIN 16
#define ETH_MDC_PIN 23
#define ETH_MDIO_PIN 18
#define ETH_TYPE ETH_PHY_LAN8720
#define ETH_CLK_MODE ETH_CLOCK_GPIO17_OUT

// Configuration Modbus
ModbusIP mb;
const int DEYE_PORT = 502;
IPAddress deyeIP(192, 168, 1, 100); // À configurer

// Configuration NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

// Configuration LVGL
Arduino_DataBus *bus = new Arduino_SWSPI(
  GFX_NOT_DEFINED, 39, 48, 47, GFX_NOT_DEFINED);
Arduino_ESP32RGBPanel *rgbpanel = new Arduino_ESP32RGBPanel(
  18, 17, 16, 21, 11, 12, 13, 14, 0, 8, 20, 3, 46, 9, 10, 4, 5, 6, 7, 15,
  1, 10, 8, 50, 1, 10, 8, 20);
Arduino_RGB_Display *gfx = new Arduino_RGB_Display(
  480, 480, rgbpanel, 0, true, bus, GFX_NOT_DEFINED, st7701_type9_init_operations, 
  sizeof(st7701_type9_init_operations));

// Variables globales
struct DeyeData {
  float gridPower;
  float pvPower;
  float batteryPower;
  float batterySOC;
  float dailyProduction;
  float dailyConsumption;
  float dailyGridConsumption;
  float mppt1Power;
  float mppt2Power;
};

DeyeData deyeData;
String weatherInfo;
String tempoColorToday;
String tempoColorTomorrow;
int tempoDayToday;
int tempoDayTomorrow;

#include "touch.h"
#include "ui_Main.h"
#include "ui_Details.h"
#include "ui_Parameters.h"

void setup() {
  Serial.begin(115200);
  
  // Initialisation Ethernet
  ETH.begin(ETH_ADDR, ETH_POWER_PIN, ETH_MDC_PIN, ETH_MDIO_PIN, ETH_TYPE, ETH_CLK_MODE);
  
  // Initialisation LVGL
  lv_init();
  if (!gfx->begin()) {
    Serial.println("gfx->begin() failed!");
  }
  gfx->fillScreen(BLACK);
  touch_init();
  
  // Configuration WiFi/NTP
  setupWiFi();
  timeClient.begin();
  timeClient.setTimeOffset(3600); // UTC+1
  
  // Initialisation Modbus
  mb.client();
  
  // Création des écrans
  createMainScreen();
  createDetailsScreen();
  createParametersScreen();
  
  // OTA
  ArduinoOTA.begin();
}

void loop() {
  lv_timer_handler();
  updateDeyeData();
  updateWeather();
  updateTempo();
  delay(5);
}

void setupWiFi() {
  // Configuration WiFi depuis les préférences
  Preferences prefs;
  prefs.begin("DeyeConfig", true);
  String ssid = prefs.getString("ssid", "");
  String password = prefs.getString("password", "");
  prefs.end();
  
  WiFi.begin(ssid.c_str(), password.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}

void updateDeyeData() {
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate < 5000) return; // Mise à jour toutes les 5s
  
  // Lecture des registres Modbus
  uint16_t regs[20];
  if (mb.readHreg(deyeIP, 0, regs, 20)) {
    deyeData.gridPower = regs[0] / 10.0; // Registre 0 - Puissance réseau
    deyeData.pvPower = regs[1] / 10.0;   // Registre 1 - Puissance PV totale
    deyeData.batteryPower = regs[2] / 10.0; // Registre 2 - Puissance batterie
    deyeData.batterySOC = regs[3];       // Registre 3 - SOC batterie
    deyeData.dailyProduction = regs[4] / 10.0; // Registre 4 - Production journalière
    deyeData.dailyConsumption = regs[5] / 10.0; // Registre 5 - Consommation journalière
    deyeData.dailyGridConsumption = regs[6] / 10.0; // Registre 6 - Consommation réseau
    deyeData.mppt1Power = regs[7] / 10.0; // Registre 7 - MPPT 1
    deyeData.mppt2Power = regs[8] / 10.0; // Registre 8 - MPPT 2
  }
  
  lastUpdate = millis();
  updateMainScreen();
}

void updateWeather() {
  // Implémentation à compléter avec OpenWeather API
}

void updateTempo() {
  // Implémentation à compléter avec API Tempo EDF
}