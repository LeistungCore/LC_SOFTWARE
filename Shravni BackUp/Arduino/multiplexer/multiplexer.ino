#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

// Wi-Fi credentials
const char* ssid = "CCSPL";     // Wi-Fi name
const char* password = "CCSPL@123";    // Wi-Fi password

// ThingSpeak Settings
unsigned long channelIDDaily = 2881821;    // Replace with your ThingSpeak Daily Channel ID
const char * writeAPIKeyDaily = "SK07FLNJHK0JG02G";    // Daily Write API Key
unsigned long channelIDMonthly = 2881821;    // Replace with your ThingSpeak Monthly Channel ID
const char * writeAPIKeyMonthly = "SK07FLNJHK0JG02G";    // Monthly Write API Key


// Static IP configuration
IPAddress local_IP(192, 168, 7, 100);  // Static IP address (change as needed)
IPAddress gateway(192, 168, 7, 1);     // Router gateway address (usually your router's IP)
IPAddress subnet(255, 255, 255, 0);    // Subnet mask
IPAddress dns(8, 8, 8, 8);             // DNS server (optional, Google DNS used here)

// Define multiplexer control pins (3 control pins for 74HC4051)
const int MUX_S0 = D5;
const int MUX_S1 = D6;
const int MUX_S2 = D7;
const int muxOut = A0;  // Multiplexer output pin connected to A0 on ESP8266

// Define pins for switch and other logic
const int switchPin = D1;         // Pin for switch status (example)
int productionCount = 0;          // Production count (number of beads)
unsigned long powerOnTime = 0;    // Power on time
unsigned long arcOnTime = 0;      // Arc on time
unsigned long idleTime = 0;       // Idle time

// Constants for scaling ADC value to voltage
const float ADC_MAX = 1023.0;      // Maximum ADC value
const float V_REF = 3.3;           // Reference voltage (1V for ESP8266)

float weldCurrent = 0.0;          // Weld current
float weldVoltage = 0.0;          // Weld voltage
float energyConsumption = 0.0;    // Energy consumption (Watt-hours)
float gasConsumption = 0.0;       // Gas consumption (example data)
bool switchStatus = false;        // Switch status (on/off)
String ipAddress = "";            // Variable to store IP address

// Create an AsyncWebServer object on port 80
AsyncWebServer server(80);

WiFiClient client;

// Function to select the MUX channel
void selectMuxChannel(int channel) {
  digitalWrite(MUX_S0, (channel & 1) ? HIGH : LOW);
  digitalWrite(MUX_S1, (channel & 2) ? HIGH : LOW);
  digitalWrite(MUX_S2, (channel & 4) ? HIGH : LOW);
}

