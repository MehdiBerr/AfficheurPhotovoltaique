
//----------------------------------------------------------------------------------------------------------------------
#include <WiFi.h>
#include <Wire.h> 

// assignation des pin aux capteurs
uint8_t TensionPin = 34;
uint8_t CourantPin = 35;
uint8_t FrequencePin = 32;


// Variables globales pour stocker les valeurs de tension et courant instantanné
double TensionBrute = 0;
double CourantBrut = 0;

float Tension = 0;
float Courant = 0;
float Puissance = 0;


// variables pour la fréquence
float Frequence = 0;
int64_t tStart = esp_timer_get_time();
int64_t tEnd;
bool mesureFinie = false;

void IRAM_ATTR isr_freq_falling(); // prototype de la fonction de calcul de freq

// Variables globales stockant les constantes pour la calibration des coefs ax+b mesure tension
const double a_Tension = 63;
const double b_Tension = -213;

// Variables globales stockant les constantes pour la calibration des coefs ax2+bx+c mesure courant
const double a_Courant = -0.000000534277;
const double b_Courant = 0.0110618;
const double c_Courant = -27.658;

// paramétrage du réseau WIFI (à changer en fonction !)
const char* ssid = "freebox_mahp";
const char* password = "61750857B2";

// numéro du port du serveur web
WiFiServer server(80);

String header;

// variables pour les temps d'attente
int64_t debut1 = esp_timer_get_time();
int compteur = 99;

//----------------------------------------------------------------------------------------------------------------------
void setup() 
{
  Serial.begin(115200);

  // définition du type des pin (entrées / sorties)
  pinMode(TensionPin, INPUT);
  pinMode(CourantPin, INPUT);
  pinMode(FrequencePin, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(FrequencePin), isr_freq_falling, FALLING);

  ConnexionAuWiFi();
}


//----------------------------------------------------------------------------------------------------------------------

void loop()
{
  LectureCapteurs();
  CalculPuissance();
  AffichageWeb();
}



//----------------------------------------------------------------------------------------------------------------------
// Ici se trouvent toutes les fonctions

// calcul de la freq
void IRAM_ATTR isr_freq_falling() 
{
  if(mesureFinie) 
  {
    tStart = esp_timer_get_time();
  }
  else 
  {
    tEnd = esp_timer_get_time();
    Frequence = 1.0/(tEnd - tStart)*1e6;
  }
  mesureFinie = !mesureFinie;
}

void LectureCapteurs()
{
     if(esp_timer_get_time() - debut1 > 10000)
   {
     TensionBrute = 0.01*analogRead(TensionPin) + 0.99*TensionBrute;
     CourantBrut = 0.01*analogRead(CourantPin) + 0.99*CourantBrut;

     if(compteur == 0)
     {
        Tension = (TensionBrute - b_Tension) / a_Tension;
        Courant = CourantBrut;
        Courant = a_Courant*Courant*Courant + b_Courant*Courant + c_Courant;

        compteur = 99;
     }

     compteur --;
     debut1 = esp_timer_get_time();
   }
}

void AffichageWeb()
{
  WiFiClient client = server.available();

  if (client)
  {
    Serial.println("Web Client connected ");
    String request = client.readStringUntil('\r');
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();


    //affichage de la page web
    client.println("<!DOCTYPE html><html>");
    client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    client.println("<link rel=\"icon\" href=\"data:,\">");

    // CCS pour rendre l'affichage plus joli
    client.println("<style>body { text-align: center; font-family: \"Arial\", Arial;}");
    client.println("table { border-collapse: collapse; width:40%; margin-left:auto; margin-right:auto;border-spacing: 2px;background-color: white;border: 4px solid green; }");
    client.println("th { padding: 20px; background-color: #008000; color: white; }");
    client.println("tr { border: 5px solid green; padding: 2px; }");
    client.println("tr:hover { background-color:yellow; }");
    client.println("td { border:4px; padding: 12px; }");
    client.println(".sensor { color:black; font-weight: bold; background-color: white; padding: 1px; }");

    // Page web principale
    client.println("</style></head><body><h1>Serveur Web ESP32</h1>");
    client.println("<h2>Lecture des valeurs de courants et tension</h2>");
    client.println("<h2>Rafraichir la page pour mettre à jour les valeurs</h2>");
    client.println("<table><tr><th>MESURE</th><th>VALEUR</th></tr>");
    client.println("<tr><td>Tension</td><td><span class=\"sensor\">");
    client.println(Tension);
    client.println(" V</span></td></tr>");
    client.println("<tr><td>Courant</td><td><span class=\"sensor\">");
    client.println(Courant);
    client.println(" A</span></td></tr>");
    client.println("<tr><td>Frequence</td><td><span class=\"sensor\">");
    client.println(Frequence);
    client.println(" Hz</span></td></tr>");
    client.println("<tr><td>Puissance</td><td><span class=\"sensor\">");
    client.println(Puissance);
    client.println(" W</span></td></tr>");
    client.println("</body></html>");
    client.stop();
    client.println();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

void ConnexionAuWiFi()
{
    Serial.print("Connexion au réseau WiFi ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connexion au WiFi réussie.");
  Serial.println("L'addresse IP de l'ESP32 est : ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.println("Serveur démarré");
}

void CalculPuissance()
{
  Puissance = Courant*Tension;
}
