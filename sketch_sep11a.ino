#include <DFRobot_Heartrate.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ThingSpeak.h>

float sensorPino =35;
float valor;
float hold = 550;



#define SSID "FIAP-IOT"//Definir a rede na faculdade
#define PASSWORD "F!@p25.IOT" //Definir a senha na faculdade
#define APIKEY "EOLQ7NRR3YYILVKT" //API
#define ID_def 3071421



char ssid[] = SSID;   //Rede
char pass[] = PASSWORD;   //Senha
WiFiClient  client;


void setup() {
  // put your setup code here, to run once:
  pinMode(sensorPino,OUTPUT);
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Inicializar o ThingSpeak
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){ //Se os status de Wifi não estiverem conectatos, tentar conecatar
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SSID);
    while(WiFi.status() != WL_CONNECTED){ //Colocar em loop até que a conecção seja feita
      WiFi.begin(ssid, pass); //Wifi beguin rede e senha
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnectado.");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  valor = analogRead(sensorPino);
  Serial.println(valor);
  if(valor>hold){
    Serial.println("Tá pegando");
  }
  else{
    Serial.println("Não tá pegado");
  }
  delay(1000);



  ThingSpeak.setField(1, valor);
  if(WiFi.status() == WL_CONNECTED){
    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int x = ThingSpeak.writeFields(ID_def, APIKEY);
    if(x == 200){
      Serial.println("Enviou os dados OK.");
    }
    else{
      Serial.println("Erro ao enviar. HTTP error code " + String(x));
    }
  }




}