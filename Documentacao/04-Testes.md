# Testes do Projeto
Os testes foram uma etapa fundamental para garantir a funcionalidade e a integração dos diferentes componentes do sistema. A abordagem de testes foi dividida em três níveis:

## Testes Unitários e de Componentes:

Hardware (ESP32): Cada funcionalidade do código embarcado foi testada de forma isolada. Por exemplo, a lógica de leitura de um botão (simulando um sensor) e o acionamento de um LED (simulando um atuador) foram validados individualmente através do monitor serial da Arduino IDE.

Backend (Python): O script de conexão com o banco de dados foi testado para garantir que a conexão com o MySQL (via Docker) era estabelecida corretamente e que as operações de inserção (INSERT) e limpeza (TRUNCATE) funcionavam como esperado.

## Testes de Integração:

O principal teste de integração focou na comunicação via MQTT. Utilizando o protótipo em protoboard, o aplicativo IoT MQTT Panel e um cliente MQTT adicional (como o MQTTX ou o próprio script Python), validamos o fluxo completo de mensagens:

Publicação de Alertas: Verificou-se se, ao pressionar um botão no ESP32, a mensagem de alerta era corretamente publicada no tópico e recebida tanto pelo aplicativo quanto pelo script de backend.

Recepção de Comandos: Verificou-se se, ao enviar um comando pelo aplicativo, a mensagem era recebida pelo ESP32, que por sua vez acionava o LED correspondente.

## Testes End-to-End (Sistema Completo):

Simulamos o ciclo completo de uso: um alerta de "nível baixo" era gerado no hardware, a notificação aparecia no aplicativo, um comando de "liberar ração" era enviado pelo app, o hardware "atuava" (acendia o LED), e todo o histórico de eventos era registrado no banco de dados, sendo consultado posteriormente via DBeaver para confirmar a persistência dos dados.

## Resultados Encontrados
Os testes demonstraram que a arquitetura proposta é funcional e robusta. A comunicação via MQTT se mostrou confiável e com baixa latência. A integração entre o hardware simulado, o aplicativo mobile e o backend com banco de dados foi bem-sucedida, validando o fluxo de dados completo. Os principais objetivos funcionais, como o envio de alertas e o recebimento de comandos, foram alcançados com sucesso.

## Limitações do Projeto
Apesar dos resultados positivos, o projeto possui algumas limitações:

Hardware não finalizado: A principal limitação é a ausência da montagem física final. Os testes foram realizados com simulações (botões e LEDs), e a calibração e o comportamento dos sensores e atuadores reais (motor de passo, bomba d'água) não puderam ser validados em um cenário real.

Dependência de Broker Público: O sistema utiliza um broker MQTT público (test.mosquitto.org), o que não é ideal para uma aplicação em produção devido a questões de segurança, privacidade e disponibilidade.

Interface do Aplicativo: O uso do IoT MQTT Panel, embora prático para prototipação, oferece pouca personalização de interface e experiência do usuário em comparação com um aplicativo nativo.

Segurança: O projeto não implementou camadas de segurança robustas, como criptografia de ponta a ponta ou autenticação segura de clientes no broker MQTT.
