#include <IRremote.h> // arduino-cli lib install "IRremote"
#include "IRButton.h"
#include "IRController.h" // arduino-cli lib install "IRremote"

// Configuração dos botões
const int firstButtonPin = 4;
const int numberOfButtons = 1;
IRButton* buttons[numberOfButtons];

// Instancia o controlador IR no pino 2 (receptor IR)
IRController irController(2);

// Variáveis de controle
unsigned long lastIRCode = 0; // Código IR gravado
bool recordingMode = false;    // Flag para modo de gravação
unsigned long lastButtonPressTime = 0;
int buttonPressCount = 0;

// LEDs conectados aos pinos
int blueLED = 13; // LED azul (modo de gravação)
int greenLED = 12; // LED verde (disparo do código)

void setup() {
  Serial.begin(9600);
  irController.begin();

  // Inicializa cada botão
  for (int i = 0; i < numberOfButtons; i++) {
    int pin = firstButtonPin + i;
    long code = 0x18E758A7; // Código IR para o botão 0
    buttons[i] = new IRButton(pin, code);
    buttons[i]->begin();
  }

  // Inicializa os LEDs
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  digitalWrite(blueLED, LOW);  // Desliga o LED azul inicialmente
  digitalWrite(greenLED, LOW); // Desliga o LED verde inicialmente
}

void loop() {
  // Atualiza o estado de cada botão
  for (int i = 0; i < numberOfButtons; i++) {
    buttons[i]->update();
  }

  // Verifica se o botão foi pressionado para iniciar o modo de gravação
  checkButtonForRecording();

  // Verifica se há sinais IR recebidos e processa o código
  if (irController.checkReceiver()) {
    unsigned long receivedCode = irController.getReceivedCode();
    if (recordingMode) {
      // Salva o último código IR quando no modo de gravação
      lastIRCode = receivedCode;
      Serial.print("Código IR salvo: ");
      Serial.println(lastIRCode, HEX);
      digitalWrite(blueLED, LOW); // Desliga o LED azul após 2 segundos
      recordingMode = false; // Finaliza o modo de gravação
    }
  }

  // Verifica os cliques do botão para disparar o código salvo
  if (buttonPressCount == 3) {
    triggerIRCode();
    buttonPressCount = 0; // Reseta a contagem de cliques
  }

  delay(100); // Delay para não sobrecarregar o processador
}

/**
 * Função que verifica o estado do botão para iniciar o modo de gravação.
 */
void checkButtonForRecording() {
  static boolean lastButtonState = HIGH;
  boolean currentButtonState = digitalRead(firstButtonPin); // Lê o estado do botão

  // Verifica se o botão foi pressionado e mantido
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    lastButtonPressTime = millis();
    buttonPressCount++; // Conta a quantidade de cliques
  }

  // Verifica se o botão foi pressionado e mantido por mais de 1 segundo para iniciar o modo de gravação
  if (buttonPressCount == 1 && (millis() - lastButtonPressTime > 1000)) {
    Serial.println("Iniciando modo de gravação...");
    recordingMode = true;
    digitalWrite(blueLED, HIGH); // Acende o LED azul para indicar o modo de gravação
  }

  // Verifica se o botão foi pressionado 3 vezes em sequência para disparar o código salvo
  if (millis() - lastButtonPressTime > 3000) {
    buttonPressCount = 0; // Reseta a contagem se o botão não for pressionado rapidamente
  }

  lastButtonState = currentButtonState;
}

/**
 * Função que dispara o código IR salvo.
 */
void triggerIRCode() {
  if (lastIRCode != 0) {
    Serial.print("Disparando código IR salvo: ");
    Serial.println(lastIRCode, HEX);
    irsend.sendSony(lastIRCode, 32);  // Envia o código IR salvo

    // Acende o LED verde para indicar que o código foi disparado
    digitalWrite(greenLED, HIGH);
    delay(500); // O LED verde fica aceso por 500ms
    digitalWrite(greenLED, LOW); // Desliga o LED verde após 500ms
  } else {
    Serial.println("Nenhum código IR salvo.");
  }
}
