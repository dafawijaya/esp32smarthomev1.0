#ifdef ESP32 // ESP32 libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#else // ESP8266 libraries
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
 
//******nama dan pass wifi************
const char* ssid = "Kelg_Hadie";
const char* password = "Vitri1972";
//************************************************
 
//status input
const char* PARAM_INPUT_1 = "state";
const char* PARAM_INPUT_2 = "state2";
const char* PARAM_INPUT_3 = "state3";
const char* PARAM_INPUT_4 = "state4";
 
//**********pin***********
const int relay1 = 15; 
const int switch1 = 32; 
const int relay2 = 2; 
const int switch2 = 35; 
const int relay3 = 4; 
const int switch3 = 34; 
const int relay4 = 22; 
const int switch4 = 39; 
//************************************
 
//*********************Variables declaration**********************
int relay_1_status = HIGH; // the current status of relay1
int switch_1_status; // the current status of switch1
int last_switch_1_status = LOW; // Last status of switch1
int relay_2_status = HIGH; // the current status of relay2
int switch_2_status; // the current status of switch2
int last_switch_2_status = LOW; // Last status of switch2
int relay_3_status = HIGH; // the current status of relay2
int switch_3_status; // the current status of switch2
int last_switch_3_status = LOW; // Last status of switch2
int relay_4_status = HIGH; // the current status of relay2
int switch_4_status; // the current status of switch2
int last_switch_4_status = LOW; // Last status of switch2
//****************************************************************
 
// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 50; // the debounce time; increase if the output flickers
 
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
 
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
<title>NodeMCU based Web Server</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
html {font-family: Arial; display: inline-block; text-align: center;}
h2 {font-size: 3.0rem;}
p {font-size: 3.0rem;}
body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
.switch {position: relative; display: inline-block; width: 120px; height: 68px}
.switch input {display: none}
.slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #F63E36; border-radius: 34px}
.slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 68px}
input:checked+.slider {background-color: #3CC33C}
input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
</style>
</head>
<body>
<h2>smarthome esp32</h2>

%BUTTONPLACEHOLDER%
%BUTTONPLACEHOLDER2%
%BUTTONPLACEHOLDER3%
%BUTTONPLACEHOLDER4%
<script>
function toggleCheckbox(element)
{
var xhr = new XMLHttpRequest();
if(element.checked)
{
xhr.open("GET", "/update?state=1", true);
}
else
{
xhr.open("GET", "/update?state=0", true);
}
xhr.send();
}
 
function toggleCheckbox2(element)
{
var xhr2 = new XMLHttpRequest();
if(element.checked)
{
xhr2.open("GET", "/update?state2=1", true);
}
else
{
xhr2.open("GET", "/update?state2=0", true);
}
xhr2.send();
}

function toggleCheckbox3(element)
{
var xhr3 = new XMLHttpRequest();
if(element.checked)
{
xhr3.open("GET", "/update?state3=1", true);
}
else
{
xhr3.open("GET", "/update?state3=0", true);
}
xhr3.send();
}


function toggleCheckbox4(element)
{
var xhr4 = new XMLHttpRequest();
if(element.checked)
{
xhr4.open("GET", "/update?state4=1", true);
}
else
{
xhr4.open("GET", "/update?state4=0", true);
}
xhr4.send();
}

 
setInterval(function ( )
{
var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function()
{
if (this.readyState == 4 && this.status == 200)
{
var inputChecked;
var outputStateM;
 
if( this.responseText == 1)
{
inputChecked = false;
outputStateM = "OFF";
}
else
{
  inputChecked = true;
outputStateM = "ON";

}
document.getElementById("output").checked = inputChecked;
document.getElementById("outputState").innerHTML = outputStateM;
}
}
xhttp.open("GET", "/state", true);
xhttp.send();
 
var xhttp2 = new XMLHttpRequest();
xhttp2.onreadystatechange = function()
{
if (this.readyState == 4 && this.status == 200)
{
var inputChecked2;
var outputStateM2;
 
if( this.responseText == 1)
{
  inputChecked2 = false;
outputStateM2 = "OFF";

}
else
{
inputChecked2 = true;
outputStateM2 = "ON";
}
document.getElementById("output2").checked = inputChecked2;
document.getElementById("outputState2").innerHTML = outputStateM2;
}
};
xhttp2.open("GET", "/state2", true);
xhttp2.send();


 var xhttp3 = new XMLHttpRequest();
xhttp3.onreadystatechange = function()
{
if (this.readyState == 4 && this.status == 200)
{
var inputChecked2;
var outputStateM2;
 
if( this.responseText == 1)
{
  inputChecked3 = false;
outputStateM3 = "OFF";

}
else
{
inputChecked3 = true;
outputStateM3 = "ON";
}
document.getElementById("output3").checked = inputChecked3;
document.getElementById("outputState3").innerHTML = outputStateM3;
}
};
xhttp3.open("GET", "/state3", true);
xhttp3.send();



 var xhttp4 = new XMLHttpRequest();
xhttp4.onreadystatechange = function()
{
if (this.readyState == 4 && this.status == 200)
{
var inputChecked4;
var outputStateM4;
 
if( this.responseText == 1)
{

inputChecked4 = false;
outputStateM4 = "OFF";
}
else
{
inputChecked4 = true;
outputStateM4 = "ON";
}
document.getElementById("output4").checked = inputChecked4;
document.getElementById("outputState4").innerHTML = outputStateM4;
}
};
xhttp4.open("GET", "/state4", true);
xhttp4.send();


}, 1000 ) ;
</script>
</body>
</html>
)rawliteral";
 
