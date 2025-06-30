/**
 * @file PetFeeder_Final.ino
 * @author Bárbara Portes & Samir Cambraia
 * @brief Firmware final para o Sistema Inteligente de Alimentação e Hidratação para Pets.
 * @version 1.0
 * @date 2025-06-30
 * * @details Este código controla um dispositivo ESP32 que monitora (simuladamente) os níveis de 
 * ração e água e a temperatura, publicando alertas via MQTT. Ele também recebe comandos
 * via MQTT para acionar (simuladamente) os atuadores correspondentes.
 */

// --- Bibliotecas ---
#include <WiFi.h>
#include <PubSubClient.h>

// --- Configurações de Rede ---
const char* SSID = "s1";                     // Insira o nome da sua rede Wi-Fi
const char* PASSWORD = "1234567aa";          // Insira a senha da sua rede Wi-Fi

// --- Configurações do Broker MQTT ---
const char* BROKER_MQTT = "test.mosquitto.org";
const int BROKER_PORT = 1883;
const char* ID_MQTT = "esp32_pet_feeder_final"; // ID único para o cliente MQTT

// --- Tópicos MQTT ---
#define TOPICO_ALERTA_RACAO       "/pet/alerta/racao"
#define TOPICO_ALERTA_AGUA        "/pet/alerta/agua"
#define TOPICO_ALERTA_TEMPERATURA "/pet/alerta/temperatura"
#define TOPICO_COMANDO_RACAO      "/pet/comando/racao"
#define TOPICO_COMANDO_AGUA       "/pet/comando/agua"
#define TOPICO_COMANDO_TEMPERATURA "/pet/comando/temperatura"

// --- Mapeamento de Pinos (Hardware Simulado) ---
// Sensores (Botões)
#define BOTAO_RACAO           4  // Simula sensor de nível de ração
#define BOTAO_AGUA            13 // Simula sensor de nível de água
#define BOTAO_TEMPERATURA     27 // Simula sensor de temperatura da água

// Atuadores (LEDs)
#define LED_RACAO             5  // Simula dispensador de ração
#define LED_AGUA              12 // Simula bomba de água
#define LED_TEMPERATURA       26 // Simula sistema de refrigeração/alerta

// --- Variáveis Globais ---
WiFiClient espClient;
PubSubClient MQTT(espClient);

// Variáveis para controle de tempo (evita spam de mensagens)
unsigned long tempoRacao = 0;
unsigned long tempoAgua = 0;
unsigned long tempoTemperatura = 0;
const unsigned long DEBOUNCE_INTERVALO = 5000; // Intervalo de 5 segundos

// --- Protótipos das Funções ---
void conectaWiFi();
void conectaMQTT();
void callback(char* topic, byte* payload, unsigned int length);
void verificaSensores();

// --- Função de Configuração (Setup) ---
void setup() {
    Serial.begin(115200);
    Serial.println("Iniciando o Sistema PetFeeder...");

    // Configura os pinos dos botões como entrada com pull-up interno
    pinMode(BOTAO_RACAO, INPUT_PULLUP);
    pinMode(BOTAO_AGUA, INPUT_PULLUP);
    pinMode(BOTAO_TEMPERATURA, INPUT_PULLUP);

    // Configura os pinos dos LEDs como saída
    pinMode(LED_RACAO, OUTPUT);
    pinMode(LED_AGUA, OUTPUT);
    pinMode(LED_TEMPERATURA, OUTPUT);

    // Garante que os LEDs comecem apagados
    digitalWrite(LED_RACAO, LOW);
    digitalWrite(LED_AGUA, LOW);
    digitalWrite(LED_TEMPERATURA, LOW);

    conectaWiFi();
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);
    MQTT.setCallback(callback);
}

// --- Laço Principal (Loop) ---
void loop() {
    if (!MQTT.connected()) {
        conectaMQTT();
    }
    MQTT.loop(); // Processa mensagens MQTT recebidas e mantém a conexão
    verificaSensores(); // Verifica o estado dos sensores simulados
}

