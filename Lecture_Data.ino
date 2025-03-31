#include <WiFiClient.h>
#include <HTTPClient.h>

void fetchDeyeData() {
  if (WiFi.status() != WL_CONNECTED) return;

  HTTPClient http;
  String url = "http://" + deyeIP.toString() + "/api/realTimeData";
  
  http.begin(url);
  int httpCode = http.GET();
  
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    
    deyeData.gridPower = doc["grid_power"];
    deyeData.pvPower = doc["pv_power"];
    deyeData.batteryPower = doc["battery_power"];
    deyeData.batterySOC = doc["battery_soc"];
    deyeData.dailyProduction = doc["daily_production"];
    deyeData.dailyConsumption = doc["daily_consumption"];
    deyeData.dailyGridConsumption = doc["daily_grid_cons"];
    deyeData.mppt1Power = doc["mppt1_power"];
    deyeData.mppt2Power = doc["mppt2_power"];
  }
  
  http.end();
}

void fetchWeatherData() {
  HTTPClient http;
  String apiKey = "YOUR_API_KEY";
  String location = "Paris,FR";
  String url = "http://api.openweathermap.org/data/2.5/weather?q=" + location + "&appid=" + apiKey + "&units=metric";
  
  http.begin(url);
  int httpCode = http.GET();
  
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    
    float temp = doc["main"]["temp"];
    float humidity = doc["main"]["humidity"];
    String description = doc["weather"][0]["description"];
    
    weatherInfo = String(temp, 1) + "°C " + description + " " + String(humidity) + "%";
  }
  
  http.end();
}

void fetchTempoData() {
  HTTPClient http;
  String url = "https://www.api-couleur-tempo.fr/api/joursTempo";
  
  http.begin(url);
  int httpCode = http.GET();
  
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    DynamicJsonDocument doc(512);
    deserializeJson(doc, payload);
    
    tempoColorToday = doc["today"]["color"];
    tempoDayToday = doc["today"]["day"];
    tempoColorTomorrow = doc["tomorrow"]["color"];
    tempoDayTomorrow = doc["tomorrow"]["day"];
  }
  
  http.end();
}