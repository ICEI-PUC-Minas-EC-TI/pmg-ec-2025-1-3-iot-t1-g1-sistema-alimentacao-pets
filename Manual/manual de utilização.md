# Manual de Utilização
Este manual descreve os passos necessários para configurar o hardware e o software do projeto "Sistema Inteligente de Alimentação e Hidratação para Pets", além de fornecer informações importantes para sua execução e teste.

## Executando o Projeto
Ligue o Hardware: Alimente o ESP32 (já com o código carregado) através da porta USB.

- Abra o Monitor Serial: Verifique na Arduino IDE se o ESP32 conectou ao Wi-Fi e ao broker MQTT com sucesso.

- Abra o Aplicativo: Conecte-se ao broker no IoT MQTT Panel.

### Teste a Comunicação:

- Hardware -> App: Pressione um dos botões na protoboard. A mensagem de alerta ("FALTA" ou "ALTA") deve aparecer no painel de texto correspondente no aplicativo.

- App -> Hardware: Pressione um dos botões de comando no aplicativo. O LED correspondente na protoboard deve acender por alguns segundos.
