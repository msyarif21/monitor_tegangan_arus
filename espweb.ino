#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
int tegangan;

const char* ssid = "OPPO A54";
const char* password = "inisarip123";
// Your Domain name with URL path or IP address with path
String serverName = "http:/192.168.140.51/MonitorKonsumsiEnergi/index.php";

// The following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

const int voltage_sensor = 35;
float voltage_sensor_raw;
float v_beban;

void setup() {
  Serial.begin(115200); 
  pzeem();

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  // Send an HTTP GET request every 5 seconds
  if ((millis() - lastTime) > timerDelay) {
    // Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      //int tegangan;
      pzeem();
      Serial.println(tegangan);
      String serverPath = serverName + "?sensor=" + String(tegangan);
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());
      
      // If you need Node-RED/server authentication, insert user and password below
      // http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

void pzeem() {
   
  // put your main code here, to run repeatedly:
  baca_sensor();
  acs();
  
  Serial.print ("Voltage : ");
  Serial.println (v_beban);
  delay (2000);


}
void acs(){
  int adc = analogRead(34);
  float voltage = adc*5/1023.0;
  float current = (voltage-2.5)/0.185;
  Serial.print("Current : ");
  Serial.println(current);
  delay(300);
  }
void baca_sensor()
{
  voltage_sensor_raw = analogRead(voltage_sensor);
  v_beban = map (voltage_sensor_raw,0,1023,0,2500);
  v_beban = v_beban/100;
  }
