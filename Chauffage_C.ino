/*------------------------------------------------------------------------------------------------------------------------------
  ** CHAUFFAGE CONNECTE **

Info :
Chauffage ON  : pas de signal
Chauffage OFF : demi alternance positive
Chauffage ECO : pleine alternance

  
Version v0.0  : Essai


------------------------------------------------------------------------------------------------------------------------------*/

//Bibliothéques
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <FS.h>

//DEFINE
#define SSID      "SFR_****"    //SSID Box
#define PASSWORD  "********"    //Clé Wifi
#define RLY1      14            //Optocoupleur 1, pin D5
#define RLY2      15            //Optocoupleur 2, pin D8
#define LED       16            //Led d'indication Wemos non connecté


//Déclaration des objets
WiFiServer server(80);          //Serveur web
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600*2, 60000);

//Définition des structures

//Enumérations
enum :byte {OFF, ON, ECO, AUTO} _mode;  //OFF = 0, ON = 1, ECO = 2, AUTO = 3

//Déclaration des constantes
String dayString[] = {"", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};

//Déclaration des variables
byte day, hour;       //Contient le numéro de jour de la semaine, puis l'heure (pas de minutes)
byte prog[8][24];     //Tableau contenant la programmation de la semaine
String data;          //Contient les données sauvegarder dans la mémoire de l'ESP8266


void setup() {

  //Configuration des sorties
  pinMode(RLY1, OUTPUT);
  pinMode(RLY2, OUTPUT);
  pinMode(LED, OUTPUT);

  //Initilisation des sorties
  digitalWrite(RLY1, LOW);
  digitalWrite(RLY2, LOW);
  digitalWrite(LED, HIGH);

  //Initialisation des variables

  //Démarrage du moniteur série
  Serial.begin(115200);

  //Connexion au réseau WIFI
  Serial.print("Connecting to ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected at IP address:");
  Serial.println(WiFi.localIP());

  //Gestionnaire de fichier
  SPIFFS.begin(); 
  File file = SPIFFS.open("/data.txt","r");    //Ouverture du fichier data contenant la programmation du chauffage 
  data = file.readString();                    //Copie dans la variable 
  Serial.println(data);                         //Affichage debugger du contenu
  file.close();                                //Fermeture du fichier

  //Appel de la fonction update pour mise à jour programmateur
  fUpdate(data, false);
  
  //Démarrage du serveur web
  server.begin();
  
  //Démarrage du client NTP
  timeClient.begin();

}

// Main loop
void loop(){

  if (WiFi.status() != WL_CONNECTED) digitalWrite(LED, HIGH);
  else digitalWrite(LED, LOW);
 
    
  // Create a client and listen for incoming clients
  WiFiClient client = server.available();   
    
  //Si client connecté
  if (client) {
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();
  
    if (request.indexOf("/?mode=") != -1) {
      fUpdate(request, true);
    }
  }

  //Récupération heure
  timeClient.update();          //Récupération date et heure du serveur NTP
  day = timeClient.getDay();    //Numéro du jour de la semaine
  if (day == 0) day = 7;        //Si 0, on remplace par 7 pour placer le dimanche au septième jour de la semaine
  
  hour = timeClient.getHours(); //Heure (seulement pas les minutes)
    
  //Affichage page web
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.print(fPage_web());
   
  //GESTION CHAUFFE
	switch (_mode){
		case OFF:	//Chauffage éteint
			digitalWrite(RLY1, HIGH);
      digitalWrite(RLY2, LOW);
		break;

		case ON:	//Chauffage forcé
			digitalWrite(RLY1, LOW);
      digitalWrite(RLY2, LOW);
    break;
		
		case AUTO:	//Mode automatique
			switch (prog[day][hour]){
			  case OFF: //Chauffage éteint
          digitalWrite(RLY1, HIGH);
          digitalWrite(RLY2, LOW);
        break;
      
			  case ON:  //Chauffage mode confort
          digitalWrite(RLY1, LOW);
          digitalWrite(RLY2, LOW);
				break;
        
			  case ECO: //Chauffage mode éco
          digitalWrite(RLY1, HIGH);
          digitalWrite(RLY2, HIGH);
				break;            
			}
		break;
	}

} //END LOOP