// Replaces placeholder with button section in your web page
String processor(const String& var)
{
//Serial.println(var);
if(var == "BUTTONPLACEHOLDER")
{
String buttons1 ="";
String outputStateValue = outputState();
buttons1+= "<h4>Device 1 - Status <span id=\"outputState\"><span></h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"output\" " + outputStateValue + "><span class=\"slider\"></span></label>";
return buttons1;
}
 
if(var == "BUTTONPLACEHOLDER2")
{
String buttons2 ="";
String outputStateValue2 = outputState2();
buttons2+= "<h4>Device 2 - Status <span id=\"outputState2\"><span></h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox2(this)\" id=\"output2\" " + outputStateValue2 + "><span class=\"slider\"></span></label>";
return buttons2;
}

if(var == "BUTTONPLACEHOLDER3")
{
String buttons3 ="";
String outputStateValue3 = outputState3();
buttons3+= "<h4>Device 3 - Status <span id=\"outputState3\"><span></h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox3(this)\" id=\"output3\" " + outputStateValue3 + "><span class=\"slider\"></span></label>";
return buttons3;
}


if(var == "BUTTONPLACEHOLDER4")
{
String buttons4 ="";
String outputStateValue4 = outputState4();
buttons4+= "<h4>Device 4 - Status <span id=\"outputState4\"><span></h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox4(this)\" id=\"output4\" " + outputStateValue4 + "><span class=\"slider\"></span></label>";
return buttons4;
}

return String();
}
 
String outputState()
{
if(digitalRead(relay1))
{
return "checked";
}
else
{
return "";
}
return "";
}
String outputState2()
{
if(digitalRead(relay2))
{
return "checked";
}
else
{
return "";
}
return "";
}


String outputState3()
{
if(digitalRead(relay3))
{
return "checked";
}
else
{
return "";
}
return "";
}

String outputState4()
{
if(digitalRead(relay4))
{
return "checked";
}
else
{
return "";
}
return "";
} 
void setup()
{
// Serial port for debugging purposes
Serial.begin(115200);
 
pinMode(relay1, OUTPUT);
digitalWrite(relay1, LOW);
pinMode(switch1, INPUT);
 
pinMode(relay2, OUTPUT);
digitalWrite(relay2, LOW);
pinMode(switch2, INPUT);

pinMode(relay3, OUTPUT);
digitalWrite(relay3, LOW);
pinMode(switch3, INPUT);

pinMode(relay4, OUTPUT);
digitalWrite(relay4, LOW);
pinMode(switch4, INPUT);
 
// Connect to Wi-Fi
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED)
{
delay(1000);
Serial.println("Connecting to WiFi..");
}
 
// Print ESP Local IP Address
Serial.println(WiFi.localIP());
 
// Route for root / web page
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
{
request->send_P(200, "text/html", index_html, processor);
});
 
