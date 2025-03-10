#include <IRremote.h>  // Biblioteca para controle remoto IR

// Definindo parâmetros principais
const int numberOfKeys = 1;  // Número de botões conectados
const int firstKey = 4;  // Pino digital inicial onde os botões começam a ser conectados

// Arrays para armazenar os estados dos botões
boolean buttonState[numberOfKeys];  
boolean lastButtonState[numberOfKeys];  

// Códigos IR para enviar ao pressionar o botão
long irKeyCodes[numberOfKeys] = {
  0x18E758A7,  // Código IR para o botão 0 (Sony)
};

// Inicializa o transmissor IR
IRsend irsend;

// Pino de recepção IR
const int RECV_PIN = 2;  // Pino digital utilizado pelo fotodetector KY-022 (receptor IR)
IRrecv irrecv(RECV_PIN);  // Cria um objeto para o receptor IR
decode_results results;  // Variável que armazena o resultado do sinal IR recebido

void setup() {
  // Inicia a comunicação serial para depuração
  Serial.begin(9600);  
  
  // Ativa a recepção do sinal IR
  irrecv.enableIRIn();  

  // Configura os pinos para os botões (usando pinos 4 a 4+numberOfKeys-1)
  for (int i = 0; i < numberOfKeys; i++) {
    int physicalPin = i + firstKey;  // Pino físico para o botão
    pinMode(physicalPin, INPUT_PULLUP);  // Configura o pino como entrada com pull-up interno ativado
  }
}

void loop() {
  // Verifica o estado de cada botão e envia o código IR se o botão for pressionado
  for (int keyNumber = 0; keyNumber < numberOfKeys; keyNumber++) {
    int physicalPinToRead = keyNumber + firstKey;  // Pino físico para o botão
    buttonState[keyNumber] = digitalRead(physicalPinToRead);  // Lê o estado atual do botão
    
    // Se o estado do botão mudou (de HIGH para LOW ou vice-versa)
    if (buttonState[keyNumber] != lastButtonState[keyNumber]) {
      // Se o botão foi pressionado (estado LOW)
      if (buttonState[keyNumber] == LOW) {
        irsend.sendSony(irKeyCodes[keyNumber], 32);  // Envia o código IR correspondente ao botão pressionado
        Serial.println("Sending IR code...");  // Exibe mensagem no monitor serial
      }
      // Atualiza o estado anterior do botão
      lastButtonState[keyNumber] = buttonState[keyNumber];
    }
  }

  // Verifica se há um sinal IR recebido e exibe no monitor serial
  if (irrecv.decode(&results)) {
    // Exibe o código IR recebido em formato hexadecimal
    Serial.print("Código HEX: ");  
    Serial.println(results.value, HEX);  
    
    // Exibe o código IR recebido em formato decimal
    Serial.print("Código DEC: ");
    Serial.println(results.value);  
    
    // Aguarda o próximo sinal IR
    irrecv.resume();  // Prepara o receptor para o próximo sinal
  }

  // Adiciona um pequeno delay para evitar sobrecarga no loop
  delay(100);  
}
