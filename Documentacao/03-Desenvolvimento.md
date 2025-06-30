# Materiais
Os materiais de hardware utilizados para a montagem do protótipo e planejados para a versão final do projeto foram:

- Microcontrolador: ESP32 DevKit V1

## Sensores:

- Sensor Ultrassônico HC-SR04 (para nível de ração)

- Sensor de Temperatura à prova d'água DS18B20 (para água)

- Botões (Push Buttons) para simulação de sensores

## Atuadores:

- Motor de Passo 28BYJ-48 com driver ULN2003 (para liberar ração)

- Mini Bomba de Água 5V

- LEDs de cores variadas para simulação de atuadores

## Componentes Adicionais:

- Protoboard

- Jumpers (macho-macho, macho-fêmea)

- Resistores

# Desenvolvimento
O desenvolvimento do trabalho foi dividido em etapas que seguiram a arquitetura de uma solução IoT, desde o hardware até a interface com o usuário.

# Desenvolvimento do Aplicativo
O aplicativo foi usado foi a plataforma IoT MQTT Panel, que permite criar dashboards de controle para dispositivos IoT sem a necessidade de programação nativa. Foram configurados os seguintes componentes:

- Painéis de Texto/Indicadores: Para exibir os alertas recebidos dos tópicos /pet/alerta/racao, /pet/alerta/agua e /pet/alerta/temperatura. Eles mudam de estado ou cor para indicar uma condição normal ou de alerta (ex: "FALTA").

- Botões de Comando: Para enviar mensagens aos tópicos de comando (/pet/comando/racao, etc.). Ao serem pressionados, publicam a mensagem "ON" no respectivo tópico, acionando o atuador correspondente no ESP32.

Código
Não houve desenvolvimento de código específico para o aplicativo, pois o IoT MQTT Panel é uma ferramenta de configuração. Toda a lógica de comunicação foi definida diretamente na interface do app, configurando os tópicos de subscribe (para os painéis de alerta) e publish (para os botões).

# Desenvolvimento do Hardware
Montagem
A montagem do hardware foi realizada em uma protoboard para fins de prototipação e validação da lógica. Os botões foram conectados às portas GPIO do ESP32 com resistores de pull-up para simular os sensores. Os LEDs foram conectados a outras portas GPIO para simular os atuadores. O diagrama elétrico foi projetado no Fritzing para guiar a montagem final, que não foi concluída.

# Desenvolvimento do Código
O código do ESP32 foi desenvolvido na Arduino IDE utilizando a linguagem C++. As principais funcionalidades implementadas foram:

- Conexão Wi-Fi: O ESP32 se conecta à rede local.

- Cliente MQTT: Utiliza a biblioteca PubSubClient para se conectar ao broker MQTT, se inscrever nos tópicos de comando e publicar nos tópicos de alerta.

- Lógica de Sensores (Simulada): O código monitora o estado dos botões. Ao detectar um botão pressionado, ele publica uma mensagem de alerta no tópico correspondente.

- Lógica de Atuadores (Simulada): Uma função de callback trata as mensagens recebidas dos tópicos de comando. Ao receber a mensagem "ON", o código aciona o LED correspondente por um breve período.

- Comunicação entre App e Hardware
A comunicação foi estabelecida através do protocolo MQTT, com o broker test.mosquitto.org atuando como intermediário.

- App para Hardware: O usuário pressiona um botão no IoT MQTT Panel (ex: "LIBERAR RAÇÃO"). O app publica a mensagem "ON" no tópico /pet/comando/racao.

- Broker: O broker recebe a mensagem e a encaminha para todos os clientes inscritos nesse tópico.

- Hardware: O ESP32, que está inscrito no tópico, recebe a mensagem "ON". A função de callback é acionada, e o ESP32 acende o LED que simula o dispensador de ração.

- Hardware para App: O usuário pressiona o botão na protoboard que simula o sensor de nível de ração baixo. O ESP32 publica a mensagem "FALTA" no tópico /pet/alerta/racao.

- Broker: O broker encaminha a mensagem para os clientes inscritos.

- App: O IoT MQTT Panel, inscrito no tópico de alerta, recebe a mensagem "FALTA" e atualiza o painel de texto correspondente para notificar o usuário.
