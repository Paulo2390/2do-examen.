const int startButton = 2; // Pin del botón iniciar/parar
const int resetButton = 3; // Pin del botón reiniciar
const int ledPin = 13;     // Pin del LED

bool running = false;       // Indica si el cronómetro está en marcha
unsigned long startTime = 0; // Tiempo de inicio
unsigned long elapsedTime = 0; // Tiempo transcurrido

void setup() {
  pinMode(startButton, INPUT_PULLUP); // Configurar botón de inicio/parada
  pinMode(resetButton, INPUT_PULLUP); // Configurar botón de reinicio
  pinMode(ledPin, OUTPUT);           // Configurar LED como salida
}

void loop() {
  // Botón para iniciar/detener el cronómetro
  if (digitalRead(startButton) == LOW) {
    delay(200); // Antirrebote
    running = !running; // Alternar estado del cronómetro
    if (running) {
      startTime = millis() - elapsedTime; // Reanudar desde el tiempo transcurrido
    } else {
      elapsedTime = millis() - startTime; // Guardar tiempo transcurrido
    }
  }

  // Botón para reiniciar
  if (digitalRead(resetButton) == LOW) {
    delay(200); // Antirrebote
    running = false;  // Detener el cronómetro
    startTime = 0;    // Reiniciar tiempo
    elapsedTime = 0;  // Borrar tiempo transcurrido
  }

  // Control del LED (parpadeo cada segundo si está corriendo)
  if (running) {
    unsigned long currentTime = millis() - startTime; // Calcular tiempo actual
    if ((currentTime / 1000) % 2 == 0) { // Parpadeo cada 1 segundo
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
  } else {
    digitalWrite(ledPin, LOW); // Apagar LED cuando no corre
  }
}