// Send a GET request
server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request)
{
String inputMessage;
String inputParam;
 
// GET input1 value on <ESP_IP>/update?state=<inputMessage>
if (request->hasParam(PARAM_INPUT_1))
{
inputMessage = request->getParam(PARAM_INPUT_1)->value();
inputParam = PARAM_INPUT_1;
digitalWrite(relay1, inputMessage.toInt());
relay_1_status = !relay_1_status;
}
else
{
inputMessage = "No message sent";
inputParam = "none";
}
Serial.println(inputMessage);
request->send(200, "text/plain", "OK");



String inputMessage2;
String inputParam2;
 
if (request->hasParam(PARAM_INPUT_2))
{
inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
inputParam2 = PARAM_INPUT_2;
digitalWrite(relay2, inputMessage2.toInt());
relay_2_status = !relay_2_status;
}
else
{
inputMessage2 = "No message sent";
inputParam2 = "none";
}
Serial.println(inputMessage2);
request->send(200, "text/plain", "OK");


String inputMessage3;
String inputParam3;
 
if (request->hasParam(PARAM_INPUT_3))
{
inputMessage3 = request->getParam(PARAM_INPUT_3)->value();
inputParam3 = PARAM_INPUT_3;
digitalWrite(relay3, inputMessage3.toInt());
relay_3_status = !relay_3_status;
}
else
{
inputMessage3 = "No message sent";
inputParam3 = "none";
}
Serial.println(inputMessage3);
request->send(200, "text/plain", "OK");

String inputMessage4;
String inputParam4;
 
if (request->hasParam(PARAM_INPUT_4))
{
inputMessage4 = request->getParam(PARAM_INPUT_4)->value();
inputParam4 = PARAM_INPUT_4;
digitalWrite(relay4, inputMessage4.toInt());
relay_4_status = !relay_4_status;
}
else
{
inputMessage4 = "No message sent";
inputParam4 = "none";
}
Serial.println(inputMessage4);
request->send(200, "text/plain", "OK");

});




 
// Send a GET request to <ESP_IP>/state
server.on("/state", HTTP_GET, [] (AsyncWebServerRequest *request)
{
request->send(200, "text/plain", String(digitalRead(relay1)).c_str());
});
 
server.on("/state2", HTTP_GET, [] (AsyncWebServerRequest *request)
{
request->send(200, "text/plain", String(digitalRead(relay2)).c_str());
});

server.on("/state3", HTTP_GET, [] (AsyncWebServerRequest *request)
{
request->send(200, "text/plain", String(digitalRead(relay3)).c_str());
});

server.on("/state4", HTTP_GET, [] (AsyncWebServerRequest *request)
{
request->send(200, "text/plain", String(digitalRead(relay4)).c_str());
});

// Start server
server.begin();
}
 
void loop()
{
int reading1 = digitalRead(switch1);
if (reading1 != last_switch_1_status)
{
lastDebounceTime = millis(); // reset the debouncing timer
}
 
if ((millis() - lastDebounceTime) > debounceDelay) 
{ 
if (reading1 != switch_1_status)
{
switch_1_status = reading1;
if (switch_1_status == HIGH)
{
relay_1_status = !relay_1_status;
}
}
}
 
int reading2 = digitalRead(switch2);
if (reading2 != last_switch_2_status)
{
lastDebounceTime = millis();
}
 
if ((millis() - lastDebounceTime) > debounceDelay)
{
if (reading2 != switch_2_status)
{
switch_2_status = reading2;
if (switch_2_status == HIGH)
{
relay_2_status = !relay_2_status;
}
}
}

int reading3 = digitalRead(switch3);
if (reading3 != last_switch_3_status)
{
lastDebounceTime = millis();
}
 
if ((millis() - lastDebounceTime) > debounceDelay)
{
if (reading3 != switch_3_status)
{
switch_3_status = reading3;
if (switch_3_status == HIGH)
{
relay_3_status = !relay_3_status;
}
}
}

int reading4 = digitalRead(switch4);
if (reading4 != last_switch_4_status)
{
lastDebounceTime = millis();
}
 
if ((millis() - lastDebounceTime) > debounceDelay)
{
if (reading4 != switch_4_status)
{
switch_4_status = reading4;
if (switch_4_status == HIGH)
{
relay_4_status = !relay_4_status;
}
}
}


// set the LED:
digitalWrite(relay1, relay_1_status);
digitalWrite(relay2, relay_2_status);
digitalWrite(relay3, relay_3_status);
digitalWrite(relay4, relay_4_status); 
// save the reading. Next time through the loop, it'll be the lastButtonState:
last_switch_1_status = reading1;
last_switch_2_status = reading2;
last_switch_3_status = reading3;
last_switch_4_status = reading4;
}
