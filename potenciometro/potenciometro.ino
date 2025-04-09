// Pines PWM a usar
int pinsPWM[5] = {3, 6, 9, 10, 11};

// Pin del potenciómetro
int pinPot = A0;

void setup() {
  Serial.begin(9600);

  // Configurar pines PWM como salidas
  for (int i = 0; i < 5; i++) {
    pinMode(pinsPWM[i], OUTPUT);
  }
}

void loop() {
  // Leer valor del potenciómetro (rango 0 a 1023)
  int valor = analogRead(pinPot);

  // Convertir valor a rango PWM (0 - 255)
  int pwmValor = map(valor, 0, 1023, 0, 255);

  // Escribir PWM en los pines (diferente intensidad para cada uno)
  for (int i = 0; i < 5; i++) {
    // Para variar un poco cada salida, dividimos por (i+1) para evitar división por cero
    int salidaPWM = pwmValor / (i + 1);
    analogWrite(pinsPWM[i], salidaPWM);
  }

  // Mostrar el valor del potenciómetro en el monitor serie
  Serial.print("Potenciómetro: ");
  Serial.print(valor);
  Serial.print(" => PWM base: ");
  Serial.println(pwmValor);

  delay(10); // Pequeño retardo
}}