// Wi-Fi connection
void setup() {
  Serial.begin(115200);

  // Set static IP configuration
  if (!WiFi.config(local_IP, gateway, subnet, dns)) {
    Serial.println("STA Failed to configure static IP");
  }

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  // Get the IP address after successful connection
  ipAddress = WiFi.localIP().toString();

  // Print the static IP address assigned
  Serial.println("Connected to WiFi");
  Serial.print("Static IP Address: ");
  Serial.println(WiFi.localIP());  // This will be your static IP

  ThingSpeak.begin(client); // Initialize ThingSpeak

  // Set up MUX control pins
  pinMode(MUX_S0, OUTPUT);
  pinMode(MUX_S1, OUTPUT);
  pinMode(MUX_S2, OUTPUT);
  pinMode(switchPin, OUTPUT);  // Set switchPin as OUTPUT for controlling the switch
  digitalWrite(switchPin, LOW);  // Initially, set the machine to OFF


  // Pin setup
  pinMode(switchPin, OUTPUT);  // Set switchPin as OUTPUT for controlling the switch
  digitalWrite(switchPin, LOW);  // Initially, set the machine to OFF

  // Start the web server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<html><head><title>Welding Machine Datalogger</title>";
    html += "<script src='https://cdn.jsdelivr.net/npm/chart.js'></script>";
    html += "<style>";
    html += "body { font-family: Arial, sans-serif; margin: 20px; background-color: black; color: white; display: flex; flex-direction: column; align-items: center; }";
    html += "h1 { text-align: center; margin-bottom: 20px; }";
    html += ".param-container { display: flex; flex-wrap: wrap; justify-content: space-between; gap: 10px; width: 100%; max-width: 1200px; box-sizing: border-box; }";
    html += ".param-box { background-color: #333; padding: 10px; border-radius: 10px; width: 30%; text-align: center; box-sizing: border-box; }";
    html += ".param-box h3 { margin: 5px 0; font-size: 16px; }";
    html += ".param-box span { font-size: 18px; font-weight: bold; color: #00FF00; }";
    html += ".chart-container { display: flex; justify-content: space-between; margin-bottom: 20px; flex-wrap: wrap; width: 100%; max-width: 1200px; }";
    html += ".chart-container canvas { max-width: 48%; max-height: 250px; width: 100%; height: 100%; margin-bottom: 20px; }";
    html += "button { background-color: #4CAF50; color: white; padding: 10px 20px; margin: 10px; border: none; border-radius: 5px; cursor: pointer; }";
    html += "button:hover { background-color: #45a049; }";
    html += "@media (max-width: 768px) { .param-box { width: 45%; } .chart-container canvas { max-width: 100%; } }";
    html += "@media (max-width: 480px) { .param-box { width: 100%; margin-bottom: 10px; } .chart-container canvas { max-width: 100%; } button { width: 100%; } }";
    html += "</style>";
    html += "</head><body>";
    html += "<h1>Welding Machine Datalogger</h1>";

    // Displaying the parameters in boxes side by side
    html += "<div class='param-container'>";
    html += "<div class='param-box'><h3>Production Count</h3><span id='production_count'>" + String(productionCount) + "</span></div>";
    html += "<div class='param-box'><h3>Power On Time</h3><span id='power_on_time'>" + String(powerOnTime) + "</span> seconds</div>";
    html += "<div class='param-box'><h3>Arc On Time</h3><span id='arc_on_time'>" + String(arcOnTime) + "</span> seconds</div>";
    html += "<div class='param-box'><h3>Idle Time</h3><span id='idle_time'>" + String(idleTime) + "</span> seconds</div>";
    html += "<div class='param-box'><h3>Weld Voltage</h3><span id='weld_voltage'>" + String(weldVoltage) + "</span> V</div>";
    html += "<div class='param-box'><h3>Weld Current</h3><span id='weld_current'>" + String(weldCurrent) + "</span> A</div>";
    html += "<div class='param-box'><h3>Energy Consumption</h3><span id='energy_consumption'>" + String(energyConsumption) + "</span> Wh</div>";
    html += "<div class='param-box'><h3>Gas Consumption</h3><span id='gas_consumption'>" + String(gasConsumption) + "</span> units</div>";
    html += "<div class='param-box'><h3>Switch Status</h3><span id='switch_status'>" + String(switchStatus ? "ON" : "OFF") + "</span></div>";
    html += "<div class='param-box'><h3>IP Address</h3><span id='ip_address'>" + ipAddress + "</span></div>";
    html += "</div>";

    // On and Off buttons
    html += "<button onclick='toggleMachine(true)'>ON</button>";
    html += "<button onclick='toggleMachine(false)'>OFF</button>";

    // Chart.js for graphical display
    html += "<div class='chart-container'>";
    html += "<canvas id='weldCurrentChart'></canvas>";
    html += "<canvas id='weldVoltageChart'></canvas>";
    html += "</div>";
    html += "<div class='chart-container'>";
    html += "<canvas id='gasConsumptionChart'></canvas>";
    html += "<canvas id='energyConsumptionChart'></canvas>";
    html += "</div>";

    html += "<script>";

    // Toggle machine function (ON/OFF)
    html += "function toggleMachine(On) {";
    html += "  var xhr = new XMLHttpRequest();";
    html += "  var action = On ? 'on' : 'off';";
    html += "  xhr.open('GET', '/toggle?state=' + action, true);";
    html += "  xhr.send();";
    html += "  xhr.onload = function() {";
    html += "    if (xhr.status == 200) {";
    html += "      document.getElementById('switch_status').innerText = xhr.responseText;";
    html += "    }";
    html += "  };";
    html += "}";

    // Initialize the charts with dummy data (can be replaced with real data)
    html += "var ctx1 = document.getElementById('weldCurrentChart').getContext('2d');";
    html += "var ctx2 = document.getElementById('weldVoltageChart').getContext('2d');";
    html += "var ctx3 = document.getElementById('gasConsumptionChart').getContext('2d');";
    html += "var ctx4 = document.getElementById('energyConsumptionChart').getContext('2d');";

    // Initialize arrays to store data
    html += "var timeLabels = [];";
    html += "var weldCurrentData = [];";
    html += "var weldVoltageData = [];";
    html += "var gasConsumptionData = [];";
    html += "var energyConsumptionData = [];";
    html += "var weldCurrentChart = new Chart(ctx1, {";
    html += "type: 'line',";
    html += "data: { labels: timeLabels, datasets: [{ label: 'Weld Current (A)', data: weldCurrentData, borderColor: 'green', fill: false }] },";

    html += "options: { scales: { x: { type: 'linear', position: 'bottom', title: { display: true, text: 'Time (s)' } }, y: { beginAtZero: true, title: { display: true, text: 'ADC Value' } } } }";
    html += "});";

    html += "var weldVoltageChart = new Chart(ctx2, {";
    html += "type: 'line',";
    html += "data: { labels: timeLabels, datasets: [{ label: 'Weld Voltage (V)', data: weldVoltageData, borderColor: 'blue', fill: false }] },";
    html += "options: { scales: { x: { type: 'linear', position: 'bottom', title: { display: true, text: 'Time (s)' } }, y: { beginAtZero: true, title: { display: true, text: 'ADC Value' } } } }";
    html += "});";

    html += "var gasConsumptionChart = new Chart(ctx3, {";
    html += "type: 'line',";
    html += "data: { labels: timeLabels, datasets: [{ label: 'Gas Consumption', data: gasConsumptionData, borderColor: 'red', fill: false }] },";
    html += "options: { scales: { x: { type: 'linear', position: 'bottom', title: { display: true, text: 'Time (s)' } }, y: { beginAtZero: true, title: { display: true, text: 'ADC Value' } } } }";
    html += "});";

    html += "var energyConsumptionChart = new Chart(ctx4, {";
    html += "type: 'line',";
    html += "data: { labels: timeLabels, datasets: [{ label: 'Energy Consumption (Wh)', data: energyConsumptionData, borderColor: 'yellow', fill: false }] },";
    html += "options: { scales: { x: { type: 'linear', position: 'bottom', title: { display: true, text: 'Time (s)' } }, y: { beginAtZero: true, title: { display: true, text: 'ADC Value' } } } }";
    html += "});";

    // Update charts with new data
    html += "function updateCharts() {";
    html += "  fetch('/data')";
    html += "    .then(response => response.json())";
    html += "    .then(data => {";
    html += "      var currentTime = Date.now() / 1000;";
    html += "      timeLabels.push(currentTime);";
    html += "      weldCurrentData.push(data.current);";
    html += "      weldVoltageData.push(data.voltage);";
    html += "      gasConsumptionData.push(data.gas);";
    html += "      energyConsumptionData.push(data.energy);";
    html += "      if (timeLabels.length > 50) {";
    html += "        timeLabels.shift();";
    html += "        weldCurrentData.shift();";
    html += "        weldVoltageData.shift();";
    html += "        gasConsumptionData.shift();";
    html += "        energyConsumptionData.shift();";
    html += "      }";
    html += "      weldCurrentChart.update();";
    html += "      weldVoltageChart.update();";
    html += "      gasConsumptionChart.update();";
    html += "      energyConsumptionChart.update();";
    html += "    })";
    html += "    .catch(error => console.error('Error fetching data:', error));";
    html += "}";

    html += "setInterval(updateCharts, 1000);";
    html += "</script>";
    html += "</body></html>";

    request->send(200, "text/html", html);
  });

  // Serve the data as JSON
  server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request){
    // Replace with real sensor data
    StaticJsonDocument<200> doc;
    doc["current"] = weldCurrent;
    doc["voltage"] = weldVoltage;
    doc["gas"] = gasConsumption;
    doc["energy"] = energyConsumption;
    String json;
    serializeJson(doc, json);
    request->send(200, "application/json", json);
  });

  // Handle toggle machine (ON/OFF)
  server.on("/toggle", HTTP_GET, [](AsyncWebServerRequest *request){
    String state = request->getParam("state")->value();
    if (state == "on") {
      digitalWrite(switchPin, HIGH);
      request->send(200, "text/plain", "ON");
    } else if (state == "off") {
      digitalWrite(switchPin, LOW);
      request->send(200, "text/plain", "OFF");
    } else {
      request->send(400, "text/plain", "Invalid State");
    }
  });

  // Start server
  server.begin();
}

