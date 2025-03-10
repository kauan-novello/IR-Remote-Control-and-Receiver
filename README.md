# IR-Remote-Control-and-Receiver

# Projeto de Controle Remoto Infra Vermelho no Arduino

Este projeto permite que você envie e receba sinais IR utilizando um Arduino. 
Ele utiliza a biblioteca **IRremote** para capturar e transmitir sinais IR, 
permitindo tanto enviar comandos de um controle remoto quanto escutar sinais IR para visualização no monitor serial.

## Componentes

- 1x Arduino Uno (ou outra placa compatível)
- 1x Receptor IR KY-022 (ou similar)
- 1x Transmissor IR LED
- 1 ou mais botões físicos
- Fios de conexão

## Esquema de Conexão

- **Pino do receptor IR**: Conecte o pino de sinal do receptor IR (KY-022) ao pino digital 2 do Arduino.
- **Pinos dos botões**: Conecte os botões físicos aos pinos digitais do Arduino (4, 5, 6, etc.).
- **Transmissor IR**: Conecte o transmissor IR ao pino 3 do Arduino (se estiver utilizando um LED IR).
