#include <FS.h>                   // Biblioteca SPIFFS para salvar e ler arquivos no ESP8266
#include <ESP8266WiFi.h>          // Biblioteca ESP8266 WiFi
#include <WiFiManager.h>          // Biblioteca WiFiManager para gerenciar a configuração do WiFi
#include <PubSubClient.h>         // Biblioteca PubSubClient para MQTT
#include <DHT.h>                  // Biblioteca DHT para sensor de temperatura e umidade
#include <ArduinoJson.h>          // Biblioteca ArduinoJson para manipulação de JSON
#include <EEPROM.h>               // Biblioteca EEPROM para armazenar dados não voláteis
#include "EmonLib.h"              // Biblioteca EmonLib

#define DHTPIN 4                  // Pino onde o sensor DHT22 está conectado
#define DHTTYPE DHT11             // Definindo o tipo de sensor como DHT22
#define RESET_COUNT_ADDR 0        // Endereço na EEPROM para armazenar o contador de reinicializações

DHT dht(DHTPIN, DHTTYPE);

WiFiClient espClient;
PubSubClient client(espClient);

// Inicialize o sensor de corrente
EnergyMonitor emon1;

char mqtt_user[40];
char mqtt_password[40]; // Novo campo para a senha MQTT
char mqtt_host[40];
char mqtt_port[6];
char mqtt_topic[40];

bool shouldSaveConfig = false;

void saveConfigCallback() {
  shouldSaveConfig = true;
}

// Declaração da função de retorno de chamada MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida no tópico: ");
  Serial.println(topic);
  Serial.print("Conteúdo: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  dht.begin();

  emon1.current(5, 111.1); // Conecte o sensor de corrente na porta D1 e defina o valor de calibração

  // Inicializar EEPROM
  EEPROM.begin(512);
  int resetCount = EEPROM.read(RESET_COUNT_ADDR);
  Serial.print("Reset count: ");
  Serial.println(resetCount);

  // Incrementar o contador de reinicializações e salvar na EEPROM
  resetCount++;
  EEPROM.write(RESET_COUNT_ADDR, resetCount);
  EEPROM.commit();

  // Verificar se houve múltiplas reinicializações rápidas
  if (resetCount > 5) {
    Serial.println("Resetando configurações de WiFi...");
    WiFiManager wifiManager;
    wifiManager.resetSettings();
    Serial.println("Configurações de WiFi resetadas. Reiniciando...");
    delay(1000);
    resetCount = 0;  // Resetar o contador após a reinicialização das configurações
    EEPROM.write(RESET_COUNT_ADDR, resetCount);
    EEPROM.commit();
    ESP.restart();
  }

  // Inicializar SPIFFS
  if (!SPIFFS.begin()) {
    Serial.println("Falha ao montar o sistema de arquivos");
    return;
  }

  // Ler a configuração do arquivo JSON
  if (SPIFFS.exists("/config.json")) {
    File configFile = SPIFFS.open("/config.json", "r");
    if (configFile) {
      size_t size = configFile.size();
      std::unique_ptr<char[]> buf(new char[size]);
      configFile.readBytes(buf.get(), size);
      DynamicJsonDocument json(1024);
      auto error = deserializeJson(json, buf.get());
      if (!error) {
        strcpy(mqtt_user, json["mqtt_user"]);
        strcpy(mqtt_password, json["mqtt_password"]); // Ler a senha do MQTT
        strcpy(mqtt_host, json["mqtt_host"]);
        strcpy(mqtt_port, json["mqtt_port"]);
        strcpy(mqtt_topic, json["mqtt_topic"]);
      }
    }
  }

  WiFiManager wifiManager;
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  // Adicionar campo para a senha do MQTT
  WiFiManagerParameter custom_mqtt_user("user", "MQTT User", mqtt_user, 40);
  WiFiManagerParameter custom_mqtt_password("password", "MQTT Password", mqtt_password, 40); // Campo para a senha MQTT
  WiFiManagerParameter custom_mqtt_host("host", "MQTT Host", mqtt_host, 40);
  WiFiManagerParameter custom_mqtt_port("port", "MQTT Port", mqtt_port, 6);
  WiFiManagerParameter custom_mqtt_topic("topic", "MQTT Topic", mqtt_topic, 40);

  wifiManager.addParameter(&custom_mqtt_user);
  wifiManager.addParameter(&custom_mqtt_password); // Adicionar o campo para a senha MQTT
  wifiManager.addParameter(&custom_mqtt_host);
  wifiManager.addParameter(&custom_mqtt_port);
  wifiManager.addParameter(&custom_mqtt_topic);

  if (!wifiManager.autoConnect("SSC5972-USP-ICMC-LAB-0002")) {
    Serial.println("Falha ao conectar, reiniciando...");
    delay(3000);
    ESP.reset();
    delay(5000);
  }

  strcpy(mqtt_user, custom_mqtt_user.getValue());
  strcpy(mqtt_password, custom_mqtt_password.getValue()); // Ler o valor do campo de senha MQTT
  strcpy(mqtt_host, custom_mqtt_host.getValue());
  strcpy(mqtt_port, custom_mqtt_port.getValue());
  strcpy(mqtt_topic, custom_mqtt_topic.getValue());

  if (shouldSaveConfig) {
    DynamicJsonDocument json(1024);
    json["mqtt_user"] = mqtt_user;
    json["mqtt_password"] = mqtt_password; // Salvar a senha MQTT
    json["mqtt_host"] = mqtt_host;
    json["mqtt_port"] = mqtt_port;
    json["mqtt_topic"] = mqtt_topic;

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("Falha ao abrir o arquivo de configuração para escrita");
    }

    serializeJson(json, configFile);
    configFile.close();
  }

  client.setServer(mqtt_host, atoi(mqtt_port));
  client.setCallback(callback); // Configurar a função de retorno de chamada MQTT
}