void loop() {

    // Read data from various sensors through the multiplexer
  // Read current (channel 0)
  selectMuxChannel(0);  
  int currentRaw = analogRead(muxOut);
  weldCurrent = (currentRaw / 1023.0) * 50.0;  // Example scaling to amperes

  // Read voltage (channel 1)
  selectMuxChannel(1);  
  int voltageRaw = analogRead(muxOut);
  weldVoltage = (voltageRaw / 1023.0) * 5.0;  // Example scaling to volts

  // Read variable current (channel 2)
  selectMuxChannel(2);  
  int variableCurrentRaw = analogRead(muxOut);
  // Process variable current data...

  // Read variable voltage (channel 3)
  selectMuxChannel(3);  
  int variableVoltageRaw = analogRead(muxOut);
  // Process variable voltage data...

  // Read energy consumption (channel 4, 5, 6)
  selectMuxChannel(4);  
  int energyPhase1 = analogRead(muxOut);
  selectMuxChannel(5);  
  int energyPhase2 = analogRead(muxOut);
  selectMuxChannel(6);  
  int energyPhase3 = analogRead(muxOut);
  energyConsumption = (energyPhase1 + energyPhase2 + energyPhase3) / 3.0;

  // Read gas consumption (channel 7)
  selectMuxChannel(7);  
  int gasRaw = analogRead(muxOut);
  gasConsumption = (gasRaw / 1023.0) * 100.0; // Example scaling

  // Calculate energy consumption (e.g., in Watt-hours)
  energyConsumption = weldCurrent * weldVoltage * 0.1;  // Example energy consumption formula

   // Send data to the Daily ThingSpeak channel
ThingSpeak.setField(1, weldCurrent);
ThingSpeak.setField(2, weldVoltage);
ThingSpeak.setField(3, energyConsumption);
ThingSpeak.setField(4, gasConsumption);
ThingSpeak.setField(5, (long)powerOnTime);  // Casting to long
ThingSpeak.setField(6, (long)arcOnTime);   // Casting to long
ThingSpeak.setField(7, (long)idleTime);    // Casting to long
ThingSpeak.setField(8, productionCount);

// Update the Daily channel
int httpCodeDaily = ThingSpeak.writeFields(channelIDDaily, writeAPIKeyDaily);
if (httpCodeDaily == 200) {
  Serial.println("Daily data sent to ThingSpeak successfully!");
} else {
  Serial.print("Failed to send Daily data to ThingSpeak!");
}

// Send data to the Monthly ThingSpeak channel
int httpCodeMonthly = ThingSpeak.writeFields(channelIDMonthly, writeAPIKeyMonthly);
if (httpCodeMonthly == 200) {
  Serial.println("Monthly data sent to ThingSpeak successfully!");
} else {
  Serial.println("Failed to send Monthly data to ThingSpeak!");
}

// Check if 24 hours have passed since the last data send
static unsigned long lastSendTime = 0;
unsigned long currentMillis = millis();

if (currentMillis - lastSendTime >= 86400000 || (currentMillis < lastSendTime && (ULONG_MAX - lastSendTime + currentMillis >= 86400000))) {
  // Send data to the Daily and Monthly ThingSpeak channels again (only once per day)
  
  // Send data for both Daily and Monthly channel
  ThingSpeak.setField(1, weldCurrent);
  ThingSpeak.setField(2, weldVoltage);
  ThingSpeak.setField(3, energyConsumption);
  ThingSpeak.setField(4, gasConsumption);
  ThingSpeak.setField(5, (long)powerOnTime);
  ThingSpeak.setField(6, (long)arcOnTime);
  ThingSpeak.setField(7, (long)idleTime);
  ThingSpeak.setField(8, productionCount);

  // Update both Daily and Monthly channels
  int httpCodeDaily = ThingSpeak.writeFields(channelIDDaily, writeAPIKeyDaily);
  int httpCodeMonthly = ThingSpeak.writeFields(channelIDMonthly, writeAPIKeyMonthly);

  if (httpCodeDaily == 200 && httpCodeMonthly == 200) {
    Serial.println("Data sent to both Daily and Monthly channels successfully!");
  } else {
    if (httpCodeDaily != 200) {
      Serial.println("Failed to send Daily data to ThingSpeak!");
    }
    if (httpCodeMonthly != 200) {
      Serial.println("Failed to send Monthly data to ThingSpeak!");
    }
  }

  lastSendTime = currentMillis;  // Reset last send time to the current time
}


  // Simulating time-based changes
  powerOnTime++;
  arcOnTime++;
  idleTime++;

  // Increment production count (could be based on actual production logic)
  productionCount++;

  delay(1000);
}