// --- Implementação das Funções ---

/**
 * @brief Conecta o ESP32 à rede Wi-Fi.
 */
void conectaWiFi() {
    delay(10);
    Serial.print("Conectando à rede Wi-Fi: ");
    Serial.println(SSID);
    WiFi.begin(SSID, PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWi-Fi conectado!");
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());
}

/**
 * @brief Conecta e se inscreve nos tópicos do broker MQTT.
 */
void conectaMQTT() {
    while (!MQTT.connected()) {
        Serial.print("Tentando conectar ao Broker MQTT...");
        if (MQTT.connect(ID_MQTT)) {
            Serial.println(" conectado!");
            
            // Se inscreve nos tópicos de comando
            MQTT.subscribe(TOPICO_COMANDO_RACAO);
            MQTT.subscribe(TOPICO_COMANDO_AGUA);
            MQTT.subscribe(TOPICO_COMANDO_TEMPERATURA);

            Serial.println("Inscrição nos tópicos de comando realizada.");
        } else {
            Serial.print(" falhou, rc=");
            Serial.print(MQTT.state());
            Serial.println(" tentando novamente em 5 segundos");
            delay(5000);
        }
    }
}

/**
 * @brief Função chamada quando uma mensagem é recebida de um tópico inscrito.
 */
void callback(char* topic, byte* payload, unsigned int length) {
    String mensagem;
    for (int i = 0; i < length; i++) {
        mensagem += (char)payload[i];
    }

    Serial.print("Mensagem recebida no tópico [");
    Serial.print(topic);
    Serial.print("]: ");
    Serial.println(mensagem);

    if (String(topic) == TOPICO_COMANDO_RACAO && mensagem == "ON") {
        Serial.println("Acionando dispensador de ração...");
        digitalWrite(LED_RACAO, HIGH);
        delay(2000); // Simula o tempo de acionamento
        digitalWrite(LED_RACAO, LOW);
    }
    else if (String(topic) == TOPICO_COMANDO_AGUA && mensagem == "ON") {
        Serial.println("Acionando bomba de água...");
        digitalWrite(LED_AGUA, HIGH);
        delay(2000);
        digitalWrite(LED_AGUA, LOW);
    }
    else if (String(topic) == TOPICO_COMANDO_TEMPERATURA && mensagem == "ON") {
        Serial.println("Acionando alerta de temperatura...");
        digitalWrite(LED_TEMPERATURA, HIGH);
        delay(2000);
        digitalWrite(LED_TEMPERATURA, LOW);
    }
}

/**
 * @brief Verifica o estado dos botões (sensores simulados) e publica alertas.
 */
void verificaSensores() {
    unsigned long tempoAtual = millis();

    // Verifica sensor de ração
    if (digitalRead(BOTAO_RACAO) == LOW && (tempoAtual - tempoRacao > DEBOUNCE_INTERVALO)) {
        Serial.println("ALERTA: Nível de ração baixo!");
        MQTT.publish(TOPICO_ALERTA_RACAO, "FALTA");
        tempoRacao = tempoAtual;
    }

    // Verifica sensor de água
    if (digitalRead(BOTAO_AGUA) == LOW && (tempoAtual - tempoAgua > DEBOUNCE_INTERVALO)) {
        Serial.println("ALERTA: Nível de água baixo!");
        MQTT.publish(TOPICO_ALERTA_AGUA, "FALTA");
        tempoAgua = tempoAtual;
    }

    // Verifica sensor de temperatura
    if (digitalRead(BOTAO_TEMPERATURA) == LOW && (tempoAtual - tempoTemperatura > DEBOUNCE_INTERVALO)) {
        Serial.println("ALERTA: Temperatura da água inadequada!");
        MQTT.publish(TOPICO_ALERTA_TEMPERATURA, "ALTA");
        tempoTemperatura = tempoAtual;
    }
}
