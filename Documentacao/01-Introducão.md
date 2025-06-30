# Introdução
Este documento apresenta a concepção e o desenvolvimento do projeto "Sistema Inteligente de Alimentação e Hidratação para Pets", realizado no âmbito da disciplina de Internet das Coisas (IoT). O trabalho aborda a criação de uma solução tecnológica completa para um problema cotidiano enfrentado por tutores de animais de estimação. A visão geral do projeto engloba a automação do cuidado com pets através de um dispositivo conectado que monitora e fornece alimento e água, controlado remotamente por um aplicativo. O contexto do projeto é acadêmico, visando aplicar os conceitos de hardware embarcado, comunicação em nuvem via MQTT, e persistência de dados, culminando em um protótipo funcional que valida a arquitetura proposta e atinge os objetivos de garantir o bem-estar animal e a tranquilidade de seus donos.

## Problema
Na vida moderna, muitos tutores de animais de estimação enfrentam dificuldades para garantir uma rotina de alimentação e hidratação consistente para seus pets, especialmente devido a longas jornadas de trabalho, viagens ou imprevistos. A ausência de um acompanhamento constante pode levar a problemas como superalimentação, desidratação ou o consumo de água parada e inadequada. O problema central que este projeto visa resolver é a falta de uma ferramenta acessível e eficiente que permita aos tutores cuidar de seus animais remotamente, assegurando que suas necessidades básicas sejam atendidas com precisão e regularidade. O contexto da aplicação é um ambiente doméstico, onde a solução será implementada utilizando tecnologias de baixo custo como o microcontrolador ESP32, sensores diversos, e uma plataforma de nuvem com o protocolo MQTT para comunicação em tempo real com um aplicativo mobile.

## Objetivos
O objetivo geral deste trabalho é desenvolver um sistema de Internet das Coisas (IoT) completo e funcional para automatizar e monitorar o fornecimento de alimento e água para animais de estimação, solucionando o problema da alimentação remota.

### Objetivos Específicos
Monitorar os níveis de alimento e água: Implementar sensores para verificar continuamente a quantidade de ração e água disponíveis nos recipientes, enviando os dados para a nuvem.

Automatizar o fornecimento: Desenvolver um sistema com atuadores (motores e bombas) capaz de liberar porções controladas de ração e renovar a água do bebedouro, tanto de forma programada quanto sob demanda via aplicativo.

Garantir o controle remoto e alertas: Criar uma interface em um aplicativo mobile que permita ao tutor visualizar o status dos recipientes, acionar os atuadores manualmente e receber notificações de alerta em situações críticas (ex: reservatório de ração vazio).

## Público-Alvo
O público-alvo deste projeto são tutores de animais de estimação (principalmente cães e gatos) que possuem uma rotina diária atarefada, viajam com frequência ou simplesmente desejam ter um controle maior e mais tecnológico sobre o bem-estar de seus pets. Este perfil de usuário geralmente possui familiaridade com o uso de smartphones e aplicativos, valoriza a praticidade que a tecnologia pode oferecer e está disposto a investir em soluções que garantam a saúde e a segurança de seus animais de companhia. Não é exigido conhecimento técnico prévio, pois a interação com o sistema se dará de forma intuitiva através da interface do aplicativo mobile.