void loop() {
  if (!client.connected()) {
    while (!client.connected()) {
      Serial.print("Conectando ao MQTT...");
      if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) { // Autenticação MQTT com usuário e senha
        Serial.println("Conectado");
        client.subscribe("inTopic");
      } else {
        Serial.print("Falha, rc=");
        Serial.print(client.state());
        delay(5000);
      }
    }
  }

  client.loop();
  
  // Leitura de temperatura e humidade
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Leitura da corrente e cálculo do consumo
  double Irms = emon1.calcIrms(1480); // Calcule a corrente RMS
  double power = Irms * 110; // Potência em Watts (considerando tensão de 110V)


  if (isnan(h) || isnan(t)) {
    Serial.println("Falha ao ler do sensor DHT");
    return;
  }

  // Imprimir valores lidos no console
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" °C, Umidade: ");
  Serial.print(h);
  Serial.println(" %");
  Serial.print("Corrente: ");
  Serial.print(Irms);
  Serial.println("Power: ");
  Serial.print(power);

  DynamicJsonDocument doc(512);

  JsonObject metrics = doc.createNestedObject("metrics");
  metrics["temperature"] = t;
  metrics["humidity"] = h;
  metrics["current"] = Irms;
  metrics["power"] = power;
  metrics["sensor_type"] = "energy";
  metrics["sensor_id"] = WiFi.macAddress();


  doc["body"] = "c29tZSBvcHRpb25hbCBjb250ZW50"; // Conteúdo opcional codificado em base64

  char buffer[256];
  size_t n = serializeJson(doc, buffer);

  // Imprimir JSON gerado no console
  Serial.println("JSON gerado:");
  serializeJsonPretty(doc, Serial);

  if (client.publish(mqtt_topic, buffer, n)) {
    Serial.println("Dados enviados com sucesso ao servidor MQTT");
  } else {
    Serial.println("Falha ao enviar dados ao servidor MQTT");
  }

  // Colocar o ESP8266 em modo de sono profundo por 3 minutos (180 segundos)
  delay(10000);
  //ESP.deepSleep(180e6); // 180e6 microsegundos = 180 segundos = 3 minutos
}
