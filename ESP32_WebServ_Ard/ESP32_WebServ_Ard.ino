
#include <Arduino.h>
#include<ESPAsyncWebServer.h>
#include<SPIFFS.h>
#include <ArduinoJson.h>


const char* ssid = "iPhone";
const char* password = "primegang0";

AsyncWebServer server (80);




void setup() {
  //.............................................SERIAL
  Serial.begin(115200);
  while(!Serial){}                   //ATTENTION !!!!! ENLEVER CETTE LIGNE A LA FIN DU DEVELOPPEMENT
  Serial.println("\n");
  //.............................................GPIO
  //.............................................JSON



  //.............................................SPIFFS
   if(!SPIFFS.begin())
  {
    Serial.println("Erreur SPIFFS...");
    return;
  }

  File root = SPIFFS.open("/");
  File file = root.openNextFile();

  while(file)
  {
    Serial.print("File: ");
    Serial.println(file.name());
    file.close();
    file = root.openNextFile();
  }
  //.............................................WIFI
  WiFi.begin(ssid, password);
  Serial.print("Tentative de connexion...");
  
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }
  
  Serial.println("\n");
  Serial.println("Connexion etablie!");
  Serial.print("Adresse IP: ");
  Serial.println(WiFi.localIP());
  //.............................................SERVER 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/index.html", "text/html");
  });

    server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/index.html", "text/html");
  });

    server.on("/graph.html", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/graph.html", "text/html");
  });

  server.on("/bootstrap.min.css", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/bootstrap.min.css", "text/css");
  });

  server.on("/bootstrap.min.js", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/bootstrap.min.js", "text/javascript");
  });

    server.on("/jquery.min.js", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/jquery.min.js", "text/javascript");
  });

    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/script.js", "text/javascript");
  });

    
  server.on("/lireLuminosite", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    int valLum = touchRead(T6);
    String luminosite = String(valLum);
    request->send(200, "text/plain", luminosite);
  });

    
    server.on("/lireTemperature", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    int valTemp = touchRead(T0);
    String temperature = String(valTemp);
    request->send(200, "text/plain", temperature);
  });

    
    server.on("/lireTension", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    int valTens = touchRead(T0);
    String tension = String(valTens);
    request->send(200, "text/plain", tension);
  });

    
    server.on("/lireCourant", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    int valCurr = touchRead(T6);
    String courant = String(valCurr);
    request->send(200, "text/plain", courant);
  });

   
    server.on("/lirePuissance", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    int valPuiss = touchRead(T0);
    String puissance = String(valPuiss);
    request->send(200, "text/plain", puissance);
  });

  server.begin();
  Serial.println("Serveur actif!");


}

void loop() {
  // put your main code here, to run repeatedly:

}
