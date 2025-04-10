const int botonPin = 2;
const int ledVerde = 3;
const int ledRojo = 4;

bool cronometroActivo = false;
unsigned long tiempoInicio = 0;
unsigned long tiempoFin = 0;

void setup() {
  pinMode(botonPin, INPUT_PULLUP);  // Pull-up interno
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  Serial.begin(9600);
  Serial.println("Presiona el botón para iniciar/detener el cronómetro.");
}

void loop() {
  static bool botonAnterior = HIGH;
  bool estadoBoton = digitalRead(botonPin);

  // Detectar flanco de bajada (presionado)
  if (estadoBoton == LOW && botonAnterior == HIGH) {
    delay(50);  // debounce
    if (digitalRead(botonPin) == LOW) {
      if (!cronometroActivo) {
        // Iniciar cronómetro
        tiempoInicio = millis();
        cronometroActivo = true;
        digitalWrite(ledRojo, LOW);  // Apagar LED rojo
        Serial.println("Cronómetro iniciado...");
      } else {
        // Detener cronómetro
        tiempoFin = millis();
        cronometroActivo = false;
        digitalWrite(ledVerde, LOW);  // Apagar LED verde
        digitalWrite(ledRojo, HIGH);  // Encender LED rojo
        unsigned long tiempoTranscurrido = tiempoFin - tiempoInicio;
        Serial.print("Cronómetro detenido. Tiempo: ");
        Serial.print(tiempoTranscurrido / 1000.0);
        Serial.println(" segundos.");
      }
    }
  }

  // LED verde parpadea durante ejecución
  if (cronometroActivo) {
    static unsigned long ultimaAlternancia = 0;
    static bool estadoLed = false;
    if (millis() - ultimaAlternancia >= 500) {
      estadoLed = !estadoLed;
      digitalWrite(ledVerde, estadoLed);
      ultimaAlternancia = millis();
    }
  }

  botonAnterior = estadoBoton;
}
